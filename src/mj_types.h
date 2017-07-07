#ifndef _MJ_TYPES_H_
#define _MJ_TYPES_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Common unsigned types */

#ifndef DEFINED_U8
#define DEFINED_U8
typedef unsigned char  U8;
#endif

#ifndef DEFINED_U16
#define DEFINED_U16
typedef unsigned short U16;
#endif

#ifndef DEFINED_U32
#define DEFINED_U32
typedef unsigned int   U32;
#endif


typedef struct _MjCard
{
	U8       index;      /* ID:     1~108*/
	U8       value;      /* Val:    1~9 */
	U8       type;       /* Type:  ����Ͳ */
	U8       priority;   /* �������ȼ� (���ڵ���)*/
	char     name[6]; /* �Ƶ�����; 1��3Ͳ2�� */
	void   *bmp;       /* ��Ӧ��ͼƬ */
}MjCard_t;

typedef enum _GameResult
{
	GAME_RUNNING = 4,
	GAME_EXIT,
	GAME_OVER
}GameResult;




#endif /* _MJ_TYPES_H_ */

