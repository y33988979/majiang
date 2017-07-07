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

		/* ���˳�� */
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
		/* ��һ������ */
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

	/* �ҵ����ȼ���ߵ� */
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
                 1,1,1,0,1,1,1,0,0,     // PA[ 1- 9]   Ҽ�򡫾���ĸ��� 
                 0, 
                 0,0,0,0,0,3,0,0,0,     // PA[11-19]   Ҽ���������ĸ���
                 0, 
                 0,0,0,0,0,0,0,0,0     // PA[21-29]    Ҽͭ����ͭ�ĸ��� 
                 }; 
#endif

int Judge::CardListToArray(Gamer *pGamer, int *PAI)
{
	int i, index;
	MjCard_t  *pCard = NULL;

	memset(PAI, 0, sizeof(CARD_KIND_MAX));

	/* �������ƣ��������� */
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
		/* ȥ��һ���� �����������滻��*/
		m_PAI[index]--;
		for(i=1 ;i<CARD_KIND_MAX; i++)
		{
			m_PAI[i]++;
			/* ��������棬�����ſ������� */
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
	static int   JIANG = 0;                            /*   ���Ʊ�־�������͡��������������еġ�����    */   
 	
	if(!Remain(PAI) )   return 1;                 /*   �ݹ��˳����������û��ʣ�ƣ�����Ʒ��ء�    */
 	
	for(i=1; !PAI[i]&&i<31; i++);                 /*   �ҵ����Ƶĵط���i���ǵ�ǰ��,   PAI[i]�Ǹ���    */
	
	printf("i   =   %d\n",i);                            

	/*   4�����(����)    */
	if(PAI[i] == 4)                                       /*   �����ǰ��������4��    */
	{    
		PAI[i] = 0;                                      /*   ����ȫ��4����    */
		if( IsHu(PAI) )   return 1;                   /*   ���ʣ�������ϳɹ�������    */
		PAI[i] = 4;                                      /*   ����ȡ��4�����  */  
	}    

	/*   3�����(���)    */
	if( PAI[i] >= 3 )                                     /*   �����ǰ�Ʋ�����3��   */ 
	{    
		PAI[i] -= 3;                                    /*   ��ȥ3����    */
		if( IsHu(PAI) )   return 1;                  /*   ���ʣ�������ϳɹ������� */   
		PAI[i] += 3;                                   /*   ȡ��3�����    */
	}    

	/*   2�����(����)    */
	if( !JIANG  &&  PAI[i] >= 2 )                   /*   ���֮ǰû�н��ƣ��ҵ�ǰ�Ʋ�����2��   */ 
	{     
		JIANG = 1;                                      /*  ���ý��Ʊ�־    */
		PAI[i] -= 2;                                    /*   ��ȥ2����    */
		if( IsHu(PAI) )   return 1;                   /*   ���ʣ�������ϳɹ�������    */
		PAI[i] += 2;                                    /*   ȡ��2�����    */
		JIANG = 0;                                      /*   ������Ʊ�־    */
	}    

	/*   ˳����ϣ�ע���Ǵ�ǰ������ϣ�    */
	if(  (i%10 != 8)   &&   (i%10 != 9)   &&    /*   �ų���ֵΪ8��9����    */
		PAI[i+1]   &&   PAI[i+2]   )              /*   �������������������    */
	{    
	  	/*   ��������1    */
		PAI[i]--;    
		PAI[i+1]--;    
		PAI[i+2]--;                                   
		
		if( IsHu(PAI) )   return   1;              /*   ���ʣ�������ϳɹ�������    */
		PAI[i]++;    
		PAI[i+1]++;    
		PAI[i+2]++;                                 /*   �ָ�������    */
	}    

	return   0;                                          /*   �޷�ȫ����ϣ�������    */
}    

/*   ���ʣ������    */
int  Judge::Remain(int *PAI)    
{    
	int  i, sum = 0;    
	
	for(i=1;i<31;i++)    
		sum += PAI[i];    
	return sum;    
}




#if 0

//========================================================
 // ��һ���Ʒ����������������������������������Ժ�����ȷ��� 
 // Ϊ�˷��㣬PAI[0],PAI[10],PAI[20],PAI[30]����֮���ã����ұ��� 
 // ��Ϊ0��ǧ��ע�⣡ 
 int PAI[38] = { 0, 
                 1,1,1,0,1,1,1,0,0,     // PAI[ 1- 9]   Ҽ�򡫾���ĸ��� 
                 0, 
                 0,0,0,0,0,3,0,0,0,     // PAI[11-19]   Ҽͭ����ͭ�ĸ��� 
                 0, 
                 0,0,0,0,0,0,0,0,0,     // PAI[21-29]   Ҽ���������ĸ��� 
                 0, 
                 0,1,1,1,0,0,0          // PAI[31-37]   ���������з��׵ĸ��� 
                 }; 

 // ��������ų����߶ԡ� �͡�ʮ���ۡ������ڼ򵥣����Բ��ṩ�� 
 // if( QIDUI(PAI) )... 
 // if( SHISANYAO(PAI) )... 

int Hu1(int PAI[38])    
{    
	int   i;
	static int   JIANG = 0;                            /*   ���Ʊ�־�������͡��������������еġ�����    */   
 	
	if(!Remain(PAI) )   return 1;                 /*   �ݹ��˳����������û��ʣ�ƣ�����Ʒ��ء�    */
 	
	for(i=1; !PAI[i]&&i<38; i++);                 /*   �ҵ����Ƶĵط���i���ǵ�ǰ��,   PAI[i]�Ǹ���    */
	
	printf("i   =   %d\n",i);                            

	/*   4�����(����)    */
	if(PAI[i] == 4)                                       /*   �����ǰ��������4��    */
	{    
		PAI[i] = 0;                                      /*   ����ȫ��4����    */
		if( Hu(PAI) )   return 1;                   /*   ���ʣ�������ϳɹ�������    */
		PAI[i] = 4;                                      /*   ����ȡ��4�����  */  
	}    

	/*   3�����(���)    */
	if( PAI[i] >= 3 )                                     /*   �����ǰ�Ʋ�����3��   */ 
	{    
		PAI[i] -= 3;                                    /*   ��ȥ3����    */
		if( Hu(PAI) )   return 1;                  /*   ���ʣ�������ϳɹ������� */   
		PAI[i] += 3;                                   /*   ȡ��3�����    */
	}    

	/*   2�����(����)    */
	if( !JIANG  &&  PAI[i] >= 2 )                   /*   ���֮ǰû�н��ƣ��ҵ�ǰ�Ʋ�����2��   */ 
	{     
		JIANG = 1;                                      /*  ���ý��Ʊ�־    */
		PAI[i] -= 2;                                    /*   ��ȥ2����    */
		if( Hu(PAI) )   return 1;                   /*   ���ʣ�������ϳɹ�������    */
		PAI[i] += 2;                                    /*   ȡ��2�����    */
		JIANG = 0;                                      /*   ������Ʊ�־    */
	}    


	if   ( i > 30 )     return 0;                        /*   �����������з��ס�û��˳����ϣ����� */   

	/*   ˳����ϣ�ע���Ǵ�ǰ������ϣ�    */
	if(  (i%10 != 8)   &&   (i%10 != 9)   &&    /*   �ų���ֵΪ8��9����    */
		PAI[i+1]   &&   PAI[i+2]   )              /*   �������������������    */
	{    
	  	/*   ��������1    */
		PAI[i]--;    
		PAI[i+1]--;    
		PAI[i+2]--;                                   
		
		if( Hu(PAI) )   return   1;              /*   ���ʣ�������ϳɹ�������    */
		PAI[i]++;    
		PAI[i+1]++;    
		PAI[i+2]++;                                 /*   �ָ�������    */
	}    

	return   0;                                          /*   �޷�ȫ����ϣ�������    */
}    

/*   ���ʣ������    */
int   Remain1(int   PAI[38])    
{    
	int  i, sum = 0;    
	
	for(i=1;i<38;i++)    
		sum += PAI[i];    
	return sum;    
}

#endif



