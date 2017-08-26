boolean mode1()
{ 
  byte error = 1; // 0 - no error / 1 - processing / 2 - error
  static byte menu = 0;
  static byte failedEvents = 0;  
   
  switch(menu)
  {
  case 0:
   // temp above 30 deg
   if( RHT03_T > (float)30 ) 
   {
     menu = 1;
     core_counter = 0; 
   }
   // temp below 30deg and humidity above 70%
   else if( (RHT03_T <= (float)30) && (RHT03_H < (float )70) )
   {
     menu = 2;
     core_counter = 0; 
   }else{
     // Do nothing
   }
  break;
  case 1:
   if( core_counter <= 3000 ){ // wait 30seg (3000*10ms)
    relay_On(pinRele1); // ligar valvula 1
    relay_On(pinRele2); // ligar valvula 2
    lcd.setCursor(0,1);
    lcd.print("Valves 1 and 2 ON   ");
    error = 1;
   }
   else{
     if( RHT03_T > (float)30 )
     {
       failedEvents++;
     }
     else{
       failedEvents = 0; }
     relay_Off(pinRele1);// desligar valvula 1
     relay_Off(pinRele2);// desligar valvula 2
     lcd.setCursor(0,1);
     lcd.print("Valves 1 and 2 OFF  ");
     menu = 0;
     if(failedEvents >= 3 ){
      error = 3;}
      else{ error = 0;}
   }
    
  break;
  case 2:
   if( core_counter <= 3000 ){ // wait 30seg (3000*10ms)
     relay_On(pinRele1); // ligar valvula 1
     lcd.setCursor(0,1);
     lcd.print("Valve 1 ON       ");
     error = 1;
   }
   else{
     /* Check first how many consecutive cycles. Max allowed cyles are 3.*/
     if( (RHT03_T <= (float)30) && (RHT03_H < (float )70) ){
       failedEvents++;
     } else{ failedEvents = 0; }
     relay_Off(pinRele1);// desligar valvula 1
     lcd.setCursor(0,1);
     lcd.print("Valve 1 OFF      ");
     menu = 0;
     if(failedEvents >= 3 ){
      error = 3;}
      else{ error = 0;}
   }
  break;
  default:
  break;
  }
  /* in case of error disable all valves and print message */
  if(error == (byte)3u ){
    failedEvents = 0;   // restart counting for next time
    relay_Off(pinRele1);// desligar valvula 1
    relay_Off(pinRele2);// desligar valvula 2
    lcd.setCursor(0,1);
    lcd.print("All valves OFF      ");
  }
return error;
}
