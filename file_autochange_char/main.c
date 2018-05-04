#include <stdio.h>
#include <string.h>
#include <stdint.h>
/* 修改源文件存放位置 */
#define PATH "tmp.txt"
#define PATH_TMP "tmp_dest.txt"

uint8_t buf[512];

struct uart_buffer_s {
    int head;
    int tail;
    uint8_t *buffer;
    int size;
};

struct uart_buffer_s recv1 = {
    .buffer = buf,
    .size = 512,
};

int ringbuffer_count(struct uart_buffer_s *lb)
{
	int n = lb->head - lb->tail;

	if (n < 0) {
		n += lb->size;
	}

	return n;
}

void uart_rx_ringbuffer_push_from_usart(struct uart_buffer_s *recv, uint8_t *u_data)
{
	recv->buffer[recv->head] = *u_data;
	recv->head = (recv->head + 1) % recv->size;
}

int uart_rx_ringbuffer_pop (struct uart_buffer_s *recv,  uint8_t *data)
{
	*data = recv->buffer[recv->tail];
	recv->tail = (recv->tail + 1) % recv->size;
	return 0;
}
uint8_t _index = 0;
uint8_t _find_str_len = 0;
uint8_t _find_dup_buf[10];


/* 1. 对于匹配比较特殊的字符串可能存在问题，如1221
 * 2. 未处理iCount值大于9的情况
 * 3. 为对产生的临时文件进行处理
 * 4. 未对入参进、函数返回值行判断
 * 5. 未处理最后一次读出的最后4个字节
 *  read end;
 * */
int file_change_char(char *path, char *find_str)
{
    FILE *stream = NULL;
    FILE *pfTmp = NULL;
    char acStr[128] = {0};
    char acStr2[128] = {0};
    char cIndex = 0;
    char cMove = 0;
    char cfind_len = strlen(find_str);
    int iCount = 0;
   
    memset(_find_dup_buf, 0x00, 10);
    _find_str_len  = strlen(find_str);
    strcpy(_find_dup_buf, find_str);
    sprintf(_find_dup_buf, "%s%d", _find_dup_buf, _index);

    printf(_find_dup_buf);
    printf("len=%d", _find_str_len);

    stream = fopen(path, "r+");
    if (stream ==NULL) {
        printf("src file no exsit\r\n");
    }
    pfTmp  = fopen(PATH_TMP, "w+");
    if (pfTmp ==NULL) {
        printf("src file no exsit\r\n");
    }
     
    do {
        memset (acStr, 0x00, sizeof(acStr));
        int ret = fread(acStr, 128, 1, stream);

        //fprintf(stdout, acStr);
        int len = strlen(acStr);

        //找到子串. 替换子川
        char *str;
        str = strstr(acStr, find_str) ;
        if (str != NULL) {
            printf(str);
            printf("find");
        }

        //计算子串的长度
        // int len1 = str - acStr;
        // printf("len:%d\r\n", len1);

        //更改内容
        _index++;
        sprintf(_find_dup_buf, "%s%d", _find_dup_buf, _index);
        strncpy(str, _find_dup_buf, _find_str_len);
        //printf(acStr);

        if (!ret) {
            fprintf(stdout, "exit\r\n");
            break;
        }
 
    } while(1);

   

    // 
    // fseek(pfTmp, 0, SEEK_SET);
    // /* 读取临时文件中内容 
    //  * 第一次读取，从acStr的0元素开始存放读出内容
    //  * 之后每次从acStr的第4个元素读取
    //  * 将内容写入源文件时，最后四个字节不写入，放置到下次读取的内容的最前4个字节
    //  * */
    // while(0 < fread(acStr+cMove, sizeof(acStr)-cMove, 1, pfTmp))
    // {
    //     test_proc(2, acStr, 128);
    //     while(125 > cIndex) 
    //     {
    //         /* 临时文件中的内容匹配abc0 */
    //         strncpy(acStr, acStr2+(sizeof(acStr2)-cMove), cMove);
    //         if(0 == strncmp(acStr+cIndex, find_str, strlen(find_str)))
    //         {
    //             acStr[cIndex+3] = '0' + iCount%10;              // 未考虑iCount大于9的情况
    //             iCount++;
    //             cIndex += 4;
    //         }
    //         else
    //         {
    //             cIndex++;
    //         }
    //     }
        
    //     test_proc(3, acStr, 128-cfind_len);
    //     /* 将修改后的内容写会到源文件 */
    //     if(0 > fwrite(acStr, sizeof(acStr)-cfind_len, 1, stream))
    //     {
    //         printf("%s:%d fwrite failed.", __FUNCTION__, __LINE__);
    //         return -1;
    //     }

    //     strncpy(acStr2, acStr, sizeof(acStr));
    //     memset(acStr, 0, sizeof(acStr));
    //     cMove = cfind_len;
    //     cIndex = 0;
    // }

    fclose(pfTmp);
    fclose(stream);

    return 0;
}



void main(void)
{
    file_change_char(PATH, "abc0");
    return;
}
