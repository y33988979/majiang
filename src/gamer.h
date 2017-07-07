#ifndef _GAMER_H_
#define _GAMER_H_

#include "mj_marco.h"
#include "mj_types.h"

#include "handcards.h"
#include "mahjong.h"
#include "painter.h"
#include "driver.h"



#define INFO_NULL		0x00
#define INFO_PENG		0x01
#define INFO_GANG		0x02
#define INFO_GANG_LAY   0x04
#define INFO_HU			0x08

typedef struct _OutCards
{
	U8             owner;
	bool           isPao;
	MjCard_t   *mj;
}OutCards_t;

class Gamer
{
public:
	U8                 m_Id;
	U32               m_Gold;	
	U8                 m_Tooltip;
	U8                 m_Desire;
	U8                 m_OutCardNum;
	bool               m_IsTing;
	bool               m_IsOver;
	U8                 m_HandCardCnt;
	HandCards      m_HandCards;
	OutCards_t     m_OutCards[MJ_PRE_OUTCARDS_NUM];
	MjCard_t        *m_pNewCard;
	MjCard_t        *m_pCurCard;
	MahJong        *m_pMahjong;
	Painter          *m_pPainter;
	void              *m_pMemPart;
	U8                  m_Priority;


public:
	Gamer(MahJong* pMahjong=NULL);
	virtual ~Gamer();
	
	virtual void play(MjCard_t *inCard, MjCard_t *outCard){};
	virtual U8 DesireThinking(MjCard_t *outCard){};
	virtual MjCard_t* PutCardThinking(){};
	virtual U8 ChoiceMustLack(){};
	virtual bool CheckDesire(MjCard_t *mj);
	virtual U8 DesireProcess(U8 Desire, MjCard_t *mj){};

	MjCard_t* GetCardThinking();
	bool InsertCardThinking(MjCard_t *inCard);
	void InsertCardProcess(MjCard_t *inCard);
 	void setPartition( DRVOS_Partition_t *pMemPart)
	{ m_pMemPart = pMemPart; }

	void setPainter( Painter *painter)
	{ m_pPainter = painter; }
	
	void setMahJong( MahJong *pMahJong)
	{ m_pMahjong = pMahJong; }
	
	MjCard_t* GetCard();
	MjCard_t* GetTwoCards();
	MjCard_t* GetFourCards();
	bool PutCard(MjCard_t* mj);

	MjCard_t* GetFirstHandCard();
	MjCard_t* GetLastHandCard();
	MjCard_t* GetNextHandCard();
	MjCard_t* FindHandCard(MjCard_t *pCard);
	U8 GetHandCardsCount();

	//bool PutThinking(); /* Computer AI */
	
	bool CheckHu(MjCard_t* mj);
	bool CheckEat(MjCard_t* mj);
	MjCard_t* CheckPair(MjCard_t* mj);	
	MjPair_t* CheckPeng(MjCard_t* mj);
	MjTern_t* CheckGang(MjCard_t* mj, bool *isLay = false);

	int Hu(MjCard_t* mj);
	int Eat(MjCard_t* mj);
	int Peng(MjPair_t *pMyPair, MjCard_t* mj);
	int Gang(MjTern_t *pMyTern, MjCard_t* mj);

	void SetMustLack(U8 type);
	U8  GetMustLack();
	
	void SortCards(U8 MustLack);	/* ХыАн */
	void InsertCard();
	void PrintHandCards();
	
};


#endif /* _GAMER_H_ */

