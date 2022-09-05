/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  PANEL                            1       /* callback function: panelCB */
#define  PANEL_COMMANDBUTTON              2       /* control type: command, callback function: connection */
#define  PANEL_COMMANDBUTTON_2            3       /* control type: command, callback function: readFromAdapter */
#define  PANEL_COMMANDBUTTON_3            4       /* control type: command, callback function: SendData */
#define  PANEL_COMMANDBUTTON_4            5       /* control type: command, callback function: exitCOM */
#define  PANEL_RING                       6       /* control type: ring, callback function: BaudRate */
#define  PANEL_TEXTBOX                    7       /* control type: textBox, callback function: (none) */
#define  PANEL_TEXTBOX_2                  8       /* control type: textBox, callback function: (none) */
#define  PANEL_RING_2                     9       /* control type: ring, callback function: LengthByte */
#define  PANEL_BYTE_16                    10      /* control type: string, callback function: (none) */
#define  PANEL_BYTE_17                    11      /* control type: string, callback function: (none) */
#define  PANEL_BYTE_18                    12      /* control type: string, callback function: (none) */
#define  PANEL_BYTE_19                    13      /* control type: string, callback function: (none) */
#define  PANEL_BYTE_20                    14      /* control type: string, callback function: (none) */
#define  PANEL_BYTE_21                    15      /* control type: string, callback function: (none) */
#define  PANEL_BYTE_22                    16      /* control type: string, callback function: (none) */
#define  PANEL_BYTE_23                    17      /* control type: string, callback function: (none) */
#define  PANEL_BYTE_8                     18      /* control type: string, callback function: (none) */
#define  PANEL_BYTE_9                     19      /* control type: string, callback function: (none) */
#define  PANEL_BYTE_10                    20      /* control type: string, callback function: (none) */
#define  PANEL_BYTE_11                    21      /* control type: string, callback function: (none) */
#define  PANEL_BYTE_12                    22      /* control type: string, callback function: (none) */
#define  PANEL_BYTE_13                    23      /* control type: string, callback function: (none) */
#define  PANEL_BYTE_14                    24      /* control type: string, callback function: (none) */
#define  PANEL_BYTE_15                    25      /* control type: string, callback function: (none) */
#define  PANEL_BYTE_7                     26      /* control type: string, callback function: (none) */
#define  PANEL_BYTE_6                     27      /* control type: string, callback function: (none) */
#define  PANEL_BYTE_5                     28      /* control type: string, callback function: (none) */
#define  PANEL_BYTE_4                     29      /* control type: string, callback function: (none) */
#define  PANEL_BYTE_3                     30      /* control type: string, callback function: (none) */
#define  PANEL_BYTE_2                     31      /* control type: string, callback function: (none) */
#define  PANEL_BYTE_1                     32      /* control type: string, callback function: (none) */
#define  PANEL_BYTE_0                     33      /* control type: string, callback function: (none) */
#define  PANEL_GET_SPEED                  34      /* control type: command, callback function: GET_SPEED */
#define  PANEL_COM                        35      /* control type: ring, callback function: (none) */
#define  PANEL_CurrentValue               36      /* control type: scale, callback function: (none) */
#define  PANEL_COMMANDBUTTON_5            37      /* control type: command, callback function: SetCurrnet */
#define  PANEL_COMMANDBUTTON_6            38      /* control type: command, callback function: PowerON */
#define  PANEL_COMMANDBUTTON_7            39      /* control type: command, callback function: PowerOFF */
#define  PANEL_VOLTAGE                    40      /* control type: numeric, callback function: (none) */
#define  PANEL_CURRENT                    41      /* control type: numeric, callback function: (none) */
#define  PANEL_DECORATION_2               42      /* control type: deco, callback function: (none) */
#define  PANEL_DECORATION_4               43      /* control type: deco, callback function: (none) */
#define  PANEL_DECORATION_3               44      /* control type: deco, callback function: (none) */
#define  PANEL_DECORATION                 45      /* control type: deco, callback function: (none) */
#define  PANEL_GetMeasure                 46      /* control type: command, callback function: GetMeasure */
#define  PANEL_STOPMEASURE                47      /* control type: command, callback function: StopMeasure */
#define  PANEL_DECORATION_5               48      /* control type: deco, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK BaudRate(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK connection(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK exitCOM(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK GET_SPEED(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK GetMeasure(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK LengthByte(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK panelCB(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK PowerOFF(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK PowerON(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK readFromAdapter(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SendData(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SetCurrnet(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK StopMeasure(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
