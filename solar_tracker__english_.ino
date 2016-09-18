#include <Servo.h> 
char c;
int RF=3;
int RB=5;
int LF=11;
int LB=6;
int ldrtl = A0; //LDR top left
int ldrtr = A1; //LDR top right
int ldrdl = A2; //LDR down left
int ldrdr = A3; //ldr down right

Servo horizontal; 
int servoh = 90;     
Servo vertical;  
int servov = 90;    

void setup()
{
  Serial.begin(9600);
  horizontal.attach(2); 
  vertical.attach(7);
  pinMode(RF,OUTPUT);
  pinMode(RB,OUTPUT);
  pinMode(LF,OUTPUT);
  pinMode(LB,OUTPUT);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  pinMode(A4,INPUT);
  pinMode(A5,INPUT);
  
}

void loop() 
{
  c=Serial.read();
  if(c=='w')
  {
     analogWrite(RF,127);
    analogWrite(RB,0); 
    analogWrite(LF,127);
    analogWrite(LB,0); 
   
  }
if(c=='d')
  {
    analogWrite(RB,127);
    analogWrite(RF,0); 
    analogWrite(LF,127);
    analogWrite(LB,0); 
  }
  if(c=='a')
  {
    analogWrite(RF,127);
    analogWrite(RB,0); 
    analogWrite(LB,127);
    analogWrite(LF,0); 
  }
  if(c=='s')
  {
    analogWrite(RF,0);
    analogWrite(RB,0); 
    analogWrite(LF,0);
    analogWrite(LB,0); 
  }
  if(c=='z')
  {
     analogWrite(RF,0);
    analogWrite(RB,127); 
    analogWrite(LF,0);
    analogWrite(LB,127); 
   
  }
  if(c=='x')
  {
    Serial.begin(9600);
    
    while(c!='y')
    {
      c=Serial.read();
  int tl = analogRead(ldrtl); // top left
  int tr = analogRead(ldrtr); // top right
  int dl = analogRead(ldrdl); // down left
  int dr = analogRead(ldrdr); // down rigt
  Serial.println(tl);
   Serial.println(tr);
    Serial.println(dl);
     Serial.println(dr);
  
  int delaytime = analogRead(A4)/20; 
  int tol = analogRead(A5)/25; 
  int avt=(tl + tr)/2; // average value top
  int avd=(dl + dr)/2; // average value down
  int avl=(tl + dl)/2; // average value left
  int avr=(tr + dr)/2; // average value right

  int dvert = avt - avd; 
  int dhoriz = avl - avr;
    
  if (-1*tol > dvert || dvert > tol)
  {
  if (avt > avd)
  {
    servov = ++servov;
     if (servov > 180) 
     { 
      servov = 180;
     }
  }
  else if (avt < avd)
  {
    servov= --servov;
    if (servov < 0)
  {
    servov = 0;
  }
  }
  vertical.write(servov);
  }
  
  if (-1*tol > dhoriz || dhoriz > tol) 
  {
  if (avl > avr)
  {
    servoh = ++servoh;
    if (servoh > 180)
    {
    servoh = 180;
    }
  }
  else if (avl < avr)
  {
    servoh = --servoh;
     if (servoh < 0)
     {
     servoh = 0;
     }
  }
  else if (avl = avr)
  {
    
  }
  horizontal.write(servoh);
  }
    
   delay(delaytime); 
  }
  }
   
}
