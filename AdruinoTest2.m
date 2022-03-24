/*

*/
//Define Pins That Hardware Is Connected To
const int Estop_pin = 2;  // Define Estop Interrupt pin, has to be pin 2, 3, 18, 19 on MEAGA
const int Left_HLFB_Pin = 18;  // Define Motor_A HLFB input Interrupt pin, used in PWM ISR, has to be pin 2, 3, 18, 19 on MEAGA
const int Right_HLFB_Pin = 19; // Define Motor_B HLFB input Interrupt pin, used in PWM ISR, has to be pin 2, 3, 18, 19 on MEAGA
const int sdCard = 10; //SD Card Shield Pin
const int Left_Enable_Pin =  53; // the pin number of the ENABLE pin
const int Left_InputA_Pin =  4 ; // the pin number of the InputA pin, needs to be pins 2 - 13, 44 - 46 for PWM
const int Left_InputB_Pin =  5 ; // the pin number of the InputB pin, needs to be pins 2 - 13, 44 - 46 for PWM

const int Right_Enable_Pin =  52 ;// the pin number of the ENABLE pin
const int Right_InputA_Pin =  6 ;// the pin number of the InputA pin, needs to be pins 2 - 13, 44 - 46 for PWM
const int Right_InputB_Pin =  7 ;// the pin number of the InputB pin, needs to be pins 2 - 13, 44 - 46 for PWM

// Define Pins for Rotary Switch
const int SwitchPin1 = 31;
const int SwitchPin2 = 29;
const int SwitchPin3 = 27;
const int SwitchPin4 = 25;
const int SwitchPin5 = 23;

// Define pin for PushButton
const int TriggerOnPin = 3;
const int TriggerOffPin = 8;

// Define Pins for LEDs
const int RedLEDpin = 39;
const int GreenLEDpin = 37;

//  Initalize variables for reading PWM values, used in PWM_ISRs
volatile float LeftHighTime = 0;  // USed in PWM_A_Falling ISR ***THIS VALUE WE NEED TO STORE IN MEMORY CARD***
volatile float LeftRiseTime = 0;  // Used in Left_PWM_Rising ISR
volatile float LeftPeriodTime = 0;// Used in Left_PWM_Rising ISR
int PrevousLeftHighTime = 0;    // Used in comparitor to check if change has occuored in PWM A Value

volatile float RightHighTime = 0;  // USed in PWM_B_Falling ISR ***THIS VALUE WE NEED TO STORE IN MEMORY CARD***
volatile float RightRiseTime = 0;  // Used in Right_PWM_Rising ISR
volatile float RightPeriodTime = 0;// Used in Right_PWM_Rising ISR
int PrevousRightHighTime = 0;     // Used in comparitor to check if change has occuored in PWM B Value

int LeftDutyCycle;
int RightDutyCycle;

// Variables for Trigger
volatile int TriggerISR = 0;
const int TriggerDebounceDelay = 100;
int CurrentPushTime;
int LastPushTime;
byte TriggerMode;

// Initial Pin States, will need to use digitalWrite to actually pull these pins low
int Left_Enable = LOW;    // Sets Enable Pin to low so the decive doesnt automatically start
int Left_InputA = LOW;    // Sets InputA to low so the decive doesnt automatically start
int Left_InputB = LOW;    // Sets InputB to low so the decive doesnt automatically start
int Right_Enable = LOW;   // Sets Enable Pin to low so the decive doesnt automatically start
int Right_InputA = LOW;   // Sets InputA to low so the decive doesnt automatically start
int Right_InputB = LOW;

unsigned long StartMillis;
unsigned long currentMillis;

byte stage = 0;
int MotorSpeed;
int OldMotorSpeed;

byte OperatingMode;

void setup() {
  // Begin Serial Output
  //Serial.begin(9600);
  Serial.begin(250000);
  delay(1000);      // Wait for predetermined amount of time before contuniung so serial monitor works as expected
  Serial.println("");
  Serial.println("this is a test");
  // set the digital pin as output:
  pinMode(Left_Enable_Pin, OUTPUT);
  pinMode(Left_InputA_Pin, OUTPUT);
  pinMode(Left_InputB_Pin, OUTPUT);

  pinMode(Right_Enable_Pin, OUTPUT);
  pinMode(Right_InputA_Pin, OUTPUT);
  pinMode(Right_InputB_Pin, OUTPUT);

  pinMode(Estop_pin, INPUT_PULLUP);
  pinMode(Left_HLFB_Pin, INPUT_PULLUP);
  pinMode(Right_HLFB_Pin, INPUT_PULLUP);

  // Define Switch pins as inputs
  pinMode(SwitchPin1, INPUT_PULLUP);
  pinMode(SwitchPin2, INPUT_PULLUP);
  pinMode(SwitchPin3, INPUT_PULLUP);
  pinMode(SwitchPin4, INPUT_PULLUP);
  pinMode(SwitchPin5, INPUT_PULLUP);

  pinMode(TriggerOffPin, INPUT_PULLUP);
  pinMode(TriggerOnPin, INPUT_PULLUP);

  pinMode(RedLEDpin, OUTPUT);
  pinMode(GreenLEDpin, OUTPUT);

  digitalWrite(RedLEDpin, LOW);
  digitalWrite(GreenLEDpin, LOW);

  attachInterrupt(digitalPinToInterrupt(TriggerOnPin), Trigger_ISR, FALLING);   //Create ISR to monitor for changes in Trigger state

  //attachInterrupt(digitalPinToInterrupt(Estop_pin), Estop_ISR, CHANGE);   //Create ISR to monitor for changes in Estop state
  attachInterrupt(digitalPinToInterrupt(Left_HLFB_Pin), Left_PWM_Rising, RISING);
  attachInterrupt(digitalPinToInterrupt(Right_HLFB_Pin), Right_PWM_Rising, RISING);
  
}

void loop() {
  currentMillis = millis();
  static int SwitchPosition;
  static int PrevousSwitchPosition = 99;
  //static int TestSwitchPosition = 99;

  //static int PrevousTriggerISR = 99;

  SwitchPosition = (-9) + (digitalRead(SwitchPin1) * 1) + (digitalRead(SwitchPin2) * 2) + (digitalRead(SwitchPin3) * 3) + (digitalRead(SwitchPin4) * 4) + (digitalRead(SwitchPin5) * 5);
  if (PrevousSwitchPosition != SwitchPosition && SwitchPosition != 6) {
    // Turn off all motor pins so the motor stops when the switch changes positions
    digitalWrite(Right_Enable_Pin, LOW);
    digitalWrite(Right_InputA_Pin, LOW);
    digitalWrite(Right_InputB_Pin, LOW);
    digitalWrite(Left_Enable_Pin, LOW);
    digitalWrite(Left_InputA_Pin, LOW);
    digitalWrite(Left_InputB_Pin, LOW);
    switch (SwitchPosition) {
      case 1:
        Serial.println("Position 1");
        OperatingMode = 1;
        break;
      case 2:
        Serial.println("Position 2");
        OperatingMode = 2;
        break;
      case 3:
        Serial.println("Position 3");
        OperatingMode = 3;
        break;
      case 4:
        Serial.println("Position 4");
        OperatingMode = 4;
        break;
      case 5:
        Serial.println("Position 5");
        OperatingMode = 5;
        break;
      case 6:
        Serial.println("ERROR");
        break;
    }
    PrevousSwitchPosition = SwitchPosition;
  }



  if (LeftHighTime != PrevousLeftHighTime) {
    LeftDutyCycle = ((1 - (LeftHighTime / 22176)) * 1000) - 50;//*1000 instead of 100 because float only has 2 decimals of perccisions so we get more perccision

    //String data_array = "";
    //data_array += String(LeftHighTime);
    //data_array += ",";
    //data_array += String(millis());

    //DutyCycle = (Ton/(Ton+Toff))*100;
    //LeftDutyCycle = LeftHighTime / LeftPeriodTime;

    //Serial.print("Left Period Time = ");
    //Serial.print(LeftPeriodTime);
    //Serial.println();
    //Serial.print("LeftHighTime = ");
    //Serial.print(LeftHighTime);
    //Serial.println();
    //Serial.print("LeftDutyCycle = ");
    Serial.print('L');
    Serial.println(LeftDutyCycle);
    
    // DELETE THIS LATER
    Serial.print('R');
    Serial.println(LeftDutyCycle);
    //Serial.println();
    //logfile.println(data_array);

    PrevousLeftHighTime = LeftHighTime;
  }

  if (RightHighTime != PrevousRightHighTime) {

    RightDutyCycle = ((1 - (RightHighTime / 22176)) * 1000) - 50;//*1000 instead of 100 because float only has 2 decimals of perccisions so we get more perccision

    //Serial.print("RightPeriod Time = ");
    //Serial.print(RightPeriodTime);
    //Serial.println();
    //Serial.print("RightHighTime = ");
    //Serial.print(RightHighTime);
    //Serial.println();
    //Serial.print("RightDutyCycle = ");

    //if (MotorSpeed < 128) {
    // Serial.println(RightDutyCycle * (-1));
    //}
    //else if (MotorSpeed >= 128) {
    Serial.print('R');
    Serial.println(RightDutyCycle);
    //}
    //Serial.println();
    //Serial.println(currentMillis - StartMillis);
    //logfile.print(RightHighTime);

    PrevousRightHighTime = RightHighTime;
  }

  if (TriggerISR == 1 && digitalRead(TriggerOnPin) == 0 && digitalRead(TriggerOffPin) == 1 && TriggerMode ==0) {
    Serial.println("Trigger");
    //Serial.println(LastPushTime);
    //Serial.println(CurrentPushTime);
    //LastPushTime = CurrentPushTime;
    //CurrentPushTime = millis();
    StartMillis = millis(); // Initial Time used in motor timing loop

    //Serial.println("Time Since Last Button Push");
    //Serial.println(CurrentPushTime - LastPushTime);
    //Serial.println();

    digitalWrite(GreenLEDpin, HIGH);
    //delay(500);
    digitalWrite(GreenLEDpin, LOW);
    
    TriggerMode = 1;
    TriggerISR = 0;
    EIFR = bit (INT5);  //  Clears ISR Flag, needed because otherwise ISR will trigger again once reenabled, INT5 is the address for pin 3 ISR
    attachInterrupt(digitalPinToInterrupt(TriggerOnPin), Trigger_ISR, FALLING);
  }
  switch (OperatingMode) {
    case 1:
      if (TriggerMode == 1) {
        //Serial.println(currentMillis - StartMillis);
        Mode1();
      }
      break;
    case 2:
      Mode2();
      break;
    case 3:
      Mode3();
      break;
    case 4:
      Mode4();
      break;
    case 5:
      Mode5();
      break;
  }

}

void Mode1 () {
  if (currentMillis - StartMillis >  0 && currentMillis - StartMillis <= 1000 && stage != 1) {
    //Serial.println("Stage 1");
    MotorSpeed = 20;
    Serial.println("LCCW");
    Serial.println("RCCW");
    digitalWrite(Right_Enable_Pin, HIGH);
    digitalWrite(Left_Enable_Pin, HIGH);
    analogWrite(Right_InputB_Pin, MotorSpeed);
    analogWrite(Left_InputB_Pin, MotorSpeed);
    stage = 1;
  }
  else if (currentMillis - StartMillis >  1000 && currentMillis - StartMillis <=  2000 && stage != 2) {
    //Serial.println("Stage 2");
    MotorSpeed = 254;
    analogWrite(Right_InputB_Pin, MotorSpeed);
    analogWrite(Left_InputB_Pin, MotorSpeed);
    Serial.println("LCW");
    Serial.println("RCW");
    stage = 2;
  }
  else if (currentMillis - StartMillis > 2000 && currentMillis - StartMillis <=  3000 && stage != 3) {
    //Serial.println("Stage 3");
    MotorSpeed = 1;
    analogWrite(Right_InputB_Pin, MotorSpeed);
    analogWrite(Left_InputB_Pin, MotorSpeed);
    Serial.println("LCCW");
    Serial.println("RCCW");
    stage = 3;
  }
  else if (currentMillis - StartMillis > 3000 && currentMillis - StartMillis <=  4000 && stage != 4) {
    //Serial.println("Stage 4");
    MotorSpeed = 128;
    analogWrite(Right_InputB_Pin, MotorSpeed);
    analogWrite(Left_InputB_Pin, MotorSpeed);
    Serial.println("LCW");
    Serial.println("RCW");
    stage = 4;
  }
  else if (currentMillis - StartMillis > 4000 && currentMillis - StartMillis <=  5000 && stage != 5) {
    digitalWrite(Right_InputA_Pin, HIGH);
    digitalWrite(Left_InputA_Pin, HIGH);
    stage = 5;
  }
  else if (currentMillis - StartMillis > 5000 && stage != 6) {
    StartMillis = currentMillis;
    Serial.println("Done");
    digitalWrite(Right_Enable_Pin, LOW);
    digitalWrite(Right_InputA_Pin, LOW);
    digitalWrite(Right_InputB_Pin, LOW);
    digitalWrite(Left_Enable_Pin, LOW);
    digitalWrite(Left_InputA_Pin, LOW);
    digitalWrite(Left_InputB_Pin, LOW);
    stage = 6;
    TriggerMode = 0;
    
  }

}
void Mode2() {

}

void Mode3() {

}

void Mode4() {

}

void Mode5() {

}

// ISR to read pwm values sent from motor
void Left_PWM_Rising () {
  attachInterrupt(digitalPinToInterrupt(Left_HLFB_Pin), PWM_A_Falling, FALLING);
  //LeftPeriodTime = micros() - LeftRiseTime;
  LeftRiseTime = micros();
}

void PWM_A_Falling () {
  attachInterrupt(digitalPinToInterrupt(Left_HLFB_Pin), Left_PWM_Rising, RISING);
  LeftHighTime = micros() - LeftRiseTime;
}

void Right_PWM_Rising () {
  attachInterrupt(digitalPinToInterrupt(Right_HLFB_Pin), PWM_B_Falling, FALLING);
  //RightPeriodTime = micros() - RightRiseTime;
  RightRiseTime = micros();
}

void PWM_B_Falling () {
  attachInterrupt(digitalPinToInterrupt(Right_HLFB_Pin), Right_PWM_Rising, RISING);
  RightHighTime = micros() - RightRiseTime;
}

void Trigger_ISR () {
  detachInterrupt(digitalPinToInterrupt(TriggerOnPin));
  TriggerISR = 1;
  //Serial.println("ISR");
  //Serial.println(digitalRead(TriggerOffPin));
  //Serial.println(digitalRead(TriggerOnPin));
  //TriggerDebounceStart = millis();
}
