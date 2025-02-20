#include "./BSP/BH1750/bh1750.h"
/**************************************************************************
 * 文件名  ：bh1750.c
 * 描述    ：光强传感模块     
****************************************************************************/

#include "./SYSTEM/delay/delay.h"


uchar    BUF[8];               //接收数据缓存区  
int   mcy;     //进位标志

/***开始信号***/
void BH1750_Start()
{
  HAL_GPIO_WritePin(bh1750_PORT,sda,GPIO_PIN_SET);                    //拉高数据线
  HAL_GPIO_WritePin(bh1750_PORT,scl,GPIO_PIN_SET);                   //拉高时钟线
  delay_us(5);                 //延时
   HAL_GPIO_WritePin(bh1750_PORT,sda,GPIO_PIN_RESET);                    //产生下降沿
  delay_us(5);                 //延时
   HAL_GPIO_WritePin(bh1750_PORT,scl,GPIO_PIN_RESET);                    //拉低时钟线
}

/*****停止信号******/
void BH1750_Stop()
{
    HAL_GPIO_WritePin(bh1750_PORT,sda,GPIO_PIN_RESET);                   //拉低数据线
    HAL_GPIO_WritePin(bh1750_PORT,scl,GPIO_PIN_SET);                      //拉高时钟线
    delay_us(5);                 //延时
    HAL_GPIO_WritePin(bh1750_PORT,sda,GPIO_PIN_SET);                    //产生上升沿
    delay_us(5);                 //延时
}

/**************************************
发送应答信号
入口参数:ack (0:ACK 1:NAK)
**************************************/
void BH1750_SendACK(int ack)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;  
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Pull = GPIO_PULLUP;                    /* 上拉 */
  GPIO_InitStruct.Pin = sda;
  HAL_GPIO_Init(bh1750_PORT, &GPIO_InitStruct);  
	
	if(ack == 1)   //写应答信号
		HAL_GPIO_WritePin(bh1750_PORT,sda,GPIO_PIN_SET); 
	else if(ack == 0)
		HAL_GPIO_WritePin(bh1750_PORT,sda,GPIO_PIN_RESET); 
	else
		return;			
  HAL_GPIO_WritePin(bh1750_PORT,scl,GPIO_PIN_SET);     //拉高时钟线
  delay_us(5);                 //延时
  HAL_GPIO_WritePin(bh1750_PORT,scl,GPIO_PIN_RESET);      //拉低时钟线
  delay_us(5);                //延时
}

/**************************************
接收应答信号
**************************************/
int BH1750_RecvACK()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.Mode=GPIO_MODE_INPUT;  /*这里一定要设成输入上拉，否则不能读出数据*/
	GPIO_InitStruct.Pull = GPIO_PULLUP;                        /* 上拉 */
  GPIO_InitStruct.Speed=GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Pin=sda;
  HAL_GPIO_Init(bh1750_PORT,&GPIO_InitStruct);
	
  HAL_GPIO_WritePin(bh1750_PORT,scl,GPIO_PIN_SET);            //拉高时钟线
  delay_us(5);                 //延时	
	if(HAL_GPIO_ReadPin(GPIOA,sda)==1)//读应答信号
    mcy = 1 ;  
  else
    mcy = 0 ;				
  HAL_GPIO_WritePin(bh1750_PORT,scl,GPIO_PIN_RESET);                    //拉低时钟线
  delay_us(5);                 //延时
  GPIO_InitStruct.Mode=GPIO_MODE_OUTPUT_PP;
  HAL_GPIO_Init(bh1750_PORT,&GPIO_InitStruct);
	return mcy;
}

/**************************************
向IIC总线发送一个字节数据
**************************************/
void BH1750_SendByte(uchar dat)
{
  uchar i;
  for (i=0; i<8; i++)         //8位计数器
  {
		if( 0X80 & dat )
      HAL_GPIO_WritePin(bh1750_PORT,sda,GPIO_PIN_SET);
    else
      HAL_GPIO_WritePin(bh1750_PORT,sda,GPIO_PIN_RESET);
		dat <<= 1;
    HAL_GPIO_WritePin(bh1750_PORT,scl,GPIO_PIN_SET);               //拉高时钟线
    delay_us(5);             //延时
    HAL_GPIO_WritePin(bh1750_PORT,scl,GPIO_PIN_RESET);                //拉低时钟线
    delay_us(5);            //延时
  }
  BH1750_RecvACK();
}

uchar BH1750_RecvByte()
{
  uchar i;
  uchar dat = 0;
	uchar bit;
	
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;   /*这里一定要设成输入上拉，否则不能读出数据*/
	GPIO_InitStruct.Pull = GPIO_PULLUP;                        /* 上拉 */
  GPIO_InitStruct.Pin = sda;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(bh1750_PORT,&GPIO_InitStruct );
	
  HAL_GPIO_WritePin(bh1750_PORT,sda,GPIO_PIN_SET);          //使能内部上拉,准备读取数据,
  for (i=0; i<8; i++)         //8位计数器
  {
    dat <<= 1;
    HAL_GPIO_WritePin(bh1750_PORT,scl,GPIO_PIN_SET);               //拉高时钟线
    delay_us(5);             //延时
			
		if( SET == HAL_GPIO_ReadPin(bh1750_PORT,sda))
      bit = 0X01;
    else
      bit = 0x00;  
		dat |= bit;             //读数据    
		HAL_GPIO_WritePin(bh1750_PORT,scl,GPIO_PIN_RESET);                //拉低时钟线
    delay_us(5);            //延时
  }		
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  HAL_GPIO_Init(bh1750_PORT, &GPIO_InitStruct );
  return dat;
}

void Single_Write_BH1750(uchar REG_Address)
{
  BH1750_Start();                  //起始信号
  BH1750_SendByte(SlaveAddress);   //发送设备地址+写信号
  BH1750_SendByte(REG_Address);    //内部寄存器地址，请参考中文pdf22页 
//  BH1750_SendByte(REG_data);       //内部寄存器数据，请参考中文pdf22页 
  BH1750_Stop();                   //发送停止信号
}

//初始化BH1750，根据需要请参考pdf进行修改****
void Init_BH1750()
{
  GPIO_InitTypeDef GPIO_InitStruct;
	 /*开启GPIOB的外设时钟*/ 
	__HAL_RCC_GPIOB_CLK_ENABLE(); 
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;  
  GPIO_InitStruct.Pull = GPIO_PULLUP;                    /* 上拉 */
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Pin = sda | scl ;
  HAL_GPIO_Init(bh1750_PORT,&GPIO_InitStruct); 
	
  Single_Write_BH1750(0x01);  
	delay_ms(180);            //延时180ms
}

//连续读出BH1750内部数据
void mread(void)
{   
	uchar i;	
  BH1750_Start();                          //起始信号
  BH1750_SendByte(SlaveAddress+1);         //发送设备地址+读信号
	
	for (i=0; i<3; i++)                      //连续读取6个地址数据，存储中BUF
  {
    BUF[i] = BH1750_RecvByte();          //BUF[0]存储0x32地址中的数据
    if (i == 3)
    {
      BH1750_SendACK(1);                //最后一个数据需要回NOACK
    }
    else
    {		
      BH1750_SendACK(0);                //回应ACK
    }
  }
  BH1750_Stop();                          //停止信号
  delay_ms(5);
}

float read_BH1750(void)
{
  int dis_data;                       //变量	
	float temp1;
	float temp2;
	Single_Write_BH1750(0x01);   // power on
  Single_Write_BH1750(0x10);   // H- resolution mode
  delay_ms(180);            //延时180ms
	mread();       //连续读出数据，存储在BUF中
  dis_data=BUF[0];
  dis_data=(dis_data<<8)+BUF[1]; //合成数据 
	temp1=dis_data/1.2;
	temp2=10*dis_data/1.2;	
	temp2=(int)temp2%10;
	return temp1;
}



