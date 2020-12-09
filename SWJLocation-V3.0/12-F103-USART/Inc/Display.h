/* 
* Display.h
*
* Created: 2018/8/20 1:57:09
* Author: Vulcan
*/

#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "stm32f1xx_hal.h"
#include "ssd1306.h"
#include "peripheral_init.h"

#ifdef __cplusplus
}
#endif

class Display
{
public:
	Display();
	void begin();
	void displayXYP(double, double, double);

protected:
private:
	const int time_x = 0;
	const int time_y = 0;
	//line 8
	//++++++++
	//++++++++
	//line10
	const int PWML1_x = 0;
	const int PWML1_y = 10;
	const int PWMR1_x = 64;
	const int PWMR1_y = 10;
	const int PWML2_x = 0;
	const int PWML2_y = 18;
	const int PWMR2_x = 64;
	const int PWMR2_y = 18;
	//line 26
	//++++++++
	//++++++++
	//line28
	const int X_encode_x = 0;
	const int X_encode_y = 28;
	const int Y_encode_x = 64;
	const int Y_encode_y = 28;
	const int P_encode_x = 0;
	const int P_encode_y = 36;
	//line 44
	//++++++++
	//++++++++
	//line 46
	const int X_real_x = 0;
	const int X_real_y = 46;
	const int Y_real_x = 64;
	const int Y_real_y = 46;
	const int P_real_x = 0;
	const int P_real_y = 54;
	//line 62
	//+++++++++
	//+++++++++
	//line 64
	const int Yaw_x = 0;
	const int Yaw_y = 46;
	const int Pitch_x = 64, Pitch_y = 46;
	const int Row_x = 0, Row_y = 54;

}; //Display
extern Display dp;

#endif //__DISPLAY_H__
