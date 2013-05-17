/*
This code can be run on an Arduino microcontroller
outfitted with 3 pressure sensing input devices.

*/


//FOR PRESSURE TRANSMITTER. 

const int pressurePinHeel = 0; 
const int pressurePinM = 2;
const int pressurePinF = 1; 
const int ledPin = 8; 
const int ledPinGreen = 2;


int pressure1H = 0; 
int pressure2H = 0;
int pressure3H = 0;
int pressure4H = 0;
int pressure5H = 0;
int pressureSumH = 0;
int pressureAvgH = 0;

int pressure1M = 0; 
int pressure2M = 0;
int pressure3M = 0;
int pressure4M = 0;
int pressure5M = 0;
int pressureSumM = 0;
int pressureAvgM = 0;

int pressure1F = 0; 
int pressure2F = 0;
int pressure3F = 0;
int pressure4F = 0;
int pressure5F = 0;
int pressureSumF = 0;
int pressureAvgF = 0;

int artificialM = 0;
int artificialF = 0;

int timer = 0; //each unit is ONE TICK
int idealTickGapMin = 11; //CHANGE THIS TO TICKS CORRESPONDING TO 0.6666 seconds
int idealTickGapMax = 23;

void setup(){
  Serial.begin(9600);
  pinMode(pressurePinHeel, INPUT);
  pinMode(pressurePinM, INPUT);
  pinMode(pressurePinF,INPUT);
  pinMode(ledPin,OUTPUT);
  pinMode(ledPinGreen,OUTPUT);
}


void loop(){
  
  if(timer== idealTickGapMax){
    timer = 0;
  }else{
  timer = timer + 1; 
  }
  
  Serial.println(timer); //TEST: IN ORDER TO SET CADENCE LED RATE!!!
  
  if(timer<idealTickGapMax && timer>idealTickGapMin){
     digitalWrite(ledPinGreen,HIGH);
     digitalWrite(ledPin,LOW);
  }else{
     digitalWrite(ledPinGreen,LOW);
     digitalWrite(ledPin,HIGH);
  }
    
  
  pressure1H = analogRead(pressurePinHeel); //read pressure from Heel
  pressure1M = analogRead(pressurePinM); //read pressure from Mid
  pressure1F = analogRead(pressurePinF); //read pressure from Front
  delay(10);
  pressure2H = analogRead(pressurePinHeel);//read pressure from Heel
  pressure2M = analogRead(pressurePinM); //read pressure from Mid
  pressure2F = analogRead(pressurePinF); //read pressure from Front
  delay(10);
  pressure3H = analogRead(pressurePinHeel);//read pressure from Heel
  pressure3M = analogRead(pressurePinM); //read pressure from Mid
  pressure3F = analogRead(pressurePinF); //read pressure from Front
  delay(10);
  pressure4H = analogRead(pressurePinHeel);//read pressure from Heel
  pressure4M = analogRead(pressurePinM); //read pressure from Mid
  pressure4F = analogRead(pressurePinF); //read pressure from Front
  delay(10);
  pressure5H = analogRead(pressurePinHeel);//read pressure from Heel
  pressure5M = analogRead(pressurePinM); //read pressure from Mid
  pressure5F = analogRead(pressurePinF); //read pressure from Front
  
  pressureSumH = pressure1H+pressure2H+pressure3H+pressure4H+pressure5H;
  pressureSumM = pressure1M+pressure2M+pressure3M+pressure4M+pressure5M;
  pressureSumF = pressure1F+pressure2F+pressure3F+pressure4F+pressure5F;
  
  //Sample 5 pressures and return results for each sensor
  pressureAvgH = pressureSumH/5; // (RANGE: 0 - 1023)
  pressureAvgM = pressureSumM/5; // (RANGE: 0 - 1023)
  pressureAvgF = pressureSumF/5; // (RANGE: 0 - 1023)

  //Write to Receiver
  if(pressureAvgH>800){
    Serial.write(")");
  }if(pressureAvgM>800){
    Serial.write("*");
  }if(pressureAvgF>800){
    Serial.write("+");
  }
  
  //Reset Values
  pressureAvgH = 0;
  pressureAvgM = 0;
  pressureAvgF = 0;
  artificialM = 0;
  artificialF = 0;
  
}