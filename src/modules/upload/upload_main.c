#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
// #include "./include/px4_getopt.h"
#include "./include/firmware_send.h"

extern void calc_crc_unittest(void);

bool task_exit = false;

extern int px4_getopt(int argc, char *argv[], const char *options, int *myoptind, const char **myoptarg);

void usage(void)
{
    printf("usage: ./main [--update <port>  <path> [--help]\r\n");
    printf("eg: ./main update /dev/ttyUSB0 *.bin\r\n");
}
#include "wolz_packet.h"
extern void wolz_unittest(command_code_t code);

struct struct_a_dump{
    int d;
    int e;
};

struct struct_a_dump a_dump;

const struct struct_a{
    struct struct_a_dump *a;
    int b;
    int c;
};

const struct struct_a a ={
    .a = &a_dump,
};

void test_struct_a(void)
{    

    const struct struct_a *p = &a;
    
    p->a->d = 1;

    //编译是不过的
    // p->b = 1;

    printf("d:%d\r\n",  p->a->d);
}


void test_str(char *str) 
{
    int a = 1; 
    int b = 2;
    sprintf(str, "%d*%d", a, b);
}

extern cmd_test();

    
// /*
// *   抽象类parent_class用来向用户提供统一的接口，如读/写，复位，初始化等等。
// *   child1_class类比于串口
// *   child2_class类比于SD卡
// */
// #include <stdlib.h>
// #include <assert.h>

// /*抽象父类*/
// struct parent_calss
// {
//     int a;
//     void (*vfunc)(void *, int a);
// };

// /*抽象类的方法调用，永远不会被调用*/
// void parent_class_vfunc(struct parent_calss *parent_self_ptr, int a)
// {
//     assert(parent_self_ptr != NULL);
//     assert(parent_self_ptr->vfunc != NULL);
//     /*调用对象本身的虚拟函数*/
//     parent_self_ptr->vfunc(parent_self_ptr, a);
// }

// /*继承自parent_class的子类child1_class*/
// struct child1_class
// {
//     struct parent_calss parent;
//     int b;
// };
// /*子类虚函数的实现*/
// static void child1_class_vfunc(struct child1_class *child1_self_ptr, int a)
// {
//     child1_self_ptr->b = a + 10;
//     printf("child1_self_ptr->b:%d\r\n", child1_self_ptr->b);
// }

// /*子类的构造函数*/
// void child1_class_init(struct child1_class *child1_self_ptr)
// {
//     struct parent_calss *parent;
//     /*强制类型转换获得子类中的父类指针*/
//     parent = (struct parent_calss *)child1_self_ptr;
//     assert(parent != NULL);
//     /*设置子类的虚函数*/
//     parent->vfunc = child1_class_vfunc;
// }


// /*继承自parent_class的子类child2_class*/
// struct child2_class
// {
//     struct parent_calss parent;
//     int b;
// };
// /*子类虚函数的实现*/
// static void child2_class_vfunc(struct child2_class *child2_self_ptr, int a)
// {
//     child2_self_ptr->b = a * 10;
//      printf("child1_self_ptr->b:%d\r\n", child1_self_ptr->b);
// }

// /*子类的构造函数*/
// void child2_class_init(struct child2_class *child2_self_ptr)
// {
//     struct parent_calss *parent;
//     /*强制类型转换获得子类中的父类指针*/
//     parent = (struct parent_calss *)child2_self_ptr;
//     assert(parent != NULL);
//     /*设置子类的虚函数*/
//     parent->vfunc = child2_class_vfunc;
// }

// int test_main(void)
// {
//     struct child1_class child1, *child1_ptr;
//     struct child2_class child2, *child2_ptr;
//     struct parent_calss *parent_ptr;
    
//     /*child1_class类比于串口的结构体*/
//     child1_ptr = &child1;
//     parent_ptr = (struct parent_calss *)child1_ptr;
//     child1_ptr->b = 10;
//     child1_class_init(child1_ptr);
//     parent_ptr->vfunc(child1_ptr, 20);
    
//     /*child2_class类比于SD卡的结构体*/
//     child2_ptr = &child2;
//     parent_ptr = (struct parent_calss *)child2_ptr;
//     child2_ptr->b = 20;
//     child2_class_init(child2_ptr);
//     parent_ptr->vfunc(child2_ptr, 20);
    
//     getchar();
//     return 0;
// }

enum Rotation {
    ROTATION_NONE                = 0,
    ROTATION_YAW_45              = 1,
    ROTATION_YAW_90              = 2,
    ROTATION_YAW_135             = 3,
    ROTATION_YAW_180             = 4,
    ROTATION_YAW_225             = 5,
    ROTATION_YAW_270             = 6,
    ROTATION_YAW_315             = 7,
    ROTATION_ROLL_180            = 8,
    ROTATION_ROLL_180_YAW_45     = 9,
    ROTATION_ROLL_180_YAW_90     = 10,
    ROTATION_ROLL_180_YAW_135    = 11,
    ROTATION_PITCH_180           = 12,
    ROTATION_ROLL_180_YAW_225    = 13,
    ROTATION_ROLL_180_YAW_270    = 14,
    ROTATION_ROLL_180_YAW_315    = 15,
    ROTATION_ROLL_90             = 16,
    ROTATION_ROLL_90_YAW_45      = 17,
    ROTATION_ROLL_90_YAW_90      = 18,
    ROTATION_ROLL_90_YAW_135     = 19,
    ROTATION_ROLL_270            = 20,
    ROTATION_ROLL_270_YAW_45     = 21,
    ROTATION_ROLL_270_YAW_90     = 22,
    ROTATION_ROLL_270_YAW_135    = 23,
    ROTATION_PITCH_90            = 24,
    ROTATION_PITCH_270           = 25,
    ROTATION_ROLL_270_YAW_270    = 26,
    ROTATION_ROLL_180_PITCH_270  = 27,
    ROTATION_PITCH_90_YAW_180    = 28,
    ROTATION_MAX
};

int gyrosim_main(int argc, char *argv[])
{
    int ch;
    enum Rotation rotation = ROTATION_NONE;
    int ret;

    /* jump over start/off/etc and look at options first */
    int myoptind = 1;
    const char *myoptarg = NULL;

    while ((ch = px4_getopt(argc, argv, "R:", &myoptind, &myoptarg)) != EOF) {
        switch (ch) {
        case 'R':
            rotation = (enum Rotation)atoi(myoptarg);
            break;

        default:
            // gyrosim::usage();
            return 0;
        }
    }
    
    return 0;
}

//注意: uint16_t calc_crc(const uint8_t *buf, const uint32_t len) 这个crc编码有2个同样的函数

int upload_main(int argc, char **argv)
{   
    // test_main();
     // cmd_test();
     // return -1;

    printf("123456\t12345678123456\t1234567\r\n");

    if (argc < 2) {
        return -1;
    }
    
    if (!strcmp(argv[1], "update")) {
        if (argc < 4) {
            usage();
            return -1;
        }
        char *port = argv[2];
        char *path = argv[3];
        if(update_firmware(path, port) == 0) {
            while(!task_exit) {
                sleep(2); 
            }
        }
    }

    if (!strcmp(argv[1], "test_const")) {
        test_struct_a();
        return 0;
    }




    if (!strcmp(argv[1], "test_str")) {

        char buf[20]; 

        memset(buf, 0x00, 20);
        test_str(buf);
        printf(buf);

        return 0;
    }
 

    if (!strcmp(argv[1], "crctest")) {
         calc_crc_unittest();
         return 0;
    }

    if (!strcmp(argv[1], "hardtest")) {
        if (argc >= 3) {
            char *port = argv[2];
            wolz_test(port);
        }
    }

    if (!strcmp(argv[1], "softtest")) {
        wolz_unittest(ACTURATOR_COMMAND_SET);
    }
    
    if (!strcmp(argv[1], "help")) {
         usage();
    }

    return 0;
}


