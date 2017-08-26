/* ***** LCD ***** */
void lcd_init()
{
  
  pinMode(lcd_ButtonOk,INPUT);
  pinMode(lcd_ButtonUp,INPUT);
  pinMode(lcd_ButtonDown,INPUT);
  
  lcd.init(); 
  // lcd.backlight();
  lcd.clear();
  lcd.setCursor(5,0);
  lcd.print("Bem Vindo");
  lcd.setCursor(1,2);
  lcd.print("Estufa a iniciar"); 
  lcd_currentState = LCD_INIT;
}
void lcd_SM()
{
  byte buttons = lcd_buttonsState();
  if(buttons != (byte)0u ){
  lcd_lastButtonPressed = buttons; }
    switch(lcd_currentState)
    {
      case LCD_INIT:
                    lcd.clear();
                    lcd_currentState = LDC_HOME;
      break;
      case LDC_HOME:
                    rtc_getTime();
                    lcd.setCursor(0,0);
                    lcd.print("00");
                    if(t.hour<10)
                    {lcd.setCursor(1,0);
                     lcd.print(t.hour);
                    }
                    else{
                     lcd.setCursor(0,0);
                     lcd.print(t.hour);                   
                    }

                    lcd.setCursor(2,0);
                    lcd.print(":");
                    lcd.setCursor(3,0);
                    lcd.print("00");
                    if(t.min<10)
                    {lcd.setCursor(4,0);
                     lcd.print(t.min);
                    }
                    else{
                     lcd.setCursor(3,0);
                     lcd.print(t.min);                   
                    }
                    
                    lcd.setCursor(5,0);
                    lcd.print(":");
                    lcd.setCursor(6,0);
                    lcd.print("00");
                    if(t.sec<10)
                    {lcd.setCursor(7,0);
                     lcd.print(t.sec);
                    }
                    else{
                     lcd.setCursor(6,0);
                     lcd.print(t.sec);                   
                    }
 
                    lcd.setCursor(10,0);
                    lcd.print("00");
                    if(t.date<10)
                    {lcd.setCursor(11,0);
                     lcd.print(t.date);
                    }
                    else{
                     lcd.setCursor(10,0);
                     lcd.print(t.date);                   
                    }
                    lcd.setCursor(12,0);
                    lcd.print(".");
                    lcd.setCursor(13,0);
                    lcd.print("00");
                    if(t.mon<10)
                    {lcd.setCursor(14,0);
                     lcd.print(t.mon);
                    }
                    else{
                     lcd.setCursor(13,0);
                     lcd.print(t.mon);                   
                    }

                    lcd.setCursor(15,0);
                    lcd.print(".");
                    lcd.setCursor(16,0);
                    lcd.print(t.year);
                    
                    
                    lcd.setCursor(0,2);
                    lcd.print("T1 ");
                    lcd.setCursor(3,2);
                    lcd.print(RHT03_T);
                    lcd.setCursor(9,2);
                    lcd.print("H1 ");
                    lcd.setCursor(12,2);
                    lcd.print(RHT03_H);
                    
//                    lcd.setCursor(10,1);
//                    lcd.print("SOLO:");
                    
                    lcd.setCursor(0,3);
                    lcd.print("T2:");
//                    lcd.setCursor(10,2);
//                    lcd.print("LUZ:");

                    if( buttons == (byte)1u ){
                    lcd.clear();
                    lcd_currentState = LCD_MENU1;}
                    
      break;
      case LCD_ERROR: 
            lcd.setCursor(0,1);
            lcd.print(" Too many Cycles ");
            lcd.setCursor(0,2);
            lcd.print(" Check Sensors. ");
            lcd.setCursor(0,3);
            lcd.print(" Press Ok to restart ");
      break;
      case LCD_MENU1:
            lcd.setCursor(0,0);
            lcd.print(" Deactivate Mode1 ? ");
            lcd.setCursor(0,2);
            lcd.print(" Yes - Press Up ");
            lcd.setCursor(0,3);
            lcd.print(" No  - Press Down ");
            if(lcd_lastButtonPressed == (byte)2u){
              Modes_active = false;
              lcd.clear();
              lcd_currentState = LDC_HOME;}
            else if(lcd_lastButtonPressed == (byte)4u){ 
              Modes_active = true;
              lcd.clear();
              lcd_currentState = LDC_HOME;}           
      break;
      default:
      break;
    }
 }
 
 
 // lê o estado de cada um dos botões
byte lcd_buttonsState()
{
  byte temp = 0;
  
  if(digitalRead(lcd_ButtonOk) == HIGH)
  {temp = 1u;}
  if(digitalRead(lcd_ButtonUp) == HIGH)
  {temp += 2u;}
  if(digitalRead(lcd_ButtonDown) == HIGH)
  {temp += 4u;}
 
  Serial.println(temp);
  return temp;
  
}
