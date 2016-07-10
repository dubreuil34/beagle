/* definitions des constantes


*/

#ifndef _BEAGLE_H_
#define _BEAGLE_H_



#define LOW 0
#define HIGH 1

#define OFF 0
#define ON 1

#define IN
#define OUT



#define USR0  	"usr0"
#define USR1 	"usr1"
#define USR2	"usr2"
#define USR3	"usr3"

#define AIN0	"/AIN0"
#define AIN1	"/AIN1"
#define AIN2	"/AIN2"
#define AIN3	"/AIN3"
#define AIN4	"/AIN4"
#define AIN5	"/AIN5"
#define AIN6	"/AIN6"
#define AIN7	"/AIN7"


// Les 4 leds USR
int LedUsr(int num, int value);
int GetGPIONum(char* nom);
int GPIO_Setup(int gpio,int inout);
int GPIO_Set(int gpio);
int GPIO_Reset(int gpio);
int GPIO_Toggle(int gpio);
int GPIO_Get(int gpio);









#endif
