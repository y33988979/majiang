#include "engine.h"
#include <time.h>

DRVOS_Partition_t   *gMemPart;

MJ_Engine::MJ_Engine(DRVOS_Partition_t *pMemPart)
{
	int i;
	for(i=0; i<4; i++)
		this->m_pGamer[i] = NULL;
	for(i=0; i<3; i++)
		m_pComputer[i] = NULL;
	m_pWinner = NULL;
	m_nPlayer = 4;
	m_isStart = false;
	m_IsOver = false;
	m_pMahjong = NULL;
	m_InitFlag = false;
	m_Bandker = NULL;
	m_Result = 0;
	m_pMemPart = pMemPart;
	gMemPart = pMemPart;
	m_pPainter = NULL;
	m_CurPlayer = NULL;
	m_Timer = NULL;
	m_pPlayer = NULL;
	
	printf("---MJ_Engine Init success! \n");
}

MJ_Engine::~MJ_Engine()
{
	int i;
	if(m_InitFlag)	
	{
		delete m_pPainter;
		
		for(i=0; i<4;i++)
			delete m_pGamer[i];
		delete m_pMahjong;
	}
}

void MJ_Engine::Init()
{
	int i;
	
	/* 在局玩家个数 */
	m_nPlayer = 4;
	
	/* 麻将牌 */
	m_pMahjong = new MahJong();
	m_pMahjong->shuffle();

	/* 玩家 */
	m_pGamer[0] = new Player();

	m_pGamer[0]->setMahJong(m_pMahjong);
	m_pGamer[0]->m_Id = 0;
	m_pPlayer = (Player*)m_pGamer[0];

	/* 电脑 */
	for(i=1; i<=3; i++)
	{
		m_pGamer[i] = new Computer();
		m_pGamer[i]->setMahJong(m_pMahjong);
		m_pGamer[i]->m_Id = i;
		m_pComputer[i-1]= (Computer*)m_pGamer[i];
	}

	/* 画板 */
	m_pPainter = new Painter();
	//m_pPainter->DrawBackground();

	m_InitFlag = true;
}

U8 MJ_Engine::GetRandNum(U8 Max)
{
	U8 RandNum;
	
	srand( (unsigned)time(NULL) );
	RandNum = rand() % 6 + 1;
	return RandNum;
}

void MJ_Engine::SetParam(MjParam *pParam)
{
	m_Param = *pParam;
}

bool MJ_Engine::IsPlayer(Gamer *pGamer)
{
	return (pGamer == m_pPlayer);
}

void MJ_Engine::CreatGamers()
{
	int i=0;
	/* 1个 玩家 */
	m_pPlayer = new Player(m_pMahjong);
	m_pPlayer->setPartition(m_pMemPart);

	/* 三个机器人 */
	for(i=0; i<3; i++)
	{
		m_pComputer[i] = new Computer();
		m_pComputer[i]->setPartition(m_pMemPart);
		m_pComputer[i]->SetLever(m_Param.lever);
	}
}

Gamer* MJ_Engine::GetNextGamer(Gamer *pCurGamer)
{
	U8 i, id;
	id = pCurGamer->m_Id;
	for(i=0; i<3; i++)
	{
		id = ++id % 4;
		if(!m_pGamer[id]->m_IsOver)
			return m_pGamer[id];
	}
	return NULL;
}

bool MJ_Engine::IsGameOver()
{
	int i;
	for(i=0; i<4; i++)
	{
		if(!m_pGamer[i]->m_IsOver)
			return false;
	}
	m_Result = GAME_OVER;
	YLOG("Gamer Over!!!\n");
	return true;
}

void MJ_Engine::GameStart()
{
	int             id,  diceNum;
	MjCard_t   *inCard = NULL;
	MjCard_t   *outCard = NULL;
	Gamer      *pCurGamer = NULL;
	Gamer      *pAnotherGamer = NULL;
	
	/* 洗牌 */
	m_pMahjong->shuffle();
	YLOG("[MJ_Engine]: shuffle !\n");
	/* 生成庄家 */
	m_Bandker = GetRandNum(4);
	YLOG("[MJ_Engine]: GetRandNum !\n");
	/* 掷骰子 */
	diceNum = Dice();
	YLOG("[MJ_Engine]: Dice !\n");
	/* 发牌 */
	Deal(m_Bandker, diceNum);
	YLOG("[MJ_Engine]: Deal !\n");

	/* 选择定缺牌 */
	ChoiceMustLack();
	YLOG("[MJ_Engine]: ChoiceMustLack !\n");
	
	id = 0;
	
	outCard = m_pPlayer->putFirstCard();
	pCurGamer = m_pGamer[0];
	/* 开始打牌，Go go !*/
	/* 逆时针顺序开始打牌，直到GameOver */
	while(!IsGameOver())
	{
		/* 其他三个玩家进行思考*/
		pAnotherGamer = GamersThinking(pCurGamer, outCard);
		YLOG("[Gamer%d play]: GamersThinking !\n", pCurGamer->m_Id);
		if(pAnotherGamer != NULL)
		{
			YLOG("[Gamer%d]: Desire %s !\n", pAnotherGamer->m_Id, outCard->name);
			if(DesireProcess(pAnotherGamer, outCard))
			{
				/* 更新pCurGamer = 下个玩家*/
				pCurGamer = GetNextGamer(pAnotherGamer);
				continue;
			}
		}
		/* 正常顺序 */
		pCurGamer = GetNextGamer(pCurGamer);
		YLOG("The Next is Gamer%d \n", pCurGamer->m_Id);
		
		pCurGamer->play(inCard, outCard);
		YLOG("[Gamer%d]: play !\n", pCurGamer->m_Id);
	}

	/* 游戏结束 */
	if(m_Result == GAME_EXIT)
	{
		GameExit();
	}
	else if(m_Result == GAME_OVER)
	{
		GameOver();
	}	
}

U8 MJ_Engine::Dice()
{
	U8 diceNum;
	diceNum = GetRandNum(6);

	/* 掷骰子动画 */
	m_pPainter->DrawDice(diceNum);
	
	return diceNum;
}

void MJ_Engine::Deal(U8 m_Bandker, U8 diceNum)
{
	int      i, j, n;
	Gamer  *tmp = NULL;
	Gamer      *pCurGamer = NULL;

	pCurGamer = m_pGamer[0];
	//m_pPainter->SetDrawParam(m_Bandker, diceNum);
	m_pMahjong->SetParam(m_Bandker, diceNum);
	for(i=0; i<6; i++)
	{
		for(j=0; j<4; j++)
		{
			YLOG("pCurGamer id=%d\n", pCurGamer->m_Id);
			pCurGamer->GetTwoCards();
			//m_pPainter->DrawRear(m_pMahjong);
			m_pPainter->DrawGamer(pCurGamer);
			MidPause(200);
			pCurGamer = GetNextGamer(pCurGamer);
		}
	}

	MidPause(500);
	/* 庄家跳牌 */
	m_pGamer[0]->GetTwoCards();
	m_pPainter->DrawRear(m_pMahjong);
	m_pPainter->DrawGamer(m_pGamer[0]);

	/* 收底 */
	m_pGamer[1]->GetCard();
	m_pGamer[2]->GetCard();
	m_pGamer[3]->GetCard();
	m_pPainter->DrawRear(m_pMahjong);

	for(i=1; i<=3; i++)
	{
		m_pPainter->DrawGamer(m_pGamer[i]);
	}
	for(i=0; i<4; i++)
		m_pGamer[i]->PrintHandCards();
	YLOG("Deal: finish!\n");
}

void MJ_Engine::ChoiceMustLack()
{
	U8   i;
	int   MustLack;

	/* computer  */
	for(i=1; i<=3; i++)
	{
		MustLack = m_pGamer[i]->ChoiceMustLack();
		m_pGamer[i]->SetMustLack(MustLack);
		YLOG("MustLack = %d\n", MustLack);
		m_pGamer[i]->SortCards(MustLack);
		YLOG("SortCards \n");
	}
	
	m_pPainter->DrawChoiceMustLack(m_pPlayer);
	YLOG("DrawChoiceMustLack \n");
	/* wait player */
	MustLack = m_pPlayer->ChoiceMustLack();
	if(MustLack < 0)
	{
		/* 随机选择定缺 */
		MustLack = GetRandNum(3);
		YLOG("m_pPlayer  - - GetRandNum \n");
		m_pPlayer->m_HandCards.m_MustLack = MustLack;
		m_pPlayer->SortCards(MustLack);
		YLOG("m_pPlayer  - - SortCards \n");
	}
	
	return;
}

Gamer* MJ_Engine::GamersThinking(Gamer* pCurGamer, MjCard_t *outCard)
{
	int i, id, rId, num;
	bool HaveDesire = false;

	/* 检查其他玩家是否要牌，并设置要牌的优先级 */
	id = pCurGamer->m_Id;
	for(i=0; i<3; i++)
	{
		id = (++id) % 4;
		
		m_pGamer[id]->m_Priority = 0;
		if(m_pGamer[id]->CheckDesire(outCard))
		{
			if(m_pGamer[id]->m_Desire != DESIRE_HU)
				m_pGamer[id]->m_Priority = 1;
			else
				m_pGamer[id]->m_Priority = 2;
			HaveDesire = true;
		}
	}

	/* 找到优先级最大的玩家 */
	rId = 0;
	num = 0;
	if(HaveDesire)
	{
		id = pCurGamer->m_Id;
		for(i=0; i<3; i++)
		{
			id = (++id) % 4; 
			if(m_pGamer[id]->m_Priority > num)
			{
				num = m_pGamer[id]->m_Priority;
				/* 优先级最大玩家ID */
				rId = id;    
			}
		}

		return m_pGamer[rId];
	}	
	
	return NULL;
}

bool MJ_Engine::DesireProcess(Gamer *pGamer, MjCard_t *pCard)
{
	U8            ThinkResult;
	U8            ret;

	/* 玩家 */
	if(IsPlayer(pGamer))
	{
		
		m_pPainter->DrawToolTip(pGamer); 
		/* Block until player finish think  */
		ThinkResult = pGamer->DesireThinking(pCard);
		if(ThinkResult != 0)
		{
			ret = pGamer->DesireProcess(pGamer->m_Desire, pCard);
			if(ret == DESIRE_HU)
			{
				m_nPlayer--;
				pGamer->m_IsOver = true;
			}
			return true;
		}
		else	
		{
			/* 过牌 */
			return false;
		}
	}
	/* 电脑 */
	else
	{
		ret = pGamer->DesireProcess(ThinkResult, pCard);
		if(ret == DESIRE_HU)
		{
			m_nPlayer--;
			pGamer->m_IsOver = true;
		}
		return true;
	}

	
}

void MJ_Engine::MemberInit()
{

}

void MJ_Engine::GameHu()
{

}

void MJ_Engine::GameOver()
{

}

void MJ_Engine::NextBout()
{

}

void MJ_Engine::GameExit()
{

}

void MJ_Engine::GameLoad()
{
}

void MJ_Engine::SaveScore()
{

}

int MJ_Engine::KeyProcess(U32 KeyCode)
{
	switch(KeyCode)
	{
		case ID_OK:
			if(!m_isStart)		
				GameStart();
			break;
		case ID_LEFT:
			break;
		case ID_RIGHT:
			break;
		case ID_UP:
			break;
		case ID_DOWN:
			break;
	}
}

