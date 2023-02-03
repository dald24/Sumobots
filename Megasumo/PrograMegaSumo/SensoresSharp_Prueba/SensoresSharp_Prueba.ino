#include <SharpIR.h>

#define IRDerecha A0 // define signal pin
#define IRCentro A2 // define signal pin
#define IRIzquierda A5

#define model1 1080 // for GP2Y0A21YK0F  used 1080
#define model2 1080 // for GP2Y0A21YK0F  used 1080
#define model3 1080

SharpIR SharpIRD(IRDerecha,model1);
SharpIR SharpIRC(IRCentro,model2);
SharpIR SharpIRI(IRIzquierda, model3);

int calculo()
{
  unsigned long startTime=millis();  // takes the time before the loop on the library begins
  int dis1=SharpIRD.distance();  
  int dis2=SharpIRC.distance();  
  int dis3=SharpIRI.distance();

  if(dis1 < dis2 && dis1 < dis3)
  {

    return 1; //Derecha

  }
  else if( dis2 < dis1 && dis2< dis3)
  {

    return 2; //Centro

  }
  else if(dis3 < dis1 && dis3< dis2)
  {

    return 3; //Izquierdo

  }
  else
  {
  
    return 4; //Desconocido
  
  }

}


void SensoresSharp(){
  delay(1000);
  

  int dis1=SharpIRD.distance();  // this returns the distance for sensor 1
  int dis2=SharpIRC.distance();  // this returns the distance for sensor 2
  int dis3=SharpIRI.distance();

  Serial.print("Distance (Derecha): ");
  Serial.print(dis1);
  Serial.print("cm");
  
  Serial.print("Distance (Centro): ");
  Serial.print(dis2);
  Serial.print("cm");

  Serial.print("Distance (Izquierda): ");
  Serial.print(dis3);
  Serial.print("cm");
  }

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
SensoresSharp();
Serial.println(calculo());
}
