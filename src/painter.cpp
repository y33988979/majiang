#include "painter.h"
#include "majiang.h"
#include "gamer.h"

Painter::Painter()
{
	DrawBackground();
	
	DrawGameInit();
}

Painter::~Painter()
{
 	
}

/* 桌布 */
void Painter::DrawBackground()
{
	drawbmp(0, 0, (void *)&Mj_bg_struct);
}

void Painter::DrawGameInit()
{
	int i,j;
	int x,y;
	int left_posX = 140;
	int left_posY = 140;
	int right_posX = 550;
	int right_posY = 140;
	int up_posX = 195;
	int up_posY = 100;
	int down_posX = 195;
	int down_posY = 430;
	int bmp_width ;
	int bmp_height ;
	const STOSD_Bitmap_t *pBmp = NULL;
	
	pBmp = &MjCard_common_backV_struct;
	bmp_width = pBmp->Width;
	bmp_height = pBmp->Height;

	/* 左边和右边 */
	for(i=0; i<13; i++)
	{
		drawbmp(left_posX, left_posY+bmp_height*i, (void *)pBmp);
		drawbmp(right_posX, right_posY+bmp_height*i, (void *)pBmp);
	}

	pBmp = &MjCard_common_backH_struct;
	bmp_width = pBmp->Width;
	bmp_height = pBmp->Height;
	/* 上边和下边 */
	for(i=0; i<14; i++)
	{
		drawbmp(up_posX+bmp_width*i, up_posY, (void *)pBmp);
		drawbmp(down_posX+bmp_width*i, down_posY, (void *)pBmp);
	}
	
}

/* 扔骰子 */
void Painter::DrawDice(U8 num)
{

}
/* 发牌 */
void Painter::DrawDeal(Gamer *pGamer)
{

}

/* 摸牌 */
void Painter::DrawGetCard(Gamer *pGamer)
{

}

/* 背牌 */
void Painter::DrawRear(MahJong *pMahJong)
{
	int i , Surplus;
	int posX, posY;
	int bmp_width ;
	int bmp_height ;
	U8 paintPos, totalPos, playerPos;
	U8 posNum;
	const STOSD_Bitmap_t *pBmp = NULL;

	totalPos = m_point*2 +pMahJong->m_Pos;
	
	/* start Pos 在左右 */

	switch(pMahJong->m_CurPosGamerId)
	{
		case 0:
			/* 画单双张，设置图片 */
			if(pMahJong->m_playerPos&0x01)
				pBmp  = NULL;
			else
				pBmp  = NULL;
			/* 调整画的坐标 */
			posX = pMahJong->m_CurPosX - 0;
			posY = pMahJong->m_CurPosY - 0;
		break;
		case 1:
			if(pMahJong->m_playerPos&0x01)
				pBmp  = NULL;
			else
				pBmp  = NULL;
			posX = pMahJong->m_CurPosX - 0;
			posY = pMahJong->m_CurPosY - 0;
		break;
		case 2:
			if(pMahJong->m_playerPos&0x01)
				pBmp  = NULL;
			else
				pBmp  = NULL;
			posX = pMahJong->m_CurPosX - 0;
			posY = pMahJong->m_CurPosY - 0;
		break;
		case 3:
			if(pMahJong->m_playerPos&0x01)
				pBmp  = NULL;
			else
				pBmp  = NULL;
			posX = pMahJong->m_CurPosX - 0;
			posY = pMahJong->m_CurPosY - 0;
		break;
	}
	drawbmp(posX, posY, (void *)pBmp);
}

void Painter::DrawHandOutCards(Gamer *pGamer)
{
	
}

void Painter::DrawHandInCards(Gamer *pGamer)
{
	
}

/* 游戏者 */
void Painter::DrawGamer(Gamer *pGamer)
{	
	int i , count;
	int posX, posY;
	int bmp_width ;
	int bmp_height ;
	const STOSD_Bitmap_t *pBmp = NULL;
	
	count = pGamer->GetHandCardsCount();
	YLOG("[Gamer%d]==CardCount == %d\n",pGamer->m_Id, count);

	switch(pGamer->m_Id)
	{
		case 0:
			
			posX = 100;
			posY = 470;
			pBmp = &Mj_inPd_s4_struct;
			bmp_width = pBmp->Width;
			bmp_height = pBmp->Height;
			for(i=0 ; i<count; i++)
			{
				drawbmp(posX+bmp_width*i, posY, (void *)pBmp);
			}
			break;
		case 1:
			posX = 660;
			posY = 440;
			pBmp = &MjCard_common_inR_struct;
			bmp_width = pBmp->Width;
			bmp_height = pBmp->Height-20;
			drawbmp(posX, posY, (void *)pBmp);
			pBmp = &MjCard_common_inRu_struct;
			posY += bmp_height;
			for(i=1 ; i<count; i++)
			{
				drawbmp(posX, posY-bmp_height*i, (void *)pBmp);
			}

			break;
		case 2:
			posX = 140;
			posY = 60;
			pBmp = &MjCard_common_inU_struct;
			bmp_width = pBmp->Width;
			bmp_height = pBmp->Height;
			for(i=0 ; i<count; i++)
			{
				drawbmp(posX+bmp_width*i, posY, (void *)pBmp);
			}

			break;
		case 3:
			posX = 60;
			posY = 100;
			pBmp = &MjCard_common_inL_struct;
			bmp_width = pBmp->Width;
			bmp_height = pBmp->Height-20;
			for(i=0 ; i<count; i++)
			{
				drawbmp(posX, posY+bmp_height*i, (void *)pBmp);
			}

			break;
	}

	DRV_OSDUpdate();
	
}

/* 玩家讲话 */
void Painter::DrawTalk(Gamer *pGamer)
{

}

/* 结算信息 */
void Painter::DrawGoldInfo()
{

}

/* 退出提示 */
void Painter::DrawDlg()
{

}

/* 提示信息 */
void Painter::DrawToolTip(Gamer *pGamer)
{

}

void Painter::BmpInit()
{
	//STOSD_Bitmap_t      *pBmp_bg;
	//checker[i++].bmp = (const STOSD_Bitmap_t*)&Mj_bg_struct;
}

void Painter::DrawChoiceMustLack(Gamer *pGamer)
{
	//drawbmp(posX+bmp_width*i, posY, (void *)pBmp);
}

void Painter::SetDrawParam(U8 banker ,U8 point)
{
	m_banker = banker;
	m_point = point;
}


#if 0

extern STOSD_Bitmap_t Mj_bg_struct;
extern STOSD_Bitmap_t Mj_info_gang_struct;
extern STOSD_Bitmap_t Mj_info_gangf_struct;
extern STOSD_Bitmap_t Mj_info_guo_struct;
extern STOSD_Bitmap_t Mj_info_guof_struct;
extern STOSD_Bitmap_t Mj_info_hu_struct;
extern STOSD_Bitmap_t Mj_info_huf_struct;
extern STOSD_Bitmap_t Mj_info_peng_struct;
extern STOSD_Bitmap_t Mj_info_pengf_struct;
extern STOSD_Bitmap_t Mj_inPd_s1_struct;
extern STOSD_Bitmap_t Mj_inPd_s2_struct;
extern STOSD_Bitmap_t Mj_inPd_s3_struct;
extern STOSD_Bitmap_t Mj_inPd_s4_struct;
extern STOSD_Bitmap_t Mj_inPd_s5_struct;
extern STOSD_Bitmap_t Mj_inPd_s6_struct;
extern STOSD_Bitmap_t Mj_inPd_s7_struct;
extern STOSD_Bitmap_t Mj_inPd_s8_struct;
extern STOSD_Bitmap_t Mj_inPd_s9_struct;
extern STOSD_Bitmap_t Mj_inPd_t1_struct;
extern STOSD_Bitmap_t Mj_inPd_t2_struct;
extern STOSD_Bitmap_t Mj_inPd_t3_struct;
extern STOSD_Bitmap_t Mj_inPd_t4_struct;
extern STOSD_Bitmap_t Mj_inPd_t5_struct;
extern STOSD_Bitmap_t Mj_inPd_t6_struct;
extern STOSD_Bitmap_t Mj_inPd_t7_struct;
extern STOSD_Bitmap_t Mj_inPd_t8_struct;
extern STOSD_Bitmap_t Mj_inPd_t9_struct;
extern STOSD_Bitmap_t Mj_inPd_w1_struct;
extern STOSD_Bitmap_t Mj_inPd_w2_struct;
extern STOSD_Bitmap_t Mj_inPd_w3_struct;
extern STOSD_Bitmap_t Mj_inPd_w4_struct;
extern STOSD_Bitmap_t Mj_inPd_w5_struct;
extern STOSD_Bitmap_t Mj_inPd_w6_struct;
extern STOSD_Bitmap_t Mj_inPd_w7_struct;
extern STOSD_Bitmap_t Mj_inPd_w8_struct;
extern STOSD_Bitmap_t Mj_inPd_w9_struct;
extern STOSD_Bitmap_t Mj_inPdo_s1_struct;
extern STOSD_Bitmap_t Mj_inPdo_s2_struct;
extern STOSD_Bitmap_t Mj_inPdo_s3_struct;
extern STOSD_Bitmap_t Mj_inPdo_s4_struct;
extern STOSD_Bitmap_t Mj_inPdo_s5_struct;
extern STOSD_Bitmap_t Mj_inPdo_s6_struct;
extern STOSD_Bitmap_t Mj_inPdo_s7_struct;
extern STOSD_Bitmap_t Mj_inPdo_s8_struct;
extern STOSD_Bitmap_t Mj_inPdo_s9_struct;
extern STOSD_Bitmap_t Mj_inPdo_t1_struct;
extern STOSD_Bitmap_t Mj_inPdo_t2_struct;
extern STOSD_Bitmap_t Mj_inPdo_t3_struct;
extern STOSD_Bitmap_t Mj_inPdo_t4_struct;
extern STOSD_Bitmap_t Mj_inPdo_t5_struct;
extern STOSD_Bitmap_t Mj_inPdo_t6_struct;
extern STOSD_Bitmap_t Mj_inPdo_t7_struct;
extern STOSD_Bitmap_t Mj_inPdo_t8_struct;
extern STOSD_Bitmap_t Mj_inPdo_t9_struct;
extern STOSD_Bitmap_t Mj_inPdo_w1_struct;
extern STOSD_Bitmap_t Mj_inPdo_w2_struct;
extern STOSD_Bitmap_t Mj_inPdo_w3_struct;
extern STOSD_Bitmap_t Mj_inPdo_w4_struct;
extern STOSD_Bitmap_t Mj_inPdo_w5_struct;
extern STOSD_Bitmap_t Mj_inPdo_w6_struct;
extern STOSD_Bitmap_t Mj_inPdo_w7_struct;
extern STOSD_Bitmap_t Mj_inPdo_w8_struct;
extern STOSD_Bitmap_t Mj_inPdo_w9_struct;
extern STOSD_Bitmap_t Mj_outHd_s1_struct;
extern STOSD_Bitmap_t Mj_outHd_s2_struct;
extern STOSD_Bitmap_t Mj_outHd_s3_struct;
extern STOSD_Bitmap_t Mj_outHd_s4_struct;
extern STOSD_Bitmap_t Mj_outHd_s5_struct;
extern STOSD_Bitmap_t Mj_outHd_s6_struct;
extern STOSD_Bitmap_t Mj_outHd_s7_struct;
extern STOSD_Bitmap_t Mj_outHd_s8_struct;
extern STOSD_Bitmap_t Mj_outHd_s9_struct;
extern STOSD_Bitmap_t Mj_outHd_t1_struct;
extern STOSD_Bitmap_t Mj_outHd_t2_struct;
extern STOSD_Bitmap_t Mj_outHd_t3_struct;
extern STOSD_Bitmap_t Mj_outHd_t4_struct;
extern STOSD_Bitmap_t Mj_outHd_t5_struct;
extern STOSD_Bitmap_t Mj_outHd_t6_struct;
extern STOSD_Bitmap_t Mj_outHd_t7_struct;
extern STOSD_Bitmap_t Mj_outHd_t8_struct;
extern STOSD_Bitmap_t Mj_outHd_t9_struct;
extern STOSD_Bitmap_t Mj_outHd_w1_struct;
extern STOSD_Bitmap_t Mj_outHd_w2_struct;
extern STOSD_Bitmap_t Mj_outHd_w3_struct;
extern STOSD_Bitmap_t Mj_outHd_w4_struct;
extern STOSD_Bitmap_t Mj_outHd_w5_struct;
extern STOSD_Bitmap_t Mj_outHd_w6_struct;
extern STOSD_Bitmap_t Mj_outHd_w7_struct;
extern STOSD_Bitmap_t Mj_outHd_w8_struct;
extern STOSD_Bitmap_t Mj_outHd_w9_struct;
extern STOSD_Bitmap_t Mj_outHl_s1_struct;
extern STOSD_Bitmap_t Mj_outHl_s2_struct;
extern STOSD_Bitmap_t Mj_outHl_s3_struct;
extern STOSD_Bitmap_t Mj_outHl_s4_struct;
extern STOSD_Bitmap_t Mj_outHl_s5_struct;
extern STOSD_Bitmap_t Mj_outHl_s6_struct;
extern STOSD_Bitmap_t Mj_outHl_s7_struct;
extern STOSD_Bitmap_t Mj_outHl_s8_struct;
extern STOSD_Bitmap_t Mj_outHl_s9_struct;
extern STOSD_Bitmap_t Mj_outHl_t1_struct;
extern STOSD_Bitmap_t Mj_outHl_t1_struct;
extern STOSD_Bitmap_t Mj_outHl_t2_struct;
extern STOSD_Bitmap_t Mj_outHl_t3_struct;
extern STOSD_Bitmap_t Mj_outHl_t4_struct;
extern STOSD_Bitmap_t Mj_outHl_t5_struct;
extern STOSD_Bitmap_t Mj_outHl_t6_struct;
extern STOSD_Bitmap_t Mj_outHl_t7_struct;
extern STOSD_Bitmap_t Mj_outHl_t8_struct;
extern STOSD_Bitmap_t Mj_outHl_t9_struct;
extern STOSD_Bitmap_t Mj_outHl_w1_struct;
extern STOSD_Bitmap_t Mj_outHl_w2_struct;
extern STOSD_Bitmap_t Mj_outHl_w3_struct;
extern STOSD_Bitmap_t Mj_outHl_w4_struct;
extern STOSD_Bitmap_t Mj_outHl_w5_struct;
extern STOSD_Bitmap_t Mj_outHl_w6_struct;
extern STOSD_Bitmap_t Mj_outHl_w7_struct;
extern STOSD_Bitmap_t Mj_outHl_w8_struct;
extern STOSD_Bitmap_t Mj_outHl_w9_struct;
extern STOSD_Bitmap_t Mj_outHr_s1_struct;
extern STOSD_Bitmap_t Mj_outHr_s2_struct;
extern STOSD_Bitmap_t Mj_outHr_s3_struct;
extern STOSD_Bitmap_t Mj_outHr_s4_struct;
extern STOSD_Bitmap_t Mj_outHr_s5_struct;
extern STOSD_Bitmap_t Mj_outHr_s6_struct;
extern STOSD_Bitmap_t Mj_outHr_s7_struct;
extern STOSD_Bitmap_t Mj_outHr_s8_struct;
extern STOSD_Bitmap_t Mj_outHr_s9_struct;
extern STOSD_Bitmap_t Mj_outHr_t1_struct;
extern STOSD_Bitmap_t Mj_outHr_t2_struct;
extern STOSD_Bitmap_t Mj_outHr_t3_struct;
extern STOSD_Bitmap_t Mj_outHr_t4_struct;
extern STOSD_Bitmap_t Mj_outHr_t5_struct;
extern STOSD_Bitmap_t Mj_outHr_t6_struct;
extern STOSD_Bitmap_t Mj_outHr_t7_struct;
extern STOSD_Bitmap_t Mj_outHr_t8_struct;
extern STOSD_Bitmap_t Mj_outHr_t9_struct;
extern STOSD_Bitmap_t Mj_outHr_w1_struct;
extern STOSD_Bitmap_t Mj_outHr_w2_struct;
extern STOSD_Bitmap_t Mj_outHr_w3_struct;
extern STOSD_Bitmap_t Mj_outHr_w4_struct;
extern STOSD_Bitmap_t Mj_outHr_w5_struct;
extern STOSD_Bitmap_t Mj_outHr_w6_struct;
extern STOSD_Bitmap_t Mj_outHr_w7_struct;
extern STOSD_Bitmap_t Mj_outHr_w8_struct;
extern STOSD_Bitmap_t Mj_outHr_w9_struct;
extern STOSD_Bitmap_t Mj_outHu_s1_struct;
extern STOSD_Bitmap_t Mj_outHu_s2_struct;
extern STOSD_Bitmap_t Mj_outHu_s3_struct;
extern STOSD_Bitmap_t Mj_outHu_s4_struct;
extern STOSD_Bitmap_t Mj_outHu_s5_struct;
extern STOSD_Bitmap_t Mj_outHu_s6_struct;
extern STOSD_Bitmap_t Mj_outHu_s7_struct;
extern STOSD_Bitmap_t Mj_outHu_s8_struct;
extern STOSD_Bitmap_t Mj_outHu_s9_struct;
extern STOSD_Bitmap_t Mj_outHu_t1_struct;
extern STOSD_Bitmap_t Mj_outHu_t2_struct;
extern STOSD_Bitmap_t Mj_outHu_t3_struct;
extern STOSD_Bitmap_t Mj_outHu_t4_struct;
extern STOSD_Bitmap_t Mj_outHu_t5_struct;
extern STOSD_Bitmap_t Mj_outHu_t6_struct;
extern STOSD_Bitmap_t Mj_outHu_t7_struct;
extern STOSD_Bitmap_t Mj_outHu_t8_struct;
extern STOSD_Bitmap_t Mj_outHu_t9_struct;
extern STOSD_Bitmap_t Mj_outHu_w1_struct;
extern STOSD_Bitmap_t Mj_outHu_w2_struct;
extern STOSD_Bitmap_t Mj_outHu_w3_struct;
extern STOSD_Bitmap_t Mj_outHu_w4_struct;
extern STOSD_Bitmap_t Mj_outHu_w5_struct;
extern STOSD_Bitmap_t Mj_outHu_w6_struct;
extern STOSD_Bitmap_t Mj_outHu_w7_struct;
extern STOSD_Bitmap_t Mj_outHu_w8_struct;
extern STOSD_Bitmap_t Mj_outHu_w9_struct;
extern STOSD_Bitmap_t MjCard_common_B2_struct;
extern STOSD_Bitmap_t MjCard_common_B6_struct;
extern STOSD_Bitmap_t MjCard_common_backH_struct;
extern STOSD_Bitmap_t MjCard_common_backV_struct;
extern STOSD_Bitmap_t MjCard_common_inL_struct;
extern STOSD_Bitmap_t MjCard_common_inR_struct;
extern STOSD_Bitmap_t MjCard_common_inU_struct;
#endif

