#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "queue_unittest.h"

#define k_work_item_allocation_chunk_size  8
work_q_item_t* p[5];
work_q_item_t work_array[k_work_item_allocation_chunk_size];
work_q_t g_free_q;	/* queue of free work items. So that we don't always need to call malloc and free*/
work_q_t g_work_q;	/* pending work items. To be consumed by worker thread */

static void init_q(work_q_t *q)
{
	sq_init(&(q->q));		/* Initialize the NuttX queue structure */
	q->size = q->max_size = 0;	/* Queue is initially empty */
}

work_q_item_t* create_work_item(void)
{
	work_q_item_t *item;

	/* Try to reuse item from free item queue */
	//lock_queue(&g_free_q);

	if ((item = (work_q_item_t *)sq_remfirst(&(g_free_q.q)))) {
		g_free_q.size--;
		printf("create work item: g_free_q.size:%d\r\n", g_free_q.size);
	} else {
		// printf("first");
	}
  
	//unlock_queue(&g_free_q);

	/* If we there weren't any free items then obtain memory for a new ones */
	if (item == NULL) {
		item = work_array;
		// printf("item:%x", (int)item);
		if (item) {
			// printf("create mem ok");
			item->first = 1;
			//lock_queue(&g_free_q);

			for (size_t i = 1; i < k_work_item_allocation_chunk_size; i++) {
				(item + i)->first = 0;
				sq_addfirst(&(item + i)->link, &(g_free_q.q));
			}

			/* Update the queue size and potentially the maximum queue size */
			g_free_q.size += k_work_item_allocation_chunk_size - 1;
            //printf("g_free_q.size:%d", g_free_q.size);
			if (g_free_q.size > g_free_q.max_size) {
				g_free_q.max_size = g_free_q.size;
			}

			//unlock_queue(&g_free_q);
		}
		printf("create work item: g_free_q.size:%d\r\n", g_free_q.size);
	}

//	/* If we got one then lock the item*/
//	if (item) {
//		px4_sem_init(&item->wait_sem, 1, 0);        /* Caller will wait on this... initially locked */
//	}

	/* return the item pointer, or NULL if all failed */
	return item;
}

void destroy_work_item(work_q_item_t *item)
{
	sq_addfirst(&item->link, &(g_free_q.q));

	/* Update the queue size and potentially the maximum queue size */
	if (++g_free_q.size > g_free_q.max_size) {
		g_free_q.max_size = g_free_q.size;
	}
	printf("free work item: g_free_q.size:%d\r\n", g_free_q.size);
}

//delete
static inline work_q_item_t *
dequeue_work_item(void)
{
	work_q_item_t *work;

	/* retrieve the 1st item on the work queue */

	if ((work = (work_q_item_t *)sq_remfirst(&g_work_q.q))) {
		g_work_q.size--;
	}

	return work;
}

//add 
static int
enqueue_work_item_and_wait_for_result(work_q_item_t *item)
{
	/* put the work item at the end of the work queue */

	sq_addlast(&item->link, &(g_work_q.q));

	/* Adjust the queue size and potentially the maximum queue size */
	if (++g_work_q.size > g_work_q.max_size) {
		g_work_q.max_size = g_work_q.size;
	}
}

int queue_unittest_main(int argc, char **argv)
{
	p[0] = create_work_item();
	enqueue_work_item_and_wait_for_result(p[0]);
	p[1] = create_work_item();
	enqueue_work_item_and_wait_for_result(p[1]);
	p[2] = create_work_item();
	enqueue_work_item_and_wait_for_result(p[2]);
	
	dequeue_work_item();
	destroy_work_item(p[0]);
	dequeue_work_item();
	destroy_work_item(p[1]);
	dequeue_work_item();
	destroy_work_item(p[2]);

	return 0;
}