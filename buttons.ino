// ficheiro com a configuração dos botões


//Funções
void buttons_init()
{
  // saidas
  pinMode(pinbutton1,INPUT);
  pinMode(pinbutton2,INPUT);
  pinMode(pinbutton3,INPUT);
  pinMode(pinbutton4,INPUT);

}

// lê o estado de cada um dos botões
byte buttons_state()
{
  byte temp = 0;
  
  if(digitalRead(pinbutton1) == HIGH)
  {temp = 1u;}
  if(digitalRead(pinbutton2) == HIGH)
  {temp += 2u;}
  if(digitalRead(pinbutton3) == HIGH)
  {temp += 4u;}
  if(digitalRead(pinbutton4) == HIGH)
  {temp += 8u;}
  
  Serial.println(temp);
  return temp;
  
}




