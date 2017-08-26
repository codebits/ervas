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
