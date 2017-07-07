#ifndef _JUDGE_H_
#define _JUDGE_H_

#include "mj_marco.h"
#include "mj_types.h"

#include "engine.h"

class MJ_Engine;

class Judge
{
public:
	MahJong           *m_pMahJong;
	int                     m_PAI[CARD_KIND_MAX];
	
public:
	Judge();
	~Judge();

	MjCard_t* PutCardThinking(Gamer *pCurGamer);
	MjCard_t* ChoosePutCard(Gamer *pGamer);
	int CardListToArray(Gamer *pGamer, int *PAI);

	MjCard_t* FindCardForCanTing(Gamer *pGamer);
	
	int IsHu(int *PAI);
	int  Remain(int *PAI);

	
};

#endif /* _JUDGE_H_ */

