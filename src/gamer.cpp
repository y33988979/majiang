#include "gamer.h"

Gamer::Gamer(MahJong* pMahjong)
{
	int i;
	
	m_Gold = MJ_GOLD_MAX;
	m_IsTing = false;

	for(i=0; i<MJ_PRE_OUTCARDS_NUM; i++)
	{
		m_OutCards[i].owner = GAMER_PLAYER;
		m_OutCards[i].isPao = false;
		m_OutCards[i].mj = NULL;
	}
	m_pNewCard = NULL;

	m_HandCardCnt = 0;
	m_OutCardNum = 0;
	m_Tooltip = 0x0;
	m_pMahjong = pMahjong;
	m_IsOver = false;
}

Gamer::~Gamer()
{
	
}

MjCard_t* Gamer::GetCard()
{
	U8    pos = m_pMahjong->m_Pos;
	char *str = NULL;

	m_pNewCard = &m_pMahjong->m_Mj[pos];
	m_HandCardCnt++;
	m_HandCards.Insert(m_pNewCard);
	m_pMahjong->dec();
	//m_pMahjong->PosUpdate();

	YLOG("[Gamer%d] GetCard: %s\n", m_Id, m_pNewCard->name);
	return m_pNewCard;
}

MjCard_t* Gamer::GetTwoCards()
{
	int i;
	U8 pos = m_pMahjong->m_Pos;

	for(i=0; i<2; i++)
	{
		m_HandCards.Insert(&m_pMahjong->m_Mj[pos+i]);
	}
	m_HandCardCnt += 2;
	m_pMahjong->dec(2);
	//m_pMahjong->PosUpdate();
	m_pNewCard = &m_pMahjong->m_Mj[pos];

	YLOG("[Gamer%d] GetTwoCard: %s, %s\n",\
		m_Id, m_pMahjong->m_Mj[pos-1].name, m_pMahjong->m_Mj[pos].name);

	return m_pNewCard;
}

MjCard_t* Gamer::GetFourCards()
{
	int i;
	U8 pos = m_pMahjong->m_Pos;
	for(i=0; i<4; i++)
	{
		m_HandCards.Insert(&m_pMahjong->m_Mj[pos+i]);
	}

	m_HandCardCnt += 4;
	m_pMahjong->dec(4);
	//m_pMahjong->PosUpdate();
	m_pNewCard = &m_pMahjong->m_Mj[pos];
	
	return m_pNewCard;
}

bool Gamer::PutCard(MjCard_t* mj)
{
	m_OutCards[m_OutCardNum].mj = mj;
	m_OutCardNum++;

	m_HandCards.Del(mj);

	return false;
}

U8 Gamer::GetHandCardsCount()
{
	int i, count = 0;
	for(i=0; i<3; i++)
		count += m_HandCards.m_MjList[i]->nLength;
	
	return count;
}

MjCard_t* Gamer::GetFirstHandCard()
{
	int     i;

	for(i=0; i<3; i++)
		ListMoveHead(m_HandCards.m_MjList[i]);
	for(i=0; i<3; i++)
	{
		if(ListGetCount(m_HandCards.m_MjList[i]))
		{
			m_pCurCard = (MjCard_t*)ListMoveHead(m_HandCards.m_MjList[i]);
			break;
		}
	}

	return m_pCurCard;
}

MjCard_t* Gamer::GetNextHandCard()
{
	int i;
	MjCard_t  *pCard = NULL;
	MjCard_t  *pNextCard = NULL;
	
	i = m_pCurCard->type;
	
	/* 找当前花色的下一个 */
	pCard = (MjCard_t*)ListMoveNext(m_HandCards.m_MjList[i]);
	if(pCard != NULL)
	{
		m_pCurCard = pCard;
		return m_pCurCard;
	}
	else
	{
		while(++i < 3)
		{
			/* 进入此处说明上一个花色遍历完成 */
			pCard = (MjCard_t*)ListMoveHead(m_HandCards.m_MjList[i]);
			if(pCard != NULL)
			{
				m_pCurCard = pCard;
				return m_pCurCard;
			}
		}
	}

	return NULL;
}

MjCard_t* Gamer::GetLastHandCard()
{
	int i;
	for(i=2; i>=0; i--)
	{
		if(ListGetCount(m_HandCards.m_MjList[i]))
		{
			m_pCurCard = (MjCard_t*)ListMoveEnd(m_HandCards.m_MjList[i]);
			return m_pCurCard;
		}
	}
}

MjCard_t* Gamer::FindHandCard(MjCard_t *pCard)
{

}


MjCard_t* Gamer::GetCardThinking()
{
	/* No thinking */

	return NULL;
} 

bool Gamer::InsertCardThinking(MjCard_t *inCard)
{
	MjCard_t *pCard = NULL;
	MjPair_t  *pPair = NULL;
	MjTern_t *pTern = NULL;
	bool         ret;

	/* 定缺牌不插入 */
	ret = true;
	if(inCard->type == m_HandCards.m_MustLack)
	{
		ret = false;
	}

	return ret;
} 

void Gamer::InsertCardProcess(MjCard_t *inCard)
{
	MjCard_t *pCard = NULL;
	MjPair_t  *pPair = NULL;
	MjTern_t *pTern = NULL;
	bool         isLay = false;
	
	if((pTern = CheckGang(inCard, &isLay)) != NULL)
		m_HandCards.AddGang(pTern, inCard);
	else if((pPair = CheckPeng(inCard)) != NULL)
		m_HandCards.AddTern(pPair, inCard);
	else if((pCard = CheckPair(inCard)) != NULL)
		m_HandCards.AddPair(pCard, inCard);
} 

bool Gamer::CheckDesire(MjCard_t* mj)
{
	bool isLay =false;
	m_Desire = 0x0;
	if(CheckPeng(mj))
		m_Desire |= INFO_PENG;
	if(CheckGang(mj, &isLay))
		m_Desire |= INFO_GANG;
	if(isLay)
		m_Desire |= INFO_GANG_LAY;
	if(CheckHu(mj))
		m_Desire |= INFO_HU;
	
	return (m_Desire!=0);
}

bool Gamer::CheckEat(MjCard_t* mj)
{
	/* Never */

	return false;
}

MjCard_t* Gamer::CheckPair(MjCard_t* mj)
{	
	int i;
	MjCard_t  *pCard = NULL;
	
	i = mj->type;
	pCard = (MjCard_t*)ListMoveHead(m_HandCards.m_MjList[i]);
	while (pCard != NULL)
	{
		if(pCard->value == mj->value)
			return pCard;
		else
			pCard = (MjCard_t*)ListMoveNext(m_HandCards.m_MjList[i]);
	}
	return NULL;
}

MjPair_t* Gamer::CheckPeng(MjCard_t* mj)
{
	MjPair_t  *pPair = NULL;
	
	pPair = (MjPair_t*)ListMoveHead(&m_HandCards.m_PairList);
	while (pPair != NULL)
	{
		if(pPair->value == mj->value)
			return pPair;
		pPair = (MjPair_t*)ListMoveNext(&m_HandCards.m_PairList);
	}

	return  NULL;
}

MjTern_t* Gamer::CheckGang(MjCard_t* mj, bool *isLay)
{
	MjTern_t *pTern = NULL;

	*isLay = false;
	/* 是否在手里or 碰上杠 */
	pTern = (MjTern_t*)ListMoveHead(&m_HandCards.m_TernList);
	while(pTern != NULL)
	{
		if(pTern->value == mj->value)
		{
			*isLay = pTern->isLay;
			return pTern;
		}
		pTern = (MjTern_t*)ListMoveNext(&m_HandCards.m_TernList);

	}
	
	return NULL;
}

bool Gamer::CheckHu(MjCard_t* mj)
{
	MjCard_t *pCard = NULL;

	pCard = (MjCard_t*)ListMoveHead(&m_HandCards.m_HuList);
	while (pCard != NULL)
	{
		if(pCard->value == mj->value)
			return true;
		pCard = (MjCard_t*)ListMoveNext(&m_HandCards.m_HuList);
	}
	return false;
}

int Gamer::Eat(MjCard_t* mj)
{

}

int Gamer::Peng(MjPair_t *pMyPair, MjCard_t* mj)
{
	MjTern_t *pTern = NULL;

	pTern = m_HandCards.AddTern(pMyPair, mj);
	pTern->isLay = true;
	
	return 1;
}

int Gamer::Gang(MjTern_t *pMyTern, MjCard_t* mj)
{
	MjGang_t *pGang = NULL;

	pGang = m_HandCards.AddGang(pMyTern, mj);
	pGang->isLay = true;
	return 1;
}

int Gamer::Hu(MjCard_t* mj)
{
	//Hu Hu ;
}

void Gamer::SetMustLack(U8 type)
{
	m_HandCards.m_MustLack = type;
}

U8  Gamer::GetMustLack()
{
	return m_HandCards.m_MustLack;
}

void Gamer::SortCards(U8 MustLack)
{
	/* 重置MjList 指针顺序，MjList[2] 为定缺类型 */
	if(MustLack == MJ_WAN)
	{
		m_HandCards.m_MjList[0] = &m_HandCards.m_TiaoList;
		m_HandCards.m_MjList[1] = &m_HandCards.m_TongList;
		m_HandCards.m_MjList[2] = &m_HandCards.m_WanList;
	}
	else if(MustLack == MJ_TIAO)
	{
		m_HandCards.m_MjList[0] = &m_HandCards.m_WanList;
		m_HandCards.m_MjList[1] = &m_HandCards.m_TongList;
		m_HandCards.m_MjList[2] = &m_HandCards.m_TiaoList;
	}
	else if(MustLack == MJ_TONG)
	{
		m_HandCards.m_MjList[0] = &m_HandCards.m_TiaoList;
		m_HandCards.m_MjList[1] = &m_HandCards.m_WanList;
		m_HandCards.m_MjList[2] = &m_HandCards.m_TongList;
	}
}

void Gamer::InsertCard()
{

}

void Gamer::PrintHandCards()
{
	int i;
	MjCard_t  *pCard = NULL;

	YLOG("[Game%d]->print HandCards:\n", m_Id);
	/* 遍历手牌 */
	pCard = GetFirstHandCard();
	while(pCard != NULL)
	{
		
		YLOG("[%s]  ", pCard->name);
		pCard = GetNextHandCard();
	}
	YLOG("\n");
}

	
