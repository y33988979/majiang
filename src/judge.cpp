#include "judge.h"

Judge::Judge()
{

}

Judge::~Judge()
{

}

MjCard_t* Judge::PutCardThinking(Gamer *pCurGamer)
{
	int i,j;
	Gamer  *pGamer = NULL;
	MjCard_t *pPutCard = NULL;
	list_t *pList = NULL;
	
	//pGamer = GetNextGamer(pCurGamer);

	pPutCard = FindCardForCanTing(pCurGamer); 
	YLOG("FindCardForCanTing done!\n");
	if(pPutCard != NULL)
	{
		return pPutCard;
	}
	
	pPutCard = ChoosePutCard(pCurGamer);

	return pPutCard;
	
}

MjCard_t* Judge::ChoosePutCard(Gamer *pGamer)
{
	list_t m_MjList[3];
	MjCard_t  *pCard = NULL;
	MjCard_t  *pPutCard = NULL;
	int i, count, priority;

	CardListToArray(pGamer, m_PAI);

	for(i=1; !m_PAI[i]&&i<31; i++); 
	
	pCard = pGamer->GetFirstHandCard();
	while(pCard != NULL)
	{
		pCard->priority = 0;
		i = pCard->type*10 + pCard->value;
		if(m_PAI[i] == 4)
			pCard->priority = 0;
		else if(m_PAI[i] == 3)
			pCard->priority = 1;
		else if(m_PAI[i] == 2)
			pCard->priority = 2;

		/* 检查顺子 */
		if(  (i%10 != 8)   &&   (i%10 != 9)   && 
			m_PAI[i+1]   &&   m_PAI[i+2] )              
		{    
			pCard->priority = 5;                            
		}
		else if(  (i%10 == 8) && m_PAI[i-1] && m_PAI[i+1])              
		{    
			pCard->priority = 5;                            
		}
		else if(  (i%10 == 9) && m_PAI[i-1] && m_PAI[i-2])  
		{    
			pCard->priority = 5;                            
		}
		/* 隔一张有牌 */
 		else if(  (i%10 != 8)   &&   (i%10 != 9)   && m_PAI[i+2])  
		{    
			pCard->priority = 6;                            
		}
		else if(  (i%10 != 1)   &&   (i%10 != 2)   && m_PAI[i-2])  
		{    
			pCard->priority = 6;                            
		}
		else if(  (i%10 == 2)  && m_PAI[i+2])  
		{    
			pCard->priority = 6;                            
		}
		else if(  (i%10 == 8)  && m_PAI[i-2])  
		{    
			pCard->priority = 6;                            
		}
		
		pCard = pGamer->GetNextHandCard();
	}

	/* 找到优先级最高的 */
	priority = 10;
	pCard = pGamer->GetFirstHandCard();
	pPutCard = pCard;
	while(pCard != NULL)
	{
		if(priority < pCard->priority)
		{
			priority = pCard->priority;	
			pPutCard = pCard;
		}
		pCard = pGamer->GetNextHandCard();
	}
	
	return pPutCard;
}


#if 0
Judge::m_PAI[30] = { 0, 
                 1,1,1,0,1,1,1,0,0,     // PA[ 1- 9]   壹万～玖万的个数 
                 0, 
                 0,0,0,0,0,3,0,0,0,     // PA[11-19]   壹条～玖条的个数
                 0, 
                 0,0,0,0,0,0,0,0,0     // PA[21-29]    壹铜～玖铜的个数 
                 }; 
#endif

int Judge::CardListToArray(Gamer *pGamer, int *PAI)
{
	int i, index;
	MjCard_t  *pCard = NULL;

	memset(PAI, 0, sizeof(CARD_KIND_MAX));

	/* 遍历手牌，填入数组 */
	pCard = pGamer->GetFirstHandCard();
	while(pCard != NULL)
	{
		index = pCard->type*10 + pCard->value;
		PAI[index]++;
		pCard = pGamer->GetNextHandCard();
		YLOG("PAI[index] = %d\n", index);
	}
}

MjCard_t* Judge::FindCardForCanTing(Gamer *pGamer)
{
	int i,index;
	int count;
	MjCard_t  *pCard = NULL;
	int CardBackUp[CARD_KIND_MAX];

	CardListToArray(pGamer, m_PAI);
	memcpy(CardBackUp, m_PAI, sizeof(CARD_KIND_MAX));

	pCard = pGamer->GetFirstHandCard();
	while(pCard != NULL)
	{
		index = pCard->type*10 + pCard->value;
		/* 去掉一张牌 ，用其他牌替换它*/
		m_PAI[index]--;
		for(i=1 ;i<CARD_KIND_MAX; i++)
		{
			m_PAI[i]++;
			/* 如果返回真，打这张可以听牌 */
			if(IsHu(m_PAI))
			{
				return pCard;
			}
			m_PAI[i]--;
		}
		m_PAI[index]++;
		
		pCard = pGamer->GetNextHandCard();
	}

	return NULL;
		
}
int Judge::IsHu(int *PAI)    
{    
	int   i;
	static int   JIANG = 0;                            /*   将牌标志，即牌型“三三三三二”中的“二”    */   
 	
	if(!Remain(PAI) )   return 1;                 /*   递归退出条件：如果没有剩牌，则和牌返回。    */
 	
	for(i=1; !PAI[i]&&i<31; i++);                 /*   找到有牌的地方，i就是当前牌,   PAI[i]是个数    */
	
	printf("i   =   %d\n",i);                            

	/*   4张组合(杠子)    */
	if(PAI[i] == 4)                                       /*   如果当前牌数等于4张    */
	{    
		PAI[i] = 0;                                      /*   除开全部4张牌    */
		if( IsHu(PAI) )   return 1;                   /*   如果剩余的牌组合成功，和牌    */
		PAI[i] = 4;                                      /*   否则，取消4张组合  */  
	}    

	/*   3张组合(大对)    */
	if( PAI[i] >= 3 )                                     /*   如果当前牌不少于3张   */ 
	{    
		PAI[i] -= 3;                                    /*   减去3张牌    */
		if( IsHu(PAI) )   return 1;                  /*   如果剩余的牌组合成功，和牌 */   
		PAI[i] += 3;                                   /*   取消3张组合    */
	}    

	/*   2张组合(将牌)    */
	if( !JIANG  &&  PAI[i] >= 2 )                   /*   如果之前没有将牌，且当前牌不少于2张   */ 
	{     
		JIANG = 1;                                      /*  设置将牌标志    */
		PAI[i] -= 2;                                    /*   减去2张牌    */
		if( IsHu(PAI) )   return 1;                   /*   如果剩余的牌组合成功，和牌    */
		PAI[i] += 2;                                    /*   取消2张组合    */
		JIANG = 0;                                      /*   清除将牌标志    */
	}    

	/*   顺牌组合，注意是从前往后组合！    */
	if(  (i%10 != 8)   &&   (i%10 != 9)   &&    /*   排除数值为8和9的牌    */
		PAI[i+1]   &&   PAI[i+2]   )              /*   如果后面有连续两张牌    */
	{    
	  	/*   各牌数减1    */
		PAI[i]--;    
		PAI[i+1]--;    
		PAI[i+2]--;                                   
		
		if( IsHu(PAI) )   return   1;              /*   如果剩余的牌组合成功，和牌    */
		PAI[i]++;    
		PAI[i+1]++;    
		PAI[i+2]++;                                 /*   恢复各牌数    */
	}    

	return   0;                                          /*   无法全部组合，不胡！    */
}    

/*   检查剩余牌数    */
int  Judge::Remain(int *PAI)    
{    
	int  i, sum = 0;    
	
	for(i=1;i<31;i++)    
		sum += PAI[i];    
	return sum;    
}




#if 0

//========================================================
 // 把一副牌放在下面的数组里，可以任意填入数字来测试函数正确与否。 
 // 为了方便，PAI[0],PAI[10],PAI[20],PAI[30]都弃之不用，并且必须 
 // 置为0，千万注意！ 
 int PAI[38] = { 0, 
                 1,1,1,0,1,1,1,0,0,     // PAI[ 1- 9]   壹万～玖万的个数 
                 0, 
                 0,0,0,0,0,3,0,0,0,     // PAI[11-19]   壹铜～玖铜的个数 
                 0, 
                 0,0,0,0,0,0,0,0,0,     // PAI[21-29]   壹条～玖条的个数 
                 0, 
                 0,1,1,1,0,0,0          // PAI[31-37]   东南西北中发白的个数 
                 }; 

 // 请务必先排除“七对” 和“十三幺”，由于简单，所以不提供了 
 // if( QIDUI(PAI) )... 
 // if( SHISANYAO(PAI) )... 

int Hu1(int PAI[38])    
{    
	int   i;
	static int   JIANG = 0;                            /*   将牌标志，即牌型“三三三三二”中的“二”    */   
 	
	if(!Remain(PAI) )   return 1;                 /*   递归退出条件：如果没有剩牌，则和牌返回。    */
 	
	for(i=1; !PAI[i]&&i<38; i++);                 /*   找到有牌的地方，i就是当前牌,   PAI[i]是个数    */
	
	printf("i   =   %d\n",i);                            

	/*   4张组合(杠子)    */
	if(PAI[i] == 4)                                       /*   如果当前牌数等于4张    */
	{    
		PAI[i] = 0;                                      /*   除开全部4张牌    */
		if( Hu(PAI) )   return 1;                   /*   如果剩余的牌组合成功，和牌    */
		PAI[i] = 4;                                      /*   否则，取消4张组合  */  
	}    

	/*   3张组合(大对)    */
	if( PAI[i] >= 3 )                                     /*   如果当前牌不少于3张   */ 
	{    
		PAI[i] -= 3;                                    /*   减去3张牌    */
		if( Hu(PAI) )   return 1;                  /*   如果剩余的牌组合成功，和牌 */   
		PAI[i] += 3;                                   /*   取消3张组合    */
	}    

	/*   2张组合(将牌)    */
	if( !JIANG  &&  PAI[i] >= 2 )                   /*   如果之前没有将牌，且当前牌不少于2张   */ 
	{     
		JIANG = 1;                                      /*  设置将牌标志    */
		PAI[i] -= 2;                                    /*   减去2张牌    */
		if( Hu(PAI) )   return 1;                   /*   如果剩余的牌组合成功，和牌    */
		PAI[i] += 2;                                    /*   取消2张组合    */
		JIANG = 0;                                      /*   清除将牌标志    */
	}    


	if   ( i > 30 )     return 0;                        /*   “东南西北中发白”没有顺牌组合，不和 */   

	/*   顺牌组合，注意是从前往后组合！    */
	if(  (i%10 != 8)   &&   (i%10 != 9)   &&    /*   排除数值为8和9的牌    */
		PAI[i+1]   &&   PAI[i+2]   )              /*   如果后面有连续两张牌    */
	{    
	  	/*   各牌数减1    */
		PAI[i]--;    
		PAI[i+1]--;    
		PAI[i+2]--;                                   
		
		if( Hu(PAI) )   return   1;              /*   如果剩余的牌组合成功，和牌    */
		PAI[i]++;    
		PAI[i+1]++;    
		PAI[i+2]++;                                 /*   恢复各牌数    */
	}    

	return   0;                                          /*   无法全部组合，不胡！    */
}    

/*   检查剩余牌数    */
int   Remain1(int   PAI[38])    
{    
	int  i, sum = 0;    
	
	for(i=1;i<38;i++)    
		sum += PAI[i];    
	return sum;    
}

#endif



