/*******************************************************************************
    Copyright (C), 2004-2007, YOUNGSUN. Co., Ltd.

    File name : Majiang

    Description :

    Others:

    History:      1. ychen creat 2014-12-01


*******************************************************************************/

/*----------------------------------------------------------------------------
 *	Include
 *----------------------------------------------------------------------------*/
#include "midware.h"
#include "digitv.h"

#include "majiang.h"
#include "engine.h"

/*----------------------------------------------------------------------------
 *	Define
 *----------------------------------------------------------------------------*/

 /*----------------------------------------------------------------------------
 *	Debug
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *	External Function Prototype
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *	External variable
 *----------------------------------------------------------------------------*/
extern unsigned char g_language;

/*----------------------------------------------------------------------------
 *	Struct
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *	Private Constant & Enum & Macro
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *	Private Module Variable
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *	Private Function Prototype
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *	Global variable
 *----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * statics
 *----------------------------------------------------------------------------*/

static char *pMajiang_str[] = 
{
    "[LIST_START]",
    "1[/]",

    //"[TEXTLABEL]",
    //"1[/]1[/]1[/]150,239,383,180[/]130[/]6[/]30[/]2[/]标签[/]TextLabel[/]1;4294967295,182,12,20,0,0;[/]0[/]1;4294967295,aaa;[/]1;4294967295,0,0,1,2;[/]1;4294967295,134217737,0,0,0;[/]0,3,14,2[/]0,10,10,2[/]0,11,11,1[/]13[/]",
    //"[TEXTCHOICE]",
    //"2[/]1[/]1[/]150,389,532,180[/]130[/]0[/]30[/]1[/][/]2;4,227,253,20,0,0;4294967295,182,12,20,0,0;[/]0[/]2;4294967295,aaa;4294967295,bbb;[/]2;4294967295,0,0,227,133;4294967295,2,0,9,2;[/]1;4294967295,134217737,0,0,0;[/]1,3,8,2[/]3,10,10,2[/]3,11,11,1[/]100[/]26[/]",

    "[LIST_END]",

    "[APP_END]"
};

/*----------------------------------------------------------------------------
*	Function
*----------------------------------------------------------------------------*/

/*****************************************************************************
  Date&Time    :    2014-12-01
  Author          :    ychen
  Function Name   : Majiang_SetBmpName
  Description     :
  Input           :
  Outut           :
  Calls           :
  Called by       :
  Global Variables:
  Others          :
*****************************************************************************/
static void *Majiang_SetBmpName(char *BmpName)
{
	#if 0
    extern STOSD_Bitmap_t Majiang_xxx1_struct;
    extern STOSD_Bitmap_t Majiang_xxx2_struct;
    extern STOSD_Bitmap_t Majiang_xxx3_struct;

    if(!(strcmp(BmpName,"name1")) )
        return (void*)&Majiang_xxx1_struct;
    else if(!(strcmp(BmpName,"name2")) )
        return (void*)&Majiang_xxx2_struct;
    else if(!(strcmp(BmpName,"name3")) )
        return (void*)&Majiang_xxx3_struct;

	#endif
    return NULL;
}

/*****************************************************************************
  Date&Time    :    2014-12-01
  Author          :    ychen
  Function Name   : Majiang_Task
  Description     :
  Input           :
  Outut           :
  Calls           :
  Called by       :
  Global Variables:
  Others          :
*****************************************************************************/
static void Majiang_Task(void *Param)
{
	APP_AppInfo_t        *pMajiangAppInfo   = ( APP_AppInfo_t*)Param;
	AppGui_t             *pMajiangAppGui    = NULL;
	DRVOS_Partition_t    *MemPart      = NULL;
	DRVOS_MsgQueue_t     *MsgQueue     = NULL;
	ControlList_t        *pCurrentList = NULL;
	ControlList_t        *pListTemp    = NULL;
	ControlItem_t        *pItemTemp    = NULL;
	BOOL                  bRun         = TRUE;
	U32                   nResult      = 0;

	MSG_MsgInfo_t         msgGetMsg;
	MSG_MsgInfo_t         msgSendMsg;
	MSG_MsgInfo_t        *pGetMsg      = &msgGetMsg;
	MSG_MsgInfo_t        *pSendMsg     = &msgSendMsg;


	if (NULL == pMajiangAppInfo)
	{
		Err_Print("Majiang Task Create Failed Because Input Para Is Error!\n");
		APP_OnExit_cpp(pMajiangAppInfo);
		DRV_OSTaskExit((int)pMajiangAppInfo);
		return;
	}

	MsgQueue = pMajiangAppInfo->MsgQueue;
	MemPart = pMajiangAppInfo->Part;
	if((MemPart == NULL)||(MsgQueue == NULL))
	{
		Err_Print("Majiang Task Create Failed Because Input Msg/Ptn Is NULL!\n");
		APP_OnExit_cpp(pMajiangAppInfo);
		DRV_OSTaskExit((int)pMajiangAppInfo);
		return;
	}

	pMajiangAppGui=AppGuiInit_cpp( pMajiang_str,MemPart);
	if(pMajiangAppGui == NULL)
	{
		Err_Print("Majiang Task Create Failed Because AppGui Init Failed!\n");
		APP_OnExit_cpp(pMajiangAppInfo);
		DRV_OSTaskExit((int)pMajiangAppInfo);
		return;
	}
	
	DTV_SendSUSPENDMsg2DTV_cpp();
	APPREG_AppRegionShow_cpp(NULL);
	GUI_BmpNameSet_cpp(Majiang_SetBmpName);
	MidDrawCls(BMP_TRANSPARENCE_COLOR);

	MJ_Engine *pMajiang;
	pMajiang = new MJ_Engine(MemPart);
	pMajiang->Init();
	//pMajiang->GameStart();
	
	ControlListDraw_cpp(pMajiangAppGui->pControlList, ORIGINAL_SHOW);
	DRV_OSDUpdate();

	while(bRun)
	{
		DRV_LOW_POWER_TASK_CHECK;
	        MSG_MsgReset_cpp(pGetMsg);
	        MSG_MsgReset_cpp(pSendMsg);
	        nResult = MSG_GetMsg_Wait_cpp(MsgQueue, pGetMsg);
		if(nResult==SUCCESS)//get system message successfully
		{
			switch(pGetMsg->Class)
			{
				case MSG_CLASS_KEY:
				{

					switch(pGetMsg->MsgCode)
					{
						case ID_EXIT:
							bRun = false;
							break;
						case ID_OK:
							pMajiang->KeyProcess(pGetMsg->MsgCode);
							break;
						default:
							break;
					}
					break;
					pGetMsg->Class = (MSG_MsgClass_e)pGetMsg->MsgCode;
					if(ControlListProcess(pMajiangAppGui->pControlList, (MessageInfo_t*)pGetMsg, (MessageInfo_t*)pSendMsg))
					{
						if(pSendMsg->Class != NULL_MSG)
						{
							MSG_SendMsgMngMsg(pSendMsg);
						}
						break;
					}
				}
				break;

				default:
				break;
			}
			DRV_OSDUpdate();
		}
	}

	AppGuiDestroy_cpp(pMajiangAppGui);
	APP_OnExit_cpp(pMajiangAppInfo);
	DRV_OSTaskExit((int)pMajiangAppInfo);

}
/*****************************************************************************
  Date&Time    :    2014-12-01
  Author          :    ychen
  Function Name   : Majiang_Init
  Description     :
  Input           :
  Outut           :
  Calls           :
  Called by       :
  Global Variables:
  Others          :
*****************************************************************************/
int Majiang_Init(APP_AppInfo_t *pGameMajing, void *Param)
{
	int Result;

	Result = APP_TaskInit_cpp(( void*)Majiang_Task,
	                        APP_NORMAL_PRIORITY,
	                        USER_WS_SIZE*16, 
	                        NORMAL_PART_SIZE,
	                        NORMAL_MSG_SIZE,
	                        NORMAL_MAX_MSGS,
	                        0,
	                        pGameMajing);

	if (FALSE_YS== Result)
	{
		Err_Print("Majiang_Init error!\n");
	}

	return Result;
}


