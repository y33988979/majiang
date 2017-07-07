#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "mj_marco.h"
#include "mj_types.h"

#include "gamer.h"
#include "majiang.h"


class Player : public Gamer
{
public:
	
	U16             m_Tooltip;
	
public:
	Player(MahJong* pMahjong=NULL);
	virtual ~Player();
 	
	virtual bool Thinking();
	virtual MjCard_t* PutCardThinking();
	virtual void play(MjCard_t *inCard, MjCard_t *outCard);
	virtual U8 ChoiceMustLack();	
	virtual U8 DesireProcess(U8 Desire, MjCard_t *mj);
	
	MjCard_t* putFirstCard();
	U16 GetToolTip();
};

#endif /* _PLAYER_H_ */

