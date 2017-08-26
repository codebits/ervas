/* Initialization of sensors */
void sensors_init()
{
  /* code here */
}

/* Read temperature and humudity sensor */
void sensors_readRHT03()
{
  
 DHT22_ERROR_t errorCode;
 errorCode = sensor_1_RHT03.readData();
 
  switch(errorCode)
  {
    case DHT_ERROR_NONE:
      RHT03_T = (float)(sensor_1_RHT03.getTemperatureC());
      RHT03_H = (float)(sensor_1_RHT03.getHumidity());
      RHT03_ERROR = false;
      break;
    case DHT_ERROR_CHECKSUM:
      RHT03_ERROR = true;
      break;
    case DHT_BUS_HUNG:
      RHT03_ERROR = true;
      break;
    case DHT_ERROR_NOT_PRESENT:
      RHT03_ERROR = true;
      break;
    case DHT_ERROR_ACK_TOO_LONG:
      RHT03_ERROR = true;
      break;
    case DHT_ERROR_SYNC_TIMEOUT:
      RHT03_ERROR = true;
      break;
    case DHT_ERROR_DATA_TIMEOUT:
      RHT03_ERROR = true;
      break;
    case DHT_ERROR_TOOQUICK:
      RHT03_ERROR = true;
      break;
  }

}


/* NTC THERMISTOR Type: NTC 10k±1% 3950
http://www.eidusa.com/Electronics_Kits_TEMP_THERMISTOR_1.htm
http://www.circuitbasics.com/arduino-thermistor-temperature-sensor-tutorial/

*/

/* reads light value from the sensor ldr */
int sensors_readThermistor1()
{
  int thermistor;
   thermistor = (int) analogRead(sensors_thermistor1); 
  return thermistor;
}

/* calulate average ambient light*/
int sensors_thermistor1_average()
{
  static byte counter = 0;
  static double temp = 0;
  /* Original constant values
      c1 = 0.001129148; 
      c2 = 0.000234125;
      c3 = 0.0000000876741;
  */
  double c1 = 0.001135148; 
  double c2 = 0.000234125;
  double c3 = 0.0000000876741;
  
  if (counter == (byte)20)
  {
      /* light average. Range 0 - 1023 */
      temp = (double) (temp / 20);
      /* convert to temperature       */
       // R = 10K * { (2V / Vout) -1}
       temp = (double)(log(10000.0/(double)(1023.0 /(double)temp - 1.0)));
       // T = 1 / {C1 + C2[ln(R)] + C3[ln(R)]^3}
       temp = (double) ( 1.0 / (c1 + (c2 + (c3 * temp * temp ))* temp ) );
       temp = (double) (temp - 273.15); 
      sensors_thermistor1_temp = (double)temp;
      counter = 0;
      temp = 0;
  }
  else
  {
    temp +=  sensors_readThermistor1();
    counter++;
  }

return  sensors_thermistor1_temp;
}
