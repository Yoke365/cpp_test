#ifndef _Ｃ_POINT_FUN_H
#define _Ｃ_POINT_FUN_H

#include <stdint.h>

#define  APP_KEY_STR_LEN_MAX      32
#define  APP_SECRET_STR_LEN_MAX   128
#define  DEVICE_ID_STR_LEN_MAX    32
#define  DEVICE_TYPE_STR_LEN_MAX  32

typedef struct {
	char appkey[APP_KEY_STR_LEN_MAX];
	char appsecret[APP_SECRET_STR_LEN_MAX];
	char device_ID[DEVICE_ID_STR_LEN_MAX];
	char device_Type[DEVICE_TYPE_STR_LEN_MAX];
} acount_info_t;

#endif /* _Ｃ_POINT_FUN_H */
