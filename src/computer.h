#ifndef _COMPUTER_H_
#define _COMPUTER_H_

#include "mj_marco.h"
#include "mj_types.h"

#include "gamer.h"
#include "judge.h"

class Judge;

class Computer:public Gamer
{
private:

	U8               m_lever;
	Judge         *m_Judge;
	
public:
	Computer(U8 lever=0);
	virtual ~Computer();

	virtual void play(MjCard_t *inCard, MjCard_t *outCard);
	virtual U8 DesireThinking(MjCard_t *outCard);
	virtual MjCard_t* PutCardThinking();
	virtual U8 ChoiceMustLack();
	virtual U8 DesireProcess(U8 Desire, MjCard_t *outCard);

	int Init();
	U8 GetLever();
	void SetLever(U8 lever);
	U8 Thinking();

};

#endif /* _COMPUTER_H_ */

