/* ***** Relays ***** */ 
 void relays_init()
{
  // saidas
  pinMode(pinRele1,OUTPUT);
  pinMode(pinRele2,OUTPUT);
  pinMode(pinRele3,OUTPUT);
  pinMode(pinRele4,OUTPUT);
  // Estado Incial Desligados ( activado a LOW level)
  digitalWrite(pinRele1,HIGH);
  digitalWrite(pinRele2,HIGH);
  digitalWrite(pinRele3,HIGH);
  digitalWrite(pinRele4,HIGH);
}
// turn on one relay
void relay_On(int relay)
{
  digitalWrite(relay,LOW);
}
// turn off one relay
void relay_Off(int relay)
{
  digitalWrite(relay,HIGH);
}

// liga e desliga os reles de acordo com a posição dos botoes
void relay_set(byte buttons)
{
  //Serial.println(buttons);
  if ((byte)(buttons & 1u) == (byte)1u ){
      digitalWrite(pinRele1,LOW);
  }else{
      digitalWrite(pinRele1,HIGH);}
      
  if ((byte)(buttons & 2u) == (byte)2u ){
      digitalWrite(pinRele2,LOW);
  }else{
      digitalWrite(pinRele2,HIGH);}
      
  if ((byte)(buttons & 4u) == (byte)4u ){
      digitalWrite(pinRele3,LOW);
  }else{
      digitalWrite(pinRele3,HIGH);}
      
  if ((byte)(buttons & 8u) == (byte)8u ){
      digitalWrite(pinRele4,LOW);
  }else{
      digitalWrite(pinRele4,HIGH);}
}
