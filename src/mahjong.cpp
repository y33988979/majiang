#include "mahjong.h"
#include <stdlib.h>
#include <time.h>

static char *MJ_typeStr[] = {"万", "条", "筒"};
static char *MJ_valueStr[] = {"一", "二", "三", "四", "五", "六", "七", "八", "九"};

MahJong::MahJong()
{
	int     i,j,k;
	int     index;
	char *str = NULL;
	for(i=0; i<3; i++)
	{
		for(j=0; j<4; j++)
		{
			for(k=0; k<9; k++)
			{
				index = i*9*4+j*9+k;
				/* type: 万条筒 */	
				this->m_Mj[index].type = i;
				/* Val: 数值(1~9) */
				this->m_Mj[index].value = k+1;
				/* Val: 索引(1~108) */
				this->m_Mj[index].index = index;
				/* 赋值名字 */
				setCardName(&m_Mj[index]);
			}
		}
	}

	
	bmpInit();
	printAll();
	
	m_Banker = 0;
	m_Count = MJ_MAX_NUM;
	m_Pos = 0;
	
}

MahJong::~MahJong()
{
	m_Banker = 0;
	m_Count = MJ_MAX_NUM;
	m_Pos = 0;
}

void MahJong::setCardName(MjCard_t *pCard)
{
	U8      type, value;
	char  *typeStr = NULL;
	char  *valueStr = NULL;
	
	type = pCard->type;
	value = pCard->value;
	
	typeStr = MJ_typeStr[type];
	valueStr = MJ_valueStr[value-1];

	memset(pCard->name, 0, sizeof(pCard->name));
	sprintf(pCard->name, "%s%s",  valueStr, typeStr);
}

void MahJong::shuffle()
{
	int   RandNum;
	MjCard_t  tmp;
	srand( (unsigned)time(NULL) );
	
	for (int i = 0; i < MJ_MAX_NUM; ++i)  
	{  
	    RandNum = rand() % MJ_MAX_NUM;  
	  
	    tmp = m_Mj[i];  
	    m_Mj[i] = m_Mj[RandNum];  
	    m_Mj[RandNum] = tmp;  
	}  
}

void MahJong::printAll()
{
	int i,j,k;
	int index;

	YLOG(" ====start====\n");
	for(i=0; i<3; i++)
	{
		for(j=0; j<4; j++)
		{
			for(k=0; k<9; k++)
			{
				index = i*9*4+j*9+k;
				YLOG("%d] %s ", index, m_Mj[index].name);
			}
			YLOG(" \n");
		}
		YLOG(" -----------------------------\n");
	}
	YLOG(" ====end====\n");
}

void MahJong::PosUpdate()
{
	int i , Surplus;
	int bmp_width ;
	int bmp_height ;
	U8 paintPos,totalPos;
	U8 posNum;

	totalPos = m_DiceNum*2 +m_Pos;
	/* start Pos 在左右 */
	if(m_Banker % 2)
	{
		if(totalPos > 26*2+28*2)  /* 13 */
		{
			m_playerPos = totalPos - 26*2+28*2;
			m_CurPosGamerId = (m_Banker+2)%4;
		}
		else if(totalPos > 26*2+28)  /* 14 */
		{
			m_playerPos = totalPos - 26*2+28;
			m_CurPosGamerId = (m_Banker+1)%4;
		}
		else if(totalPos > 26+28)  /* 13 */
		{
			m_playerPos = totalPos - 26+28;
			m_CurPosGamerId = m_Banker;
		}
		else if(totalPos > 26)  /* 14 */
		{
			m_playerPos = totalPos - 26;
			m_CurPosGamerId = (m_Banker+3)%4;
		}
	}
	else
	{
		if(totalPos > 26*2+28*2)  /* 14 */
		{
			m_playerPos = totalPos - 26*2+28*22;
			m_CurPosGamerId = (m_Banker+2)%4;
		}
		else if(totalPos > 28*2+26)  /* 13 */
		{
			m_playerPos = totalPos - 28*2+26;
			m_CurPosGamerId = (m_Banker+1)%4;
		}
		else if(totalPos > 26+28)  /* 14 */
		{
			m_playerPos = totalPos - 26+28;
			m_CurPosGamerId = m_Banker;
		}
		else if(totalPos > 28)  /* 13 */
		{
			m_playerPos = totalPos - 26;
			m_CurPosGamerId = (m_Banker+3)%4;
		}
	}

	/* set current pos */
	if(m_CurPosGamerId == 0)
	{
		m_CurPosX = 500-m_playerPos*40;
		m_CurPosY = 430;
	}
	else if(m_CurPosGamerId == 1)
	{
		m_CurPosX = 550;
		m_CurPosY = 120+m_playerPos*30;
	}
	else if(m_CurPosGamerId== 2)
	{
		m_CurPosX = 170+m_playerPos*40;
		m_CurPosY = 100;
	}
	else if(m_CurPosGamerId== 3)
	{
		m_CurPosX = 140;
		m_CurPosY = 350-m_playerPos*30;
	}
}

void MahJong::dec(U8  n)
{
	m_Pos += n;
}


U8 MahJong::GetSurplus()
{
	return m_Count - m_Pos;
}

void MahJong::SetParam(U8 banker ,U8 diceNum)
{
	m_DiceNum  = diceNum;
	m_Banker = banker;
}

void MahJong::bmpInit()
{
	int i = 0;
	
	//m_Mj[i++].bmp = (void *)&MjCard_common_inR_struct;
	//m_Mj[i++].bmp = (void *)&MjCard_common_inR_struct;
}

