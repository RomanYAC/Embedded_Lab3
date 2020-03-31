#include "stm32f4x7_eth.h"
#include "netconf.h"
#include "main.h"
#include "lwip/tcp.h"
#include "lwip/tcp_impl.h"
#include "serial_debug.h"
#include "initialize.h"

#define SYSTEMTICK_PERIOD_MS  10

int8_t messageIndex = -1;

char *test_strings[] = {
	"developing",
	"embeded",
	"lab",
	"with",
	"ETHERNET"
};

__IO uint32_t LocalTime = 0; /* this variable is used to create a time reference incremented by 10ms */
uint32_t timingdelay;

/* Private function prototypes -----------------------------------------------*/
void LCD_LED_BUTTON_Init(void);

int main(void)
{
  ETH_BSP_Config();
	InitializeButtons();
	InitializeInterruptions();
	LCD_LED_BUTTON_Init();
  
  LwIP_Init();

  while (1)
  {  
    /* check if any packet received */
    if (ETH_CheckFrameReceived())
    { 
      /* process received ethernet packet */
      LwIP_Pkt_Handle();
    }
    
    LwIP_Periodic_Handle(LocalTime);
		
		//handle button press
		if(messageIndex != -1){
			LCD_Clear(Black);
			LCD_DisplayStringLine(Line0,(uint8_t*)test_strings[messageIndex]);
			
			messageIndex = -1;
		}				
  }
}

void Delay(uint32_t nCount)
{
  timingdelay = LocalTime + nCount;
  while(timingdelay > LocalTime)  {}
}
void Time_Update(void)
{
  LocalTime += SYSTEMTICK_PERIOD_MS;
}

void LCD_LED_BUTTON_Init(void)
{
  /* Initialize the STM324xG-EVAL's LCD */
  STM324xG_LCD_Init();
  /* Initialize STM324xG-EVAL's LEDs */

  LCD_Clear(Black);
  LCD_SetBackColor(Black);
  LCD_SetTextColor(White);
  
  STM_EVAL_PBInit(BUTTON_KEY, BUTTON_MODE_EXTI);
}
