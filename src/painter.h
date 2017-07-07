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
	
	/* 桌布 */
	void DrawBackground();
	void DrawGameInit();
	/* 扔骰子 */
	void DrawDice(U8 num);
	/* 摸牌 */
	void DrawGetCard(Gamer *pGamer);
	/* 发牌 */
	void DrawDeal(Gamer *pGamer);
	/* 背牌 */
	void DrawRear(MahJong *pMahJong);
	/* 游戏者 */
	void DrawGamer(Gamer *pGamer);
	void DrawHandInCards(Gamer *pGamer);
	void DrawHandOutCards(Gamer *pGamer);
	/* 玩家讲话 */
	void DrawTalk(Gamer *pGamer);
	/* 结算信息 */
	void DrawGoldInfo();
	/* 退出提示 */
	void DrawDlg();
	/* 提示信息 */
	void DrawToolTip(Gamer *pGamer);
	/* 选择定缺 */
	void DrawChoiceMustLack(Gamer *pGamer);
	
	void SetDrawParam(U8 banker ,U8 point);
	void BmpInit();
};

#endif /* _PAINTER_H_ */

