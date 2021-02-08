#include "HC08.h"

HC08 hc08;

HC08::HC08(/* args */)
{
}

HC08::~HC08()
{
}

void HC08::begin()
{
    USART_init();

    gpio_init();

    DMA_init();
}

void HC08::USART_init()
{
    //开USART外设时钟
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART3);

    LL_USART_InitTypeDef USART_InitStruct = {0};
    USART_InitStruct.BaudRate = 115200;
    USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
    USART_InitStruct.Parity = LL_USART_PARITY_NONE;
    USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
    USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
    LL_USART_Init(USART3, &USART_InitStruct);

    LL_USART_Enable(USART3);
}

void HC08::gpio_init()
{
    /**USART3 GPIO Configuration    
    PC10     ------> USART3_TX
    PC11     ------> USART3_RX 
    */

    //开GPIOB时钟
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);

    //GPIO配置
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Alternate = LL_GPIO_AF_7;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pin = LL_GPIO_PIN_10 | LL_GPIO_PIN_11;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;
    LL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

void HC08::DMA_init()
{
    LL_USART_EnableDMAReq_RX(USART3);

    //开启DMA时钟
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);

    //选择连接的通道
    LL_DMA_SetChannelSelection(DMA1, LL_DMA_STREAM_1, LL_DMA_CHANNEL_4);
    //设置通道优先级
    LL_DMA_SetStreamPriorityLevel(DMA1, LL_DMA_STREAM_1, LL_DMA_PRIORITY_HIGH);

    //设置源地址
    LL_DMA_SetPeriphAddress(DMA1, LL_DMA_STREAM_1, (uint32_t)(&USART3->DR));
    //设置源带宽
    LL_DMA_SetPeriphSize(DMA1, LL_DMA_STREAM_1, LL_DMA_PDATAALIGN_BYTE);

    //设置目标地址
    LL_DMA_SetMemoryAddress(DMA1, LL_DMA_STREAM_1, (uint32_t)receive_buffer);
    //目标地址自增
    LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_STREAM_1, LL_DMA_MEMORY_INCREMENT);
    //设置外设带宽
    LL_DMA_SetMemorySize(DMA1, LL_DMA_STREAM_1, LL_DMA_MDATAALIGN_BYTE);

    //设置数据传输方向
    LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_STREAM_1, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
    //设置传输数量
    LL_DMA_SetDataLength(DMA1, LL_DMA_STREAM_1, 3);

    //使能传输完成中断
    LL_DMA_EnableIT_TC(DMA1, LL_DMA_STREAM_1);
    //在NVIC使能中断
    HAL_NVIC_SetPriority(DMA1_Stream1_IRQn, 1, 2);
    HAL_NVIC_EnableIRQ(DMA1_Stream1_IRQn);

    //开启循环模式
    LL_DMA_SetMode(DMA1,LL_DMA_STREAM_1,LL_DMA_MODE_CIRCULAR);
    //使能DMA
    LL_DMA_EnableStream(DMA1, LL_DMA_STREAM_1);
}

void HC08::send(float pitch, float speed)
{
    int16_t _pitch = pitch * 100;
    int32_t _speed = speed * 100;

    uint8_t data[8] = {0xAA,
                       _pitch >> 8,
                       _pitch & 0Xff,
                       (_speed >> 24) & 0Xff,
                       (_speed >> 16) & 0Xff,
                       (_speed >> 8) & 0Xff,
                       (_speed)&0Xff,
                       0x55};

    for (size_t i = 0; i < 8; i++)
    {
        while (!LL_USART_IsActiveFlag_TXE(USART3))
        {
        }
        LL_USART_TransmitData8(USART3, data[i]);
    }
}

float HC08::getKp()
{
    return kp;
}

float HC08::getKi()
{
    return ki;
}

float HC08::getKd()
{
    return kd;
}

float HC08::getTarget_Angle()
{
    return Target_Angle;
}

void HC08::buffer_process()
{
    switch (hc08.receive_buffer[0])
    {
    case kp_buffer_header:
        kp = int16_t(hc08.receive_buffer[1] << 8 | hc08.receive_buffer[2]);
        kp /=100; 
        break;
    case ki_buffer_header:
        ki = int16_t(hc08.receive_buffer[1] << 8 | hc08.receive_buffer[2]);
        ki /=100; 
        break;
    case kd_buffer_header:
        kd = int16_t(hc08.receive_buffer[1] << 8 | hc08.receive_buffer[2]);
        kd /=100; 
        break;
    case Target_Angle_buffer_header:
        Target_Angle = int16_t(hc08.receive_buffer[1] << 8 | hc08.receive_buffer[2]);
        Target_Angle /= 100;
        break;
    default:
        break;
    }
}

void DMA1_Stream1_IRQHandler()
{
    //清空传输完成标志位
    LL_DMA_ClearFlag_TC1(DMA1);

    hc08.buffer_process();
}