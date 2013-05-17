#include <Servo.h>

/*
This code analyzes the pressure data coming in from the Pressure Transmitter
within the shoe. This code should be run alongside a Serial Port connection.
*/
const int buzzPin = 8; 


/*
Sets up the global variables
*/ 
int incomingByte; //A variable to read incoming serial data into
int totalTime=0; //Maintains a record of the time increment the system is recording for
int heelTime = 0; //Records how much time is spent on the heel
double heelPercent=0.0; //heelTime/totalTime
int midTime=0;
double midPercent=0.0;
int frontTime=0;
double frontPercent=0.0;
double totalPercent = 0.0;
int playBuzzer = 0; //A binary representation of when the buzzer should sound 
byte abc; //temporary storage byte
int value; 
int steps1; 
int totalSteps; //how many steps are taken by the user
double cadence; //steps per minute
int cadenceDelay; //an intentional lag in the system
int ringBuzzer = 0; // DO NOT RING BUZZER is 0
int printResultsOnce=1;
int printResultsTwice=1;
int stopPrinting = 0;

void setup(){
  Serial.begin(9600); //Baud rate is 9600
  totalTime = 0;
  pinMode(buzzPin,OUTPUT);
  cadenceDelay = 0;
}

void clearEveryThing(){ //artificially refresh the Serial Port for every new entry
 int temp = 100;
 while(temp>0){
      Serial.println();
      temp=temp-1;
 }
}

void loop(){ //main forever loop

if(playBuzzer == 0){
 digitalWrite(buzzPin,LOW);
}else{
  digitalWrite(buzzPin,HIGH);
}
    /*Assigns appropriate percentages based on time spent on various parts of the foot */
    totalPercent = frontTime+heelTime+midTime;
    heelPercent=heelTime/totalPercent*100;
    midPercent=midTime/totalPercent*100;
    frontPercent=frontTime/totalPercent*100;
    
    //Common running injuries stem from excess pressure on the Heel. Let's stop that!
    if(heelPercent>40 && ringBuzzer == 1){ // >40% heel time triggers an alarm
      playBuzzer = 1;
    }else{
      playBuzzer = 0;
    }
    
    if(totalTime>4310 && printResultsTwice==1){ 
      printResultsOnce=1;
      printResultsTwice=0;
      stopPrinting=1;
    }
      
    
  if(totalTime>2155 && printResultsOnce==1){ 
    clearEveryThing();
    Serial.println("HEEL Percent: ");
    Serial.print(heelPercent);
    Serial.println();
    Serial.println("MIDFOOT Percent: ");
    Serial.print(midPercent);
    Serial.println();
    Serial.println("FRONT Percent: ");
    Serial.print(frontPercent);
    Serial.println();
    
    Serial.println("Total Steps: ");
    Serial.print(totalSteps);
    Serial.println();
    
    printResultsOnce = 0;
    ringBuzzer = 1; //let the buzzer do its function if need be after first 30 sec...
    delay(1000);
      /*reset*/
      heelPercent = 0;
      midPercent = 0;
      frontPercent = 0; 
      totalSteps = 0;
      heelTime = 0;
      midTime = 0;
      frontTime = 0;
      totalPercent = 0;
  }
  
  totalTime = totalTime + 1;
  if(cadenceDelay>0){
    cadenceDelay = cadenceDelay-1;
  }
  
  delay(10);
  
  if(Serial.available() > 0 && stopPrinting==0){ 
    incomingByte = Serial.read();
    
  if(incomingByte==41){  
     heelTime = heelTime + 1;
    Serial.println("h");
       steps1 = 2;
    }else if(incomingByte==42){  
     midTime = midTime + 1;
    Serial.println("m");
      steps1 = 1;
   }else if(incomingByte==43){  
     frontTime = frontTime + 1;
    Serial.println("f");
      steps1 = 2;
    }
    if(steps1==2 && value==1 && (cadenceDelay == 0)){
      totalSteps = totalSteps+1;
      cadenceDelay = 40;
    }
    value = steps1;
    
  }
}
