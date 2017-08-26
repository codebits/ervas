/* Light Dependent Resistor Sensor */

/* reads light value from the sensor ldr */
int ldr_read()
{
  int light;
   light = (int) analogRead(ldr_sensor); 
  return light;
}

/* calulate average ambient light*/
int ldr_average()
{
  static byte counter = 0;
  static unsigned long int light = 0;
  
  if (counter == (byte)10)
  {
      /* light average. Range 0 - 1023 */
      light =(unsigned long int)(light / 10);
      /* convert to percentage */
      light = (unsigned long int)( (light * 100) / (unsigned long int)(1023) );
      ldr_light = (unsigned long int)light;
      counter = 0;
      light = 0;
  }
  else
  {
    light +=  ldr_read();
    counter++;
  }

return  ldr_light;
}
