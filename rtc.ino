/* ***** RTC ***** */ 
void rtc_init()
{
 // Initialize the rtc object
 rtc.begin();
 // Configurar hora: Hora-Min-Sec
//rtc.setTime(7,24,50);   // descomentar para acertar.Dps comentar.
 // Configurar data: Dia-Mês-Ano
// rtc.setDate(24,8,2017); // descomentar para acertar.Dps comentar.
}
/* get time from RTC clock */
void rtc_getTime()
{
  t = rtc.getTime();
}

/* print time to serial bus */
void rtc_serialPrint()
{
  rtc_getTime();
  Serial.print("Hora ");
  Serial.print(t.hour);
  Serial.print(":");
  Serial.print(t.min);
  Serial.print(":");
  Serial.print(t.sec);

  Serial.print(" --- Data ");
  Serial.print(t.dow); // dia da semana
  Serial.print(" ");
  Serial.print(t.date);
  Serial.print(".");
  Serial.print(t.mon);
  Serial.print(".");
  Serial.println(t.year);
}
