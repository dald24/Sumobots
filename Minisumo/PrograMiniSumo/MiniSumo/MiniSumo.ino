#include <SharpIR.h>

//MOTOR IZQUIERDA POR FUNCION
#define MOTOR_PWMA 5
#define MOTOR_AIN2 6  // CAMBIAR SI LA DIRECCION MOTOR ESTA AL CONTRARIO 6 por 7
#define MOTOR_AIN1 7  // CAMBIAR SI LA DIRECCION MOTOR ESTA AL CONTRARIO 7 por 6

//MOTOR DERECHA POR FUNCION
#define MOTOR_PWMB 11
#define MOTOR_BIN1 9  // CAMBIAR SI LA DIRECCION MOTOR ESTA AL CONTRARIO 11 por 10
#define MOTOR_BIN2 10  // CAMBIAR SI LA DIRECCION MOTOR ESTA AL CONTRARIO 10 por 11

//SENSORES DE PISO
#define SENSOR_IN_P1 A7
#define SENSOR_IN_P2 A6

//CONFIGURACION DE BUSQUEDA Y ATAQUE (MAX 255 Min 0)
#define VELOCIDAD_ATAQUE        254
#define VELOCIDAD_BUSQUEDA      200

#define IRDerecha A0 // define signal pin
#define IRCentro A2 // define signal pin
#define IRIzquierda A5

#define model1 1080 // for GP2Y0A21YK0F  used 1080
#define model2 1080 // for GP2Y0A21YK0F  used 1080
#define model3 1080

SharpIR SharpIRD(IRDerecha,model1);
SharpIR SharpIRC(IRCentro,model2);
SharpIR SharpIRI(IRIzquierda, model3);

//Sensores
int cal_sp_l,cal_sp_d;
int sp_l,sp_d;
int SensorDistaciaCentral;
int detecto_oponente;

//estrategia
int dsw;
int oponente_det;
int bandera_inicio;
int timeout_str;
int tiempo = 0;

//Ataque
int a_ataque;
int a_ubicacion;
int control_md, control_mi;
int x = 0;
int y = 0;
int cen = 0;
int der = 0;
int izq = 0;


//------------------------------------------------------------------------------FUNCIONES---------------------------------------
void adelante(int velocidad)
{
    analogWrite(MOTOR_PWMA, velocidad);
    analogWrite(MOTOR_PWMB, velocidad);
    digitalWrite(MOTOR_BIN1, LOW);
    digitalWrite(MOTOR_BIN2, HIGH);
    digitalWrite(MOTOR_AIN1, LOW);
    digitalWrite(MOTOR_AIN2, HIGH);
}

void atras(int velocidad)
{
    analogWrite(MOTOR_PWMA, velocidad);
    analogWrite(MOTOR_PWMB, velocidad);
    digitalWrite(MOTOR_BIN1, HIGH);
    digitalWrite(MOTOR_BIN2, LOW);
    digitalWrite(MOTOR_AIN1, HIGH);
    digitalWrite(MOTOR_AIN2, LOW);
}



void derecha(int velocidad)
{
    analogWrite(MOTOR_PWMA, velocidad);
    analogWrite(MOTOR_PWMB, velocidad);
    digitalWrite(MOTOR_BIN1, LOW);
    digitalWrite(MOTOR_BIN2, HIGH);
    digitalWrite(MOTOR_AIN1, HIGH);
    digitalWrite(MOTOR_AIN2, LOW);
}

void izquierda(int velocidad)
{
    analogWrite(MOTOR_PWMA, velocidad);
    analogWrite(MOTOR_PWMB, velocidad);
    digitalWrite(MOTOR_BIN1, HIGH);
    digitalWrite(MOTOR_BIN2, LOW);
    digitalWrite(MOTOR_AIN1, LOW);
    digitalWrite(MOTOR_AIN2, HIGH);
}

void detener(int velocidad)
{
    analogWrite(MOTOR_PWMA, velocidad);
    analogWrite(MOTOR_PWMB, velocidad);
    digitalWrite(MOTOR_BIN1, LOW);
    digitalWrite(MOTOR_BIN2, LOW);
    digitalWrite(MOTOR_AIN1, LOW);
    digitalWrite(MOTOR_AIN2, LOW);
}

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


int calculo()
{

  int dis1=SharpIRD.distance();  
  int dis2=SharpIRC.distance();  
  int dis3=SharpIRI.distance();

  if(dis1 < dis2 && dis1 < dis3 && dis1 <10)
  {

    return 1; //Derecha

  }
   if(dis2< dis3 && dis2 < 10)
  {

    return 2; //Centro

  }
  else if(dis3< dis2 && dis3 < 10)
  {

    return 3; //Izquierdo

  }
  else
  {
  
    return 4; //Desconocido
  
  }

}


void setup()
{
 
  //PWM
  pinMode(MOTOR_PWMA,OUTPUT);
  pinMode(MOTOR_PWMB,OUTPUT);
  pinMode(MOTOR_AIN2,OUTPUT);
  pinMode(MOTOR_AIN1,OUTPUT);
  pinMode(MOTOR_BIN1,OUTPUT);
  pinMode(MOTOR_BIN2,OUTPUT);
 

  
  pinMode(SENSOR_IN_P1,INPUT);
  pinMode(SENSOR_IN_P2,INPUT);

 

  pinMode(IRIzquierda,INPUT);
  pinMode(IRCentro,INPUT);
  pinMode(IRDerecha,INPUT);
   digitalWrite(8,HIGH);

    //PARA DEBUGER
  Serial.begin(9600);
  
  //CALIBRAR SENSORES DE PISO
   cal_sp_l = 0;
   cal_sp_d = 0;

  delay(5000);
  adelante(240);
}

void loop() {


if(lineaIzquierda() || lineaDerecha())
{
 
int direccion = calculo();

Serial.print(direccion);
  
  if(direccion == 1)
  {
    derecha(240);
  }

  if ( direccion == 2)
  {

    adelante(255);
    
  }
  else if (direccion == 3 )
  {
    izquierda(255);
  }
  else if (direccion == 4)
  {
    adelante(200);
    }
  
}
else 
{
atras(255);
delay(550);
detener(100);
}

}
    
    

   
