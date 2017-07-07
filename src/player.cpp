#include "player.h"

Player::Player(MahJong* pMahjong)
{
	m_Tooltip = INFO_NULL;
	printf("new player!\n");
}

Player::~Player()
{

}


bool Player::Thinking()
{
	/* No thinking */
}

MjCard_t* Player::PutCardThinking()
{
	
}


U8 Player::ChoiceMustLack()
{
	U8 MustLack;
	int TimeOut = TIMEOUT_MUST_LACK;
	
	while(TimeOut--)
	{
		MustLack = GetMustLack();
		if(MustLack != 0xFF)
		{
			SortCards(MustLack);
			return MustLack;
		}
		MidPause(100);
		YLOG("\rWaiting player choice...%d \n", TimeOut);
		fflush(stdout);
	}
	YLOG("\nPlayer choice type: %x\n ", MustLack);
	return INVAID;
}

U8 Player::DesireProcess(U8 Desire, MjCard_t *mj)
{
	MjPair_t   *pPair = NULL;
	MjTern_t  *pTern = NULL;
	if(Desire == DESIRE_PENG)
	{
		pPair = CheckPeng(mj);
		Peng(pPair, mj);
		//m_pPainter->DrawPeng(this);
	}
	else if(Desire == DESIRE_GANG)
	{
		pTern = CheckGang(mj);
		Gang(pTern, mj);
		//m_pPainter->DrawPeng(this);
	}
	else if(Desire == DESIRE_HU)
	{
		if(CheckHu(mj))
			Hu(mj);
		//m_pPainter->DrawHu(this);
	}

	return Desire;
}

MjCard_t* Player::putFirstCard()
{
	MjCard_t  *outCard = NULL;
	
	outCard = PutCardThinking();
	PutCard(outCard);
	return outCard;
}

void  Player::play(MjCard_t *inCard, MjCard_t *outCard)
{
	GetCard();
	
	m_pPainter->DrawGetCard(this);

	//InsertCardProcess(inCard);
	
	outCard = PutCardThinking();

	PutCard(outCard);	
}

U16 Player::GetToolTip()
{
	return m_Tooltip;
}
	
	
