#include "handcards.h"

extern DRVOS_Partition_t   *gMemPart;

HandCards::HandCards()
{
	m_MustLack = 0xFF;
	Init();
}

HandCards::~HandCards()
{

}

bool HandCards::Init()
{
	int i;
	for(i=0; i<4; i++)
	{
		memset(m_Pair, 0, sizeof(MjPair_t));
		memset(m_Tern, 0, sizeof(MjPair_t));
	}

	ListInit(&m_WanList, 0, NULL, NULL, NULL, gMemPart);
	ListInit(&m_TiaoList, 0, NULL, NULL, NULL, gMemPart);
	ListInit(&m_TongList, 0, NULL, NULL, NULL, gMemPart);
	ListInit(&m_PairList, 0, NULL, NULL, NULL, gMemPart);
	ListInit(&m_TernList, 0, NULL, NULL, NULL, gMemPart);
	ListInit(&m_GangList, 0, NULL, NULL, NULL, gMemPart);
	ListInit(&m_HuList, 0, NULL, NULL, NULL, gMemPart);

	m_MjList[0] = &m_WanList;
	m_MjList[1] = &m_TiaoList;
	m_MjList[2] = &m_TongList;
	
}

U8 HandCards::GetError()
{
	return m_ErroCode;
}

MjPair_t* HandCards::CreatNewPair()
{
	int i;
	for(i=0; i<6; i++)
	{
		if(m_Pair[i].isFree)
			return &m_Pair[i];
	}
	
}

MjTern_t* HandCards::CreatNewTern()
{
	int i;
	for(i=0; i<4; i++)
	{
		if(m_Tern[i].isFree)
			return &m_Tern[i];
	}
}

MjGang_t* HandCards::CreatNewGang()
{
	int i;
	for(i=0; i<4; i++)
	{
		if(m_Gang[i].isFree)
			return &m_Gang[i];
	}
}

bool HandCards::Add(MjCard_t *mj)
{
	ListAddEnd(m_MjList[mj->type], mj);
}

bool HandCards::Del(MjCard_t *mj)
{
	ListDeleteItem(m_MjList[mj->type], mj);
}

bool HandCards::Insert(MjCard_t *mj)
{
	int i;
	MjCard_t *pCard = NULL;

	
	i = mj->type;

	pCard = (MjCard_t*)ListMoveHead(m_MjList[i]);
	while(pCard != NULL)
	{
		if(mj->value <= pCard->value)
		{
			ListInsertBefore(m_MjList[i], pCard, mj);
			return true;
		}
		pCard = (MjCard_t*)ListMoveNext(m_MjList[i]);
	}	

	/* 找不到比mj 小的牌，插到最后 */
	if(ListGetCount(m_MjList[i]))
	{
		ListAddEnd(m_MjList[i], mj);
	}
	else   /* 手中没有此花色，添加到首位置 */
	{
		ListAddBegin(m_MjList[i], mj);	
	}

}

MjPair_t* HandCards::AddPair(MjCard_t *mj, MjCard_t *newMj)
{
	MjCard_t *pCard = NULL;
	MjPair_t  *pNewPair = NULL;
	
	/* 生成MjTern_t 结构 */
	pNewPair = CreatNewPair();

	if(m_TernList.nLength >= 6)
	{
		printf("AddPair: AddPair.nLength >=6!!\n ");
		return false;
	}
	pNewPair->isFree = false;
	pNewPair->type = mj->type;
	pNewPair->index = mj->index;
	pNewPair->value= mj->value;
	pNewPair->mj[0] = mj;
	pNewPair->mj[1] = newMj;

	return pNewPair;
}

bool HandCards::DelPair(MjCard_t *mj)
{
	MjPair_t *pPair = NULL;
	
	pPair = (MjPair_t*)ListMoveHead(&m_PairList);
	while (pPair != NULL)
	{
		if(pPair->value== mj->value)
		{
			ListDeleteItem(&m_PairList, pPair);
			pPair->isFree = true;
			return true;
		}
		pPair = (MjPair_t*)ListMoveNext(&m_PairList);
	}
}

MjTern_t* HandCards::AddTern(MjPair_t *pPair, MjCard_t *mj)
{
	int i, n = 0;
	MjCard_t *pCard = NULL;
	MjTern_t *pNewTern = NULL;

	/* 获取MjTern_t 结构 */
	pNewTern = CreatNewTern();
	
	if(m_TernList.nLength >= 4)
	{
		printf("AddTern: AddTern.nLength >=4!!\n ");
		return false;
	}
	
	/* 填充m_Tern结构 */
	memcpy((void*)pNewTern, pPair, sizeof(MjPair_t));
	pNewTern->mj[2] = mj;

	/* 花色 */
	i = mj->type;
	/* 删除手中一对 牌 */
	n = 0;
	pCard = (MjCard_t*)ListMoveHead(m_MjList[i]);
	while (pCard != NULL)
	{
		if(pCard->index == mj->index)
		{
			n++;
			//pNewTern->mj[n] = mj;
			ListDeleteItem(m_MjList[i], pCard);
		}
		else
		{
			pCard = (MjCard_t*)ListMoveNext(m_MjList[i]);
		}
		if(n == 2)  break;
	}


	/* Pair--  tern++ */
	ListDeleteItem(&m_PairList, pPair);
	pPair->isFree = true;
	ListAddEnd(&m_TernList, pNewTern);
	
	return pNewTern;	
}

bool HandCards::DelTern(MjCard_t *mj)
{
	MjTern_t *pTern = NULL;
	
	pTern = (MjTern_t*)ListMoveHead(&m_TernList);
	while (pTern != NULL)
	{
		if(pTern->index == mj->index)
		{
			ListDeleteItem(&m_TernList, pTern);
			pTern->isFree = true;
			return true;
		}
		pTern = (MjTern_t*)ListMoveNext(&m_TernList);
	}

	return false;
}

MjGang_t* HandCards::AddGang(MjTern_t *pTern ,MjCard_t *mj, bool *isLay)
{
	int i, n = 0;
	MjCard_t *pCard = NULL;
	MjGang_t *pNewGang = NULL;

	/* 获取MjTern_t 结构 */
	pNewGang = CreatNewGang();
	
	if(m_GangList.nLength >= 4)
	{
		printf("AddGang: m_GangList.nLength >=4!!\n ");
		return false;
	}

	/* 填充Gang 结构 */
	memcpy((void *)pNewGang, pTern, sizeof(MjTern_t));
	pNewGang->mj[3] = mj;
		
	/* 牌在手中 ，从手牌list 中删除3 张gang*/
	if(!isLay)
	{
		/* 花色 */
		i = mj->type;
		pCard = (MjCard_t*)ListMoveHead(m_MjList[i]);
		while (pCard != NULL)
		{
			if(pCard->index == mj->index)
			{
				n++;
				//pNewGang->mj[n] = mj;
				ListDeleteItem(m_MjList[i], pCard);
			}
			else
			{
				pCard = (MjCard_t*)ListMoveNext(m_MjList[i]);
			}
			if(n == 3)  break;
		}
	}

	/* Tern--  Gang++ */
	ListDeleteItem(&m_TernList, pTern);
	pTern->isFree = true;
	ListAddEnd(&m_GangList, pNewGang);

	return pNewGang;
}

MjCard_t* HandCards::AddHu(MjCard_t *mj)
{
	return (MjCard_t*)ListAddEnd(&m_HuList, mj);
}

void HandCards::DelHu(MjCard_t *mj)
{
	ListDeleteItem(&m_HuList, mj);
}

U8 HandCards::GetNewCard()
{

}

void HandCards::SetNewCard(U8  cnt)
{

}

U8 HandCards::GetGangCnt()
{
	int cnt = 0;
	MjGang_t *pGang;
	
	pGang = (MjGang_t*)ListMoveHead(&m_GangList);
	while(pGang != NULL)
	{
		if(pGang->isLay)
			cnt++;
		pGang = (MjGang_t*)ListMoveNext(&m_GangList);
	}
	return cnt;
}

U8 HandCards::GetTernCnt()
{
	return ListGetCount(&m_TernList);
}

U8 HandCards::GetPengCnt()
{
	int cnt = 0;
	MjTern_t *pTern;
	
	pTern = (MjTern_t*)ListMoveHead(&m_TernList);
	while(pTern != NULL)
	{
		if(pTern->isLay)
			cnt++;
		pTern = (MjTern_t*)ListMoveNext(&m_TernList);
	}
	return cnt;
}

bool HandCards::IsWholeColored()
{
	int i, n;
	for(i=0; i<3; i++)
	{
		if(ListGetCount(m_MjList[i]) == 0)
		{
			n++;
		}
	}

	return (n==2) ? true : false;
}

