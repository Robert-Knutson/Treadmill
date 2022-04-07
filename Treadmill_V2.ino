
// **************************************************
// ***************BELT SPEED SETTINGS ***************
// **************************************************
// The variables below control the speeds and timings of the desired perturbation profile
// The profiles are defined in terms of speed and duration
// So, the first item in speed is run for as long as the time listed in the first interval
// The speed profile is defined in terms of motor RPM
// The timing interval is defined in terms of milliseconds (1000 ms = 1s)
// ***NOTE*** - The number of items in speed MUST equal the number of items in interval for their respective sides
//            - Left and Right do not have to have the same number of items
const int LeftSpeedProfile2 []  = {500, -800, 500, 800, 0, 1000};
const int LeftMotorTiming2 []   = {1000, 2000, 1000, 2000, 2000, 3000};
const int RightSpeedProfile2 [] = {-500, 800, -500, 0};
const int RightMotorTiming2 []  = {12000, 1000, 1000, 1000};

const int LeftSpeedProfile3 []  = {250, -250, 250, 800, 0, 0, 250};
const int LeftMotorTiming3 []   = {1000, 2000, 1000, 2000, 1000, 2000, 3000};

const int RightSpeedProfile3 [] = {-700, 500, -300, 0};
const int RightMotorTiming3 []  = {1000, 1000, 2000, 1000};

int LeftSpeedProfile4 [200];
int LeftMotorTiming4 [200];

const int RightSpeedProfile4 [] = {-1.2};
const int RightMotorTiming4 []  = {985};

// The following variables control the creation of the desired profiles
const byte LeftSpeedLength2 = (sizeof(LeftSpeedProfile2) / sizeof(LeftSpeedProfile2[0]));
const byte RightSpeedLength2 = (sizeof(RightSpeedProfile2) / sizeof(RightSpeedProfile2[0]));
const byte LeftSpeedLength3 = (sizeof(LeftSpeedProfile3) / sizeof(LeftSpeedProfile3[0]));
const byte RightSpeedLength3 = (sizeof(RightSpeedProfile3) / sizeof(RightSpeedProfile3[0]));
const byte LeftSpeedLength4 = (sizeof(LeftSpeedProfile4) / sizeof(LeftSpeedProfile4[0]));
const byte RightSpeedLength4 = (sizeof(RightSpeedProfile4) / sizeof(RightSpeedProfile4[0]));

int LeftTiming2 [LeftSpeedLength2];
int RightTiming2 [RightSpeedLength2];
int LeftTiming3 [LeftSpeedLength3];
int RightTiming3 [RightSpeedLength3];

int LeftTiming [LeftSpeedLength4];

int RightTiming4 [RightSpeedLength4];

byte LeftSpeedPWM2 [LeftSpeedLength2];
byte RightSpeedPWM2 [RightSpeedLength2];
byte LeftSpeedPWM3 [LeftSpeedLength3];
byte RightSpeedPWM3 [RightSpeedLength3];

byte LeftSpeedPWM [LeftSpeedLength4];

byte RightSpeedPWM4 [RightSpeedLength4];

// **************************************************
// ***************** Hardware Pins ******************
// **************************************************
// In the following section we will define the pins that the hardware is connected to
const int Estop_pin = 2;  // Define Estop pin
const int Left_HLFB_Pin = 18;  // Define Motor_A HLFB input Interrupt pin, used in PWM ISR, has to be pin 2, 3, 18, 19 on MEAGA
const int Right_HLFB_Pin = 19; // Define Motor_B HLFB input Interrupt pin, used in PWM ISR, has to be pin 2, 3, 18, 19 on MEAGA

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

// **************************************************
// **************** Global Variables ****************
// **************************************************
//  Initialize variables for reading PWM values, used in PWM_ISRs
volatile float LeftHighTime = 0;  // USed in PWM_A_Falling ISR ***THIS VALUE WE NEED TO STORE IN MEMORY CARD***
volatile float LeftRiseTime = 0;  // Used in Left_PWM_Rising ISR
volatile float LeftPeriodTime = 0;// Used in Left_PWM_Rising ISR
int PrevousLeftHighTime = 0;    // Used in comparator to check if change has occurred in PWM A Value

volatile float RightHighTime = 0;  // USed in PWM_B_Falling ISR ***THIS VALUE WE NEED TO STORE IN MEMORY CARD***
volatile float RightRiseTime = 0;  // Used in Right_PWM_Rising ISR
volatile float RightPeriodTime = 0;// Used in Right_PWM_Rising ISR
int PrevousRightHighTime = 0;     // Used in comparator to check if change has occurred in PWM B Value

int LeftDutyCycle;
int RightDutyCycle;

// Variables for Trigger
volatile int TriggerISR = 0;
const int TriggerDebounceDelay = 100;
int CurrentPushTime;
int LastPushTime;
byte TriggerMode;

unsigned long StartMillis;
unsigned long currentMillis;

byte LeftStage = 0;
byte RightStage = 0;

byte stage = 0;
int MotorSpeed;
int OldMotorSpeed;

// Settings for 2-way communication on mode 5
byte i = 0; // Controlls loop for mode 5
byte ReadBeltSpeed = 0;  // Controls read  data loop in mode 5
int NewBeltSpeed [4];

// Variables For EStop State
bool EstopState;

// Variables for PerturbationProfile
const float vi = -1.2;
const int MaxMotorRPM = 1000;
byte BeltAccel;
float dT;
int NumSpaces;


void setup() {
  // Begin Serial Output
  //Serial.begin(9600);
  Serial.begin(250000);
  delay(2000);      // Wait for predetermined amount of time before continuing so serial monitor doesn’t output garbage
  Serial.println();

  int LeftTimingSum = 0;
  int RightTimingSum = 0;
  int LeftTimingSum2 = 0;
  int RightTimingSum2 = 0;
  int LeftTimingSum3 = 0;
  int RightTimingSum3 = 0;
  int LeftTimingSum4 = 0;
  int RightTimingSum4 = 0;

  // Mode 2
  for (int L = 0; L < LeftSpeedLength2; L++) {
    // Converts Motor RPM (-1000 to 1000 to corresponding PWM (0 to 255), 0 is max CCW and 255 is max CW)
    LeftSpeedPWM2 [L] = map(LeftSpeedProfile2[L], -1000, 1000, 0, 255);
    LeftTimingSum2 += LeftMotorTiming2 [L];
    LeftTiming2 [L] = LeftTimingSum2;
    Serial.print("Left Mode 2 PWM ");
    Serial.print(L);
    Serial.print(" = ");
    Serial.print(LeftSpeedPWM2 [L]);
    Serial.print(" @ ");
    Serial.println(LeftTiming2 [L]);
  }
  for (int R = 0; R < RightSpeedLength2; R++) {
    // Converts Motor RPM (-1000 to 1000 to corresponding PWM (0 to 255), 0 is max CCW and 255 is max CW)
    RightSpeedPWM2 [R] = map(RightSpeedProfile2[R], -1000, 1000, 0, 255);
    RightTimingSum2 += RightMotorTiming2 [R];
    RightTiming2 [R] = RightTimingSum2;
    Serial.print("Right Mode 2 PWM ");
    Serial.print(R);
    Serial.print(" = ");
    Serial.print( RightSpeedPWM2 [R]);
    Serial.print(" @ ");
    Serial.println(RightTiming2 [R]);
  }
  Serial.println("");

  // Mode 3
  for (int L = 0; L < LeftSpeedLength3; L++) {
    // Converts Motor RPM (-1000 to 1000 to corresponding PWM (0 to 255), 0 is max CCW and 255 is max CW)
    LeftSpeedPWM3 [L] = map(LeftSpeedProfile3[L], -1000, 1000, 0, 255);
    LeftTimingSum3 += LeftMotorTiming3 [L];
    LeftTiming3 [L] = LeftTimingSum3;
    Serial.print("Left Mode 3 PWM ");
    Serial.print(L);
    Serial.print(" = ");
    Serial.print(LeftSpeedPWM3 [L]);
    Serial.print(" @ ");
    Serial.println(LeftTiming3 [L]);
  }
  for (int R = 0; R < RightSpeedLength3; R++) {
    // Converts Motor RPM (-1000 to 1000 to corresponding PWM (0 to 255), 0 is max CCW and 255 is max CW)
    RightSpeedPWM3 [R] = map(RightSpeedProfile3[R], -1000, 1000, 0, 255);
    RightTimingSum3 += RightMotorTiming3 [R];
    RightTiming3 [R] = RightTimingSum3;
    Serial.print("Right Mode 3 PWM ");
    Serial.print(R);
    Serial.print(" = ");
    Serial.print( RightSpeedPWM3 [R]);
    Serial.print(" @ ");
    Serial.println(RightTiming3 [R]);
  }
  Serial.println("");

  // Mode 4
  for (int L = 0; L < LeftSpeedLength4; L++) {
    // Converts Motor RPM (-1000 to 1000 to corresponding PWM (0 to 255), 0 is max CCW and 255 is max CW)
    //LeftSpeedPWM [L] = map(LeftSpeedProfile4[L], -1000, 1000, 0, 255);
    //LeftTimingSum4 += LeftMotorTiming4 [L];
    //LeftTiming [L] = LeftTimingSum4;

    LeftSpeedPWM [L] = LeftSpeedProfile4[L];
    LeftTiming [L] = LeftMotorTiming4 [L];

    //Serial.print("Left Mode 4 PWM ");
    //Serial.print(L);
    //Serial.print(" = ");
    //Serial.print(LeftSpeedPWM [L]);
    //Serial.print(" @ ");
    //Serial.println(LeftTiming [L]);
  }
  for (int R = 0; R < RightSpeedLength4; R++) {
    // Converts Motor RPM (-1000 to 1000 to corresponding PWM (0 to 255), 0 is max CCW and 255 is max CW)
    RightSpeedPWM4 [R] = map(RightSpeedProfile4[R], -1000, 1000, 0, 255);
    RightTimingSum4 += RightMotorTiming4 [R];
    RightTiming4 [R] = RightTimingSum4;
    Serial.print("Right Mode 4 PWM ");
    Serial.print(R);
    Serial.print(" = ");
    Serial.print( RightSpeedPWM4 [R]);
    Serial.print(" @ ");
    Serial.println(RightTiming4 [R]);
  }
  Serial.println("");

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

  //attachInterrupt(digitalPinToInterrupt(Left_HLFB_Pin), Left_PWM_Rising, RISING);
  //attachInterrupt(digitalPinToInterrupt(Right_HLFB_Pin), Right_PWM_Rising, RISING);
}

void loop() {
  EstopState = digitalRead(Estop_pin);
  static bool PrevousEstopState;
  if (EstopState == 1) {
    // This forces the motors to disable every loop iteration even if another function is trying to enable them.
    digitalWrite(Right_Enable_Pin, LOW);
    digitalWrite(Left_Enable_Pin, LOW);
    digitalWrite(RedLEDpin, HIGH);
    PrevousEstopState = 1;
    Serial.println("EStop");
  }
  else if (PrevousEstopState != EstopState) {
    Serial.println("EStop Disengaged");
    digitalWrite(RedLEDpin, LOW);
    PrevousEstopState = 0;
  }
  currentMillis = millis();
  static byte SwitchPosition;
  static byte PrevousSwitchPosition = 8;
  static byte OperatingMode;

  SwitchPosition = (-9) + (digitalRead(SwitchPin1) * 1) + (digitalRead(SwitchPin2) * 2) + (digitalRead(SwitchPin3) * 3) + (digitalRead(SwitchPin4) * 4) + (digitalRead(SwitchPin5) * 5);
  if (PrevousSwitchPosition != SwitchPosition && SwitchPosition != 6) {
    // Turn off motor enable pins so the motor stops when the switch changes positions
    digitalWrite(Right_Enable_Pin, LOW);
    digitalWrite(Left_Enable_Pin, LOW);
    // Reset trigger so belt speed profiles dont continue to run when the switch changes position
    TriggerMode = 0;
    digitalWrite(GreenLEDpin, LOW); // Turn off Trigger LED
    LeftStage = 0;  // Reset belt stage so belt speed profiles starts at begining
    RightStage = 0;
    switch (SwitchPosition) {
      case 1:
        Serial.println("Position 1");
        OperatingMode = 1;
        break;
      case 2:
        Serial.println("Position 2");
        OperatingMode = 2;
        BeltAccel = 5;
        dT = 0.4;
        PerturbationProfile(vi, BeltAccel, dT);
        break;
      case 3:
        Serial.println("Position 3");
        OperatingMode = 3;
        BeltAccel = 5;
        dT = 0.5;
        PerturbationProfile(vi, BeltAccel, dT);
        break;
      case 4:
        Serial.println("Position 4");
        OperatingMode = 4;
        BeltAccel = 6;
        dT = 0.3;
        PerturbationProfile(vi, BeltAccel, dT);
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
    LeftDutyCycle = ((1 - (LeftHighTime / 22176)) * 1000) - 50;//*1000 instead of 100 because float only has 2 decimals of precision so we get more precision
    Serial.print('L');
    Serial.println(LeftDutyCycle);
    PrevousLeftHighTime = LeftHighTime;
  }

  if (RightHighTime != PrevousRightHighTime) {
    RightDutyCycle = ((1 - (RightHighTime / 22176)) * 1000) - 50;//*1000 instead of 100 because float only has 2 decimals of precision so we get more precision
    Serial.print('R');
    Serial.println(RightDutyCycle);
    PrevousRightHighTime = RightHighTime;
  }

  if (TriggerISR == 1 && digitalRead(TriggerOnPin) == 0 && digitalRead(TriggerOffPin) == 1 && TriggerMode == 0) {
    Serial.println("Trigger");
    StartMillis = millis(); // Initial Time used in motor timing loop
    digitalWrite(GreenLEDpin, HIGH);
    TriggerMode = 1;
    TriggerISR = 0;
    EIFR = bit (INT5);  //  Clears ISR Flag, needed because otherwise ISR will trigger again once reenabled, INT5 is the address for pin 3 ISR
    attachInterrupt(digitalPinToInterrupt(TriggerOnPin), Trigger_ISR, FALLING);
  }
  switch (OperatingMode) {
    case 1:
      if (TriggerMode == 1) {
        Mode1();
      }
      break;
    case 2:
      if (TriggerMode == 1) {
        Mode2();
      }
      break;
    case 3:
      if (TriggerMode == 1) {
        Mode3();
      }
      break;
    case 4:
      if (TriggerMode == 0) {
        digitalWrite(Right_Enable_Pin, HIGH);
        digitalWrite(Left_Enable_Pin, HIGH);
        MotorSpeed = LeftSpeedPWM [0];
        analogWrite(Right_InputB_Pin, MotorSpeed);
        analogWrite(Left_InputB_Pin, MotorSpeed);
      }
      else if (TriggerMode == 1) {
        Mode4();
      }
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
    digitalWrite(GreenLEDpin, LOW);
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
  MotorController(NumSpaces, LeftSpeedPWM, LeftTiming, RightSpeedLength2, RightSpeedPWM2, RightTiming2);
}

void Mode3() {
  MotorController(NumSpaces, LeftSpeedPWM, LeftTiming, RightSpeedLength3, RightSpeedPWM3, RightTiming3);
}

void Mode4() {
  MotorController(NumSpaces, LeftSpeedPWM, LeftTiming, RightSpeedLength4, RightSpeedPWM4, RightTiming4);
}

void Mode5() {
  while (i != 1) {
    for (int j = 0; j < 4; j++) {
      //Serial.println(j);
      Serial.println(LeftSpeedProfile4[j]);
      if (j == 3) {
        Serial.println("Done");
        i = 1;
      }
    }
  }
  while (ReadBeltSpeed != 1 && i == 1) {
    if (Serial.available()) {
      for (int j = 0; j < 4; j++) {
        int IncomingData = Serial.parseInt();
        NewBeltSpeed[j] = IncomingData;
        //Serial.println("Test");
        if (j == 3) {
          for (int k = 0; k < 4; k++) {
            Serial.println(NewBeltSpeed[k]);
            ReadBeltSpeed = 1;
          }
        }
      }
    }
  }
}

void MotorController (int NumSpaces, byte LeftSpeedPWM[], int LeftTiming [], int RightSpeedLength, byte RightSpeedPWM [], int RightTiming []) {

  if (currentMillis - StartMillis >  0 && currentMillis - StartMillis <= LeftTiming[1] && LeftStage < 1) {
    digitalWrite(Left_Enable_Pin, HIGH);
    analogWrite(Left_InputB_Pin, LeftSpeedPWM [LeftStage]);
    Serial.print("Left Stage ");
    Serial.print(LeftStage);
    Serial.print(" - ");
    Serial.println(LeftSpeedPWM [LeftStage]);
    //MotorDirection(LeftSpeedPWM[LeftStage], RightSpeedPWM[RightStage]);
    Serial.println();
    LeftStage = 1;
  }

  else if (currentMillis - StartMillis >  LeftTiming[LeftStage] && currentMillis - StartMillis <= LeftTiming[LeftStage+1] && LeftStage >= 1) {
    analogWrite(Left_InputB_Pin, LeftSpeedPWM [LeftStage]);
    //LeftStage=2;
    Serial.print("Left Stage ");
    Serial.print(LeftStage);
    Serial.print(" - ");
    Serial.print(LeftSpeedPWM [LeftStage]);
    Serial.print(", NumSpaces = ");
    Serial.println(NumSpaces);
    //MotorDirection(LeftSpeedPWM[LeftStage], RightSpeedPWM[RightStage]);
    Serial.println();
    LeftStage++;
  }
  else if (LeftStage == NumSpaces) {
    if (LeftTiming[NumSpaces] >= RightTiming[RightSpeedLength]) {
      Serial.println(LeftTiming[NumSpaces]);
      Serial.println(RightTiming[RightSpeedLength]);
      Serial.println("Done");
      TriggerMode = 0;
      digitalWrite(GreenLEDpin, LOW);
    }
    LeftStage = 0;
    Serial.println("Left Done");
  }

  // Same for right motor
  if (currentMillis - StartMillis >  0 && currentMillis - StartMillis <= RightTiming[1] && RightStage < 1) {
    digitalWrite(Right_Enable_Pin, HIGH);
    analogWrite(Right_InputB_Pin, RightSpeedPWM [RightStage]);
    Serial.print("Right Stage ");
    Serial.print(RightStage);
    Serial.print(" - ");
    Serial.println(RightSpeedPWM [RightStage]);
    //MotorDirection(LeftSpeedPWM[LeftStage], RightSpeedPWM[RightStage]);
    Serial.println();
    RightStage = 1;
  }

  else if (currentMillis - StartMillis >  RightTiming[RightStage] && currentMillis - StartMillis <= RightTiming[RightStage+1] && RightStage >= 1) {
    analogWrite(Right_InputB_Pin, RightSpeedPWM [RightStage]);
    //LeftStage=2;
    Serial.print("Right Stage ");
    Serial.print(RightStage);
    Serial.print(" - ");
    Serial.println(RightSpeedPWM [RightStage]);
    //MotorDirection(LeftSpeedPWM[LeftStage], RightSpeedPWM[RightStage]);
    Serial.println();
    RightStage++;
  }
  else if (RightStage == RightSpeedLength && currentMillis - StartMillis >  RightTiming[RightStage]) {
    if (RightTiming[RightSpeedLength] >= LeftTiming[NumSpaces]) {
      Serial.println(RightTiming[RightSpeedLength]);
      Serial.println(LeftTiming[NumSpaces]);
      Serial.println("Done");
      TriggerMode = 0;
      digitalWrite(GreenLEDpin, LOW);
    }
    RightStage = 0;
    Serial.println("Right Done");
  }
}
void MotorDirection (int LeftSpeedPWM, int RightSpeedPWM) {
  if (LeftSpeedPWM < 127) {
    Serial.println("LCCW");
  }
  else if (LeftSpeedPWM > 127) {
    Serial.println("LCW");
  }
  if (RightSpeedPWM < 127) {
    Serial.println("RCCW");
  }
  else if (RightSpeedPWM > 127) {
    Serial.println("RCW");
  }
}


int numSpaces (float vi, byte BeltAccel, float dT) {
  Serial.println("numSpacesBegin");

  // Declare Local Varriables
  int aSlow = -1;              // Rate to slow down the belt after hitting peak speed (m/s^2)

  // Calculate peak velocity
  float vf = vi + BeltAccel * dT;

  // Calculate time to return to Steady State Speed from peak velocity
  float dtSlow = (vi - vf) / aSlow;

  int NumSpaces = (dT + dtSlow) * 40;

  return NumSpaces;
}


void PerturbationProfile (float vi, byte BeltAccel, float dT) {
  // Function to calculate the belt speed profile from the given inputs and
  // convert that to a PWM value, this function assumes 40 data points per second.

  Serial.println("ProfileBegin");

  // Declare Local Varriables
  float r = 0.0762;             // Radius of the hub (m)
  float BeltThickness = 0.0028; // Thickness of the belt (m)
  int GearRto = 5;            // Gear reduction from the motor to the hub
  int aSlow = -1;              // Rate to slow down the belt after hitting peak speed (m/s^2)

  float rNet = r + BeltThickness;

  // Calculate peak velocity
  float vf = vi + BeltAccel * dT;
  //Serial.print("vf = ");
  //Serial.println(vf);

  // Calculate time to return to Steady State Speed from peak velocity
  float dtSlow = (vi - vf) / aSlow;
  //Serial.print("dtSlow = ");
  //Serial.println(dtSlow);

  // Calculate angular accel of motor from belt acceleration
  // This is the output tp put into Clearpath's Max Accel
  // Rounded up to nearest intiger
  // Output is in units of RPM/s
  int MotorAngAccel = ceil((BeltAccel / r) * (60 / (2 * 3.14)) * GearRto);
  //Serial.print("MotorAngAccel = ");
  //Serial.println(MotorAngAccel);

  // Save Time and Velocity points in array
  float t[3] = {0, dT * 1000, dT * 1000 + dtSlow * 1000};
  float v[3] = {vi, vf, vi};

  // Create array of timing values
  NumSpaces = numSpaces (vi, BeltAccel, dT);
  Serial.print("NumSpaces = ");
  Serial.println(NumSpaces);


  float MotorTiming[NumSpaces];
  float TimingDivision = ((dT + dtSlow) / (NumSpaces - 1)) * 1000;
  //Serial.print("TimingDivision = ");
  //Serial.println(TimingDivision);

  float TimingSum = 0;
  float MotorVel[NumSpaces];
  float yIntercept = vf - ((float)aSlow * dT);
  //Serial.print("yIntercept = ");
  //Serial.println(yIntercept);
  float MotorRPM[NumSpaces];
  byte MotorPWM[NumSpaces];


  for (int i = 0; i < NumSpaces + 1; i++) {
    MotorTiming[i] = round(TimingSum);
    LeftTiming[i] = MotorTiming[i] ;
    //Serial.print("LeftMotorTiming4 [");
    //Serial.print(i);
    //Serial.print("] =  ");
    //Serial.println(LeftMotorTiming4[i]);
    TimingSum = TimingSum + TimingDivision;
    if (MotorTiming[i] <= dT * 1000) {
      MotorVel[i] = BeltAccel * ((float)MotorTiming[i] / 1000) + vi;
      //Serial.print("Motor Vel [");
      //Serial.print(i);
      //Serial.print("] =  ");
      //Serial.println(MotorVel[i]);
    }
    else if (MotorTiming[i] > dT * 1000) {
      MotorVel[i] = aSlow * ((float)MotorTiming[i] / 1000) + yIntercept;
      //Serial.print("Motor Vel [");
      //Serial.print(i);
      //Serial.print("] =  ");
      //Serial.println(MotorVel[i]);
    }

    //MotorRPM[i] = (MotorVel[i]/rNet)*(60/(2*3.1415))*GearRto;
    MotorRPM[i] = (MotorVel[i] / rNet) * (9.549297) * GearRto;
    //Serial.print("MotorRPM [");
    //Serial.print(i);
    //Serial.print("] =  ");
    //Serial.println(MotorRPM[i]);

    // add in a variable for min and max motor speeds because it depends on motor voltage
    float TempPWM;
    TempPWM = round((MotorRPM[i] + MaxMotorRPM) * 255 / (2 * MaxMotorRPM));

    if (TempPWM > 255) {
      MotorPWM[i] = 255;
    }
    else if (TempPWM < 0) {
      MotorPWM[i] = 0;
    }
    else {
      MotorPWM[i] = TempPWM;
    }
    LeftSpeedPWM[i] = MotorPWM[i];
    //Serial.print("MotorPWM [");
    //Serial.print(i);
    //Serial.print("] =  ");
    //Serial.println(MotorPWM[i]);
  }
  Serial.println("END");

  //*MotorPWM = &LeftSpeedProfile4
  //*MotorTiming = &LeftMotorTiming4
}


/*
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

*/

void Trigger_ISR () {
  detachInterrupt(digitalPinToInterrupt(TriggerOnPin));
  TriggerISR = 1;
  //Serial.println("ISR");
  //Serial.println(digitalRead(TriggerOffPin));
  //Serial.println(digitalRead(TriggerOnPin));
  //TriggerDebounceStart = millis();
}
