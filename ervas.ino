// estrutura para a hora e data
#include <Arduino.h>
#include <DS3231.h>
#include <Wire.h> /* used for I2C comunication */
#include <LiquidCrystal_I2C.h> /* used for LCD 4x20*/
#include "TimerFour.h"
#include <DHT22.h>
//#include <avr/wdt.h>


LiquidCrystal_I2C lcd(0x3f,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

// Init the DS3231 using the hardware interface
// DS3231:  SDA pin   -> Arduino Digital 20 (SDA) or the dedicated SDA pin
//          SCL pin   -> Arduino Digital 21 (SCL) or the dedicated SCL pin
DS3231  rtc(20, 21);
//Global Variables
Time t;
unsigned long int ldr_light = 0;
double sensors_thermistor1_temp = 0;

// Pins dos relés
int pinRele1 = 31;
int pinRele2 = 32;
int pinRele3 = 33;
int pinRele4 = 34;

// Pins dos Botoes
int pinbutton1 = 26;
int pinbutton2 = 27;
int pinbutton3 = 28;
int pinbutton4 = 29;
int lcd_ButtonOk = 37;
int lcd_ButtonUp = 36 ;
int lcd_ButtonDown = 35;

// Pin do LDR
int ldr_sensor = A0;
// Pin thermistor 1
int sensors_thermistor1 = A1;
// Pin motor
int motor_in1 = A14;
int motor_in2 = A15;

/* Structure for Core */
enum core_currentState { CORE_INIT, CORE_LCD, CORE_RELAYS,CORE_MODES,CORE_ERROR };
core_currentState coreState;
unsigned int core_counter = 0;
unsigned int core_sensorCounter = 0;

/* Structure for LCD Dislay */
enum lcd_states { LCD_INIT,LDC_HOME,LCD_MENU1,LCD_MENU2,LCD_ERROR };
lcd_states lcd_currentState;
byte lcd_lastButtonPressed = 0;

/* Activate Automatic modes from the start
 - Set true to activate.
 - Set False to deactivate               */
boolean Modes_active = false;

// Data wire is plugged into port 7
// Connect a 4.7K resistor between VCC and the data pin (strong pullup)
#define DHT22_PIN 6
// Setup a DHT22 instance
DHT22 sensor_1_RHT03(DHT22_PIN);
float RHT03_T = 0;
float RHT03_H = 0;
boolean RHT03_ERROR = false;

/* prototypes*/
void lcd_init();
void lcd_SM();
byte lcd_buttonsState();
void Core_MainLoop();
void Core_Main();
void rtc_init();
void relay_set(byte buttons);
void relay_On(int relay);
void relay_Off(int relay);
int ldr_read();
int ldr_average();
int sensors_readThermistor1();
int sensors_thermistor1_average();
void motor_init();
void motor_move_cw();
void motor_move_ccw();
void motor_stop();
void motor_hold();

void setup()
{
  // Setup Serial connection
  //Serial.begin(9600);
  relays_init();
  rtc_init();
  buttons_init();
  delay(1000);
  lcd_init();
  delay(2000);
  
  // system mainloop task of 5ms
  Timer4.initialize(10000);         // initialize timer1, and set a 10ms (10000) second period
  Timer4.attachInterrupt(Core_MainLoop);  // attaches callback() as a timer overflow interrupt
  coreState = CORE_INIT;
  // Enable whatcdog of 1 second 
  //wdt_enable(WDTO_250MS);
  //wdt_disable();
  //rtc_serialPrint();
  motor_init();
}

void loop()
{
    /* call main function */
    Core_Main();
    /* Perform reset of whatchDog */
    //wdt_reset();
  
}


 




