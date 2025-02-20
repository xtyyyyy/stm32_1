#include "./BSP/BH1750/bh1750.h"
/**************************************************************************
 * �ļ���  ��bh1750.c
 * ����    ����ǿ����ģ��     
****************************************************************************/

#include "./SYSTEM/delay/delay.h"


uchar    BUF[8];               //�������ݻ�����  
int   mcy;     //��λ��־

/***��ʼ�ź�***/
void BH1750_Start()
{
  HAL_GPIO_WritePin(bh1750_PORT,sda,GPIO_PIN_SET);                    //����������
  HAL_GPIO_WritePin(bh1750_PORT,scl,GPIO_PIN_SET);                   //����ʱ����
  delay_us(5);                 //��ʱ
   HAL_GPIO_WritePin(bh1750_PORT,sda,GPIO_PIN_RESET);                    //�����½���
  delay_us(5);                 //��ʱ
   HAL_GPIO_WritePin(bh1750_PORT,scl,GPIO_PIN_RESET);                    //����ʱ����
}

/*****ֹͣ�ź�******/
void BH1750_Stop()
{
    HAL_GPIO_WritePin(bh1750_PORT,sda,GPIO_PIN_RESET);                   //����������
    HAL_GPIO_WritePin(bh1750_PORT,scl,GPIO_PIN_SET);                      //����ʱ����
    delay_us(5);                 //��ʱ
    HAL_GPIO_WritePin(bh1750_PORT,sda,GPIO_PIN_SET);                    //����������
    delay_us(5);                 //��ʱ
}

/**************************************
����Ӧ���ź�
��ڲ���:ack (0:ACK 1:NAK)
**************************************/
void BH1750_SendACK(int ack)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;  
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Pull = GPIO_PULLUP;                    /* ���� */
  GPIO_InitStruct.Pin = sda;
  HAL_GPIO_Init(bh1750_PORT, &GPIO_InitStruct);  
	
	if(ack == 1)   //дӦ���ź�
		HAL_GPIO_WritePin(bh1750_PORT,sda,GPIO_PIN_SET); 
	else if(ack == 0)
		HAL_GPIO_WritePin(bh1750_PORT,sda,GPIO_PIN_RESET); 
	else
		return;			
  HAL_GPIO_WritePin(bh1750_PORT,scl,GPIO_PIN_SET);     //����ʱ����
  delay_us(5);                 //��ʱ
  HAL_GPIO_WritePin(bh1750_PORT,scl,GPIO_PIN_RESET);      //����ʱ����
  delay_us(5);                //��ʱ
}

/**************************************
����Ӧ���ź�
**************************************/
int BH1750_RecvACK()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.Mode=GPIO_MODE_INPUT;  /*����һ��Ҫ������������������ܶ�������*/
	GPIO_InitStruct.Pull = GPIO_PULLUP;                        /* ���� */
  GPIO_InitStruct.Speed=GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Pin=sda;
  HAL_GPIO_Init(bh1750_PORT,&GPIO_InitStruct);
	
  HAL_GPIO_WritePin(bh1750_PORT,scl,GPIO_PIN_SET);            //����ʱ����
  delay_us(5);                 //��ʱ	
	if(HAL_GPIO_ReadPin(GPIOA,sda)==1)//��Ӧ���ź�
    mcy = 1 ;  
  else
    mcy = 0 ;				
  HAL_GPIO_WritePin(bh1750_PORT,scl,GPIO_PIN_RESET);                    //����ʱ����
  delay_us(5);                 //��ʱ
  GPIO_InitStruct.Mode=GPIO_MODE_OUTPUT_PP;
  HAL_GPIO_Init(bh1750_PORT,&GPIO_InitStruct);
	return mcy;
}

/**************************************
��IIC���߷���һ���ֽ�����
**************************************/
void BH1750_SendByte(uchar dat)
{
  uchar i;
  for (i=0; i<8; i++)         //8λ������
  {
		if( 0X80 & dat )
      HAL_GPIO_WritePin(bh1750_PORT,sda,GPIO_PIN_SET);
    else
      HAL_GPIO_WritePin(bh1750_PORT,sda,GPIO_PIN_RESET);
		dat <<= 1;
    HAL_GPIO_WritePin(bh1750_PORT,scl,GPIO_PIN_SET);               //����ʱ����
    delay_us(5);             //��ʱ
    HAL_GPIO_WritePin(bh1750_PORT,scl,GPIO_PIN_RESET);                //����ʱ����
    delay_us(5);            //��ʱ
  }
  BH1750_RecvACK();
}

uchar BH1750_RecvByte()
{
  uchar i;
  uchar dat = 0;
	uchar bit;
	
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;   /*����һ��Ҫ������������������ܶ�������*/
	GPIO_InitStruct.Pull = GPIO_PULLUP;                        /* ���� */
  GPIO_InitStruct.Pin = sda;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(bh1750_PORT,&GPIO_InitStruct );
	
  HAL_GPIO_WritePin(bh1750_PORT,sda,GPIO_PIN_SET);          //ʹ���ڲ�����,׼����ȡ����,
  for (i=0; i<8; i++)         //8λ������
  {
    dat <<= 1;
    HAL_GPIO_WritePin(bh1750_PORT,scl,GPIO_PIN_SET);               //����ʱ����
    delay_us(5);             //��ʱ
			
		if( SET == HAL_GPIO_ReadPin(bh1750_PORT,sda))
      bit = 0X01;
    else
      bit = 0x00;  
		dat |= bit;             //������    
		HAL_GPIO_WritePin(bh1750_PORT,scl,GPIO_PIN_RESET);                //����ʱ����
    delay_us(5);            //��ʱ
  }		
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  HAL_GPIO_Init(bh1750_PORT, &GPIO_InitStruct );
  return dat;
}

void Single_Write_BH1750(uchar REG_Address)
{
  BH1750_Start();                  //��ʼ�ź�
  BH1750_SendByte(SlaveAddress);   //�����豸��ַ+д�ź�
  BH1750_SendByte(REG_Address);    //�ڲ��Ĵ�����ַ����ο�����pdf22ҳ 
//  BH1750_SendByte(REG_data);       //�ڲ��Ĵ������ݣ���ο�����pdf22ҳ 
  BH1750_Stop();                   //����ֹͣ�ź�
}

//��ʼ��BH1750��������Ҫ��ο�pdf�����޸�****
void Init_BH1750()
{
  GPIO_InitTypeDef GPIO_InitStruct;
	 /*����GPIOB������ʱ��*/ 
	__HAL_RCC_GPIOB_CLK_ENABLE(); 
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;  
  GPIO_InitStruct.Pull = GPIO_PULLUP;                    /* ���� */
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Pin = sda | scl ;
  HAL_GPIO_Init(bh1750_PORT,&GPIO_InitStruct); 
	
  Single_Write_BH1750(0x01);  
	delay_ms(180);            //��ʱ180ms
}

//��������BH1750�ڲ�����
void mread(void)
{   
	uchar i;	
  BH1750_Start();                          //��ʼ�ź�
  BH1750_SendByte(SlaveAddress+1);         //�����豸��ַ+���ź�
	
	for (i=0; i<3; i++)                      //������ȡ6����ַ���ݣ��洢��BUF
  {
    BUF[i] = BH1750_RecvByte();          //BUF[0]�洢0x32��ַ�е�����
    if (i == 3)
    {
      BH1750_SendACK(1);                //���һ��������Ҫ��NOACK
    }
    else
    {		
      BH1750_SendACK(0);                //��ӦACK
    }
  }
  BH1750_Stop();                          //ֹͣ�ź�
  delay_ms(5);
}

float read_BH1750(void)
{
  int dis_data;                       //����	
	float temp1;
	float temp2;
	Single_Write_BH1750(0x01);   // power on
  Single_Write_BH1750(0x10);   // H- resolution mode
  delay_ms(180);            //��ʱ180ms
	mread();       //�����������ݣ��洢��BUF��
  dis_data=BUF[0];
  dis_data=(dis_data<<8)+BUF[1]; //�ϳ����� 
	temp1=dis_data/1.2;
	temp2=10*dis_data/1.2;	
	temp2=(int)temp2%10;
	return temp1;
}



