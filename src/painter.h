#ifndef _PAINTER_H_
#define _PAINTER_H_

#include "mj_marco.h"
#include "mj_types.h"

#include "./bmp.h"


class Gamer;
class Player;
class Computer;
class MahJong;

class Painter
{
public:
	U8          m_banker;
	U8          m_point;
public:
	Painter();
	~Painter();
	
	/* ���� */
	void DrawBackground();
	void DrawGameInit();
	/* ������ */
	void DrawDice(U8 num);
	/* ���� */
	void DrawGetCard(Gamer *pGamer);
	/* ���� */
	void DrawDeal(Gamer *pGamer);
	/* ���� */
	void DrawRear(MahJong *pMahJong);
	/* ��Ϸ�� */
	void DrawGamer(Gamer *pGamer);
	void DrawHandInCards(Gamer *pGamer);
	void DrawHandOutCards(Gamer *pGamer);
	/* ��ҽ��� */
	void DrawTalk(Gamer *pGamer);
	/* ������Ϣ */
	void DrawGoldInfo();
	/* �˳���ʾ */
	void DrawDlg();
	/* ��ʾ��Ϣ */
	void DrawToolTip(Gamer *pGamer);
	/* ѡ��ȱ */
	void DrawChoiceMustLack(Gamer *pGamer);
	
	void SetDrawParam(U8 banker ,U8 point);
	void BmpInit();
};

#endif /* _PAINTER_H_ */

