#ifndef __IIC_H
#define __IIC_H
#include "stm32f30x.h"



//IO�ڲ����궨��
#define BitBand_ADDR(addr)	(*((volatile unsigned long *)(addr)))

//IO�ڵ�ַӳ��
#define GPIOA_ODR_Addr    (GPIOA_BASE+0x14) //0x48000014
#define GPIOB_ODR_Addr    (GPIOB_BASE+0x14) //0x48000414 
#define GPIOC_ODR_Addr    (GPIOC_BASE+0x14) //0x48000814 
#define GPIOD_ODR_Addr    (GPIOD_BASE+0x14) //0x48000C14 
#define GPIOE_ODR_Addr    (GPIOE_BASE+0x14) //0x48001014 
#define GPIOF_ODR_Addr    (GPIOF_BASE+0x14) //0x48001414     

#define GPIOA_IDR_Addr    (GPIOA_BASE+0x10) //0x4001080A 
#define GPIOB_IDR_Addr    (GPIOB_BASE+0x10) //0x40010C0A 
#define GPIOC_IDR_Addr    (GPIOC_BASE+0x10) //0x4001100A 
#define GPIOD_IDR_Addr    (GPIOD_BASE+0x10) //0x4001140A 
#define GPIOE_IDR_Addr    (GPIOE_BASE+0x10) //0x4001180A 
#define GPIOF_IDR_Addr    (GPIOF_BASE+0x10) //0x40011A0A 

//���, sΪ 0~1, nȡ 0~31
#define PBout(n,s)		(s?(BitBand_ADDR(GPIOB_ODR_Addr)|=(1<<n)):(BitBand_ADDR(GPIOB_ODR_Addr)&=(~(1<<n)))) 
//���� 
#define PBin(n)			((BitBand_ADDR(GPIOB_IDR_Addr)&(1<<n))>>n)  
   	   		   
////�����ӿڣ�GPIOģ��IIC
//SCL-->PB6
//SDA-->PB7
#define SDA_IN()  {GPIOB->MODER=0x1000;GPIOB->PUPDR=0x4000;}//��������
#define SDA_OUT() {GPIOB->MODER=0x5000;GPIOB->OTYPER=(1<<7);GPIOB->OSPEEDR=0xC000;}//��©���50MHz


//IO��������	 
#define IIC_SCL(s)		PBout(6,s) //SCL
#define IIC_SDA(s)		PBout(7,s) //SDA	 
#define READ_SDA		PBin(7)  //����SDA 

//IIC���в�������
void IIC_Init(void);          //��ʼ��IIC��IO��				 
void IIC_Start(void);			   	//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(uint8_t txd);			//IIC����һ���ֽ�
uint8_t IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
uint8_t IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�

void IIC_Write_One_Byte(uint8_t daddr,uint8_t addr,uint8_t data);
uint8_t IIC_Read_One_Byte(uint8_t daddr,uint8_t addr);	 
unsigned char I2C_Readkey(unsigned char I2C_Addr);

unsigned char I2C_ReadOneByte(unsigned char I2C_Addr,unsigned char addr);
unsigned char IICwriteByte(unsigned char dev, unsigned char reg, unsigned char data);
uint8_t IICwriteBytes(uint8_t dev, uint8_t reg, uint8_t length, uint8_t* data);
uint8_t IICwriteBits(uint8_t dev,uint8_t reg,uint8_t bitStart,uint8_t length,uint8_t data);
uint8_t IICwriteBit(uint8_t dev,uint8_t reg,uint8_t bitNum,uint8_t data);
uint8_t IICreadBytes(uint8_t dev, uint8_t reg, uint8_t length, uint8_t *data);

#endif

//------------------End of File----------------------------







