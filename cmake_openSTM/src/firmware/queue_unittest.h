#ifndef __INCLUDE_QUEUE_UNITTEST_H
#define __INCLUDE_QUEUE_UNITTEST_H

#ifdef __cplusplus
#define EXTERN extern "C"
extern "C" {
#else
#define EXTERN extern
#endif

#include <queue.h>
#define ssize_t uint32_t 

typedef enum {
  DM_KEY_SAFE_POINTS = 0,   /* Safe points coordinates, safe point 0 is home point */
  DM_KEY_FENCE_POINTS,    /* Fence vertex coordinates */
  DM_KEY_WAYPOINTS_OFFBOARD_0,  /* Mission way point coordinates sent over mavlink */
  DM_KEY_WAYPOINTS_OFFBOARD_1,  /* (alernate between 0 and 1) */
  DM_KEY_WAYPOINTS_OFFBOARD_2,  /* (new offboard) */
  DM_KEY_WAYPOINTS_OFFBOARD_3,  /* (new offboard) */
  DM_KEY_WAYPOINTS_ONBOARD, /* Mission way point coordinates generated onboard */
  DM_KEY_MISSION_STATE,   /* Persistent mission state */
  DM_KEY_NUM_KEYS     /* Total number of item types defined */
} dm_item_t;

typedef struct {
  sq_queue_t q;   /* Nuttx queue */
  unsigned size;    /* Current size of queue */
  unsigned max_size;  /* Maximum queue size reached */
} work_q_t;


typedef struct {
  sq_entry_t link;  /**< list linkage */
  unsigned char first;
  unsigned char func;
  ssize_t result;
  //union {
    struct {
      dm_item_t item;
      unsigned char index;
      void *buf;
      size_t count;
    } read_params;
  //};
} work_q_item_t;

void queue_work_test(void); 

#undef EXTERN
#ifdef __cplusplus
}
#endif

#endif /* __INCLUDE_QUEUE_UNITTEST_H */

