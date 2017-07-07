#ifndef _ENGINE_H_
#define _ENGINE_H_

#include "mj_marco.h"
#include "mj_types.h"

#include "gamer.h"
#include "player.h"
#include "computer.h"
#include "mahjong.h"
#include "painter.h"
#include "judge.h"
#include "majiang.h"

#define GAME_RUNNING           0x02
#define GAME_EXIT                  0x03
#define GAME_HU                     0x04
#define GAME_OVER                 0x05

extern DRVOS_Partition_t   *gMemPart;

typedef struct _MjParam
{
	U8          lever;
	
}MjParam;

class MJ_Engine
{
public:

	U8                  m_CurPlayer;
	U8                  m_nPlayer;
	U8                  m_Timer;
	Player            *m_pPlayer;
	Computer       *m_pComputer[3];
	MahJong         *m_pMahjong;
	Painter           *m_pPainter;
	MjParam          m_Param;

	 Gamer   *m_pGamer[4];
	Gamer            *m_pWinner;
	U8                  m_Bandker;
	U8                  m_Result;
	bool                m_isStart;
	bool                m_IsOver;
	bool                m_InitFlag;
	DRVOS_Partition_t   *m_pMemPart;
public:
	 Gamer* GetNextGamer(Gamer *pCurGamer);
public:
	MJ_Engine(DRVOS_Partition_t *pMemPart = NULL);
	~MJ_Engine();
	
	void Init();
	void CreatGamers();
	void ParamInit();
	void MemberInit();
	void GameStart();
	U8 Dice();
	void Deal(U8 m_Bandker, U8 diceNum);
	void ChoiceMustLack();
	Gamer* GamersThinking(Gamer* pCurGamer, MjCard_t *outCard);
	bool DesireProcess(Gamer *pGamer, MjCard_t *pCard);
	
	bool IsGameOver();
	void GameHu();
	void GameOver();
	void NextBout();
	void GameExit();
	void GameLoad();
	void SaveScore();

	int KeyProcess(U32 KeyCode);

	U8 GetRandNum(U8 Max);

	bool IsPlayer(Gamer *pGamer);
	void SetParam(MjParam *pParam);
	
	void SetPartition( DRVOS_Partition_t *pMemPart)
	{
		m_pMemPart = pMemPart; 
	}
	
};

#endif /* _ENGINE_H_ */

