#include "computer.h"

Computer::Computer(U8 lever)
{
	m_Judge = new Judge();
	YLOG("New Computer! \n");
}

Computer::~Computer()
{
	delete m_Judge;
}

int Computer::Init()
{
	
}

void Computer::play(MjCard_t *inCard, MjCard_t *outCard)
{
	int ret;
	
	inCard = GetCard();

	m_pPainter->DrawGetCard(this);
	YLOG("test4\n");
	/* Computer thinking... */
	if(InsertCardThinking(inCard) == false)
	{YLOG("test5\n");
		PutCard(outCard);
		return ;
	}
	YLOG("test6\n");
	
	InsertCardProcess(inCard);
	YLOG("test7\n");
	outCard = PutCardThinking();
	YLOG("test8\n");
	PutCard(outCard);
	YLOG("test9\n");
}

U8 Computer::DesireThinking(MjCard_t *outCard)
{
	return 0;
}

/* 选择一张要打出的牌 */
MjCard_t* Computer::PutCardThinking()
{
	MjCard_t *outCard = NULL;

	/* 检查定缺牌 */
	if(ListGetCount(m_HandCards.m_MjList[2]))
	{
		outCard = (MjCard_t*)ListMoveEnd(m_HandCards.m_MjList[2]);
	}
	else
	{
		/* 调用出牌算法 */
		outCard = m_Judge->PutCardThinking(this);
	}

	YLOG("outCard = %d\n", outCard->value);
	return outCard;
}

U8 Computer::ChoiceMustLack()
{
	YLOG("Gamer%d: ChoiceMustLack!\n", this->m_Id);
	int i, type , count ;
	int min = 15;
	for(i=0; i<3; i++)
	{
		count = m_HandCards.m_MjList[i]->nLength;
		if(count < min)
		{
			min = count;
			type = i;
		}
	}

	return type;
}

U8 Computer::DesireProcess(U8 Desire, MjCard_t *outCard)
{
	MjCard_t   *pCard = NULL;
	MjPair_t    *pPair = NULL;
	MjTern_t   *pTern = NULL;
	bool           isLay = false;

	if(CheckHu(outCard))
	{
		Desire = DESIRE_HU;
		return Desire;
	}
	
	pTern = CheckGang(outCard, &isLay);
	if(pTern != NULL)
	{
		Desire = DESIRE_GANG;
		m_HandCards.AddGang(pTern, outCard, &isLay);
		return Desire;
	}
	
	pPair = CheckPeng(outCard);
	if(pPair != NULL)
	{
		Desire = DESIRE_PENG;
		m_HandCards.AddTern(pPair, outCard);	
		return Desire;
	}

	return Desire;
}

U8 Computer::GetLever()
{
	return 0;
}

void Computer::SetLever(U8 lever)
{
	m_lever = lever;
}

U8 Computer::Thinking()
{
	return 0;
}



