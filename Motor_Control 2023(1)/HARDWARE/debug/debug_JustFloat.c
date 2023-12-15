#include "debug_JustFloat.h"
#include "string.h"

const unsigned char tail[4] = {0x00, 0x00, 0x80, 0x7f};
static unsigned char sendBuf[50];
/**
  * @brief  Send data to USART4, @VOFA.exe
  * @param  debugData :address of data array
  * @param  chNum :number of data
  * @retval None
  */
void Debug_SendData(float* debugData, const uint16_t chNum)
{
	memcpy(sendBuf, debugData, 4*chNum);
	sendBuf[4*chNum] = 0x00;
	sendBuf[4*chNum+1] = 0x00;
	sendBuf[4*chNum+2] = 0x80;
	sendBuf[4*chNum+3] = 0x7F;
	USART1_SendString(sendBuf, 4*chNum+4);
}
