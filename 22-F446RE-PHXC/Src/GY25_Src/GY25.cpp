#include "GY25.h"

GY25 gy25(USART1, USART1_IRQn);

GY25::GY25(USART_TypeDef *USARTx, IRQn_Type USARTx_IRQn)
{
    this->USARTx = USARTx;
    this->USARTx_IRQn = USARTx_IRQn;
}

GY25::~GY25()
{
}

void GY25::begin()
{
    //开启USART所用gpio
    USART_gpio_init();
    //开启串口通信
    USART_begin();
    //
    correctYaw();
    HAL_Delay(3000);
    autoMode();
}

void GY25::USART_begin()
{
    //开时钟
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);

    //USARTx外设配置
    LL_USART_InitTypeDef USART_InitStruct = {0};
    USART_InitStruct.BaudRate = 115200;
    USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
    USART_InitStruct.Parity = LL_USART_PARITY_NONE;
    USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
    USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
    LL_USART_Init(USARTx, &USART_InitStruct);
    LL_USART_Enable(USARTx);

    //使能中断
    LL_USART_EnableIT_RXNE(USARTx);
    NVIC_SetPriority(USARTx_IRQn, NVIC_EncodePriority(0, 2, 1));
    NVIC_EnableIRQ(USARTx_IRQn);
}

void GY25::USART_gpio_init()
{
    //开GPIOB时钟
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);

    //GPIO配置
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Alternate = LL_GPIO_AF_7;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pin = LL_GPIO_PIN_6 | LL_GPIO_PIN_7;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;
    LL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void GY25::USART_send(uint8_t data)
{
    while (!LL_USART_IsActiveFlag_TXE(USARTx))
    {
    }
    LL_USART_TransmitData8(USARTx, data);
}

void GY25::autoMode()
{
    USART_send(0XA5);
    USART_send(0X52);
}

void GY25::autoModeASCII()
{
    USART_send(0XA5);
    USART_send(0X53);
}

void GY25::singleMode()
{
    USART_send(0XA5);
    USART_send(0X51);
}

void GY25::correctPitchRow()
{
    USART_send(0XA5);
    USART_send(0X54);
}

void GY25::correctYaw()
{
    USART_send(0XA5);
    USART_send(0X55);
}

void GY25::refresh()
{
    Re_buf[counter] = LL_USART_ReceiveData8(USARTx);
    if (counter == 0 && Re_buf[0] != 0xAA)
        return; // 检查帧头
    counter++;
    if (counter == 8) //接收到数据
    {
        counter = 0; //重新赋值，准备下一帧数据的接收
        sign = 1;
    }
    if (sign == 1)
    {
        if (Re_buf[0] == 0xAA && Re_buf[7] == 0x55) //检查帧头，帧尾
        {
            YPR[0] = int16_t(Re_buf[1] << 8 | Re_buf[2]) / 100.00; //合成数据，去掉小数点后2位
            YPR[1] = int16_t(Re_buf[3] << 8 | Re_buf[4]) / 100.00;
            YPR[2] = int16_t(Re_buf[5] << 8 | Re_buf[6]) / 100.00;
        }
        sign = 0;
    }
}

void USART1_IRQHandler(void)
{
    if (LL_USART_IsActiveFlag_RXNE(USART1))
    {
        gy25.refresh();
        LL_USART_ClearFlag_RXNE(USART1);
    }
}