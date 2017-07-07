#ifndef _MYCARDS_H_
#define _MYCARDS_H_

#include "mj_marco.h"
#include "mj_types.h"

#include "driver.h"

/* Õº∞∏ */
#define MJ_WAN                   0
#define MJ_TIAO		          1
#define MJ_TONG                 2

#define OK                           1
#define ERR_BASE                10
#define ERR_ERROR             ERR_BASE+1

typedef struct _MjPair
{
	bool              isFree;
	U8                type;
	U8                value;
	U8                index;
	MjCard_t      *mj[2];
}MjPair_t;

typedef struct _MjTern
{
	bool              isFree;
	U8                type;
	U8                value;
	U8                index;
	bool              isLay;	/* ÃÀ≈∆ */
	MjCard_t      *mj[3];
}MjTern_t;

typedef struct _MjGang
{
	bool              isFree;
	U8                type;
	U8                value;
	U8                index;
	bool              isLay;
	MjCard_t      *mj[4];
}MjGang_t;

class HandCards
{
public:
	list_t              m_WanList;
	list_t              m_TiaoList;
	list_t              m_TongList;
	list_t             *m_MjList[3];
	
	list_t              m_PairList;
	list_t              m_TernList;
	list_t              m_HuList;

	list_t              m_PengList;
	list_t              m_GangList;

	MjPair_t          m_Pair[6];
	MjTern_t         m_Tern[4];
	MjGang_t        m_Gang[4];
	
	U8                  m_MustLack;   /* ∂®»± */
	MjCard_t        *m_NewCard;
	bool                m_IsWholeColored;

	U8                  m_ErroCode;
	void              *m_pMemPart;
	
private:
	MjPair_t *CreatNewPair();
	MjTern_t *CreatNewTern();
	MjGang_t *CreatNewGang();

public:
	HandCards();
	~HandCards();

	bool Init();
	bool Add(MjCard_t *mj);
	bool Del(MjCard_t *mj);
	bool Insert(MjCard_t *mj);
	
	U8 GetError();

	MjPair_t* AddPair(MjCard_t *mj, MjCard_t *newMj);
	bool DelPair(MjCard_t *mj);
	MjTern_t* AddTern(MjPair_t *pPair, MjCard_t *mj);
	bool DelTern(MjCard_t *mj);
	MjGang_t* AddGang(MjTern_t *pTern ,MjCard_t *mj, bool *isLay = false);
	MjCard_t* AddHu(MjCard_t *mj);
	void DelHu(MjCard_t *mj);

	U8 GetNewCard();
	void SetNewCard(U8  cnt);

	U8 GetTernCnt();
	U8 GetGangCnt();
	U8 GetPengCnt();
	
	bool IsWholeColored();

	void setPartition( DRVOS_Partition_t *pMemPart)
	{ m_pMemPart = pMemPart; }
	
};

#endif /* _MYCARDS_H_ */

