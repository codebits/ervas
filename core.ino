void Core_MainLoop()
{
  core_counter++;
  core_sensorCounter++;
  /* Read sensors every 1second */
  if( core_sensorCounter >= (unsigned int)200u ){
    core_sensorCounter=0;
    sensors_readRHT03();
  }
}

void Core_Main()
{
   byte mode1result;
   /* Print to LCD state machine  */
   lcd_SM();
   /* calculate ambient light  */
   ldr_average();
   /* calculate thermistor temperature 1 */
   sensors_thermistor1_average();
   
  // motor_move_ccw();
   
  switch (coreState)
  {
    case CORE_INIT:
           core_counter = 0;
           coreState = CORE_RELAYS;
    break;
    case CORE_RELAYS:
           /* relays are set by the position of buttons */
           relay_set( (byte)buttons_state() );
           if(Modes_active == true){
           coreState = CORE_MODES;}
    break;
    case CORE_MODES:
          /* Sequence.If finish goes to Init state. Else goes to error state by safety */ 
          mode1result = mode1();
          if( mode1result == 0 ){
            lcd.clear();
            coreState = CORE_INIT;
          } else if(mode1result == 3){
            coreState = CORE_ERROR;
            lcd.clear();
            lcd_currentState = LCD_ERROR;
          } else{ /* Do Nothing */}

    break;
    case CORE_ERROR:
          /* mode failed due many cycles. turn off relays and print warning message */
          relays_init();
          if( (byte)(lcd_buttonsState() & 1u) == (byte)1u ){
            lcd_currentState = LDC_HOME;
            coreState = CORE_INIT;
            lcd.clear();}
    break;
    default:
    break;
  }

}
