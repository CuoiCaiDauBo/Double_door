#include<Arduino.h>
#include<Servo.h>

int pirA1 = 2;
int pirA2 = 3;
int pirB2 = 4;
int pirB1 = 5;

int doorA = 6;
int doorB = 7;
//int relayLock = 9;

  int prepirA1 = LOW;
  int prepirA2 = LOW;
  int prepirB1 = LOW;
  int prepirB2 = LOW;

int crpirA1 = digitalRead(pirA1);
int crpirA2 = digitalRead(pirA2);
int crpirB1 = digitalRead(pirB1);
int crpirB2 = digitalRead(pirB2);


Servo svdoorA;
Servo svdoorB;

int open = 180;
int close = 0;
//Variables
//*********************************************************************


//boolean moving = false;


//*********************************************************************

// the setup routine runs once when you press reset:
void setup() {

  Serial.begin(9600);

  svdoorA.attach(doorA);
  svdoorB.attach(doorB);

  //It´s necessary to indicate the inputs and outputs 

  pinMode(doorA, OUTPUT);
  pinMode(doorB, OUTPUT);



  // pinMode(buttonOpenClose, INPUT);
  // pinMode(buttonEmergency, INPUT);
  // pinMode(remoteOpenClose, INPUT);  
  // pinMode(securitySensor, INPUT);
  // pinMode(limitOpen1, INPUT);
  // pinMode(limitClose1, INPUT);
  // pinMode(limitOpen2, INPUT);
  // pinMode(limitClose2, INPUT);

  pinMode(pirA1,INPUT);
  pinMode(pirA2,INPUT);
  pinMode(pirB1,INPUT);
  pinMode(pirB2,INPUT);
}

void openDoorA() {
  svdoorA.write(open);
}

void closeDoorA() {
  svdoorA.write(close);
}

void openDoorB() {
  svdoorB.write(open);
}

void closeDoorB() {
  svdoorB.write(close);
}

//Methods:
//*********************************************************************

// boolean checkOpenClose(int limit1, int limit2){
 
//   if ( (digitalRead(limit1) == HIGH) && (digitalRead(limit2) == HIGH)){ return true; }
 
//   else{ return false; }
    
// }


// boolean pressButton(int button, int remote){

//   if ( (digitalRead(button) == HIGH) || (digitalRead(remote) == HIGH)){ return true; }

//   else{return false;}
    
// }

void TH12A() {
  if(digitalRead(pirA1) == HIGH){
    Serial.println("A");
    openDoorA();
    delay(2000);
    if(digitalRead(pirB2) == HIGH){
      Serial.println("B");
      delay(1000);
      closeDoorA();
      delay(1000);
      openDoorB();
      delay(4000);
      Serial.println("C");      
      closeDoorB();
    }else{
      delay(2000);
      Serial.println("D");
      closeDoorA();
      delay(2000);
    }
  }
}

void TH12B() {
  if(digitalRead(pirB1) == HIGH){
    Serial.println("AA");
    openDoorB();
    delay(4000);
    if(digitalRead(pirA2) == HIGH){
      Serial.println("BB");
      delay(1000);
      closeDoorB();
      delay(1000);
      openDoorA();
      delay(4000);
      Serial.println("CC");      
      closeDoorA();
    }else{
      delay(2000);
      Serial.println("DD");
      closeDoorB();
      delay(2000);
    }
  }
}

// void TH3() {
//   if(digitalRead(pirA1 == HIGH))

// }

void test() {
      if(digitalRead(pirA1) == HIGH){
      openDoorA();
      delay(5000);
      closeDoorA();
      delay(2000);
      openDoorB();
      delay(5000);
      closeDoorB();
      delay(2000);
    }
}

void tracking(){
    if(crpirA1 != prepirA1){
      Serial.print("pirA1: ");
      Serial.println(crpirA1);
      prepirA1 = crpirA1;
    }
        if(crpirA2 != prepirA2){
      Serial.print("pirA2: ");
      Serial.println(crpirA2);
      prepirA2 = crpirA2;
    }
        if(crpirB1 != prepirB1){
      Serial.print("pirB1: ");
      Serial.println(crpirB1);
      prepirB1 = crpirB1;
    }
        if(crpirB2 != prepirB2){
      Serial.print("pirB2: ");
      Serial.println(crpirB2);
      prepirB2 = crpirB2;
    }
    delay(1000);
}

void controlv3() {
  if(digitalRead(pirA1) == HIGH){
    Serial.println("Cua A mo");
    openDoorA();
    while(digitalRead(pirA1) == HIGH || digitalRead(pirA2) == HIGH){
        Serial.println("giu cua A mo");
        if(digitalRead(pirB2) == HIGH){
          Serial.println("cua B mo");
          openDoorB();
          delay(2000);
          closeDoorA();
          closeDoorB();
        }else{}
    } closeDoorA();
    Serial.println("cua A dong");}
      if(digitalRead(pirB2) == HIGH){
        Serial.println("cua B mo");
        openDoorB();
        while(digitalRead(pirB2) == HIGH){
          Serial.println("giu cua B mo");
        }closeDoorB();
        Serial.println("cua B dong");
  }

   if(digitalRead(pirB1) == HIGH){
    Serial.println("Cua B mo");
    openDoorB();
    while(digitalRead(pirB1) == HIGH || digitalRead(pirB2) == HIGH){
        Serial.println("giu cua B mo");
        if(digitalRead(pirA2) == HIGH){
          Serial.println("cua A mo");
          openDoorA();
          delay(2000);
          closeDoorB();
          closeDoorA();
        }else{}
    } closeDoorB();
    Serial.println("cua B dong");}
      if(digitalRead(pirA2) == HIGH){
        Serial.println("cua A mo");
        openDoorA();
        while(digitalRead(pirA2) == HIGH){
          Serial.println("giu cua A mo");
        }closeDoorA();
        Serial.println("cua A dong");
  }
}

void controlv2() {
   if (digitalRead(pirA1) == HIGH) {
    Serial.println("cua A mo");
    openDoorA();
    delay(1000);

    if (digitalRead(pirA1) == LOW) {
      if (digitalRead(pirB2) == HIGH) {
        Serial.println("cua A dong");
        closeDoorA();
        delay(1000);

        Serial.println("cua B mo");
        openDoorB();
        delay(1000);

        if (digitalRead(pirB2) == HIGH) {
          Serial.println("cua B mo");
          openDoorB();
          delay(1000);
        } else {
          Serial.println("cua B dong");
          closeDoorB();
          delay(1000);
        }
      } else if (digitalRead(pirB2) == LOW) {
        Serial.println("cua B dong");
        closeDoorB();
        delay(1000);

        if (digitalRead(pirA1) == HIGH) {
          Serial.println("cua A mo");
          openDoorA();
          delay(1000);
        } else {
          Serial.println("cua A dong");
          closeDoorA();
          delay(1000);
        }
      } else {
        Serial.println("cua A dong");
        closeDoorA();
        delay(1000);
        Serial.println("cua B dong");
        closeDoorB();
        delay(1000);
      }
    } else {
      Serial.println("cua A dong");
      closeDoorA();
      delay(1000);
      Serial.println("cua B dong");
      closeDoorB();
      delay(1000);
    }
  } else {
    Serial.println("cua A dong");
    closeDoorA();
    delay(1000);
  }
}

void control(){
if (digitalRead(pirA1) == HIGH){
    // digitalWrite(doorA ,HIGH);
    Serial.println("cua A mo");
    openDoorA();
  while (digitalRead(pirA1) == HIGH){
    
  }
        if (digitalRead(pirA1) == LOW && digitalRead(pirB2 == HIGH)){
            // digitalWrite(doorA,LOW);
            Serial.println("cua A dong");
            closeDoorA();
            delay(1000);
            // digitalWrite(doorB, HIGH);
            Serial.println("cua B mo");
            openDoorB();
            delay(1000);
            if(digitalRead(pirB2 == HIGH)){
              // digitalWrite(doorB, HIGH);
              Serial.println("cua B mo");
              openDoorB();
              delay(1000);
            }else{
              // digitalWrite(doorB, LOW);
              Serial.println("cua B dong");
              closeDoorB();
              delay(1000);
            }
        }else if (digitalRead(pirA1) == HIGH && digitalRead(pirB2 == LOW)){
            // digitalWrite(doorA, HIGH);
            Serial.println("cua A mo");
            openDoorA();
            delay(1000);
            // digitalWrite(doorB, LOW);
            Serial.println("cua B dong");
            closeDoorB();
            delay(1000);
            if(digitalRead(pirA1 == HIGH)){
              // digitalWrite(doorA, HIGH);
              Serial.println("cua A mo");
              openDoorA();
              delay(1000);
            }else{
              // digitalWrite(doorA, LOW);
              Serial.println("cua A dong");
              closeDoorA();
              delay(1000);
            }
        }else if(digitalRead(pirA1) == HIGH && digitalRead(pirB2 == HIGH)){     
            // digitalWrite(doorA, HIGH);
            Serial.println("cua A mo");
            openDoorA();
            delay(1000);
            // digitalWrite(doorB, HIGH);
            Serial.println("cua B mo");
            openDoorB();
            delay(1000);
            if(digitalRead(pirB2 == HIGH)){
              delay(2000);
              Serial.println("cua A dong");
              closeDoorA();
              delay(1000);
              Serial.println("cua B mo");
              openDoorB();
              delay(1000);
              }else{
                Serial.println("cua A dong");
                closeDoorA();
                delay(1000);
                Serial.println("cua B dong");
                closeDoorB();
                delay(1000);
              }
        }else{
            // digitalWrite(doorA, LOW);
            Serial.println("cua A dong");
            closeDoorA();
            delay(1000);
            Serial.println("cua B dong");
            closeDoorB();
            delay(1000);
        }
}else
    // digitalWrite(doorA, LOW);
    Serial.println("cua A dong");
    closeDoorA();
    delay(1000);
}
void loop() {
    // tracking();
    // control();
    //test();
    // TH12A();
    // TH12B();
    //controlv2();
    controlv3();
}