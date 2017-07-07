#ifndef _MAJIANG_H_
#define _MAJIANG_H_

/* C++ support */
/* ----------- */
#ifdef __cplusplus
extern "C" {
#endif

extern AppGui_t *AppGuiInit_cpp(char**, partition_s*);
extern void DTV_SendSUSPENDMsg2DTV_cpp();
extern void APPREG_AppRegionShow_cpp(void*);
extern void GUI_BmpNameSet_cpp(void* (*)(char*));
extern void ControlListDraw_cpp(ControlList*, int);
extern int MSG_MsgReset_cpp(MSG_MsgInfo_t*);
extern int MSG_GetMsg_Wait_cpp(DRVOS_MsgQueue_s*, MSG_MsgInfo_t*);
extern HRESULT AppGuiDestroy_cpp(AppGui*);
extern void APP_OnExit_cpp(APP_AppInfo_t *AppInfo);
extern int APP_TaskInit_cpp(void*, int, int, int, int, unsigned int, int, APP_AppInfo*);
extern bool ControlListProcess_cpp(ControlList_t * pList, MessageInfo_t *pMsgIn, MessageInfo_t *pMsgOut);
extern void MSG_SendMsgMngMsg_cpp(MSG_MsgInfo_t *Msg);
extern void *DRV_OSMalloc(DRVOS_Partition_p Partition_p, size_t Size);
extern void DRV_OS_TaskDelay_MS(unsigned int Delay);

int Majiang_Init(APP_AppInfo_t *pGameMajing, void *Param);
void drawbmp(S32 x,S32 y, void *graphic);


/* ----------- */
#ifdef __cplusplus
}
#endif

#endif /* _MAJIANG_H_ */

