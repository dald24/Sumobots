//--------------------------------------Variables-------------------------------------

int valor_deteccion = 0;
int estado = 0;

//MOTORES IZQUIERDA POR FUNCION
#define MOTOR_PWMA 5
#define MOTOR_AIN2 6  // CAMBIAR SI LA DIRECCION MOTOR ESTA AL CONTRARIO 6 por 7
#define MOTOR_AIN1 7


//MOTORES DERECHA POR FUNCION
#define MOTOR_PWMB1 9  //direccion 1
#define MOTOR_PWMB2 10  //direccion 2

//SENSORES PISO ENFRENTE
#define SP1 A1
#define SP2 A2

//SENSORES PISO ATRAS
#define SP3 A3
#define SP4 A4

//SENSORES INFRARROJOS
#define IR_Front 11
#define IR_45Der 12
#define IR_45Izq 2
#define IR_Izq 3
#define IR_Der 4

//---------------------------------------------------------Funciones----------------------------------------------
void atras(int velocidad)
{ 
    analogWrite(MOTOR_PWMA, velocidad);
    digitalWrite(MOTOR_AIN1, LOW);
    digitalWrite(MOTOR_AIN2, HIGH);
    
  analogWrite(MOTOR_PWMB1, velocidad);
  analogWrite(MOTOR_PWMB2,0);
  
  }

void adelante(int velocidad)
{
    analogWrite(MOTOR_PWMA, velocidad);
    digitalWrite(MOTOR_AIN2, LOW);
    digitalWrite(MOTOR_AIN1, HIGH);
      
  analogWrite(MOTOR_PWMB2, velocidad);
  analogWrite(MOTOR_PWMB1,0);
  
  }

void alto(int velocidad)
{
    analogWrite(MOTOR_PWMA, velocidad);
    digitalWrite(MOTOR_AIN1, LOW);
    digitalWrite(MOTOR_AIN2, LOW); 
    
  analogWrite(MOTOR_PWMB1, 0);
  analogWrite(MOTOR_PWMB2,0);
  
  }


void izquierda(int velocidad)
{
    analogWrite(MOTOR_PWMA, velocidad);
    digitalWrite(MOTOR_AIN1, LOW);
    digitalWrite(MOTOR_AIN2, HIGH);
  analogWrite(MOTOR_PWMB2, 0);
  analogWrite(MOTOR_PWMB1,velocidad);
  
  }

 void derecha(int velocidad)
{
    analogWrite(MOTOR_PWMA, velocidad);
    digitalWrite(MOTOR_AIN1, LOW);
    digitalWrite(MOTOR_AIN2, HIGH); 
    
  analogWrite(MOTOR_PWMB2, velocidad);
  analogWrite(MOTOR_PWMB1,0);
  
  }


 bool lineaAtras()
{

  if(digitalRead(SP2)==0 or digitalRead(SP4==0))
  {
      return true;
  }
  else
  {
    return false;  
  }
}

bool lineaEnfrente()
{

  if(digitalRead(SP1)==0 or digitalRead(SP3)==0)
  {
      return true;
  }
  else
  {
    return false;  
  }
}


int deteccion()
{
  if(digitalRead(IR_Front)==1){
    return 1;
    }

  if (digitalRead(IR_45Der)==1){
    return 2;
    }

  if(digitalRead(IR_45Izq)==1){
    return 3;
    }

  if(digitalRead(IR_Der)==1){
    return 4;
    }

  if(digitalRead(IR_Izq)==1){
    return 5;
    }

    else return 0;
 
}

void setup() {
  //PWM MOTORES
  pinMode(MOTOR_PWMA,OUTPUT);
  pinMode(MOTOR_AIN2,OUTPUT);
  pinMode(MOTOR_AIN1,OUTPUT);
  pinMode(MOTOR_PWMB1, OUTPUT);
  pinMode(MOTOR_PWMB2, OUTPUT);

  //SENSORES LINEA
  pinMode(SP1, INPUT);
  pinMode(SP2, INPUT);
  pinMode(SP3, INPUT);
  pinMode(SP4, INPUT);

  //SENSORES INFRARROJOS
  pinMode(IR_Front, INPUT);
  pinMode(IR_45Der, INPUT);
  pinMode(IR_45Izq, INPUT);
  pinMode(IR_Der, INPUT);
  pinMode(IR_Izq, INPUT);

  pinMode(13, INPUT);
  pinMode(A5, OUTPUT);
  pinMode(8, INPUT);
  pinMode(0, OUTPUT);

  digitalWrite(0,HIGH);

  Serial.begin(9600);

  adelante(200);

  
}

void loop() {
 

if(digitalRead(8) == 1){
      estado = 0;
      }
 if(digitalRead(13) == 1){
  estado = 1;  
 }

 Serial.print(estado);

 //TODO: Develop more strategies

if(estado == 0){
  alto(0);
  }

if(estado == 1){

  if(digitalRead(8) == 1){
    estado = 0;
    }

  if(!lineaEnfrente()){
  
    int direccion = deteccion();
  
    Serial.print(direccion);
    
    if(direccion == 1)//Front InfraRed Sensor
    {
      adelante(255);
    }
    else if ( direccion == 2)
    {
      derecha(125); 
    }
    else if (direccion == 3 )
    {
      izquierda(125);
    }
    else if (direccion == 4)
    {
      derecha(255);
    }
    else if (direccion == 5)
    {
      izquierda(255);
    }
    else if(direccion == 0)
    {
      alto(255);
    }
    
  }
  else 
  {
    atras(255);
    delay(550);
    alto(100);
  }
}
}


   
          

 
