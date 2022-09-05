//==============================================================================
//
// Title:		EL205-1
// Purpose:		A short description of the application.
//
// Created on:	08.06.2021 at 13:08:11 by qe.
// Copyright:	qwe. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include "EL205-1.h"
#include "toolbox.h"
#include <rs232.h> 
#include <stdbool.h>
#define numberOfbytes 21
//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables

static int panelHandle = 0;

//==============================================================================
// Static functions

//==============================================================================
// Global variables
unsigned char outRegister = 0;
int com;  
int boxs[numberOfbytes] = {PANEL_BYTE_0, PANEL_BYTE_1, PANEL_BYTE_2, PANEL_BYTE_3, PANEL_BYTE_4, PANEL_BYTE_5, PANEL_BYTE_6, PANEL_BYTE_7,
			    		   PANEL_BYTE_8, PANEL_BYTE_9, PANEL_BYTE_10, PANEL_BYTE_11, PANEL_BYTE_12, PANEL_BYTE_13, PANEL_BYTE_14, PANEL_BYTE_15,
			   			   PANEL_BYTE_16, PANEL_BYTE_17, PANEL_BYTE_18, PANEL_BYTE_19, PANEL_BYTE_20, PANEL_BYTE_21, PANEL_BYTE_22, PANEL_BYTE_23};
int array_test[] = {0x1C, 0x05, 0x03, 0x80, 0x01}; //oanoiaay iinueea
int speed_125[] = {0x1C, 0x05, 0x06, 0x80, 0x46, 0x03, 0x78, 0x00}; //nei?inou 125 eA/n
int speed_250[] = {0x1C, 0x05, 0x06, 0x80, 0x46, 0x03, 0x78, 0x01}; //nei?inou 250 eA/n    
int speed_500[] = {0x1C, 0x05, 0x06, 0x80, 0x46, 0x03, 0x78, 0x02}; //nei?inou 125 eA/n 
int speed_get[] = {0x1C, 0x05, 0x05, 0x80, 0x46, 0x03, 0x00}; //cai?in nei?inoe iaiaia 
int array_test1[] = {0x1C, 0x05, 0x0B, 0x00, 0x24, 0xAA, 0x07, 0x05, 0x23, 0x24, 0x25, 0x26, 0x27}; //oanoiaay iinueea   
int mass_test[] = {0x87, 0x5A, 0x14, 0x73, 0xB2, 0x40, 0x37, 0xF5, 0x07, 0x00, 0x00, 0x00, 0x08, 0x01, 0x00, 0x17, 0x76, 0xFE, 0xD6, 0xD1, 0x7F, 0xF6, 0x48};
//==============================================================================
// Global functions
void f(); 
void eventCOM();
void ShowBytes(char str[], int mass[], int lengthMass);  
/// HIFN The main entry-point function.
int main (int argc, char *argv[])
{
	int error = 0;
	
	/* initialize and load resources */
	nullChk (InitCVIRTE (0, argv, 0));
	errChk (panelHandle = LoadPanel (0, "EL205-1.uir", PANEL));
	
	/* display the panel and run the user interface */									    
	errChk (DisplayPanel (panelHandle));
	errChk (RunUserInterface ());

Error:
	/* clean up */
	if (panelHandle > 0)
		DiscardPanel (panelHandle);
	return 0;
}

//==============================================================================
// UI callback function prototypes

/// HIFN Exit when the user dismisses the panel.
int CVICALLBACK panelCB (int panel, int event, void *callbackData,
		int eventData1, int eventData2)
{
	if (event == EVENT_CLOSE)
		QuitUserInterface (0);
	return 0;
}
//============================================================================== 
//Функция расчета котнрольной суммы
//==============================================================================
int CalcCheckSum(int array[], int lenght)
{
	int CheckSum = 0;
    int indexStartByte = 2;

    for (int i = indexStartByte; i < lenght; i++)
    {
        CheckSum ^= array[i];
    }
	
	return CheckSum; 
}
//============================================================================== 
//Функция определения команды
//==============================================================================
void definingCommand(int mass[], int length)
{
	double current;
	double voltage;
	
	for(int i = 0; i < length - 1; i++)
	{
		if(mass[i] == 0x87 && mass[i + 1] == 0x5A && CalcCheckSum(mass, mass[i + 2] + 2) == mass[mass[i + 2] + 2])
		{
			if(mass[13] == 0x01 && mass[14] == 0x00)
			{
				current = mass[17] << 16 | mass[16] << 8 | mass[15];      
				if(current >= 0 && current <= 4194303)
				{
					current = current * 20 / 4194303;
					//printf("%.2f\n", current); 
			
				}
				else
				{
					current = mass[17] << 16 | mass[16] << 8 | mass[15];
					current = -(16777215 - current) * 20 / 4194303;
					//printf("%.2f\n", current); 	
				}
				SetCtrlVal(panelHandle, PANEL_CURRENT, current);
			}
		}
		if(mass[i] == 0x87 && mass[i + 1] == 0x5A && CalcCheckSum(mass, mass[i + 2] + 2) == mass[mass[i + 2] + 2])
		{
			if(mass[13] == 0x01 && mass[14] == 0x01)
			{
				voltage = mass[17] << 16 | mass[16] << 8 | mass[15];      
				if(voltage >= 0 && voltage <= 4194303)
				{
					voltage = voltage * 50 / 4194303;
					//printf("%.2f\n", current); 
			
				}
				else
				{
					voltage = mass[17] << 16 | mass[16] << 8 | mass[15];
					voltage = -(16777215 - voltage) * 50 / 4194303;
					//printf("%.2f\n", current); 	
				}
				SetCtrlVal(panelHandle, PANEL_VOLTAGE, voltage);
			}
		}
	}
}
//============================================================================== 
//Функция отправки команды
//==============================================================================
void sendCommand(int array[], int length)
{
	int *sendMSG = (int*)malloc((length + 1) * sizeof(int));
	int i;
	for( i = 0; i < length; i++)
	{
		ComWrtByte(com, array[i]);
		sendMSG[i] = array[i];
	}
	ComWrtByte(com, CalcCheckSum(array, length));
	sendMSG[i] = CalcCheckSum(array, length);
	ShowBytes("Write: ", sendMSG, length + 1); 
	free(sendMSG);   
}
//============================================================================== 
//Функция показать байты
//==============================================================================
void ShowBytes(char str[], int mass[], int lengthMass)
{
	int ix = 0;
	char str1[120] = {0}; 
	char str2[100] = {0}; 
	
	for(int i = 0; i < lengthMass; i++)
	{
		if(mass[i] < 16)
		{
			sprintf (str2, "0%x ", mass[i]);
			strcat(str1, str2); 
		}
		else
		{
			sprintf (str2, "%x ", mass[i]); 
			strcat(str1, str2); 
		}
	}   
	
	while (str1[ix])                           
   	{									 
		str1[ix] = toupper(str1[ix]);           
   		ix++;                                  
   	}
    
	SetCtrlVal(panelHandle, PANEL_TEXTBOX, str); 
	SetCtrlVal(panelHandle, PANEL_TEXTBOX, str1);
	SetCtrlVal(panelHandle, PANEL_TEXTBOX, "\n");	
}
//============================================================================== 
//Auaia oaenoiaiai niiauaiey
//==============================================================================
void SetMessage(char str[])
{
	ResetTextBox(panelHandle, PANEL_TEXTBOX_2, str);
}
//============================================================================== 
//Прочитать байты
//==============================================================================
void getByte()
{
	int mass[100];
	int lenght = GetInQLen (com);

	if(lenght != 0)
	{
		for(int i = 0; i < lenght; i++)
		{
			mass[i] = ComRdByte(com);      
		}
		definingCommand(mass, lenght + 1);
		ShowBytes("Read: ", mass, lenght);
	}
}
//==============================================================================                 
int CVICALLBACK connection (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panelHandle, PANEL_COM, &com);
			if(0 == OpenComConfig (com, "com3", 9600, 2, 8, 1, 512, 512))
			{
				InstallComCallback(com, LWRS_RECEIVE, 2, "A", eventCOM, 2);  
				SetMessage("Connection established");
			}
			else
			{
				SetMessage("Error"); 
			}
			break;						 
	}
	return 0;
}

//==============================================================================  
int CVICALLBACK readFromAdapter (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			getByte();
			break;
	}
	return 0;
}
//============================================================================== 
//Ioi?aaeou aaeou
//==============================================================================             
int CVICALLBACK SendData (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	char str[3];
	int b, bytes;
	int *sendMSG;
	int a;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panelHandle, PANEL_RING_2, &bytes); 	     
			sendMSG = (int*)malloc((3 + bytes) * sizeof(int));
			for(int i = 0; i < bytes + 3; i++)
			{
			 	GetCtrlVal(panelHandle, boxs[i], str);
				b = strtol(str, NULL, 16); 
				sendMSG[i] = b;
			}
			a = bytes + 3;
			sendCommand(sendMSG, a);
			//ShowBytes("Write: ", sendMSG, a); 
			free(sendMSG);
			
			break;
	}

	return 0;
}
//============================================================================== 
//Закрыть COM порт
//==============================================================================
int CVICALLBACK exitCOM (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			CloseCom(com);
			break;
	}
	return 0;
}
//============================================================================== 
//изменить скорость передачи данных
//==============================================================================
int CVICALLBACK BaudRate (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	int rate;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panelHandle, PANEL_RING, &rate);
			switch(rate)
			{
				case 125:
					sendCommand(speed_125, 8);
					break;
				case 250:
					sendCommand(speed_250, 8);;   
					break;
				case 500:
					sendCommand(speed_500, 8);
					break;
			}
			break;
	}
	return 0;
}
//============================================================================== 
//Сколько байтов нужно отправить
//==============================================================================
int CVICALLBACK LengthByte (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	int bytes;
	switch (event)
	{
		case EVENT_COMMIT:
		GetCtrlVal (panelHandle, PANEL_RING_2, &bytes);
		char str[3];
		char str0[4] = {"0"};
	
		for (int i = 3; i < numberOfbytes; i++)
		{
			if(i < bytes + 3)
			{
				SetCtrlAttribute (panelHandle, boxs[i], ATTR_DIMMED, false);
			}
			else
			{
				SetCtrlAttribute (panelHandle, boxs[i], ATTR_DIMMED, true);     
			}
	  	
		}
		GetCtrlVal (panelHandle, PANEL_RING_2, &bytes); 
		sprintf (str, "%x", bytes + 1);
	
		int ix = 0; 
	
		while (str[ix])                           
   		{
			str[ix] = (char)toupper(str[ix]);     
   		 	ix++;                                  
   		}

		if(bytes < 16)
		{
			SetCtrlVal(panelHandle, PANEL_BYTE_2, strcat(str0, str));       
		}
		else
		{
			SetCtrlVal(panelHandle, PANEL_BYTE_2, str);       
		} 
		break;
	}
	return 0;
}
//============================================================================== 
//Iieo?eou nei?inou ia?aaa?e
//==============================================================================
int CVICALLBACK GET_SPEED (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			//definingCommand(mass_test, 23);
			for(int i = 0; i <= 255; i++)
			{
				printf("%d	%c\n", i, i);
			}
			char str[10];
			//int a = strtol(str, NULL, 16);
			sprintf (str, "%x ", 30); 
			break;
	}
	return 0;
}
//============================================================================== 
//
//==============================================================================
void eventCOM()
{
	getByte();
}
//============================================================================== 
//Задать значение тока
//==============================================================================
int CVICALLBACK SetCurrnet (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	double current;
	int pak[] = {0x1C, 0x05, 0x0B, 0x00, 0x00, 0xF4, 0x06, 0x06, 0x80, 0x00, 0x00, 0x00, 0x00}; 
	int ans;
	int L, H;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panelHandle, PANEL_CurrentValue, &current);
			if(current >= 0)
			{
				ans = 32768 + current * 1638.35;
			}
			else
			{
				ans = 32768 + current * 1638.4;
			}
			
			H = (ans >> 8) & 0xFF; 
			L = ans & 0xFF;
			pak[9] = H;
			pak[10] = L;   
			sendCommand(pak, 13); 
			break;
	}
	return 0;
}
//============================================================================== 
//Включить питание
//==============================================================================
int CVICALLBACK PowerON (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
		int mass[] = {0x1C, 0x05, 0x08, 0x00, 0x00, 0xF4, 0x06, 0x02, 0xF9, 0x02};
		sendCommand(mass, 10);
			break;
	}
	return 0;
}
//============================================================================== 
//Включить питание
//==============================================================================
int CVICALLBACK PowerOFF (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			int mass1[] = {0x1C, 0x05, 0x08, 0x00, 0x00, 0xF4, 0x06, 0x02, 0xF9, 0x04};
			sendCommand(mass1, 10);
			break;
	}
	return 0;
}
//============================================================================== 
//Включить отправку тока и напряжения
//==============================================================================
int CVICALLBACK GetMeasure (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			int mass1[] = {0x1C, 0x05, 0x0C, 0x00, 0x00, 0xF4, 0x06, 0x06, 0x01, 0x00, 0x01, 0x04, 0x30, 0x00};
			sendCommand(mass1, 14);
			break;
	}
	return 0;
}
//============================================================================== 
//Включить отправку тока и напряжения
//==============================================================================
int CVICALLBACK StopMeasure (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			int mass1[] = {0x1C, 0x05, 0x07, 0x00, 0x00, 0xF4, 0x06, 0x01, 0x00};
			sendCommand(mass1, 9);
			break;
	}
	return 0;
}
