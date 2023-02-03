#define SENSOR_IN_P1 A7
#define SENSOR_IN_P2 A6

bool lineaIzquierda()
{

  if(analogRead(SENSOR_IN_P1) > 300)
  {
      return true;
  }
  else
  {
    return false;  
  }
}

bool lineaDerecha()
{

  if(analogRead(SENSOR_IN_P2) > 300)
  {
      return true;
  }
  else
  {
    return false;  
  }
}


void setup() {
  Serial.begin(9600);
  pinMode(SENSOR_IN_P1,INPUT);
  pinMode(SENSOR_IN_P2,INPUT);

}

void loop() {
  if(lineaIzquierda()) 
  {
    Serial.print(analogRead(SENSOR_IN_P1));
  }
  else 
  {
    Serial.print(0);
  }
  Serial.print("-----------OKAY----------");
  if(lineaDerecha())
  {
    Serial.println(analogRead(SENSOR_IN_P2));
  }
  else
  {
    Serial.println(0);
  }
  
 
}
