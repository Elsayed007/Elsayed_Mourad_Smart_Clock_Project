//Letzte Änderung 17.12.2019 09:10

#include "string.h"
#include "smartclock.h"
#include "stdlib.h"

/*Variablen*/






uint8_t MODE = MODE_TIME;
uint8_t INTERLUDE = TRUE;
uint8_t RST = TRUE;
uint8_t SWITCH = 1;

uint8_t B_PLUS = 1;
uint8_t B_SET = 1;
uint8_t TIMER_POS = 0;
uint8_t ALARM_POS = 0;
uint8_t TICK = FALSE;
uint8_t ALARM_ST =0;

TIME_TIMER_STOPWATCH TIMER = {0};
TIME_TIMER_STOPWATCH STOPWATCH = {0};

DS3231_ALARM ALARM1 = {0};
DS3231_ALARM ALARM2 = {0};

uint8_t NUMBERS[10][9]={	
							{Bit1|Bit2|Bit3|Bit4|Bit5,Bit1|Bit5,Bit1|Bit2|Bit3|Bit4|Bit5,0,0,0,0,0,2},			// 0 Breite 3
							{Bit2|Bit5,Bit1|Bit2|Bit3|Bit4|Bit5,Bit5,0,0,0,0,0,2},													// 1 Breite 3
							{Bit1|Bit3|Bit4|Bit5,Bit1|Bit3|Bit5,Bit1|Bit2|Bit3|Bit5,0,0,0,0,0,2},						// 2 Breite 3
							{Bit1|Bit3|Bit5,Bit1|Bit3|Bit5,Bit1|Bit2|Bit3|Bit4|Bit5,0,0,0,0,0,2},						// 3 Breite 3
							{Bit1|Bit2|Bit3,Bit3,Bit1|Bit2|Bit3|Bit4|Bit5,0,0,0,0,0,2},											// 4 Breite 3
							{Bit1|Bit2|Bit3|Bit5,Bit1|Bit3|Bit5,Bit1|Bit3|Bit4|Bit5,0,0,0,0,0,2},						// 5 Breite 3
							{Bit1|Bit2|Bit3|Bit4|Bit5,Bit1|Bit3|Bit5,Bit1|Bit3|Bit4|Bit5,0,0,0,0,0,2},			// 6 Breite 3
							{Bit1,Bit1,Bit1|Bit2|Bit3|Bit4|Bit5,0,0,0,0,0,2},																// 7 Breite 3
							{Bit1|Bit2|Bit3|Bit4|Bit5,Bit1|Bit3|Bit5,Bit1|Bit2|Bit3|Bit4|Bit5,0,0,0,0,0,2},	// 8 Breite 3
							{Bit1|Bit2|Bit3,Bit1|Bit3,Bit1|Bit2|Bit3|Bit4|Bit5,0,0,0,0,0,2}									// 9 Breite 3
};				
uint8_t ASCII[128][9]={	{0,0,0,0,0,0,0,0,0},																																			//NUL[0]	 Breite 1
												{0,0,0,0,0,0,0,0,0},																																			//SOH[1] -
												{0,0,0,0,0,0,0,0,0},																																			//STX[2] -
												{0,0,0,0,0,0,0,0,0},																																			//ETX[3] -
												{0,0,0,0,0,0,0,0,0},																																			//EOT[4] -
												{0,0,0,0,0,0,0,0,0},																																			//ENQ[5] -
												{0,0,0,0,0,0,0,0,0},																																			//ACK[6] -
												{0,0,0,0,0,0,0,0,0},																																			//BEL[7] -
												{0,0,0,0,0,0,0,0,0},																																			//BS [8] -
												{0,0,0,0,0,0,0,0,0},																																			//TAB[9] -
												{0,0,0,0,0,0,0,0,0},																																			//LF [10] -
												{0,0,0,0,0,0,0,0,0},																																			//VT [11] -
												{0,0,0,0,0,0,0,0,0},																																			//FF [12] -
												{0,0,0,0,0,0,0,0,0},																																			//CR [13] -
												{0,0,0,0,0,0,0,0,0},																																			//SO [14] -
												{0,0,0,0,0,0,0,0,0},																																			//SI [15] -
												{0,0,0,0,0,0,0,0,0},																																			//DLE[16] -
												{0,0,0,0,0,0,0,0,0},																																			//DC1[17] -
												{0,0,0,0,0,0,0,0,0},																																			//DC2[18] -
												{0,0,0,0,0,0,0,0,0},																																			//DC3[19] -
												{0,0,0,0,0,0,0,0,0},																																			//DC4[20] - 
												{0,0,0,0,0,0,0,0,0},																																			//NAK[21] - 
												{0,0,0,0,0,0,0,0,0},																																			//SYN[22] - 
												{0,0,0,0,0,0,0,0,0},																																			//ETB[23] -
												{0,0,0,0,0,0,0,0,0},																																			//CAN[24] - 
												{0,0,0,0,0,0,0,0,0},																																			//EM [25] -
												{0,0,0,0,0,0,0,0,0},																																			//SUB[26] -
												{0,0,0,0,0,0,0,0,0},																																			//ESC[27] -
												{0,0,0,0,0,0,0,0,0},																																			//FS [28]	-										
												{0,0,0,0,0,0,0,0,0},																																			//GS [29] -
												{0,0,0,0,0,0,0,0,0},																																			//RS [30] -
												{0,0,0,0,0,0,0,0,0},																																			//US [31] -
												
												{0,0,0,0,0,0,0,0,0},																																			//SPACE[32]	Breite 1 
												{Bit1|Bit2|Bit3|Bit5,0,0,0,0,0,0,0,0},																										//!  [33]		Breite 1
												{Bit1,0,Bit1,0,0,0,0,0,2},																																//"  [34]		Breite 3
												{Bit2|Bit4,Bit1|Bit2|Bit3|Bit4|Bit5,Bit2|Bit4,Bit1|Bit2|Bit3|Bit4|Bit5,Bit2|Bit4,0,0,0,4},//#	 [35]		Breite 5
												{0,0,0,0,0,0,0,0,0},																																			//   [36] - 
												{Bit1|Bit2|Bit5,Bit1|Bit2|Bit4,Bit3,Bit2|Bit4|Bit5,Bit1|Bit4|Bit5,0,0,0,4},								//%  [37]		Breite 5
												{0,0,0,0,0,0,0,0,0},																																			//   [38] - 
												{Bit1|Bit2,0,0,0,0,0,0,0,0},																															//'  [39]		Breite 1
												{Bit2|Bit3|Bit4,Bit1|Bit5,0,0,0,0,0,0,1},																									//(  [40]		Breite 2
												{Bit1|Bit5,Bit2|Bit3|Bit4,0,0,0,0,0,0,1},																									//)  [41]		Breite 2
												{0,0,0,0,0,0,0,0,0},																																			//   [42] - 
												{Bit3,Bit2|Bit3|Bit4,Bit3,0,0,0,0,2},																											//+  [43]		Breite 3
												{Bit4|Bit5,0,0,0,0,0,0,0,0},																															//,  [44]		Breite 1
												{Bit3,Bit3,Bit3,0,0,0,0,0,2},																															//-  [45]		Breite 3
												{Bit5,0,0,0,0,0,0,0,0},																																		//.  [46]		Breite 1
												{Bit5,Bit2|Bit3|Bit4,Bit1,0,0,0,0,0,2},																										///  [47]		Breite 3
												
	

												{Bit1|Bit2|Bit3|Bit4|Bit5,Bit1|Bit5,Bit1|Bit2|Bit3|Bit4|Bit5,0,0,0,0,0,2},								//0  [48]		Breite 3
												{Bit2|Bit5,Bit1|Bit2|Bit3|Bit4|Bit5,Bit5,0,0,0,0,0,2},																		//1  [49]		Breite 3
												{Bit1|Bit3|Bit4|Bit5,Bit1|Bit3|Bit5,Bit1|Bit2|Bit3|Bit5,0,0,0,0,0,2},											//2  [50]		Breite 3
												{Bit1|Bit3|Bit5,Bit1|Bit3|Bit5,Bit1|Bit2|Bit3|Bit4|Bit5,0,0,0,0,0,2},											//3  [51]		Breite 3
												{Bit1|Bit2|Bit3,Bit3,Bit1|Bit2|Bit3|Bit4|Bit5,0,0,0,0,0,2},																//4  [52]		Breite 3
												{Bit1|Bit2|Bit3|Bit5,Bit1|Bit3|Bit5,Bit1|Bit3|Bit4|Bit5,0,0,0,0,0,2},											//5  [53]		Breite 3
												{Bit1|Bit2|Bit3|Bit4|Bit5,Bit1|Bit3|Bit5,Bit1|Bit3|Bit4|Bit5,0,0,0,0,0,2},								//6  [54]		Breite 3
												{Bit1,Bit1,Bit1|Bit2|Bit3|Bit4|Bit5,0,0,0,0,0,2},																					//7  [55]		Breite 3
												{Bit1|Bit2|Bit3|Bit4|Bit5,Bit1|Bit3|Bit5,Bit1|Bit2|Bit3|Bit4|Bit5,0,0,0,0,0,2},						//8  [56]		Breite 3
												{Bit1|Bit2|Bit3|Bit5,Bit1|Bit3|Bit5,Bit1|Bit2|Bit3|Bit4|Bit5,0,0,0,0,0,2},								//9  [57]		Breite 3
												
												{Bit2|Bit4,0,0,0,0,0,0,0},																																//:  [58]		Breite 1 
												{Bit2|Bit4|Bit5,0,0,0,0,0,0,0},																														//;  [59]		Breite 1
												{Bit3,Bit2|Bit4,0,0,0,0,0,0,1},																														//<  [60] 	Breite 2
												{Bit3,Bit2|Bit3|Bit4,Bit3,0,0,0,0,0,2},																										//=  [61]		Breite 3
												{Bit2|Bit4,Bit3,0,0,0,0,0,1},																															//>  [62] 	Breite 2
												{Bit1,Bit1|Bit3|Bit5,Bit1|Bit2|Bit3,0,0,0,0,0,2},																					//?  [63]		Breite 3
												{Bit1|Bit2,Bit1|Bit2,Bit3|Bit4,Bit2|Bit5,Bit2|Bit5,0,0,0,4},															//°C [64]		Breite 5
												
												{Bit1|Bit2|Bit3|Bit4|Bit5,Bit1|Bit3,Bit2|Bit3|Bit4|Bit5,0,0,0,0,0,2},											//A  [65]		Breite 3
												{Bit1|Bit2|Bit3|Bit4|Bit5,Bit1|Bit3|Bit5,Bit2|Bit3|Bit4,0,0,0,0,0,2},											//B  [66]		Breite 3
												{Bit1|Bit2|Bit3|Bit4|Bit5,Bit1|Bit5,Bit1|Bit5,0,0,0,0,0,2},																//C  [67]		Breite 3
												{Bit1|Bit2|Bit3|Bit4|Bit5,Bit1|Bit5,Bit2|Bit3|Bit4,0,0,0,0,0,2},													//D  [68]		Breite 3
												{Bit1|Bit2|Bit3|Bit4|Bit5,Bit1|Bit3|Bit5,Bit1|Bit3|Bit5,0,0,0,0,0,2},											//E  [69]		Breite 3
												{Bit1|Bit2|Bit3|Bit4|Bit5,Bit1|Bit3,Bit1,0,0,0,0,0,2},																		//F  [70]		Breite 3
												{Bit2|Bit3|Bit4,Bit1|Bit5,Bit1|Bit3|Bit4|Bit5,0,0,0,0,0,2},																//G  [71]		Breite 3
												{Bit1|Bit2|Bit3|Bit4|Bit5,Bit3,Bit1|Bit2|Bit3|Bit4|Bit5,0,0,0,0,0,2},											//H  [72]		Breite 3
												{Bit1|Bit2|Bit3|Bit4|Bit5,0,0,0,0,0,0,0,0},																								//I  [73]		Breite 1
												{Bit4|Bit5,Bit5,Bit1|Bit2|Bit3|Bit4|Bit5,0,0,0,0,0,2},																		//J  [74]		Breite 3
												{Bit1|Bit2|Bit3|Bit4|Bit5,Bit3,Bit1|Bit2|Bit4|Bit5,0,0,0,0,0,2},													//K  [75]		Breite 3
												{Bit1|Bit2|Bit3|Bit4|Bit5,Bit5,Bit5,0,0,0,0,0,2},																					//L  [76]		Breite 3
												{Bit1|Bit2|Bit3|Bit4|Bit5,Bit2|Bit3,Bit3|Bit4,Bit2|Bit3,Bit1|Bit2|Bit3|Bit4|Bit5,0,0,0,4},//M  [77]		Breite 5
												{Bit1|Bit2|Bit3|Bit4|Bit5,Bit2,Bit3,Bit1|Bit2|Bit3|Bit4|Bit5,0,0,0,0,3},									//N  [78]		Breite 4
												{Bit1|Bit2|Bit3|Bit4|Bit5,Bit1|Bit5,Bit1|Bit2|Bit3|Bit4|Bit5,0,0,0,0,0,2},								//O  [79]		Breite 3
												{Bit1|Bit2|Bit3|Bit4|Bit5,Bit1|Bit3,Bit1|Bit2|Bit3,0,0,0,0,0,2},													//P  [80]		Breite 3
												{Bit1|Bit2|Bit3|Bit4|Bit5,Bit1|Bit5,Bit1|Bit2|Bit3|Bit4|Bit5,Bit5,0,0,0,0,3},							//Q  [81]		Breite 4
												{Bit1|Bit2|Bit3|Bit4|Bit5,Bit1|Bit3|Bit4,Bit1|Bit2|Bit3|Bit5,0,0,0,0,0,2},								//R  [82]		Breite 3
												{Bit1|Bit2|Bit3|Bit5,Bit1|Bit3|Bit5,Bit1|Bit3|Bit4|Bit5,0,0,0,0,0,2},											//S  [83]		Breite 3
												{Bit1,Bit1|Bit2|Bit3|Bit4|Bit5,Bit1,0,0,0,0,0,2},																					//T  [84]		Breite 3
												{Bit1|Bit2|Bit3|Bit4|Bit5,Bit5,Bit1|Bit2|Bit3|Bit4|Bit5,0,0,0,0,0,2},											//U  [85]		Breite 3
												{Bit1|Bit2|Bit3|Bit4,Bit5,Bit1|Bit2|Bit3|Bit4,0,0,0,0,0,2},																//V  [86]		Breite 3
												{Bit1|Bit2|Bit3|Bit4,Bit5,Bit4,Bit5,Bit1|Bit2|Bit3|Bit4,0,0,0,4},													//W  [87]		Breite 5
												{Bit1|Bit2|Bit4|Bit5,Bit2|Bit3|Bit4,Bit1|Bit2|Bit4|Bit5,0,0,0,0,0,2},											//X  [88]		Breite 3
												{Bit1|Bit2|Bit3|Bit5,Bit3|Bit5,Bit1|Bit2|Bit3|Bit4,0,0,0,0,0,2},													//Y  [89]		Breite 3
												{Bit1|Bit4|Bit5,Bit1|Bit3|Bit5,Bit1|Bit2|Bit5,0,0,0,0,0,2},																//Z  [90]		Breite 3
												
												{Bit1|Bit2|Bit3|Bit4|Bit5,Bit1|Bit5,0,0,0,0,0,0,1},																				//[  [91]		Breite 2																	
												{Bit1,Bit2|Bit3|Bit4,Bit5,0,0,0,0,0,2},																										//\  [92]		Breite 3
												{Bit1|Bit5,Bit1|Bit2|Bit3|Bit4|Bit5,0,0,0,0,0,0,1},																				//]  [93]		Breite 2
												{Bit2,Bit1,Bit2,0,0,0,0,0,2},																															//^  [94]		Breite 3						
												{Bit5,Bit5,Bit5,0,0,0,0,0,2},																															//_  [95]		Breite 3												
												{Bit1|Bit2,0,0,0,0,0,0,0,0},																															//'  [96]		Breite 1
												
												{Bit1|Bit2|Bit3|Bit4|Bit5,Bit1|Bit3,Bit2|Bit3|Bit4|Bit5,0,0,0,0,0,2},											//A  [97]		Breite 3
												{Bit1|Bit2|Bit3|Bit4|Bit5,Bit1|Bit3|Bit5,Bit2|Bit3|Bit4,0,0,0,0,0,2},											//B  [98]		Breite 3
												{Bit1|Bit2|Bit3|Bit4|Bit5,Bit1|Bit5,Bit1|Bit5,0,0,0,0,0,2},																//C  [99]		Breite 3
												{Bit1|Bit2|Bit3|Bit4|Bit5,Bit1|Bit5,Bit2|Bit3|Bit4,0,0,0,0,0,2},													//D  [100]	Breite 3
												{Bit1|Bit2|Bit3|Bit4|Bit5,Bit1|Bit3|Bit5,Bit1|Bit3|Bit5,0,0,0,0,0,2},											//E  [101]	Breite 3
												{Bit1|Bit2|Bit3|Bit4|Bit5,Bit1|Bit3,Bit1,0,0,0,0,0,2},																		//F  [102]	Breite 3
												{Bit2|Bit3|Bit4,Bit1|Bit5,Bit1|Bit3|Bit4|Bit5,0,0,0,0,0,2},																//G  [103]	Breite 3
												{Bit1|Bit2|Bit3|Bit4|Bit5,Bit3,Bit1|Bit2|Bit3|Bit4|Bit5,0,0,0,0,0,2},											//H  [104]	Breite 3
												{Bit1|Bit2|Bit3|Bit4|Bit5,0,0,0,0,0,0,0,0},																								//I  [105]	Breite 1
												{Bit4|Bit5,Bit5,Bit1|Bit2|Bit3|Bit4|Bit5,0,0,0,0,0,2},																		//J  [106]	Breite 3
												{Bit1|Bit2|Bit3|Bit4|Bit5,Bit3,Bit1|Bit2|Bit4|Bit5,0,0,0,0,0,2},													//K  [107]	Breite 3
												{Bit1|Bit2|Bit3|Bit4|Bit5,Bit5,Bit5,0,0,0,0,0,2},																					//L  [108]	Breite 3
												{Bit1|Bit2|Bit3|Bit4|Bit5,Bit2|Bit3,Bit3|Bit4,Bit2|Bit3,Bit1|Bit2|Bit3|Bit4|Bit5,0,0,0,4},//M  [109]	Breite 5
												{Bit1|Bit2|Bit3|Bit4|Bit5,Bit2,Bit3,Bit1|Bit2|Bit3|Bit4|Bit5,0,0,0,0,3},									//N  [110]	Breite 4
												{Bit1|Bit2|Bit3|Bit4|Bit5,Bit1|Bit5,Bit1|Bit2|Bit3|Bit4|Bit5,0,0,0,0,0,2},								//O  [111]	Breite 3
												{Bit1|Bit2|Bit3|Bit4|Bit5,Bit1|Bit3,Bit1|Bit2|Bit3,0,0,0,0,0,2},													//P  [112]	Breite 3
												{Bit1|Bit2|Bit3|Bit4|Bit5,Bit1|Bit5,Bit1|Bit2|Bit3|Bit4|Bit5,Bit5,0,0,0,0,3},							//Q  [113]	Breite 4
												{Bit1|Bit2|Bit3|Bit4|Bit5,Bit1|Bit3|Bit4,Bit1|Bit2|Bit3|Bit5,0,0,0,0,0,2},								//R  [114]	Breite 3
												{Bit1|Bit2|Bit3|Bit5,Bit1|Bit3|Bit5,Bit1|Bit3|Bit4|Bit5,0,0,0,0,0,2},											//S  [115]	Breite 3
												{Bit1,Bit1|Bit2|Bit3|Bit4|Bit5,Bit1,0,0,0,0,0,2},																					//T  [116]	Breite 3
												{Bit1|Bit2|Bit3|Bit4|Bit5,Bit5,Bit1|Bit2|Bit3|Bit4|Bit5,0,0,0,0,0,2},											//U  [117]	Breite 3
												{Bit1|Bit2|Bit3|Bit4,Bit5,Bit1|Bit2|Bit3|Bit4,0,0,0,0,0,2},																//V  [118]	Breite 3
												{Bit1|Bit2|Bit3|Bit4,Bit5,Bit4,Bit5,Bit1|Bit2|Bit3|Bit4,0,0,0,4},													//W  [119]	Breite 5
												{Bit1|Bit2|Bit4|Bit5,Bit2|Bit3|Bit4,Bit1|Bit2|Bit4|Bit5,0,0,0,0,0,2},											//X  [120]	Breite 3
												{Bit1|Bit2|Bit3|Bit5,Bit3|Bit5,Bit1|Bit2|Bit3|Bit4,0,0,0,0,0,2},													//Y  [121]	Breite 3
												{Bit1|Bit4|Bit5,Bit1|Bit3|Bit5,Bit1|Bit2|Bit5,0,0,0,0,0,2},																//Z  [122]	Breite 3
												
												{Bit2|Bit3|Bit4,Bit1|Bit5,0,0,0,0,0,0,1},																									//{  [123]	Breite 2						
												{Bit1|Bit2|Bit3|Bit4|Bit5,0,0,0,0,0,0,0,0},																								//|  [124]	Breite 1
												{Bit2|Bit3|Bit4,Bit1|Bit5,0,0,0,0,0,0,1},																									//}  [125]	Breite 2
												{0,0,0,0,0,0,0,0,0},																																			//	 [126] -
												{0,0,0,0,0,0,0,0,0},																																			//DEL[127] -
};	

char WEEKDAYS[7][4] = {"MON","TUE","WED","THU","FRI","SAT","SUN"};
char MONTHS[12][4] = {"JAN","FEB","MAR","APR","MAY","JUN","JUL","AUG","SEP","OCT","NOV","DEC"};

uint8_t RGB_PATTERN[8][RGB_COMS][RGB_ROWS/3]=	{			
											
											{{BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK},
											{BLACK,BLACK,BLACK,RED,RED,BLACK,BLACK,BLACK},
											{BLACK,BLACK,RED,RED,RED,RED,BLACK,BLACK},
											{BLACK,RED,RED,RED,RED,RED,RED,BLACK},
											{RED,RED,RED,RED,RED,RED,RED,RED},
											{BLACK,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,BLACK},
											{BLACK,WHITE,ORANGE,WHITE,WHITE,BLUE,WHITE,BLACK},
											{BLACK,WHITE,ORANGE,WHITE,WHITE,WHITE,WHITE,BLACK},},				//house -> inside temperature display
																								
											{{BLACK,BLACK,BLACK,YELLOW,BLACK,BLACK,BLACK,BLACK},
											{BLACK,BLACK,BLACK,YELLOW,YELLOW,BLACK,BLACK,BLACK},
											{BLACK,BLACK,YELLOW,YELLOW,YELLOW,YELLOW,BLACK,BLACK},
											{BLACK,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,BLACK},
											{BLACK,YELLOW,BLUE,YELLOW,YELLOW,YELLOW,YELLOW,BLACK},
											{BLACK,YELLOW,BLUE,YELLOW,YELLOW,YELLOW,YELLOW,BLACK},
											{BLACK,YELLOW,YELLOW,BLUE,YELLOW,YELLOW,YELLOW,BLACK},
											{BLACK,BLACK,YELLOW,YELLOW,YELLOW,YELLOW,BLACK,BLACK},},		//water drop -> inside humidity display
																								
											{{RED,RED,RED,RED,RED,RED,RED,RED},
											{RED,RED,RED,RED,RED,RED,RED,RED},
											{RED,BLACK,BLACK,BLACK,RED,RED,BLACK,RED},
											{WHITE,WHITE,WHITE,BLACK,WHITE,BLACK,BLACK,WHITE},
											{WHITE,BLACK,BLACK,BLACK,WHITE,WHITE,BLACK,WHITE},
											{WHITE,WHITE,WHITE,BLACK,WHITE,WHITE,BLACK,WHITE},
											{WHITE,BLACK,BLACK,BLACK,WHITE,WHITE,BLACK,WHITE},
											{WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE},},				//date 31-> date display
											
											{{BLACK,BLACK,GREEN,GREEN,GREEN,GREEN,BLACK,BLACK},
											{BLACK,GREEN,WHITE,BLUE,WHITE,WHITE,GREEN,BLACK},
											{GREEN,WHITE,WHITE,BLUE,WHITE,WHITE,WHITE,GREEN},
											{GREEN,WHITE,WHITE,BLUE,WHITE,WHITE,WHITE,GREEN},
											{GREEN,WHITE,WHITE,BLUE,BLUE,BLUE,WHITE,GREEN},
											{GREEN,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,GREEN},
											{BLACK,GREEN,WHITE,WHITE,WHITE,WHITE,GREEN,BLACK},
											{BLACK,BLACK,GREEN,GREEN,GREEN,GREEN,BLACK,BLACK},},				//clock -> timer mode
											
											{{BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK},
											{BLACK,BLACK,GREEN,BLUE,BLUE,GREEN,BLACK,BLACK},
											{BLACK,GREEN,BLUE,BLACK,WHITE,BLUE,GREEN,BLACK},
											{BLACK,BLUE,WHITE,BLACK,WHITE,WHITE,BLUE,BLACK},
											{BLACK,BLUE,WHITE,BLACK,BLACK,WHITE,BLUE,BLACK},
											{BLACK,BLACK,BLUE,WHITE,WHITE,BLUE,BLACK,BLACK},
											{BLACK,BLACK,BLACK,BLUE,BLUE,BLACK,BLACK,BLACK},
											{BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK},},				// small clock -> stopwatch		

											{{BLACK,BLACK,BLACK,ORANGE,ORANGE,BLACK,BLACK,BLACK},
											{BLACK,BLACK,ORANGE,ORANGE,ORANGE,ORANGE,BLACK,BLACK},
											{BLACK,BLACK,ORANGE,ORANGE,ORANGE,ORANGE,BLACK,BLACK},
											{BLACK,BLACK,ORANGE,ORANGE,ORANGE,ORANGE,BLACK,BLACK},
											{BLACK,BLACK,ORANGE,ORANGE,ORANGE,ORANGE,BLACK,BLACK},
											{BLACK,ORANGE,ORANGE,ORANGE,ORANGE,ORANGE,ORANGE,BLACK},
											{BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK},
											{BLACK,BLACK,BLACK,ORANGE,ORANGE,BLACK,BLACK,BLACK},},						//bell -> alarm mode		
											
											{{BLACK,BLACK,GREEN,GREEN,GREEN,GREEN,BLACK,BLACK},
											{BLACK,GREEN,WHITE,BLACK,WHITE,WHITE,GREEN,BLACK},
											{GREEN,WHITE,WHITE,BLACK,WHITE,WHITE,WHITE,GREEN},
											{GREEN,WHITE,WHITE,BLACK,BLACK,BLACK,WHITE,GREEN},
											{GREEN,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,GREEN},											
											{BLACK,GREEN,WHITE,WHITE,WHITE,WHITE,GREEN,BLACK},
											{BLACK,BLACK,GREEN,GREEN,GREEN,GREEN,BLACK,BLACK},
											{GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN},},				//standing clock 
											
											{{BLACK,BLACK,BLACK,BLACK,BLACK,RED,RED,BLACK},
											{BLACK,BLACK,RED,RED,BLACK,BLACK,RED,BLACK},
											{BLACK,BLACK,BLACK,RED,BLACK,BLACK,RED,BLACK},
											{RED,BLACK,BLACK,RED,BLACK,BLACK,RED,BLACK},
											{RED,BLACK,BLACK,RED,BLACK,BLACK,RED,BLACK},
											{BLACK,BLACK,BLACK,RED,BLACK,BLACK,RED,BLACK},
											{BLACK,BLACK,RED,RED,BLACK,BLACK,RED,BLACK},
											{BLACK,BLACK,BLACK,BLACK,BLACK,RED,RED,BLACK},},						//signal				
};

uint8_t HT1632_MEM_BW[BW_ROWS] = {0};
uint8_t HT1632_MEM_RGB[RGB_ROWS] = {0};

uint8_t HOURS = 13;
uint8_t MINUTES = 30;
uint8_t SECONDS = 0;

uint8_t DAY = 1;
uint8_t DATE = 17;
uint8_t MONTH = 11;

float TEMPERATURE = 20.6;
float HUMIDITY = 34.7;

uint8_t Tilt1 = 1;	//Neigung 1
uint8_t Tilt2 = 1;	//Neigung 2

uint8_t Registers[3] = { 0x03, 0x00, 0x04 };

/*Funktionen*/

//HT1632

void HT1632_ChipSelect(uint8_t Chip)
{
	if(Chip == HT1632_CS_BW)
	{
		HAL_GPIO_WritePin(HT1632_CS_GPIO_Port,HT1632_CS_Pin,GPIO_PIN_RESET); 	// Low active
	}
	else
	{
		HAL_GPIO_WritePin(HT1632_CS_GPIO_Port,HT1632_CS_Pin,GPIO_PIN_SET); 			// High active
		
	}
}


void HT1632_ChipUnSelect(uint8_t Chip)
{
	if(Chip == HT1632_CS_BW)
	{
		HAL_GPIO_WritePin(HT1632_CS_GPIO_Port,HT1632_CS_Pin,GPIO_PIN_SET); 		// High inactive
	}
}


void HT1632_SendId(uint8_t Id)
{
	int8_t i = 0;
	for(i = 2; i >= 0; i--)
	{
		(Id & (1<<i)) ? (HAL_GPIO_WritePin(HT1632_DATA_GPIO_Port,HT1632_DATA_Pin,GPIO_PIN_SET)) : (HAL_GPIO_WritePin(HT1632_DATA_GPIO_Port,HT1632_DATA_Pin,GPIO_PIN_RESET));
		HAL_GPIO_WritePin(HT1632_WR_GPIO_Port,HT1632_WR_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(HT1632_WR_GPIO_Port,HT1632_WR_Pin,GPIO_PIN_RESET);
	}
}


void HT1632_SendAddr(uint8_t Addr)
{
	int8_t i = 0;
	for(i = 6; i >= 0; i--)
	{
		(Addr & (1<<i)) ? (HAL_GPIO_WritePin(HT1632_DATA_GPIO_Port,HT1632_DATA_Pin,GPIO_PIN_SET)) : (HAL_GPIO_WritePin(HT1632_DATA_GPIO_Port,HT1632_DATA_Pin,GPIO_PIN_RESET));
		HAL_GPIO_WritePin(HT1632_WR_GPIO_Port,HT1632_WR_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(HT1632_WR_GPIO_Port,HT1632_WR_Pin,GPIO_PIN_RESET);
	}	
}


void HT1632_SendCmdSingle(uint8_t Chip, uint8_t Cmd)
{
	int8_t i = 0;
	HT1632_ChipSelect(Chip);
	HT1632_SendId(CMD);
	for(i = 7; i >= 0; i--)
	{
		(Cmd & (1<<i)) ? (HAL_GPIO_WritePin(HT1632_DATA_GPIO_Port,HT1632_DATA_Pin,GPIO_PIN_SET)) : (HAL_GPIO_WritePin(HT1632_DATA_GPIO_Port,HT1632_DATA_Pin,GPIO_PIN_RESET));
		HAL_GPIO_WritePin(HT1632_WR_GPIO_Port,HT1632_WR_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(HT1632_WR_GPIO_Port,HT1632_WR_Pin,GPIO_PIN_RESET);
	}
	HAL_GPIO_WritePin(HT1632_WR_GPIO_Port,HT1632_WR_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(HT1632_WR_GPIO_Port,HT1632_WR_Pin,GPIO_PIN_RESET);
	HT1632_ChipUnSelect(Chip);
}


void HT1632_SendCmdMultiple(uint8_t Chip, uint8_t *Cmd, uint8_t Count)
{
	int8_t i = 0, x = 0;
	HT1632_ChipSelect(Chip);
	HT1632_SendId(CMD);
	for(x = 0; x < Count; x++)
	{
		for(i = 7; i >= 0; i--)
		{
			(Cmd[x] & (1<<i)) ? (HAL_GPIO_WritePin(HT1632_DATA_GPIO_Port,HT1632_DATA_Pin,GPIO_PIN_SET)) : (HAL_GPIO_WritePin(HT1632_DATA_GPIO_Port,HT1632_DATA_Pin,GPIO_PIN_RESET));
			HAL_GPIO_WritePin(HT1632_WR_GPIO_Port,HT1632_WR_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(HT1632_WR_GPIO_Port,HT1632_WR_Pin,GPIO_PIN_RESET);
		}
		HAL_GPIO_WritePin(HT1632_WR_GPIO_Port,HT1632_WR_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(HT1632_WR_GPIO_Port,HT1632_WR_Pin,GPIO_PIN_RESET);
	}
	HT1632_ChipUnSelect(Chip);
}
void HT1632_SendDataSingle(uint8_t Chip, uint8_t Addr, uint8_t Data, uint8_t Size, uint8_t Dir)
{
		int8_t i = 0;
	HT1632_ChipSelect(Chip);
	HT1632_SendId(WRITE);
	HT1632_SendAddr(Addr);
	if(Dir == LSB)
	{
		for(i = 0; i <= Size; i++)
		{
			(Data & (1<<i)) ? (HAL_GPIO_WritePin(HT1632_DATA_GPIO_Port,HT1632_DATA_Pin,GPIO_PIN_SET)) : (HAL_GPIO_WritePin(HT1632_DATA_GPIO_Port,HT1632_DATA_Pin,GPIO_PIN_RESET));
			HAL_GPIO_WritePin(HT1632_WR_GPIO_Port,HT1632_WR_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(HT1632_WR_GPIO_Port,HT1632_WR_Pin,GPIO_PIN_RESET);
		}
	}
	else
	{
		for(i = Size; i >= 0; i--)
		{
			(Data & (1<<i)) ? (HAL_GPIO_WritePin(HT1632_DATA_GPIO_Port,HT1632_DATA_Pin,GPIO_PIN_SET)) : (HAL_GPIO_WritePin(HT1632_DATA_GPIO_Port,HT1632_DATA_Pin,GPIO_PIN_RESET));
			HAL_GPIO_WritePin(HT1632_WR_GPIO_Port,HT1632_WR_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(HT1632_WR_GPIO_Port,HT1632_WR_Pin,GPIO_PIN_RESET);
		}
	}
	HT1632_ChipUnSelect(Chip);
}
void HT1632_SendDataMultiple(uint8_t Chip, uint8_t Addr, uint8_t *Data, uint8_t Size, uint8_t Dir, uint8_t LeftEdge, uint8_t RightEdge, uint8_t Count)
{
	int8_t i = 0, x = 0, z = 0;
	HT1632_ChipSelect(Chip);
	HT1632_SendId(WRITE);
	HT1632_SendAddr(Addr);
	if(Dir == LSB)
	{
		if(Size == FULL)
		{
			for(x = LeftEdge; x <= RightEdge; x++)
			{
				for(i = 0; i <= 7; i++)
				{
					(Data[x] & (1<<i)) ? (HAL_GPIO_WritePin(HT1632_DATA_GPIO_Port,HT1632_DATA_Pin,GPIO_PIN_SET)) : (HAL_GPIO_WritePin(HT1632_DATA_GPIO_Port,HT1632_DATA_Pin,GPIO_PIN_RESET));
					HAL_GPIO_WritePin(HT1632_WR_GPIO_Port,HT1632_WR_Pin,GPIO_PIN_SET);
					HAL_GPIO_WritePin(HT1632_WR_GPIO_Port,HT1632_WR_Pin,GPIO_PIN_RESET);
				}
			}
		}
		else
		{
			x = Addr / 2;
			i = Addr;
			while(Count)
			{
				if(i % 2)
				{
					for(z = 4; z <= 7; z++)
					{
						(Data[x] & (1<<i)) ? (HAL_GPIO_WritePin(HT1632_DATA_GPIO_Port,HT1632_DATA_Pin,GPIO_PIN_SET)) : (HAL_GPIO_WritePin(HT1632_DATA_GPIO_Port,HT1632_DATA_Pin,GPIO_PIN_RESET));
						HAL_GPIO_WritePin(HT1632_WR_GPIO_Port,HT1632_WR_Pin,GPIO_PIN_SET);
						HAL_GPIO_WritePin(HT1632_WR_GPIO_Port,HT1632_WR_Pin,GPIO_PIN_RESET);
					}
					x++;
				}
				else
				{
					for(z = 0; z <= 3; z++)
					{
						(Data[x] & (1<<i)) ? (HAL_GPIO_WritePin(HT1632_DATA_GPIO_Port,HT1632_DATA_Pin,GPIO_PIN_SET)) : (HAL_GPIO_WritePin(HT1632_DATA_GPIO_Port,HT1632_DATA_Pin,GPIO_PIN_RESET));
						HAL_GPIO_WritePin(HT1632_WR_GPIO_Port,HT1632_WR_Pin,GPIO_PIN_SET);
						HAL_GPIO_WritePin(HT1632_WR_GPIO_Port,HT1632_WR_Pin,GPIO_PIN_RESET);
					}
				}
				Count--;
				i++;
			}
		}
	}
	else
	{
		if(Size == FULL)
			{
				for(x = LeftEdge; x <= RightEdge; x++)
				{
					for(i = 7; i >= 0; i--)
					{
						(Data[x] & (1<<i)) ? (HAL_GPIO_WritePin(HT1632_DATA_GPIO_Port,HT1632_DATA_Pin,GPIO_PIN_SET)) : (HAL_GPIO_WritePin(HT1632_DATA_GPIO_Port,HT1632_DATA_Pin,GPIO_PIN_RESET));
						HAL_GPIO_WritePin(HT1632_WR_GPIO_Port,HT1632_WR_Pin,GPIO_PIN_SET);
						HAL_GPIO_WritePin(HT1632_WR_GPIO_Port,HT1632_WR_Pin,GPIO_PIN_RESET);
					}
				}
			}
		else
		{
			x = Addr / 2;
			i = Addr;
			while(Count)
			{
				if(i % 2)
				{
					for(z = 7; z >= 4; z--)
					{
						(Data[x] & (1<<i)) ? (HAL_GPIO_WritePin(HT1632_DATA_GPIO_Port,HT1632_DATA_Pin,GPIO_PIN_SET)) : (HAL_GPIO_WritePin(HT1632_DATA_GPIO_Port,HT1632_DATA_Pin,GPIO_PIN_RESET));
						HAL_GPIO_WritePin(HT1632_WR_GPIO_Port,HT1632_WR_Pin,GPIO_PIN_SET);
						HAL_GPIO_WritePin(HT1632_WR_GPIO_Port,HT1632_WR_Pin,GPIO_PIN_RESET);
					}
					x++;
				}
				else
				{
					for(z = 3; z >= 0; z--)
					{
						(Data[x] & (1<<i)) ? (HAL_GPIO_WritePin(HT1632_DATA_GPIO_Port,HT1632_DATA_Pin,GPIO_PIN_SET)) : (HAL_GPIO_WritePin(HT1632_DATA_GPIO_Port,HT1632_DATA_Pin,GPIO_PIN_RESET));
						HAL_GPIO_WritePin(HT1632_WR_GPIO_Port,HT1632_WR_Pin,GPIO_PIN_SET);
						HAL_GPIO_WritePin(HT1632_WR_GPIO_Port,HT1632_WR_Pin,GPIO_PIN_RESET);
					}
				}
				Count--;
				i++;
			}
		}
	}
	HT1632_ChipUnSelect(Chip);
}

//HT1632-BW

void HT1632_BW_Init(void)
{
	HT1632_ChipUnSelect(HT1632_CS_BW);
	HAL_GPIO_WritePin(HT1632_WR_GPIO_Port,HT1632_WR_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(HT1632_RD_GPIO_Port,HT1632_RD_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(HT1632_DATA_GPIO_Port,HT1632_DATA_Pin,GPIO_PIN_SET);
	
	HT1632_SendCmdSingle(HT1632_CS_BW, SYS_DIS);
	HT1632_SendCmdSingle(HT1632_CS_BW, COM_P8);
	HT1632_SendCmdSingle(HT1632_CS_BW, RC_MODE);
	HT1632_SendCmdSingle(HT1632_CS_BW, PWM_16);
	HT1632_SendCmdSingle(HT1632_CS_BW,BLINK_OFF);
	HT1632_SendCmdSingle(HT1632_CS_BW,SYS_EN);
	HT1632_SendCmdSingle(HT1632_CS_BW,LED_ON);
}


void HT1632_BW_Shift(uint8_t *Dst, uint8_t *DataIn, uint8_t *DataOut, uint8_t LeftEdge, uint8_t RightEdge, uint8_t Dir)
{
	//DataIn und DataOut bereits invertiert übergeben
	int8_t i = 0;
	switch(Dir){
		case LEFT:
			/*DataOut zuweisen*/
			*DataOut = Dst[LeftEdge];
			/*Links Shift*/
			for(i = LeftEdge; i < RightEdge; i++){
				Dst[i] = Dst[i+1];
			}
			/*DataIn einfügen*/
			Dst[RightEdge] = *DataIn;
			break;
		case RIGHT:
			/*DataOut zuweisen*/
			*DataOut = Dst[RightEdge];
			/*Rechts Shift*/
			for(i = RightEdge; i > LeftEdge; i--){
				Dst[i] = Dst[i-1];
			}
			/*DataIn einfügen*/
			Dst[LeftEdge] = *DataIn;
			break;
		case UP:
			for(i = LeftEdge; i <= RightEdge; i++){
				/*DataOut zuweisen*/
				if(Dst[i] & (1<<0)){
					DataOut[i/8] |= (1<<(i%8));
				}else{
					DataOut[i/8] &= ~(1<<(i%8));
				}
				/*Hoch Shift*/
				Dst[i] >>= 1;
				/*DataIn einfügen*/
				if(DataIn[i/8] & (1<<(i%8))){
					Dst[i] |= (1<<7);
				}else{
					Dst[i] &= ~(1<<7);
				}
			}
			break;
		case DOWN:
			for(i = LeftEdge; i <= RightEdge; i++){
				/*DataOut zuweisen*/
				if(Dst[i] & (1<<7)){
					DataOut[i/8] |= (1<<(i%8));
				}else{
					DataOut[i/8] &= ~(1<<(i%8));
				}
				/*Hoch Shift*/
				Dst[i] <<= 1;
				/*DataIn einfügen*/
				if(DataIn[i/8] & (1<<(i%8))){
					Dst[i] |= (1<<0);
				}else{
					Dst[i] &= ~(1<<0);
				}
			}
			break;
		default:
			//No further action
			break;
	}
}


uint8_t HT1632_BW_String(uint8_t *Dst, char *String, 	uint8_t *Space, uint8_t *CharPos, uint8_t *StringPos, uint8_t LeftEdge, uint8_t RightEdge, uint8_t Align)
{
	int8_t i = 0;
	uint16_t Length = 0;
	uint8_t Offset = 0;
	uint8_t Fin = 0;
	
	if(Align == ALIGN_MID)
	{
		
		Length = STRING_GetLength(String, SPACE_BETWEEN_CHARACTERS);
		(Length < (RightEdge - LeftEdge)+1) ? (Offset = ((((RightEdge-LeftEdge)+1-Length)/2)+(Length%2))) : (Offset = 0);
		
		for(i = LeftEdge + Offset; i <= RightEdge; i++)
		{
			if(*Space)
			{
				(*Space)--;
				Dst[i] = 0xFF;
			}
			else
			{
				Dst[i] = ~(ASCII[String[*StringPos]][*CharPos]);
				if(++(*CharPos) > ASCII[String[*StringPos]][8])
				{
					*CharPos = 0;
					*Space = SPACE_BETWEEN_CHARACTERS;
					
					if(String[++(*StringPos)] == '\0')
					{
						Fin = FIN_CHAR;
						break;
					}
				}
			}
		}
	}
	else if(Align == ALIGN_LEFT)
	{
		for(i = LeftEdge; i <= RightEdge; i++)
		{
			if(*Space)
			{
				(*Space)--;
				Dst[i] = 0xFF;
			}
			else
			{
				Dst[i] = ~(ASCII[String[*StringPos]][*CharPos]);
				if(++(*CharPos) > ASCII[String[*StringPos]][8])
				{
					*CharPos = 0;
					*Space = SPACE_BETWEEN_CHARACTERS;
					
					if(String[++(*StringPos)] == '\0')
					{
						Fin = FIN_STRING;
						break;
					}
				}
			}
		}
	}
	else if(Align == ALIGN_RIGHT)
	{
		*StringPos = strlen(String)-1;
		*CharPos = ASCII[String[*StringPos]][8] + 1;
		for(i = RightEdge; i >= LeftEdge; i--)
		{
			if(*Space)
			{
				(*Space)--;
				Dst[i] = 0xFF;
			}
			else
			{
				*CharPos -= 1;
				Dst[i] = ~(ASCII[String[*StringPos]][*CharPos]);
				if(*CharPos == 0 && *StringPos != 0)
				{
					*StringPos -= 1;
					*CharPos = ASCII[String[*StringPos]][8]+1;
					*Space = SPACE_BETWEEN_CHARACTERS;
				}
				else if(*CharPos == 0 && *StringPos == 0)
				{
					Fin = FIN_STRING;
					break;
				}
			}
		}
		//No further action
	}
	return Fin;
}


void HT1632_BW_Time(uint8_t *Dst, uint8_t Hours, uint8_t Minutes, uint8_t Skip)
{
	int8_t i = 0;
	
	uint8_t xh = Hours % 10;
	uint8_t hx = Hours / 10;
	uint8_t xm = Minutes % 10;
	uint8_t mx = Minutes / 10;
	
	uint8_t Middle = BW_ROWS / 2;
	uint8_t Pos = Middle;
	
	/*SET HOURS*/
	Pos = Middle - SPACE_BETWEEN_NUMBERS;
	for(i = NUMBERS[xh][8]; i >= 0; i--)
	{
		Pos--;
		if(Skip != 1){Dst[Pos] = ~(NUMBERS[xh][i]);}
	}
	Pos = Pos - SPACE_BETWEEN_NUMBERS;
	for(i = NUMBERS[hx][8]; i >= 0; i--)
	{
		Pos--;
		if(Skip != 0){Dst[Pos] = ~(NUMBERS[hx][i]);}
	}
	
	/*SET MINUTES*/
	Pos = Middle + SPACE_BETWEEN_NUMBERS;
	for(i = 0; i <= NUMBERS[mx][8]; i++)
	{
		Pos++;
		if(Skip != 2){Dst[Pos] = ~(NUMBERS[mx][i]);}
	}
	Pos = Pos + SPACE_BETWEEN_NUMBERS;
	for(i = 0; i <= NUMBERS[xm][8]; i++)
	{
		Pos++;
		if(Skip != 3){Dst[Pos] = ~(NUMBERS[xm][i]);}
	}
}


extern void HT1632_BW_TimePoints(uint8_t *Dst, uint8_t POINTS_ON)
{
		uint8_t Middle = BW_ROWS / 2;
	if(POINTS_ON == TRUE)
	{
		Dst[Middle] = POINTS;
	}
	else
	{
		Dst[Middle] = 0xFF;
	}
}

uint8_t HT1632_BW_Date(uint8_t *Dst, uint8_t *GoTo, uint8_t *Next, uint8_t *Dir, uint8_t* Count, uint8_t *CharPos, uint8_t *StringPos, uint8_t *Mask, uint8_t *Step, uint8_t Rst, uint8_t CpltRst)
{
		int8_t i = 0;
	uint8_t Fin = 0, State = 0;
	uint8_t DataIn = 0xFF, DataOut = 0x00;
	uint8_t LDataIn[3] = {0xFF, 0xFF, 0xFF}, LDataOut[3] = {0};
	uint8_t LeftEdge = 0, RightEdge = 23, Align = ALIGN_MID;
	static char *sptr;
	static char Date[7] = "";
	
	if(CpltRst)
	{
		(*Step) = 0;
	}
	
	if(Rst)
	{
		if((*Step) == 2){*Step = 0;}
		if((*Step) == 1){sptr = WEEKDAYS[DAY]; *GoTo = UP; *Mask = (1<<1);}
		else if(*Step == 0){sprintf(Date,"%i%c%s",DATE,39,MONTHS[MONTH]); sptr = Date; *Mask = (1<<5); *GoTo = DOWN;}
		*StringPos = *CharPos = 0;
	}
	
	switch(*GoTo)
	{
		case UP:
			
			State = STRING_GetData(LDataIn, sptr, StringPos, CharPos, Mask, LeftEdge, RightEdge, Align, UP);
			HT1632_BW_Shift(Dst, LDataIn, LDataOut, LeftEdge, RightEdge, UP);
			
			if(State == FIN_STRING)
			{
				*Dir = UP; *GoTo = SFT; *Next = 0; *Count = 2;
			}
			
			break;
		case DOWN:
			
			State = STRING_GetData(LDataIn, sptr, StringPos, CharPos, Mask, LeftEdge, RightEdge, Align, DOWN);
			HT1632_BW_Shift(Dst, LDataIn, LDataOut, LeftEdge, RightEdge, DOWN);

			if(State == FIN_STRING)
			{
				*Dir = DOWN; *GoTo = SFT; *Next = 0; *Count = 1;
			}
		
			break;
		case SFT:
			
			if( *Dir == UP || *Dir == DOWN)
			{
				HT1632_BW_Shift(Dst, LDataIn, LDataOut, LeftEdge, RightEdge, *Dir);
			}
			else
			{
				HT1632_BW_Shift(Dst, &DataIn, &DataOut, LeftEdge, RightEdge, *Dir);
			}
			
			if(--(*Count) == 0)
			{
				if((*Dir) == UP)
				{
					*Count = WAIT_WEEKDAY;
					for(i = LeftEdge; i <= RightEdge; i++)
					{
						if(!(Dst[i] & (1 << 0)))
						{
							*Next = CORR;
							//Evtl Count
						}
					}
				}
				else if((*Dir) == DOWN)
				{
					*Count = WAIT_DAYMONTH;
					for(i = LeftEdge; i <= RightEdge; i++)
					{
						if(!(Dst[i] & (1<<7)))
						{
							*Next = CORR;
							*Count = 1;
						}
					}
					
					for(i = LeftEdge; i <= RightEdge; i++)
					{
						if(!(Dst[i] & (1<<6)))
						{
							*Next = CORR;
							*Count = 2;
						}
					}
				}
				*GoTo = *Next;
				*Next = 0;
			}
			break;
		case CORR:
			
				if(*Dir == UP)
			{
				for(i = LeftEdge; i <= RightEdge; i++)
				{
					Dst[i] |= (1<<0);
				}
				*GoTo = *Next;
				*Count = WAIT_WEEKDAY;
			}
			else if((*Dir) == DOWN)
			{
				if((*Count) == 2)
				{
					for(i = LeftEdge; i <= RightEdge; i++)
					{
						if(Dst[i] & (1<<6))
						{
							Dst[i] |= (1<<7);
						}
						else
						{
							Dst[i] &= ~(1<<7);
						}
						Dst[i] |= (1<<6);
					}
					(*Count)--;
				}
				else
				{
					for(i = LeftEdge; i <= RightEdge; i++)
					{
						Dst[i] |= (1<<7);
					}
					*GoTo = *Next;
					*Count = WAIT_DAYMONTH;
				}
			}
			
			break;
			
		default:
			
				if(--(*Count) == 0)
				{
					Fin = 1;
					(*Step)++;
				}
		
			break;
	}
	
	return Fin;
}


uint8_t HT1632_BW_TempHum(uint8_t *Dst, uint8_t *GoTo, uint8_t *Next, uint8_t *Dir, uint8_t *Count, uint8_t *Space, uint8_t *FrontPos, uint8_t *CharPos, uint8_t *StringPos, uint8_t *Mask, uint8_t *Step, uint8_t Rst, uint8_t CpltRst)
{
	int8_t i = 0;
	uint8_t Fin = 0, State = 0;
	uint8_t DataIn = 0xFF, DataOut = 0x00;
	uint8_t LDataIn[3] = {0xFF, 0xFF, 0xFF}, LDataOut[3] = {0};
	uint8_t LeftEdge = 0, RightEdge = 23, Align = ALIGN_MID;
	uint8_t Free = 0;
	char temp_txt[] = "TEMP";
	char hum_txt[] = "HUM";
	static char temp_val[6] = "";
	static char hum_val[6] = "";
	static char *sptr = NULL;
	/*RESET*/
	if(CpltRst)
	{
		sprintf(temp_val,"%.0f%c",TEMPERATURE,64);
		sprintf(hum_val,"%0.f%c",HUMIDITY,37);
		*Step = 0;
	}
	if(Rst)
	{
		*StringPos = *CharPos = 0;
		if((*Step) == 4){*Step = 0;}
		if((*Step) == 0){sptr = temp_txt; *GoTo = DOWN; *Mask = (1<<5);}
		else if((*Step) == 1){sptr = temp_val;*GoTo = RIGHT; *StringPos = strlen(temp_val)-1; *CharPos = ASCII[temp_val[*StringPos]][8];}
		else if((*Step) == 2){sptr = hum_txt;*GoTo = UP; *Mask = (1<<1);}
		else if((*Step) == 3){sptr = hum_val;*GoTo = LEFT;}
	}
	
	
	/*DISPLAY CONTROL*/
	
	switch(*GoTo)
	{
		case UP:
			
			State = STRING_GetData(LDataIn, sptr, StringPos, CharPos, Mask, LeftEdge, RightEdge, Align, UP);
			HT1632_BW_Shift(Dst, LDataIn, LDataOut, LeftEdge, RightEdge, UP);
			
			if(State == FIN_STRING)
			{
				*Dir = UP; *GoTo = SFT; *Next = 0; *Count = 2;
			}
		
			break;
		case DOWN:
			
			State = STRING_GetData(LDataIn, sptr, StringPos, CharPos, Mask, LeftEdge, RightEdge, Align, DOWN);
			HT1632_BW_Shift(Dst, LDataIn, LDataOut, LeftEdge, RightEdge, DOWN);

			if(State == FIN_STRING)
			{
				*Dir = DOWN; *GoTo = SFT; *Next = 0; *Count = 1;
			}
		
			break;
		case LEFT:
			
			State = STRING_GetData(&DataIn, sptr, StringPos, CharPos, Mask, LeftEdge, RightEdge, Align, LEFT);
			HT1632_BW_Shift(Dst, &DataIn, &DataOut, LeftEdge, RightEdge, LEFT);
			
			(*Count)++;
		
			if(State == FIN_CHAR)
			{
				*Dir = LEFT; *GoTo = SPC; *Next = LEFT; *Space = SPACE_BETWEEN_CHARACTERS;
			}
			else if(State == FIN_STRING)
			{
				*Dir = LEFT;
				Free = RightEdge - LeftEdge + 1;
				
				if((*Count) == Free)
				{
					*GoTo = 0; *Next = 0; *Count = WAIT_TEMPHUM;
				}
				else if(*Count == (Free -1))
				{
					*GoTo = CORR; *Next = 0; *Count = 1;
				}
				else
				{
					*GoTo = SFT; *Next = 0; *FrontPos = LeftEdge + (Free - (*Count))/2 + (Free - (*Count))%2; *Count = (Free - (*Count))/2;
				}
			}
			
			break;
		case RIGHT:
			
			State = STRING_GetData(&DataIn, sptr, StringPos, CharPos, Mask, LeftEdge, RightEdge, Align, RIGHT);
			HT1632_BW_Shift(Dst, &DataIn, &DataOut, LeftEdge, RightEdge, RIGHT);
		
			(*Count)++;
		
			if(State == FIN_CHAR)
			{
				*Dir = RIGHT; *GoTo = SPC; *Next = RIGHT; *Space = SPACE_BETWEEN_CHARACTERS;
			}
			else if(State == FIN_STRING)
			{
				*Dir = RIGHT;
				Free = RightEdge -LeftEdge + 1;
				
				if((*Count) == Free)
				{
					*GoTo = 0; *Next = 0; *Count = WAIT_TEMPHUM;
				}
				else if((*Count) == (Free - 1))
				{
					*GoTo = SFT; *Next = 0; *Count = 1;
				}
				else
				{
					*GoTo = SFT; *Next = 0; *FrontPos = RightEdge - (Free - (*Count))/2; *Count = (Free - (*Count))/2 + (Free - (*Count))%2;
				}
			}
		
			break;
		case SPC:
			
			HT1632_BW_Shift(Dst, &DataIn, &DataOut, LeftEdge, RightEdge, *Dir);
		
			(*Count)++;
		
			if(--(*Space) == 0)
			{
				*GoTo = *Next;
			}
			
			break;
		case SFT:
			
			if( *Dir == UP || *Dir == DOWN)
			{
				HT1632_BW_Shift(Dst, LDataIn, LDataOut, LeftEdge, RightEdge, *Dir);
			}
			else
			{
				HT1632_BW_Shift(Dst, &DataIn, &DataOut, LeftEdge, RightEdge, *Dir);
			}
			
			if(--(*Count) == 0)
			{
				*Count = WAIT_TEMPHUM;
				if((*Dir) == UP)
				{
					for(i = LeftEdge; i <= RightEdge; i++)
					{
						if(!(Dst[i] & (1 << 0)))
						{
							*Next = CORR;
							//Evtl Count
						}
					}
				}
				else if((*Dir) == DOWN)
				{
					for(i = LeftEdge; i <= RightEdge; i++)
					{
						if(!(Dst[i] & (1<<7)))
						{
							*Next = CORR;
							*Count = 1;
						}
					}
					
					for(i = LeftEdge; i <= RightEdge; i++)
					{
						if(!(Dst[i] & (1<<6)))
						{
							*Next = CORR;
							*Count = 2;
						}
					}
				}
				else if((*Dir) == LEFT)
				{
					for(i = (*FrontPos) - 1; i >= LeftEdge; i--)
					{
						if(Dst[i] != 0xFF)
						{
							*Next = CORR;
							*Count = i - LeftEdge + 1;
							break;
						}
					}
				}
				else if((*Dir) == RIGHT)
				{
					if((*FrontPos) == 0)
					{
						// No further action
					}
					else
					{
						for(i = (*FrontPos) + 1; i <= RightEdge; i++)
						{
							if(Dst[i] != 0xFF)
							{
								*Next = CORR;
								*Count = RightEdge - i + 1;
								break;
							}
						}
					}
				}
				*GoTo = *Next;
				*Next = 0;
			}
			
			break;
		case CORR:
			
			if(*Dir == UP)
			{
				for(i = LeftEdge; i <= RightEdge; i++)
				{
					Dst[i] |= (1<<0);
				}
				*GoTo = *Next;
				*Count = WAIT_TEMPHUM;
			}
			else if((*Dir) == DOWN)
			{
				if((*Count) == 2)
				{
					for(i = LeftEdge; i <= RightEdge; i++)
					{
						if(Dst[i] & (1<<6))
						{
							Dst[i] |= (1<<7);
						}
						else
						{
							Dst[i] &= ~(1<<7);
						}
						Dst[i] |= (1<<6);
					}
					(*Count)--;
				}
				else
				{
					for(i = LeftEdge; i <= RightEdge; i++)
					{
						Dst[i] |= (1<<7);
					}
					*GoTo = *Next;
					*Count = WAIT_TEMPHUM;
				}
			}
			else if((*Dir) == LEFT)
			{
				HT1632_BW_Shift(Dst, &DataIn, &DataOut, LeftEdge, LeftEdge + (*Count) - 1, LEFT);
				if(--(*Count) == 0)
				{
					*GoTo = *Next;
					*Count = WAIT_TEMPHUM;
				}
			}
			else if((*Dir) == RIGHT)
			{
				HT1632_BW_Shift(Dst, &DataIn, &DataOut, RightEdge - ((*Count) - 1), RightEdge, RIGHT);
				if(--(*Count) == 0)
				{
					*GoTo = *Next;
					*Count = WAIT_TEMPHUM;
				}
			}
		
			break;
		default:
				
				if(--(*Count) == 0)
				{
					Fin = 1;
					(*Step)++;
				}
				
			break;
	}
	
	return Fin;
}


//HT1632-RGB

void HT1632_RGB_Init(void)
{
	HT1632_ChipUnSelect(HT1632_CS_RGB);
	HAL_GPIO_WritePin(HT1632_WR_GPIO_Port,HT1632_WR_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(HT1632_RD_GPIO_Port,HT1632_RD_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(HT1632_DATA_GPIO_Port,HT1632_DATA_Pin,GPIO_PIN_SET);
	
	HT1632_SendCmdSingle(HT1632_CS_RGB, SYS_DIS);
	HT1632_SendCmdSingle(HT1632_CS_RGB, COM_P8);
	HT1632_SendCmdSingle(HT1632_CS_RGB, SLV_MODE);
	HT1632_SendCmdSingle(HT1632_CS_RGB, PWM_16);
	HT1632_SendCmdSingle(HT1632_CS_RGB,BLINK_OFF);
	HT1632_SendCmdSingle(HT1632_CS_RGB,SYS_EN);
	HT1632_SendCmdSingle(HT1632_CS_RGB,LED_ON);
}


void HT1632_RGB_Pattern(uint8_t *Dst, uint8_t Src[][RGB_COMS][RGB_ROWS/3],uint8_t Pattern)
{
	int8_t Com = 0;
	int8_t Row = 0;
	int8_t Pos = 0;
	
	/*SET RED*/
	Pos = 0;
	for(Row = 0; Row < 8; Row++){
		for(Com = 0; Com < 8; Com++){
			(Src[Pattern][Com][Row] & RED) ? (Dst[Pos] &= ~(1<<Com)) : (Dst[Pos] |= (1<<Com));
		}
		Pos += 3;
	}
	/*SET GREEN*/
	Pos = 1;
	for(Row = 0; Row < 8; Row++){
		for(Com = 0; Com < 8; Com++){
			(Src[Pattern][Com][Row] & GREEN) ? (Dst[Pos] &= ~(1<<Com)) : (Dst[Pos] |= (1<<Com));
		}
		Pos += 3;
	}
	/*SET BLUE*/
	Pos = 2;
	for(Row = 0; Row < 8; Row++){
		for(Com = 0; Com < 8; Com++){
			(Src[Pattern][Com][Row] & BLUE) ? (Dst[Pos] &= ~(1<<Com)) : (Dst[Pos] |= (1<<Com));
		}
		Pos += 3;
	}
}

//Sonstiges

void HT1632_ClearMemory(uint8_t *Mem, uint8_t LeftEdge, uint8_t RightEdge)
{
	int8_t i = 0;
	for(i = LeftEdge; i <= RightEdge; i++)
	{
		Mem[i] = 0xFF;
	}
}
void HT1632_SetOutput(uint8_t Chip, uint8_t *Src, uint8_t Tilt1, uint8_t Tilt2, uint8_t LeftEdge, uint8_t RightEdge)	//Verbessern Toggle
{
	if(Chip == HT1632_CS_BW)
	{
		int8_t i = 0;
		uint8_t Dst[BW_ROWS] = {0};
		uint8_t Dir = 0;
		if(Tilt1 == 1&&Tilt2 == 1)
		{
			for(i = LeftEdge; i <= RightEdge; i++)
			{
				Dst[i] = Src[RightEdge - i];
			}
			Dir = MSB;
		}
		else
		{
			for(i = LeftEdge; i <= RightEdge; i++)
			{
				Dst[i] = Src[i];
			}
			Dir = LSB;
		}
		HT1632_SendDataMultiple(Chip, LeftEdge*2, Dst, FULL, Dir, LeftEdge, RightEdge, 0);
	}
	else
	{
		int8_t i = 0;
		uint8_t Dst[RGB_ROWS] = {0};
		uint8_t Dir = 0;
		if(Tilt1 == 0 && Tilt2 == 0)
		{
		
			for(i = 0; i < 8; i++)
			{
				Dst[i*3] = Src[RGB_ROWS - 3 - i * 3];
			}
			for(i = 0; i < 8; i++)
			{
				Dst[i*3+1] = Src[RGB_ROWS - 2 - i * 3];
			}
			for(i = 0; i < 8; i++)
			{
				Dst[i*3+2] = Src[RGB_ROWS - 1 - i * 3];
			}
			Dir = MSB;
		}
		else
		{
			for(i = LeftEdge; i <= RightEdge; i++)
			{
				Dst[i] = Src[i];
			}
			Dir = LSB;
		}
		HT1632_SendDataMultiple(Chip, LeftEdge*2, Dst, FULL, Dir, LeftEdge, RightEdge, 0);
	}
}


uint16_t STRING_GetLength(char *String, uint8_t Space)
{
	uint16_t Length = 0;
	int8_t i = 0;
	while(String[i] != '\0'){
		Length += ASCII[String[i]][8]+1;
		i++;
	}
	i--;
	Length += i*Space;
	return Length;
}


uint8_t STRING_GetData(uint8_t *DataIn, char *String, uint8_t *StringPos, uint8_t *CharPos, uint8_t *Mask, uint8_t LeftEdge, uint8_t RightEdge, uint8_t Align, uint8_t Dir){
	int8_t i = 0;
	uint8_t Fin = 0;
	uint8_t Length = 0;
	uint8_t Offset = 0;
	uint8_t Space = 0;
	switch(Dir){
		case LEFT:
			/*DataIn zuweisen*/
			*DataIn = ~(ASCII[String[*StringPos]][*CharPos]);
			/*Überprüfen auf Ende von Character oder String*/
			if((++(*CharPos)) > ASCII[String[*StringPos]][8]){
				(*CharPos) = 0;
				Fin = FIN_CHAR;
				if(String[++(*StringPos)] == '\0'){
					Fin = FIN_STRING;
				}
			}
			break;
		case RIGHT:
			/*DataIn zuweisen*/
			*DataIn = ~(ASCII[String[*StringPos]][*CharPos]);
			/*Überprüfen auf Ende von Character oder String*/
			if(((*CharPos) == 0) && ((*StringPos) == 0)){
				Fin = FIN_STRING;
			}else if((*CharPos) == 0){
				Fin = FIN_CHAR;
				(*CharPos) = ASCII[String[--(*StringPos)]][8];
			}else{
				(*CharPos)--;
			}
			break;
		case UP:
			/*DataIn zuweisen*/
		switch(Align){
			case ALIGN_MID:
				Length = STRING_GetLength(String,SPACE_BETWEEN_CHARACTERS);
				(Length < (RightEdge - LeftEdge)+1) ? (Offset = ((((RightEdge-LeftEdge)+1-Length)/2)+(Length%2))) : (Offset = 0);
				for(i = LeftEdge; i < LeftEdge + Offset; i++){
					DataIn[i/8] |= (1<<(i%8));
				}
				for(i = LeftEdge + Offset; i <= RightEdge; i++){
					if(Space != 0){
						Space--;
						DataIn[i/8] |= (1<<(i%8));
					}else{
						if(ASCII[String[*StringPos]][*CharPos] & (*Mask)){
							DataIn[i/8] &= ~(1<<(i%8));
						}else{
							DataIn[i/8] |= (1<<(i%8));
						}
						/*Überprüfen auf Ende von String*/
						if(++(*CharPos) > ASCII[String[*StringPos]][8]){
							*CharPos = 0;
							Space = SPACE_BETWEEN_CHARACTERS;
							if(String[++(*StringPos)] == '\0'){
								i++;
								while(i <= RightEdge){
									DataIn[i/8] |= (1<<(i%8));
									i++;
								}
								*StringPos = 0;
								break;
							}
						}
					}
				}
				(*Mask) <<= 1;
				if((*Mask) == (1<<6)){
					Fin = FIN_STRING;
				}
				break;
			case ALIGN_LEFT:
				for(i = LeftEdge; i <= RightEdge; i++){
					if(Space != 0){
						Space--;
						DataIn[i/8] |= (1<<(i%8));
					}else{
						if(ASCII[String[*StringPos]][*CharPos] & (*Mask)){
							DataIn[i/8] &= ~(1<<(i%8));
						}else{
							DataIn[i/8] |= (1<<(i%8));
						}
						/*Überprüfen auf Ende von String*/
						if(++(*CharPos) > ASCII[String[*StringPos]][8]){
							*CharPos = 0;
							Space = SPACE_BETWEEN_CHARACTERS;
							if(String[++(*StringPos)] == '\0'){
								i++;
								while(i <= RightEdge){
									DataIn[i/8] |= (1<<(i%8));
									i++;
								}
								*StringPos = 0;
								break;
							}
						}
					}
				}
				(*Mask) <<= 1;
				if((*Mask) == (1<<6)){
					Fin = FIN_STRING;
				}
				break;
				case ALIGN_RIGHT:
					Length = STRING_GetLength(String,SPACE_BETWEEN_CHARACTERS);
				for(i = LeftEdge; i <= RightEdge - Length; i++){
					DataIn[i/8] |= (1<<(i%8));
				}
				for(i = RightEdge-Length+1; i <= RightEdge; i++){
					if(Space != 0){
						Space--;
						DataIn[i/8] |= (1<<(i%8));
					}else{
						if(ASCII[String[*StringPos]][*CharPos] & (*Mask)){
							DataIn[i/8] &= ~(1<<(i%8));
						}else{
							DataIn[i/8] |= (1<<(i%8));
						}
						/*Überprüfen auf Ende von String*/
						if(++(*CharPos) > ASCII[String[*StringPos]][8]){
							*CharPos = 0;
							Space = SPACE_BETWEEN_CHARACTERS;
							if(String[++(*StringPos)] == '\0'){
								i++;
								while(i <= RightEdge){
									DataIn[i/8] |= (1<<(i%8));
									i++;
								}
								*StringPos = 0;
								break;
							}
						}
					}
				}
				(*Mask) <<= 1;
				if((*Mask) == (1<<6)){
					Fin = FIN_STRING;
				}
				break;
		}
			break;
		case DOWN:
				/*DataIn zuweisen*/
		switch(Align){
			case ALIGN_MID:
				Length = STRING_GetLength(String,SPACE_BETWEEN_CHARACTERS);
				(Length < (RightEdge - LeftEdge)+1) ? (Offset = ((((RightEdge-LeftEdge)+1-Length)/2)+(Length%2))) : (Offset = 0);
				for(i = LeftEdge; i < LeftEdge + Offset; i++){
					DataIn[i/8] |= (1<<(i%8));
				}
				for(i = LeftEdge + Offset; i <= RightEdge; i++){
					if(Space != 0){
						Space--;
						DataIn[i/8] |= (1<<(i%8));
					}else{
						if(ASCII[String[*StringPos]][*CharPos] & (*Mask)){
							DataIn[i/8] &= ~(1<<(i%8));
						}else{
							DataIn[i/8] |= (1<<(i%8));
						}
						/*Überprüfen auf Ende von String*/
						if(++(*CharPos) > ASCII[String[*StringPos]][8]){
							*CharPos = 0;
							Space = SPACE_BETWEEN_CHARACTERS;
							if(String[++(*StringPos)] == '\0'){
								i++;
								while(i <= RightEdge){
									DataIn[i/8] |= (1<<(i%8));
									i++;
								}
								*StringPos = 0;
								break;
							}
						}
					}
				}
				(*Mask) >>= 1;
				if((*Mask) == (1<<0)){
					Fin = FIN_STRING;
				}
				break;
			case ALIGN_LEFT:
				for(i = LeftEdge; i <= RightEdge; i++){
					if(Space != 0){
						Space--;
						DataIn[i/8] |= (1<<(i%8));
					}else{
						if(ASCII[String[*StringPos]][*CharPos] & (*Mask)){
							DataIn[i/8] &= ~(1<<(i%8));
						}else{
							DataIn[i/8] |= (1<<(i%8));
						}
						/*Überprüfen auf Ende von String*/
						if(++(*CharPos) > ASCII[String[*StringPos]][8]){
							*CharPos = 0;
							Space = SPACE_BETWEEN_CHARACTERS;
							if(String[++(*StringPos)] == '\0'){
								i++;
								while(i <= RightEdge){
									DataIn[i/8] |= (1<<(i%8));
									i++;
								}
								*StringPos = 0;
								break;
							}
						}
					}
				}
				(*Mask) >>= 1;
				if((*Mask) == (1<<0)){
					Fin = FIN_STRING;
				}
				break;
				case ALIGN_RIGHT:
					Length = STRING_GetLength(String,SPACE_BETWEEN_CHARACTERS);
				for(i = LeftEdge; i <= RightEdge - Length; i++){
					DataIn[i/8] |= (1<<(i%8));
				}
				for(i = RightEdge-Length+1; i <= RightEdge; i++){
					if(Space != 0){
						Space--;
						DataIn[i/8] |= (1<<(i%8));
					}else{
						if(ASCII[String[*StringPos]][*CharPos] & (*Mask)){
							DataIn[i/8] &= ~(1<<(i%8));
						}else{
							DataIn[i/8] |= (1<<(i%8));
						}
						/*Überprüfen auf Ende von String*/
						if(++(*CharPos) > ASCII[String[*StringPos]][8]){
							*CharPos = 0;
							Space = SPACE_BETWEEN_CHARACTERS;
							if(String[++(*StringPos)] == '\0'){
								i++;
								while(i <= RightEdge){
									DataIn[i/8] |= (1<<(i%8));
									i++;
								}
								*StringPos = 0;
								break;
							}
						}
					}
				}
				(*Mask) >>= 1;
				if((*Mask) == (1<<0)){
					Fin = FIN_STRING;
				}
				break;
		}
		break;
		default:
			break;
	}
	return Fin;
}


//AM2320

AM2320 AM2320_Init(I2C_HandleTypeDef *I2C_Handle, uint8_t device_addr)
{
	AM2320 init;
	init.AM2320_Handle=I2C_Handle;
	init.addr=device_addr;
	return init;
}

HAL_StatusTypeDef AM2320_ReadValue(AM2320 *Handle)
{
	HAL_StatusTypeDef Status = HAL_OK;
	Status = HAL_I2C_Master_Transmit(Handle->AM2320_Handle,Handle->addr,0x00,0,HAL_MAX_DELAY);
	if(Status != HAL_OK){return Status;}
	Status = HAL_I2C_Master_Transmit(Handle->AM2320_Handle,Handle->addr,Registers,3,HAL_MAX_DELAY);
	if(Status != HAL_OK){return Status;}
	Status = HAL_I2C_Master_Receive(Handle->AM2320_Handle,Handle->addr,Handle->data,8,HAL_MAX_DELAY);
	return Status;
}

HAL_StatusTypeDef AM2320_GetValue(AM2320 *Handle,float *temp,float *hum)
{
	HAL_StatusTypeDef Status = HAL_OK;
	Status = AM2320_ReadValue(Handle);
	if(Status != HAL_OK){return Status;}
	uint16_t temperature=0;
	temperature = (Handle->data[5] | Handle->data[4] << 8);
	if (temperature & 0x8000) {
		temperature = -(int16_t) (temperature & 0x7fff);
	} else {
		temperature = (int16_t) temperature;
	}
	*temp = (float) temperature / 10.0;
	*hum = (float) (Handle->data[3] | (Handle->data[2] << 7)) / 10.0;
	return Status;
}



//DS3231


HAL_StatusTypeDef DS3231_SetTime(DS3231_TIME Time, I2C_HandleTypeDef * I2C_Handle)
{
	
	uint8_t Tx[3] = {0};
	uint8_t StartAddr = 0x00;
										
	Tx[0] = DS3231_DecToBcd(Time.Seconds);				// Seconds
	Tx[1] = DS3231_DecToBcd(Time.Minutes);				// Minutes
	Tx[2] = DS3231_DecToBcd(Time.Hours);					// Hours
	if(Time.TimeFormat == 1)											// 12 Hours Format
	{
		Tx[2] |= (1<<6);
		
		if(Time.AM_PM == 0)													// AM
		{
			Tx[2] &= ~(1<<5);										
		}
		else																				// PM
		{
			Tx[2] |= (1<<5);
		}
	}		
	else																					// 24 Hours Format
	{
		Tx[2] &= ~(1<<6);
	}								
	return HAL_I2C_Mem_Write(I2C_Handle,DS3231,StartAddr,1,Tx,3,HAL_MAX_DELAY);
}
	

HAL_StatusTypeDef DS3231_GetTime(DS3231_TIME *Time, I2C_HandleTypeDef * I2C_Handle)
{
	
	uint8_t Rx[3] = {0};
	uint8_t StartAddr = 0x00;
	HAL_StatusTypeDef Status = HAL_OK;
	
	//Read Data
	if(Status == HAL_OK)
	{
		Status = HAL_I2C_Mem_Read(I2C_Handle,DS3231,StartAddr,1,Rx,3,HAL_MAX_DELAY);
	}
	
	//Convert to Dec
	if(Status != HAL_OK)
	{
		//No further action
	}
	else
	{
		Time->Seconds = DS3231_BcdToDec(Rx[0]);	// Seconds
		Time->Minutes = DS3231_BcdToDec(Rx[1]);	// Minutes
		
		if(Rx[2] & (1 << 6))										// 12 Hours Format
		{
			Time->TimeFormat = 1;
			if(Rx[2] & (1 << 5))									// PM
			{
				Time->AM_PM = 1;
			}
			else																	// AM
			{
				Time->AM_PM = 0;
			}
			Rx[2] &= ~(1 << 6);
		}
		else																		// 24 Hours Format
		{
			Time->TimeFormat = 0;
		}
		
		Time->Hours = DS3231_BcdToDec(Rx[2]);		// Hours
	}
	return Status;
}


HAL_StatusTypeDef DS3231_SetDate(DS3231_DATE Date, I2C_HandleTypeDef * I2C_Handle)
{
	uint8_t Tx[4] = {0};
	uint8_t StartAddr = 0x03;
									
	Tx[0] = DS3231_DecToBcd(Date.Day);
	Tx[1] = DS3231_DecToBcd(Date.Date);
	Tx[2] = DS3231_DecToBcd(Date.Month);
	Tx[3] = DS3231_DecToBcd(Date.Year);
	
	return HAL_I2C_Mem_Write(I2C_Handle,DS3231,StartAddr,1,Tx,4,HAL_MAX_DELAY);
}


HAL_StatusTypeDef DS3231_GetDate(DS3231_DATE *Date, I2C_HandleTypeDef * I2C_Handle)
{
	uint8_t Rx[4] = {0};
	uint8_t StartAddr = 0x03;
	HAL_StatusTypeDef Status = HAL_OK;
	
	//Read Data
	if(Status == HAL_OK)
	{
		Status = HAL_I2C_Mem_Read(I2C_Handle,DS3231,StartAddr,1,Rx,4,HAL_MAX_DELAY);
	}
	
	//Convert to Dec
	if(Status != HAL_OK)
	{
		//No further action
	}
	else
	{
		Date->Day = DS3231_BcdToDec(Rx[0]);
		Date->Date = DS3231_BcdToDec(Rx[1]);
		if(Rx[2] & (1<<7)){Date->Century = 1; Rx[2] &= ~(1<<7);}
		Date->Month = DS3231_BcdToDec(Rx[2]);
		Date->Year = DS3231_BcdToDec(Rx[3]);
	}
	return Status;
}


HAL_StatusTypeDef DS3231_SetAlarm1(DS3231_ALARM Alarm, I2C_HandleTypeDef * I2C_Handle)
{
	uint8_t Tx[4] = {0};
	uint8_t StartAddr = 0x07;
	
	Tx[0] = DS3231_DecToBcd(Alarm.Seconds);
	Tx[1] = DS3231_DecToBcd(Alarm.Minutes);
	
	if(Alarm.TimeFormat == 1)																															//12 Hours Format
	{
		Tx[2] = DS3231_DecToBcd(Alarm.Hours); Tx[2] |= (1<<6);
		if(Alarm.AM_PM == 1){Tx[2] |= (1<<5);}																							//AM
		else{Tx[2] &= ~(1<<5);}																															//PM
	}			
	else																																									//24 Hours Format
	{
		Tx[2] = DS3231_DecToBcd(Alarm.Hours); Tx[3] &= ~(1<<6);
	}													
	
	if(Alarm.DY_DT == 1){Tx[3] = DS3231_DecToBcd(Alarm.Day); Tx[3] |= (1<<6);}						// Day matching Alarm
	else{Tx[3] = DS3231_DecToBcd(Alarm.Date); Tx[3] &= ~(1<<6);}													// Date matching Alarm
	
	//Set Masks
	if(Alarm.AlarmMask & (1 << 0)){Tx[0] |= (1<<7);}																			// Seconds
	else{Tx[0] &= ~(1<<7);}
	if(Alarm.AlarmMask & (1 << 1)){Tx[1] |= (1<<7);}																			// Minutes
	else{Tx[1] &= ~(1<<7);}
	if(Alarm.AlarmMask & (1 << 2)){Tx[2] |= (1<<7);}																			// Hours
	else{Tx[2] &= ~(1<<7);}
	if(Alarm.AlarmMask & (1 << 3)){Tx[3] |= (1<<7);}																			// Day/Date
	else{Tx[3] &= ~(1<<7);}
	
	return HAL_I2C_Mem_Write(I2C_Handle,DS3231,StartAddr,1,Tx,4,HAL_MAX_DELAY);
}



HAL_StatusTypeDef DS3231_GetAlarm1(DS3231_ALARM *Alarm, I2C_HandleTypeDef * I2C_Handle)
{
	uint8_t Rx[4] = {0};
	uint8_t StartAddr = 0x07;
	HAL_StatusTypeDef Status = HAL_OK;
	
	//Set Pointer
	Status = HAL_I2C_Master_Transmit(I2C_Handle,DS3231,&StartAddr,1,HAL_MAX_DELAY);
	
	//Read Data
	if(Status == HAL_OK)
	{
		Status = HAL_I2C_Master_Receive(I2C_Handle,DS3231,Rx,4,HAL_MAX_DELAY);
	}
	
	//Convert to Dec
	if(Status != HAL_OK)
	{
		//No further action
	}
	else
	{
		//Check Masks
		Alarm->AlarmMask = 0;
		if(Rx[0] & (1<<7)){Alarm->AlarmMask |= (1<<0); Rx[0] &= ~(1<<7);}
		if(Rx[1] & (1<<7)){Alarm->AlarmMask |= (1<<1); Rx[1] &= ~(1<<7);}
		if(Rx[2] & (1<<7)){Alarm->AlarmMask |= (1<<2); Rx[2] &= ~(1<<7);}
		if(Rx[3] & (1<<7)){Alarm->AlarmMask |= (1<<3); Rx[3] &= ~(1<<7);}
		
		//Convert to Dec
		Alarm->Seconds = DS3231_BcdToDec(Rx[0]);
		Alarm->Minutes = DS3231_BcdToDec(Rx[1]);
		
		if(Rx[2] & (1 << 6))
		{
			Alarm->TimeFormat = 1; Rx[2] &= ~(1<<6);
			if(Rx[2] & (1 << 5)){Alarm->AM_PM = 1; Rx[2] &= ~(1<<5);}
			else{Alarm->AM_PM = 0;}
		}
		else
		{
			Alarm->TimeFormat = 0;
		}
		Alarm->Hours = DS3231_BcdToDec(Rx[2]); 
		
		if(Rx[3] & (1 << 6)){Alarm->DY_DT = 1; Rx[3] &= ~(1<<6); Alarm->Day = DS3231_BcdToDec(Rx[3]);}
		else{Alarm->DY_DT = 0; Alarm->Date = DS3231_BcdToDec(Rx[3]);}
	}
	
	return Status;
}

HAL_StatusTypeDef DS3231_SetAlarm2(DS3231_ALARM Alarm, I2C_HandleTypeDef * I2C_Handle)
{
	uint8_t Tx[4] = {0};
	uint8_t StartAddr = 0x0B;
	
	Tx[0] = StartAddr;
	Tx[1] = DS3231_DecToBcd(Alarm.Minutes);
	
	if(Alarm.TimeFormat == 1)																															//12 Hours Format
	{
		Tx[2] = DS3231_DecToBcd(Alarm.Hours); Tx[2] |= (1<<6);
		if(Alarm.AM_PM == 1){Tx[2] |= (1<<5);}																							//AM
		else{Tx[2] &= ~(1<<5);}																															//PM
	}			
	else																																									//24 Hours Format
	{
		Tx[2] = DS3231_DecToBcd(Alarm.Hours); Tx[3] &= ~(1<<6);
	}													
	
	if(Alarm.DY_DT == 1){Tx[3] = DS3231_DecToBcd(Alarm.Day); Tx[3] |= (1<<6);}						// Day matching Alarm
	else{Tx[3] = DS3231_DecToBcd(Alarm.Date); Tx[3] &= ~(1<<6);}													// Date matching Alarm
	
	//Set Masks
	if(Alarm.AlarmMask & (1 << 1)){Tx[1] |= (1<<7);}																			// Minutes
	else{Tx[1] &= ~(1<<7);}
	if(Alarm.AlarmMask & (1 << 2)){Tx[2] |= (1<<7);}																			// Hours
	else{Tx[2] &= ~(1<<7);}
	if(Alarm.AlarmMask & (1 << 3)){Tx[3] |= (1<<7);}																			// Day/Date
	else{Tx[3] &= ~(1<<7);}
	
	return HAL_I2C_Master_Transmit(I2C_Handle,DS3231,Tx,4,HAL_MAX_DELAY);
}


HAL_StatusTypeDef DS3231_GetAlarm2(DS3231_ALARM *Alarm, I2C_HandleTypeDef * I2C_Handle)
{
	uint8_t Rx[3] = {0};
	uint8_t StartAddr = 0x0B;
	HAL_StatusTypeDef Status = HAL_OK;
	
	//Set Pointer
	Status = HAL_I2C_Master_Transmit(I2C_Handle,DS3231,&StartAddr,1,HAL_MAX_DELAY);
	
	//Read Data
	if(Status == HAL_OK)
	{
		Status = HAL_I2C_Master_Receive(I2C_Handle,DS3231,Rx,3,HAL_MAX_DELAY);
	}
	
	//Convert to Dec
	if(Status != HAL_OK)
	{
		//No further action
	}
	else
	{
		//Check Masks
		Alarm->AlarmMask = 0;
		if(Rx[0] & (1<<7)){Alarm->AlarmMask |= (1<<1); Rx[0] &= ~(1<<7);}
		if(Rx[1] & (1<<7)){Alarm->AlarmMask |= (1<<2); Rx[1] &= ~(1<<7);}
		if(Rx[2] & (1<<7)){Alarm->AlarmMask |= (1<<3); Rx[2] &= ~(1<<7);}
		
		//Convert to Dec
		Alarm->Minutes = DS3231_BcdToDec(Rx[0]);
		
		if(Rx[1] & (1 << 6))
		{
			Alarm->TimeFormat = 1; Rx[1] &= ~(1<<6);
			if(Rx[1] & (1 << 5)){Alarm->AM_PM = 1; Rx[1] &= ~(1<<5);}
			else{Alarm->AM_PM = 0;}
		}
		else
		{
			Alarm->TimeFormat = 0;
		}
		Alarm->Hours = DS3231_BcdToDec(Rx[1]); 
		
		if(Rx[2] & (1 << 6)){Alarm->DY_DT = 1; Rx[2] &= ~(1<<6); Alarm->Day = DS3231_BcdToDec(Rx[2]);}
		else{Alarm->DY_DT = 0; Alarm->Date = DS3231_BcdToDec(Rx[2]);}
	}
	
	return Status;
}

HAL_StatusTypeDef DS3231_GetAll(DS3231_REGISTERS *Registers, I2C_HandleTypeDef * I2C_Handle)
{
	uint8_t Rx[19] = {0};
	HAL_StatusTypeDef Status = HAL_OK;
	
	
	
	Status = HAL_I2C_Mem_Read(I2C_Handle,DS3231,0x00,1,Rx,19,HAL_MAX_DELAY);
	
	if(Status == HAL_OK)
	{
		//Time
		Registers->TimeSeconds = DS3231_BcdToDec(Rx[0]);
		Registers->TimeMinutes = DS3231_BcdToDec(Rx[1]);
		
		if(Rx[2] & (1 << 6))			// -> 12 Hours Format
		{
			Registers->TimeFormat = HF12;
			
			if(Rx[2] & (1 << 5))		// -> PM
			{
				Registers->TimeAmPm = PM;
			}
			else										// -> AM
			{
				Registers->TimeAmPm = AM;
			}
			Rx[2] &= ~((1 << 6) | (1 << 5));
		}
		else											// -> 24 Hours Format
		{
			Registers->TimeFormat = HF24;
		}
		Registers->TimeHours = DS3231_BcdToDec(Rx[2]);
		
		//Date
		Registers->DateDay = DS3231_BcdToDec(Rx[3]);
		Registers->DateDate = DS3231_BcdToDec(Rx[4]);
		
		if(Rx[5] & (1 << 7))			// -> Century Change
		{
			Registers->DateCentury = 1;
		}
		else
		{
			Registers->DateCentury = 0;
		}
		Rx[5] &= ~(1 << 7); 
		Registers->DateMonth = DS3231_BcdToDec(Rx[5]);
		Registers->DateYear = DS3231_BcdToDec(Rx[6]);
		
		//Alarm 1
		Registers->Alarm1Mask = 0;
		if(Rx[7] & (1 << 7)){Registers->Alarm1Mask |= (1 << 0); Rx[7] &= ~(1<<7);}
		if(Rx[8] & (1 << 7)){Registers->Alarm1Mask |= (1 << 1); Rx[8] &= ~(1<<7);}
		if(Rx[9] & (1 << 7)){Registers->Alarm1Mask |= (1 << 2); Rx[9] &= ~(1<<7);}
		if(Rx[10] & (1 << 7)){Registers->Alarm1Mask |= (1 << 3); Rx[10] &= ~(1<<7);}
		
		Registers->Alarm1Seconds = DS3231_BcdToDec(Rx[7]);
		Registers->Alarm1Minutes = DS3231_BcdToDec(Rx[8]);
		
		if(Rx[9] & (1 << 6))			// -> 12 Hours Format
		{
			Registers->Alarm1Format = HF12;
			
			if(Rx[9] & (1 << 5))		// -> PM
			{
				Registers->Alarm1AmPm = PM;
			}
			else										// -> AM
			{
				Registers->Alarm1AmPm = AM;
			}
			Rx[9] &= ~((1 << 6) | (1 << 5));
		}
		else											// -> 24 Hours Format
		{
			Registers->Alarm1Format = HF24;
		}
		Registers->Alarm1Hours = DS3231_BcdToDec(Rx[9]);
		
		if(Rx[10] & (1 << 6))			// -> DyDt = Day
		{
			Rx[10] &= ~(1 << 6);
			Registers->Alarm1DyDt = 1;
			Registers->Alarm1Date = 0;
			Registers->Alarm1Day = DS3231_BcdToDec(Rx[10]);
		}
		else											// -> DyDt = Date
		{
			Registers->Alarm1DyDt = 0;
			Registers->Alarm1Day = 0;
			Registers->Alarm1Date = DS3231_BcdToDec(Rx[10]);
		}
		
		//Alarm 2
		Registers->Alarm2Mask = 0;
		if(Rx[11] & (1 << 7)){Registers->Alarm1Mask |= (1 << 1); Rx[11] &= ~(1<<7);}
		if(Rx[12] & (1 << 7)){Registers->Alarm1Mask |= (1 << 2); Rx[12] &= ~(1<<7);}
		if(Rx[13] & (1 << 7)){Registers->Alarm1Mask |= (1 << 3); Rx[13] &= ~(1<<7);}
		
		Registers->Alarm2Minutes = DS3231_BcdToDec(Rx[11]);
		
		if(Rx[12] & (1 << 6))			// -> 12 Hours Format
		{
			Registers->Alarm2Format = HF12;
			
			if(Rx[12] & (1 << 5))		// -> PM
			{
				Registers->Alarm2AmPm = PM;
			}
			else										// -> AM
			{
				Registers->Alarm2AmPm = AM;
			}
			Rx[12] &= ~((1 << 6) | (1 << 5));
		}
		else											// -> 24 Hours Format
		{
			Registers->Alarm2Format = HF24;
		}
		Registers->Alarm2Hours = DS3231_BcdToDec(Rx[12]);
		
		if(Rx[13] & (1 << 6))			// -> DyDt = Day
		{
			Rx[13] &= ~(1 << 6);
			Registers->Alarm2DyDt = 1;
			Registers->Alarm2Date = 0;
			Registers->Alarm2Day = DS3231_BcdToDec(Rx[13]);
		}
		else											// -> DyDt = Date
		{
			Registers->Alarm2DyDt = 0;
			Registers->Alarm2Day = 0;
			Registers->Alarm2Date = DS3231_BcdToDec(Rx[13]);
		}
		
		//Control
		Registers->Control = Rx[14];
		
		//Control & Status
		Registers->ControlStatus = Rx[15];
		
		//Aging Offset
		Registers->AgingOffset = Rx[16];
		
		//Msb of Temp
		Registers->MsbOfTemp = Rx[17];
		
		//Lsb of Temp
		Registers->LsbOfTemp = Rx[18];
			
	}
	else
	{
		// No further action
	}
	
	return Status;
	
}


//Sonstiges

uint8_t DS3231_DecToBcd(uint8_t Dec)
{
	uint8_t Msb = 0, Lsb = 0;
	
	Lsb = Dec % 10;
	Msb = Dec / 10;
	Msb <<= 4;
	
	return Msb + Lsb;
}


uint8_t DS3231_BcdToDec(uint8_t Bcd)
{
	uint8_t Msb = 0, Lsb = 0;
	
	Lsb = Bcd & 0x0F;
	Msb = Bcd >> 4;
	
	return Msb * 10 + Lsb;
}


float GetMin(char Array[][4], uint8_t Len, uint8_t Idx)
{
	float Min;
	
	 if(Idx>= Len-2)
    {
        if(atof(Array[Idx]) < atof(Array[Idx + 1]))
            return atof(Array[Idx]);
        else
            return atof(Array[Idx + 1]);
    }
		
		Min = GetMin(Array,Len,Idx+1);
		
		if(atof(Array[Idx]) < Min)
        return atof(Array[Idx]);
    else
        return Min;
}

float GetMax(char Array[][4], uint8_t Len, uint8_t Idx)
{
	float Max;
	
	 if(Idx>= Len-2)
    {
        if(atof(Array[Idx]) > atof(Array[Idx + 1]))
            return atof(Array[Idx]);
        else
            return atof(Array[Idx + 1]);
    }
		
		Max = GetMax(Array,Len,Idx+1);
		
		if(atof(Array[Idx]) > Max)
        return atof(Array[Idx]);
    else
        return Max;
}




//void RGB_Test(void)
//{
//	HAL_GPIO_WritePin(IN1_GPIO_Port,IN1_Pin,GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(IN2_GPIO_Port,IN2_Pin,GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(IN3_GPIO_Port,IN3_Pin,GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(IN4_GPIO_Port,IN4_Pin,GPIO_PIN_SET);
//	HAL_GPIO_WritePin(IN5_GPIO_Port,IN5_Pin,GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(IN6_GPIO_Port,IN6_Pin,GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(IN7_GPIO_Port,IN7_Pin,GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(IN8_GPIO_Port,IN8_Pin,GPIO_PIN_RESET);
//}