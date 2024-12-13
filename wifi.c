#include "main.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <main.h>
#include "wifi.h"



 //const char* weather_server_URL = "api.openweathermap.org";
const char* weather_server_IP = "178.128.122.9";
const int WeatherIP_length =13;
const int WeatherURL_length=22;


const char* weather_server_URL = "api.openweathermap.org";
const char* time_server_URL0 = "AT+SOCKA1=UDPC,0.cn.pool.ntp.org,123\r";
const char* time_server_URL1 = "AT+SOCKA1=UDPC,1.cn.pool.ntp.org,123\r";
const char* time_server_URL2 = "AT+SOCKA1=UDPC,2.cn.pool.ntp.org,123\r";
const char* time_server_URL3 = "AT+SOCKA1=UDPC,3.cn.pool.ntp.org,123\r";
const char* time_server_URL4 = "AT+SOCKA1=UDPC,cn.pool.ntp.org,123\r";


uint32_t Transmit_Timestamp=0;
uint8_t receive_mode=0;
uint8_t rx_string1[max1]={0};	//receive buffer for Timestamp
uint8_t rx_string2[max2]={0};
uint8_t rx_timestamp[max1]={0};	
struct weathertype forecast_weather[forecast_length]={0};
struct tm gmt_time={0};
 
 
 void GetTime(void){
	 
	
	 
	SetTimeServerURL(time_server_URL4);	
	
	for(int i=0;i<max2;i++){
		rx_string2[i]=NULL;
	}

	
	SNTP_HEADER_TypeDef SntpHeader ={0};
	SntpHeader.Flag=35;
	//receive_mode=1;
	HAL_UART_Receive_IT (&huart1, rx_string2, max2);
	uint8_t SendCounter=0;
	
		while(rx_string2[0]==NULL){
			if (SendCounter == 4){ 
				HAL_Delay(1000);
	SetTimeServerURL(time_server_URL4);
	Wifi_Uart_Weather("+++",3);			//Switch to AT+ Command part1
	
	Wifi_Uart_Weather("a",1);				//Switch to AT+ Command part2
	Wifi_Uart_Weather("AT+Z\r", 5);	//Restart the wifi module
	Wifi_Uart_Weather("AT+ENTM\r", 8);	//end AT+command mode & switch back to Trans-Mode
	HAL_Delay(5000);
	GetTime();//SetTimeServerURL(time_server_URL4);
				}	
			/*	}
			else if (SendCounter ==12){SetTimeServerURL(time_server_URL4);	}
			else if (SendCounter ==16){SetTimeServerURL(time_server_URL4);	}*/
			//HAL_UART_Transmit(&huart2,(uint8_t*)"Wait...\r\n", 9,100);							//wartebildschirm!!!
			Wifi_Uart_Time("#00000000000000000000000000000000000000000000000", 48);
			HAL_Delay(3000);
			SendCounter++;
}
		
		for(int i=0;i<max1;i++){
	rx_timestamp[i]=(uint8_t)rx_string2[i];
	}
		
		Transmit_Timestamp+=(rx_timestamp[40]<<24);
		Transmit_Timestamp+=(rx_timestamp[41]<<16);
		Transmit_Timestamp+=(rx_timestamp[42]<<8);
		Transmit_Timestamp+=(rx_timestamp[43]<<0);
	
		Transmit_Timestamp-=2208988800; 				//Time from 1900 to 1970 in seconds 
		Transmit_Timestamp+=((3600*Timezone)+3);
		gmt_time = *localtime(&Transmit_Timestamp);
	
//		HAL_UART_Transmit(&huart2,(uint8_t*)"\n\r", 2,100);
//		HAL_UART_Transmit(&huart2,(uint8_t*)"\n\r", 2,100);
//		HAL_UART_Transmit(&huart2,(uint8_t*)rx_timestamp, 100,100);
}
 



void SetGMT_to_Local(void){
	if(gmt_time.tm_hour>=(24-Timezone)){
		
		gmt_time.tm_hour+=Timezone-24;
		
		if(gmt_time.tm_wday==0){gmt_time.tm_wday=1;}
		else if(gmt_time.tm_wday==1){gmt_time.tm_wday=2;}
		else if(gmt_time.tm_wday==2){gmt_time.tm_wday=3;}
		else if(gmt_time.tm_wday==3){gmt_time.tm_wday=4;}
		else if(gmt_time.tm_wday==4){gmt_time.tm_wday=5;}
		else if(gmt_time.tm_wday==5){gmt_time.tm_wday=6;}
		else if(gmt_time.tm_wday==6){gmt_time.tm_wday=0;}
		
		if (gmt_time.tm_mon==12&&gmt_time.tm_mday==31){gmt_time.tm_mday=1;gmt_time.tm_mon=1;gmt_time.tm_year++;}
		else if(gmt_time.tm_mon==11&&gmt_time.tm_mday==30){gmt_time.tm_mday=1;gmt_time.tm_mon++;}
		else if(gmt_time.tm_mon==10&&gmt_time.tm_mday==31){gmt_time.tm_mday=1;gmt_time.tm_mon++;}
		else if(gmt_time.tm_mon==9&&gmt_time.tm_mday==30){gmt_time.tm_mday=1;gmt_time.tm_mon++;}
		else if(gmt_time.tm_mon==8&&gmt_time.tm_mday==31){gmt_time.tm_mday=1;gmt_time.tm_mon++;}
		else if(gmt_time.tm_mon==7&&gmt_time.tm_mday==31){gmt_time.tm_mday=1;gmt_time.tm_mon++;}
		else if(gmt_time.tm_mon==6&&gmt_time.tm_mday==30){gmt_time.tm_mday=1;gmt_time.tm_mon++;}
		else if(gmt_time.tm_mon==5&&gmt_time.tm_mday==31){gmt_time.tm_mday=1;gmt_time.tm_mon++;}
		else if(gmt_time.tm_mon==4&&gmt_time.tm_mday==30){gmt_time.tm_mday=1;gmt_time.tm_mon++;}
		else if(gmt_time.tm_mon==3&&gmt_time.tm_mday==31){gmt_time.tm_mday=1;gmt_time.tm_mon++;}
		
		else if(gmt_time.tm_mon==2&&gmt_time.tm_mday==29&&(gmt_time.tm_year==20||gmt_time.tm_year==24||gmt_time.tm_year==28||gmt_time.tm_year==32||gmt_time.tm_year==36||
						gmt_time.tm_year==40||gmt_time.tm_year==44||gmt_time.tm_year==48||gmt_time.tm_year==52||gmt_time.tm_year==56||gmt_time.tm_year==60||gmt_time.tm_year==64||
						gmt_time.tm_year==68||gmt_time.tm_year==72||gmt_time.tm_year==76||gmt_time.tm_year==80||gmt_time.tm_year==84||gmt_time.tm_year==88||gmt_time.tm_year==92||
						gmt_time.tm_year==96||gmt_time.tm_year==00)){gmt_time.tm_mday=1;gmt_time.tm_mon++;} 	//leap year
		else if(gmt_time.tm_mon==2&&gmt_time.tm_mday==28){gmt_time.tm_mday=1;gmt_time.tm_mon++;}	//no leap year
		
		else if(gmt_time.tm_mon==1&&gmt_time.tm_mday==31){gmt_time.tm_mday=1;gmt_time.tm_mon++;}
		else{gmt_time.tm_mday++;}
		
	}
	else{gmt_time.tm_hour+=Timezone;}
}


void GetWeather(void){
	SetWeatherServerURL(weather_server_URL);
	///data/2.5/forecast?id=2172797&units=metric&appid=33c2c6b47138c2ba83251eda6c71f8aa
	///data/2.5/weather?id=2172797&units=metric&appid=33c2c6b47138c2ba83251eda6c71f8aa
	int strlength= strlen("/data/2.5/weather?id=2172797&units=metric&appid=33c2c6b47138c2ba83251eda6c71f8aa");
		for(int i=0;i<max2;i++){
		rx_string2[i]=NULL;
	}
		//receive_mode=2;
	HAL_UART_Receive_IT (&huart1, rx_string2, max2);
	
		
	while(rx_string2[max2-2]==NULL){
		//HAL_UART_Transmit(&huart2,(uint8_t*)"Wait...\r\n", 9,100);
		Wifi_Uart_Weather("/data/2.5/forecast?id=1796236&units=metric&appid=33c2c6b47138c2ba83251eda6c71f8aa", 81);
		HAL_Delay(3000);

		}
	
		//ConvertWeather((char*)rx_string2);
}


void ConvertWeather(char* text){
//	HAL_UART_Transmit(&huart2,(uint8_t*)"\n\r", 2,100);
//	HAL_UART_Transmit(&huart2,(uint8_t*)"\n\r", 2,100);
//	HAL_UART_Transmit(&huart2,(uint8_t*)text, max2,100);
//	HAL_UART_Transmit(&huart2,(uint8_t*)"\n\r", 2,100);
//	HAL_UART_Transmit(&huart2,(uint8_t*)"\n\r", 2,100);
	
	int j=0;
	int counter_temp=0;
	int counter_dt_txt=0;
	int counter_main=0;
	int counter_icon=0;
	int counter_description=0;
	
	for(int j=0;j<8;j++){
	for(int i=0;i<9;i++){
	forecast_weather[j].temp[i]=NULL;}
	
	for(int i=0;i<20;i++){
	forecast_weather[j].dt_txt[i]=NULL;}
	
	for(int i=0;i<20;i++){
	forecast_weather[j].main[i]=NULL;}
	
	for(int i=0;i<20;i++){
	forecast_weather[j].description[i]=NULL;}
	
	for(int i=0;i<9;i++){
	forecast_weather[j].icon[i]=NULL;}
}
	for(int i=0;i<max2;i++){
		
		//get Temperature
				if(text[i]=='"'&&text[i+1]=='t'&&text[i+2]=='e'&&text[i+3]=='m'&&text[i+4]=='p'&&text[i+5]=='"'&&text[i+6]==':'){	
					i+=7;
					while(text[i]!='.'){
					forecast_weather[counter_temp].temp[j]=text[i];j++;
					i++;}
					j=0;counter_temp++;}
				//get the time for the forecast
				else if(text[i]=='"'&&text[i+1]=='d'&&text[i+2]=='t'&&text[i+3]=='_'&&text[i+4]=='t'&&text[i+5]=='x'&&text[i+6]=='t'&&text[i+7]=='"'&&text[i+8]==':'&&text[i+9]=='"'){	
					i+=10;
					while(text[i]!='"'){forecast_weather[counter_dt_txt].dt_txt[j]=text[i];j++;i++;}
					j=0;counter_dt_txt++;
					if(counter_dt_txt==8){break;}}
				//get the main weathertype
				else if(text[i]=='"'&&text[i+1]=='m'&&text[i+2]=='a'&&text[i+3]=='i'&&text[i+4]=='n'&&text[i+5]=='"'&&text[i+6]==':'&&text[i+7]=='"'){	
					i+=8;
					while(text[i]!='"'){forecast_weather[counter_dt_txt].main[j]=text[i];j++;i++;}
					j=0;counter_main++;}
				//get the icon id
				else if(text[i]=='"'&&text[i+1]=='i'&&text[i+2]=='c'&&text[i+3]=='o'&&text[i+4]=='n'&&text[i+5]=='"'&&text[i+6]==':'&&text[i+7]=='"'){	
					i+=8;
					while(text[i]!='"'){forecast_weather[counter_icon].icon[j]=text[i];j++;i++;}
					j=0;counter_icon++;}
				//get the closer description if weathertype
				else if(text[i]=='i'&&text[i+1]=='p'&&text[i+2]=='t'&&text[i+3]=='i'&&text[i+4]=='o'&&text[i+5]=='n'&&text[i+6]=='"'&&text[i+7]==':'&&text[i+8]=='"'){	
					i+=9;
					while(text[i]!='"'){forecast_weather[counter_description].description[j]=text[i];j++;i++;}
					j=0;counter_description++;}
	}
	
	
}

void SetWeatherServerURL(const char* WeatherServerURL){
	//HAL_UART_Transmit(&huart2,(uint8_t*)"\n\r\n\r-------------------------------------------------------------\n\r\n\r\n\r", 70,100);

	Wifi_Uart_Weather("+++",3);			//Switch to AT+ Command part1
	
	Wifi_Uart_Weather("a",1);				//Switch to AT+ Command part2
	Wifi_Uart_Weather("AT+WKMOD1=HTPC\r", 15);	//set UART1 Socket Work Mode
	Wifi_Uart_Weather("AT+SOCKA1=TCPC,api.openweathermap.org,80\r",19+22);		//set network protocol parameters
	Wifi_Uart_Weather("AT+SOCKA1\r", 10);				//query network protocol parameters
	Wifi_Uart_Weather("AT+HTPTP1=GET\r", 14);	//set mode of httpd client to GET
	
	Wifi_Uart_Weather("AT+HTPURL1=api.openweathermap.org\r", 12+22);	//set POST URL address
	
	Wifi_Uart_Weather("AT+HTPHEAD1=Accept:*/*<<CRLF>>\r", 13+18);	//set Httpd client customer defined head	
	Wifi_Uart_Weather("AT+HTPCHD1=ON\r",14);	//set Httpd client customer defined head	
	Wifi_Uart_Weather("AT+HTPSV1=api.openweathermap.org,80\r", 14+22);	//set Httpd client server address
//	Wifi_Uart_Weather("AT+Z\r", 5);	//Restart the wifi module
	Wifi_Uart_Weather("AT+ENTM\r", 8);	//end AT+command mode & switch back to Trans-Mode
	//Wifi_Uart_Weather("AT+Z\r", 5);	//Restart the wifi module
}

void SetTimeServerURL(const char* TimeServerURL){
	
		
	//HAL_UART_Transmit(&huart2,(uint8_t*)"\n\r\n\r-------------------------------------------------------------\n\r\n\r\n\r", 70,100);
	
	Wifi_Uart_Time("+++",3);			//Switch to AT+ Command part1
	
	Wifi_Uart_Time("a",1);				//Switch to AT+ Command part2
	
	Wifi_Uart_Time("AT+WKMOD1\r", 10);				//asking UART1 Socket Work Mode
	
	Wifi_Uart_Time("AT+WKMOD1=TRANS\r", 16);	//set UART1 Socket Work Mode
	
	Wifi_Uart_Time("AT+SOCKA1\r", 10);				//query network protocol parameters
	
//	Wifi_Uart_Time("AT+HTPSV1\r", 10);		//query Httpd client server address
	
	//Wifi_Uart_Time("AT+REGENA1=OFF\r",15);
//	Wifi_Uart_Time("AT+HTPHEAD1\r", 12);	//query Httpd client customer defined head	
//	SNTP_HEADER_TypeDef TimeHeader={0};
	//TimeHeader.Flag=35;
	Wifi_Uart_Time(TimeServerURL, strlen(TimeServerURL));		//set network protocol parameters
//	Wifi_Uart_Time("AT+SOCKA1\r", 10);				//query network protocol parameters
	//Wifi_Uart_Time("AT+HTPTP1=GET\r", 14);	//set mode of httpd client to GET
//	Wifi_Uart_Time("AT+PING=pool.ntp.org\r", 21);		//ping server
	//Wifi_Uart_Time("AT+HTPURL1=pool.ntp.org\r", 12+12);	//set POST URL address
//	Wifi_Uart_Time("AT+HTPHEAD1=Accept:*/*<<CRLF>>\r", 13+18);	//set Httpd client customer defined head	
//	Wifi_Uart_Time("AT+HTPCHD1=OFF\r",15);	//set Httpd client customer defined head	
//	Wifi_Uart_Time("AT+HTPHEAD1\r", 12);	//query Httpd client customer defined head	
	
//	Wifi_Uart_Time("AT+HTPSV1=pool.ntp.org,123\r", 15+12);	//set Httpd client server address

	Wifi_Uart_Time("AT+ENTM\r", 8);	//end AT+command mode & switch back to Trans-Mode
	
}

void Wifi_Uart_Time(const char* send, int length){
	for(int i=0;i<max2;i++){
		rx_string2[i]=NULL;
	}
	//HAL_UART_Transmit(&huart2,(uint8_t*)"\n\r", 2,100);
	HAL_UART_Transmit(&huart1,(uint8_t*)send, length,100);
	HAL_UART_Receive(&huart1,rx_string2, max2,100);
	//HAL_UART_Transmit(&huart2,rx_string2, max2,100);
	//HAL_UART_Transmit(&huart2,(uint8_t*)"\n\r", 2,100);
	
}

void Wifi_Uart_Weather(const char* send, int length){
	//Wifi_Uart_Time(send,length);
	for(int i=0;i<max2;i++){
		rx_string2[i]=NULL;
	}
	//HAL_UART_Transmit(&huart2,(uint8_t*)"\n\r", 2,100);
	HAL_UART_Transmit(&huart1,(uint8_t*)send, length,100);
	HAL_UART_Receive(&huart1,rx_string2, max2,100);
	//HAL_UART_Transmit(&huart2,rx_string2, max2,100);
	//HAL_UART_Transmit(&huart2,(uint8_t*)"\n\r", 2,100);
	
}

void Wifi_ATCommands(void){
	//HAL_UART_Transmit(&huart2,(uint8_t*)"\n\r\n\r-------------------------------------------------------------\n\r\n\r\n\r", 70,100);
	
	Wifi_Uart_Time("+++", 3);	
	
	Wifi_Uart_Time("a", 1);		
	
	Wifi_Uart_Time("AT+VER\r", 7);	
	
	Wifi_Uart_Time("AT+WMODE\r", 9);		

	Wifi_Uart_Time("AT+WSTA\r", 8);	
	
	Wifi_Uart_Time("AT+WSTA=TCN411,technology411\r", 29);		

	Wifi_Uart_Time("AT+WSTA\r", 8);	

	Wifi_Uart_Time("AT+WANN\r", 8);	
	
	Wifi_Uart_Time("AT+Z\r", 5);		
	
	Wifi_Uart_Time("AT+WSLK\r", 9);	
	
	Wifi_Uart_Time("AT+ENTM\r", 8);		
	
}

