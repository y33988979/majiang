#ifndef _MAHJONG_H_
#define _MAHJONG_H_

#include "mj_marco.h"
#include "mj_types.h"

class MahJong
{
public:
	U8                   m_Banker;
	U8                   m_DiceNum;
	U8                   m_Count;
	U8                   m_Pos;
	U8                   m_CurPosGamerId;
	U8                   m_CurPosX;
	U8                   m_CurPosY;
	U8                   m_playerPos;
	MjCard_t           m_Mj[MJ_MAX_NUM];
public:
	MahJong();
	~MahJong();

public:
	void shuffle();
	void dec(U8  n = 1);

	U8 GetSurplus();
	
	
	void PosUpdate();
	void SetParam(U8 banker ,U8 diceNum);
	void setCardName(MjCard_t *pCard);
	void printAll();
	void bmpInit();

};

#endif /* _MAHJONG_H_ */

