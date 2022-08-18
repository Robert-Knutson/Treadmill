// **************************************************
// **********STATIC PROFILE OPERATING MODE **********
// **************************************************
// The variables below control the speeds and timings of the desired perturbation profile
// The profiles are defined in terms of speed and duration
// So, the first item in speed is run for as long as the time listed in the first interval
// The speed profile is defined in terms of motor RPM
// The timing interval is defined in terms of milliseconds (1000 ms = 1s)
// ***NOTE*** - The number of items in speed MUST equal the number of items in interval for their respective sides
//            - Left and Right do not have to have the same number of items

// PASTE VALUES FROM MATLAB CSV SCRIPT HERE
const int TestSpeed5L[] = {137, 147, 157, 166, 176, 186, 196, 205, 215, 225, 235, 244, 243, 242, 241, 240, 239, 238, 237, 236, 235, 234, 233, 232, 231, 230, 229, 228, 227, 226, 225, 224, 223, 222, 221, 220, 219, 218, 217, 216, 215, 214, 213, 212, 211, 210, 209, 208, 207, 206, 205, 204, 203, 202, 201, 200, 199, 198, 197, 196, 195, 194, 193, 192, 191, 190, 189, 188, 187, 186, 185, 184, 183, 182, 181, 180, 179, 178, 177, 176, 175, 174, 173, 172, 171, 170, 169, 168, 167, 166, 165, 164, 163, 162, 161, 160, 159, 158, 157, 156, 155, 154, 153, 152, 151, 150, 149, 148, 147, 146, 145, 144, 143, 142, 141, 140, 139, 138, 137, 136, 135, 134, 133, 132, 131, 130, 129, 128};
const int TestSpeed5R[] = {118, 108, 98, 89, 79, 69, 59, 50, 40, 30, 20, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127};
const int TestTiming5[] = {25, 50, 75, 100, 126, 151, 176, 201, 226, 251, 276, 301, 327, 377, 402, 452, 502, 527, 578, 628, 678, 703, 754, 804, 829, 879, 929, 980, 1005, 1055, 1105, 1130, 1181, 1231, 1281, 1306, 1356, 1407, 1432, 1482, 1532, 1582, 1608, 1658, 1708, 1733, 1783, 1834, 1884, 1909, 1959, 2009, 2035, 2085, 2135, 2160, 2210, 2261, 2311, 2336, 2386, 2436, 2462, 2512, 2562, 2612, 2637, 2688, 2738, 2763, 2813, 2864, 2914, 2939, 2989, 3039, 3064, 3115, 3165, 3215, 3240, 3291, 3341, 3366, 3416, 3466, 3517, 3542, 3592, 3642, 3667, 3718, 3768, 3818, 3843, 3893, 3944, 3969, 4019, 4069, 4119, 4145, 4195, 4245, 4270, 4320, 4371, 4421, 4446, 4496, 4546, 4572, 4622, 4672, 4722, 4747, 4798, 4848, 4873, 4923, 4973, 5024, 5049, 5099, 5149, 5174, 5225, 5275};
const int NumSpaces5 = sizeof(TestTiming5) / sizeof(TestTiming5[0]);

const int TestSpeed4L[] = {136, 145, 154, 163, 171, 180, 189, 198, 206, 215, 224, 232, 231, 230, 229, 228, 227, 226, 225, 224, 223, 222, 221, 220, 219, 218, 217, 216, 215, 214, 213, 212, 211, 210, 209, 208, 207, 206, 205, 204, 203, 202, 201, 200, 199, 198, 197, 196, 195, 194, 193, 192, 191, 190, 189, 188, 187, 186, 185, 184, 183, 182, 181, 180, 179, 178, 177, 176, 175, 174, 173, 172, 171, 170, 169, 168, 167, 166, 165, 164, 163, 162, 161, 160, 159, 158, 157, 156, 155, 154, 153, 152, 151, 150, 149, 148, 147, 146, 145, 144, 143, 142, 141, 140, 139, 138, 137, 136, 135, 134, 133, 132, 131, 130, 129, 128};
const int TestSpeed4R[] = {119, 110, 101, 92, 84, 75, 66, 57, 49, 40, 31, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127};
const int TestTiming4[] = {25, 50, 75, 100, 126, 151, 176, 201, 226, 251, 276, 301, 352, 402, 427, 477, 527, 578, 628, 678, 728, 779, 829, 879, 904, 955, 1005, 1055, 1105, 1155, 1206, 1256, 1306, 1356, 1382, 1432, 1482, 1532, 1582, 1633, 1683, 1733, 1783, 1834, 1884, 1909, 1959, 2009, 2060, 2110, 2160, 2210, 2261, 2311, 2361, 2386, 2436, 2487, 2537, 2587, 2637, 2688, 2738, 2788, 2838, 2864, 2914, 2964, 3014, 3064, 3115, 3165, 3215, 3265, 3316, 3341, 3391, 3441, 3491, 3542, 3592, 3642, 3692, 3743, 3793, 3843, 3868, 3918, 3969, 4019, 4069, 4119, 4170, 4220, 4270, 4320, 4345, 4396, 4446, 4496, 4546, 4597, 4647, 4697, 4747, 4798, 4823, 4873, 4923, 4973, 5024, 5074, 5124, 5174, 5225, 5275};
const int NumSpaces4 = sizeof(TestTiming4) / sizeof(TestTiming4[0]);

const int TestSpeed3L[] = {135, 142, 149, 156, 164, 171, 178, 185, 193, 200, 207, 214, 213, 212, 211, 210, 209, 208, 207, 206, 205, 204, 203, 202, 201, 200, 199, 198, 197, 196, 195, 194, 193, 192, 191, 190, 189, 188, 187, 186, 185, 184, 183, 182, 181, 180, 179, 178, 177, 176, 175, 174, 173, 172, 171, 170, 169, 168, 167, 166, 165, 164, 163, 162, 161, 160, 159, 158, 157, 156, 155, 154, 153, 152, 151, 150, 149, 148, 147, 146, 145, 144, 143, 142, 141, 140, 139, 138, 137, 136, 135, 134, 133, 132, 131, 130, 129, 128};
const int TestSpeed3R[] = {120, 113, 106, 99, 91, 84, 77, 70, 62, 55, 48, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127};
const int TestTiming3[] = {25, 50, 75, 100, 125, 151, 176, 201, 226, 251, 276, 301, 351, 427, 477, 552, 627, 703, 753, 828, 904, 979, 1029, 1104, 1180, 1255, 1305, 1380, 1456, 1531, 1606, 1657, 1732, 1807, 1882, 1933, 2008, 2083, 2159, 2209, 2284, 2359, 2435, 2485, 2560, 2635, 2711, 2786, 2836, 2912, 2987, 3062, 3112, 3188, 3263, 3338, 3388, 3464, 3539, 3614, 3665, 3740, 3815, 3890, 3966, 4016, 4091, 4167, 4242, 4292, 4367, 4443, 4518, 4568, 4643, 4719, 4794, 4844, 4920, 4995, 5070, 5145, 5196, 5271, 5346, 5422, 5472, 5547, 5622, 5698, 5748, 5823, 5898, 5974, 6024, 6099, 6175, 6250};
const int NumSpaces3 = sizeof(TestTiming3) / sizeof(TestTiming3[0]);

const int TestSpeed2L[] = {133, 139, 145, 151, 156, 162, 168, 174, 180, 185, 191, 197, 196, 195, 194, 193, 192, 191, 190, 189, 188, 187, 186, 185, 184, 183, 182, 181, 180, 179, 178, 177, 176, 175, 174, 173, 172, 171, 170, 169, 168, 167, 166, 165, 164, 163, 162, 161, 160, 159, 158, 157, 156, 155, 154, 153, 152, 151, 150, 149, 148, 147, 146, 145, 144, 143, 142, 141, 140, 139, 138, 137, 136, 135, 134, 133, 132, 131, 130, 129, 128};
const int TestSpeed2R[] = {122, 116, 110, 104, 99, 93, 87, 81, 75, 70, 64, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127};
const int TestTiming2[] = {25, 50, 75, 100, 126, 151, 176, 201, 226, 251, 276, 301, 327, 402, 477, 553, 603, 678, 754, 829, 904, 980, 1055, 1130, 1206, 1256, 1331, 1407, 1482, 1557, 1633, 1708, 1783, 1834, 1909, 1984, 2060, 2135, 2210, 2286, 2361, 2411, 2487, 2562, 2637, 2713, 2788, 2864, 2939, 2989, 3064, 3140, 3215, 3291, 3366, 3441, 3517, 3567, 3642, 3718, 3793, 3868, 3944, 4019, 4094, 4145, 4220, 4295, 4371, 4446, 4521, 4597, 4672, 4722, 4798, 4873, 4948, 5024, 5099, 5174, 5250};
const int NumSpaces2 = sizeof(TestTiming2) / sizeof(TestTiming2[0]);

const int TestSpeed1L[] = {132, 137, 142, 147, 152, 157, 162, 166, 171, 176, 181, 186, 185, 184, 183, 182, 181, 180, 179, 178, 177, 176, 175, 174, 173, 172, 171, 170, 169, 168, 167, 166, 165, 164, 163, 162, 161, 160, 159, 158, 157, 156, 155, 154, 153, 152, 151, 150, 149, 148, 147, 146, 145, 144, 143, 142, 141, 140, 139, 138, 137, 136, 135, 134, 133, 132, 131, 130, 129, 128};
const int TestSpeed1R[] = {123, 118, 113, 108, 103, 98, 93, 89, 84, 79, 74, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127};
const int TestTiming1[] = {25, 50, 75, 101, 126, 151, 176, 201, 226, 251, 277, 302, 327, 377, 453, 528, 604, 654, 729, 805, 880, 930, 1006, 1081, 1157, 1207, 1282, 1358, 1433, 1484, 1559, 1635, 1685, 1760, 1836, 1911, 1961, 2037, 2112, 2188, 2238, 2313, 2389, 2464, 2515, 2590, 2665, 2741, 2791, 2867, 2942, 2992, 3068, 3143, 3219, 3269, 3344, 3420, 3495, 3546, 3621, 3696, 3772, 3822, 3898, 3973, 4049, 4099, 4174, 4250};
const int NumSpaces1 = sizeof(TestTiming1) / sizeof(TestTiming1[0]);


int aFastStor [] =    {    -5,    -5,    8,     -12,   -12};
//float aFastStor [] =    {    -5,    -5,    0,     -12,   -12};
float VmaxStor [] =   {  1.5,  1.5,  2.5,    3.6,  3.6};
float dtStor [] =    {  0.3,  0.3,  0.3,    0.3,  0.3};
float dtSlowStor [] = {0.3,  0.3,  0.3,    0.3,  0.3};
//float dtSlowStor [] = {dtStor[1],    4,    6,  dtStor[4],    8};
int aSlowStor [] =  {    5,    5,    8,     12,   12};
//float aSlowStor [] =  {aFastStor[1] * -1, 0, 0, aFastStor[4] * -1, 0};
int vi = 0;
float Vmax;
float dtSlow;

// Initialize array thats arbitrarily large to store motor speed and timnig values
int LeftSpeedProfile4 [100];
int LeftMotorTiming4 [100];

const int RightSpeedProfile4 [100];
const int RightMotorTiming4 [100];

// Determine the length of the profile, used to changes
const byte LeftSpeedLength4 = (sizeof(LeftSpeedProfile4) / sizeof(LeftSpeedProfile4[0]));
const byte RightSpeedLength4 = (sizeof(RightSpeedProfile4) / sizeof(RightSpeedProfile4[0]));

//
int LeftTiming [100];
int RightTiming [100];

//byte LeftSpeedPWM2 [LeftSpeedLength2];
//byte RightSpeedPWM2 [RightSpeedLength2];
//byte LeftSpeedPWM3 [LeftSpeedLength3];
//byte RightSpeedPWM3 [RightSpeedLength3];

int LeftSpeedPWM [100];
int RightSpeedPWM [100];

// **************************************************
// ***************** Hardware Pins ******************
// **************************************************
// Define the Arduino pins that hardware is connected to

// ******************* MOTOR PINS *******************
//  Both motors have 4 pins for communication
//  Enable Pin turns on the motor,
//        Enable = High, motors active
//        Enable = Low, motors inactive
//  Input A Pin is the Inhibit Pin.  This forces the belt speed to zero, overiding other inputs.
//        The function of this is simillar to the enable pin, but it does so without shutting down the motors,
//        so the pin state of the other inputs can still be monitored in ClearPath.
//        Input A = Low, motion enabled
//        Input A = High, motion disabled.
//  Input B Pin is the PWM pin, the motors read a PWM signal sent over this pin whose duty cycle represents the desired veolcity
//        Duty Cucle = 0% commands max speed in CCW direction
//        Duty Cycle = 100% commands max speed in CW direction
//        Duty Cycle = 50% commands zero speed
//        The max speed is set using the ClearPath software, and is a function of input voltage
//  HLFB Pin is an output pin, as in the motors output data that can be read by the arduino over this pin.
//        There are many modes this output can represent, see the ClearPath user manual
//        It is currently being used to output a PWM signal proportional the the motor speed.
//        But it also can output torque, pulses per revolution, system power on, among many othres

const int Left_Enable_Pin =  53; // the pin number of the ENABLE pin
const int Left_InputA_Pin =  4 ; // the pin number of the InputA pin, the Inhibit Pin
const int Left_InputB_Pin =  5 ; // the pin number of the InputB pin, needs to be pins 2 - 13, 44 - 46 for PWM
const int Left_HLFB_Pin = 18;    // the pin number of the HLFB pin, used in PWM ISR, has to be pin 2, 3, 18, 19 on MEAGA

const int Right_Enable_Pin =  52 ; // the pin number of the ENABLE pin
const int Right_InputA_Pin =  6 ;  // the pin number of the InputA pin, the Inhibit Pin
const int Right_InputB_Pin =  7 ;  // the pin number of the InputB pin, needs to be pins 2 - 13, 44 - 46 for PWM
const int Right_HLFB_Pin = 19;     // the pin number of the HLFB pin, used in PWM ISR, has to be pin 2, 3, 18, 19 on MEAGA

// Estop
const int Estop_pin = 2;  // Define Estop pin

// Rotary Switch
const int SwitchPin1 = 31;
const int SwitchPin2 = 29;
const int SwitchPin3 = 27;
const int SwitchPin4 = 25;
const int SwitchPin5 = 23;

// PushButton
const int TriggerOnPin = 3;
const int TriggerOffPin = 8;

// LEDs
const int RedLEDpin = 39;
const int GreenLEDpin = 37;
const int PWRLEDpin = 9;

// Belst Select Toggle Switch
const int SwitchLeftPin = 51;
const int SwitchRightPin = 50;

// Belt Speed Potentiometer
const int PotPin = A0;


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
volatile int TriggerISR = 0;          // Volatile needed so so varibale can be read and modified outside of ISR
const int TriggerDebounceDelay = 100;
int CurrentPushTime;
int LastPushTime;
byte TriggerMode;

// Variables for timing
unsigned long StartMillis;
unsigned long currentMillis;

// Variables for mmotor controller
int LeftStage = 0;
int RightStage = 0;

int stage = 0;
int MotorSpeed;
int OldMotorSpeed;

// Settings for 2-way communication on mode 5
byte i = 0; // Controlls loop for mode 5
byte ReadBeltSpeed = 0;  // Controls read  data loop in mode 5
int NewBeltSpeed [4];

// Variables For EStop State
bool EstopState;


// Varriables for Potentiometer
float WalkingSpeed;

// Varrialbes for Belt Select Toggle Switch
byte SelectState;

// Variables for PerturbationProfile
const int MaxMotorRPM = 2200;
float aSlow;
float BeltAccel;
float dT;
//float dTslow;
int NumSpaces;
float MotorTiming[50];
float MotorVel[50];
float MotorRPM[50];
byte MotorPWM[50];
//int MotorTiming;
//float MotorRPM[350];
//float MotorVel;

// Varriables for Safety Systems
bool EstopSafetyDisable;

byte OperatingMode;

//  Begin Setup Loop, this only runs once during startup.
void setup() {
  // Begin Serial Output
  //Serial.begin(9600);   // Uncomment if using the Arduino Serial Monitor
  Serial.begin(250000);   // Uncomment if using the Matlab Serial Monitor
  delay(2000);      // Wait for predetermined amount of time before continuing so serial monitor doesn’t output garbage
  Serial.println();

  // Define inut and output pins
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

  pinMode(SwitchLeftPin, INPUT_PULLUP);
  pinMode(SwitchRightPin, INPUT_PULLUP);

  pinMode(RedLEDpin, OUTPUT);
  pinMode(GreenLEDpin, OUTPUT);
  pinMode(PWRLEDpin, OUTPUT);

  digitalWrite(RedLEDpin, LOW);
  digitalWrite(GreenLEDpin, LOW);

  attachInterrupt(digitalPinToInterrupt(TriggerOnPin), Trigger_ISR, FALLING);   //Create ISR to monitor for changes in Trigger state

  //attachInterrupt(digitalPinToInterrupt(Left_HLFB_Pin), Left_PWM_Rising, RISING);
  //attachInterrupt(digitalPinToInterrupt(Right_HLFB_Pin), Right_PWM_Rising, RISING);

  EstopSafetyDisable = 1; // Dont allow motion to begin if the belt speed is at a non zero state when the device is first turned on

  for (int i = 0; i < 5; i++) {
    if (aFastStor[i] == 0 && VmaxStor[i] != 0) {
      aFastStor[i] = (VmaxStor[i] - vi) / dtStor[i];
    }
    if (aSlowStor[i] == 0 && dtSlowStor[i] != 0) {
      aSlowStor[i] = (vi - VmaxStor[i]) / dtSlowStor[i];
    }
    Serial.print("Mode ");
    Serial.print(i);
    Serial.print(", aFast =");
    Serial.print(aFastStor[i]);
    Serial.print(", aSlow =");
    Serial.println(aSlowStor[i]);
  }
  Serial.println(NumSpaces5);
  Serial.println(NumSpaces3);
  Serial.println(NumSpaces2);
}

void loop() {

  // Estop - disables motors if its engaged
  EstopState = digitalRead(Estop_pin);
  static bool PrevousEstopState;
  if (EstopState == 1) {
    // This forces the motors to disable every loop iteration even if another function is trying to enable them.
    digitalWrite(Right_InputA_Pin, HIGH);
    digitalWrite(Left_InputA_Pin, HIGH);
    digitalWrite(RedLEDpin, HIGH);
    PrevousEstopState = 1;
    Serial.println("EStop");
  }
  else if (PrevousEstopState != EstopState) {
    Serial.println("EStop Disengaged");
    Serial.println("Return Belt Speed To Zero To Re-Enable Motion");
    digitalWrite(RedLEDpin, LOW);
    PrevousEstopState = 0;
    EstopSafetyDisable = 1;   // Flag to not allow belt motion untill belt speed is reset to zero
  }

  currentMillis = millis(); // Store time starting since the device was turned on, milliseconds

  // Belt Toggle Switch, lets user sselect between left, right or both belts
  static bool RecalcPerturbationProfile = 1; // Flag to store if Perturbation Profile needs to be recalculated, set to 1 so it auto executes on the first cycle
  static byte PrevousSelectState = 0;
  SelectState = digitalRead(SwitchLeftPin) + digitalRead(SwitchRightPin) * 2;
  if (SelectState != PrevousSelectState) {
    switch (SelectState) {
      case 1:
        Serial.println("Left");
        break;
      case 2:
        Serial.println("Right");
        break;
      case 3:
        Serial.println("BOTH");
        break;
    }
    PrevousSelectState = SelectState; // this is used to make the loop only run once, after state change
    RecalcPerturbationProfile = 1;  // Set flag high to recalculate perturbation profile
  }

  // Mode Switch, used to different operating modes, with different belt speed settings
  static byte SwitchPosition;
  static byte PrevousSwitchPosition = 8;  // initially set arbitrarily large so current switch position is read

  SwitchPosition = (-9) + (digitalRead(SwitchPin1) * 1) + (digitalRead(SwitchPin2) * 2) + (digitalRead(SwitchPin3) * 3) + (digitalRead(SwitchPin4) * 4) + (digitalRead(SwitchPin5) * 5);
  if (PrevousSwitchPosition != SwitchPosition && SwitchPosition != 6) {
    RecalcPerturbationProfile = 1;  // Profile needs to be reculculated if switch has changed positions
    TriggerMode = 0;// Reset trigger so belt speed profiles dont continue to run when the switch changes position
    digitalWrite(GreenLEDpin, LOW); // Turn off Trigger LED
    LeftStage = 0;  // Reset belt stage so belt speed profiles starts at begining
    RightStage = 0;
    switch (SwitchPosition) {
      case 1:
        Serial.println("Position 1");
        OperatingMode = 1;
        BeltAccel = -5;
        dT = 0.3;
        aSlow = 0.3;
        //BeltAccel = aFastStor[OperatingMode - 1];
        //dT = dtStor[OperatingMode - 1];
        //aSlow = aSlowStor[OperatingMode - 1];
        //dtSlow = dtSlowStor[OperatingMode - 1];
        //Vmax = VmaxStor[OperatingMode - 1];
        //aSlow = 1;
        break;
      case 2:
        Serial.println("Position 2");
        OperatingMode = 2;
        BeltAccel = -5;
        dT = 0.3;
        aSlow = 0.3;
        //BeltAccel = aFastStor[OperatingMode - 1];
        //dT = dtStor[OperatingMode - 1];
        //aSlow = aSlowStor[OperatingMode - 1];
        //dtSlow = dtSlowStor[OperatingMode - 1];
        //Vmax = VmaxStor[OperatingMode - 1];
        break;
      case 3:
        Serial.println("Position 3");
        OperatingMode = 3;
        BeltAccel = -8;
        dT = 0.3;
        aSlow = 0.3;
        //BeltAccel = aFastStor[OperatingMode - 1];
        //dT = dtStor[OperatingMode - 1];
        //aSlow = aSlowStor[OperatingMode - 1];
        //dtSlow = dtSlowStor[OperatingMode - 1];
        //Vmax = VmaxStor[OperatingMode - 1];
        break;
      case 4:
        Serial.println("Position 4");
        OperatingMode = 4;
        BeltAccel = -12;
        dT = 0.3;
        aSlow = 0.3;
        //aSlow = BeltAccel * - 1;
        break;
      case 5:
        Serial.println("Position 5");
        OperatingMode = 5;
        BeltAccel = -12;
        dT = 0.3;
        aSlow = 0.3;
        //BeltAccel = aFastStor[OperatingMode - 1];
        //dT = dtStor[OperatingMode - 1];
        //aSlow = aSlowStor[OperatingMode - 1];
        //dtSlow = dtSlowStor[OperatingMode - 1];
        //Vmax = VmaxStor[OperatingMode - 1];
        break;
      case 6:
        Serial.println("ERROR");
        break;
    }
    PrevousSwitchPosition = SwitchPosition; // Set prevous value to current value so loop only executes on state change
  }

  // Read Potentiometer to Determine Walking Speed
  static byte PrevousPotState = 0;
  byte PotState = map(analogRead(PotPin), 0, 1024, 0, 255); // Map to byte, used to reduce noise
  if (abs(PotState - PrevousPotState) >= 2) { // Only update if a large enough change has occoured
  Serial.println(PotState);
    //float WalkingSpeed = (PotState - 0) * (1.25 - -1.25) / (255 - 0) + -1.25;
    // Maps PotState to Belt Speed,
    // Map is used twice to reduce number of floating point calculations in main loop
    WalkingSpeed = (0.0098039 * PotState - 1.25);

    //WalkingSpeed = (0.0529*PotState + 127.5000);
    if (abs(WalkingSpeed) <= 0.05) {  // Set Walking speed to 0 if its close to 0
      WalkingSpeed = 0;
    }
    byte BeltSpeed;
    BeltSpeed = (WalkingSpeed - -1.2) * (173 - 81) / (1.2 - -1.2) + 81; //map(WalkingSpeed,-1.2,1.2,81,173);
    if (SelectState == 2 && BeltSpeed > 126) {  // Writes Walking Speed to motors if Belt Select Switch is set to RIGHT
      //if (abs(PotState - 127) <= 2){
      //  PotState = 127;
      //}
      
      Serial.print("BeltSpeed = ");
      Serial.println(BeltSpeed);
      digitalWrite(Right_Enable_Pin, HIGH);
      digitalWrite(Left_Enable_Pin, HIGH);
      analogWrite(Right_InputB_Pin, map(BeltSpeed, 1, 254, 254, 1));
      analogWrite(Left_InputB_Pin, BeltSpeed);
      Serial.println("Walking Mode");
    }
    Serial.println(PrevousPotState);
    Serial.print("Pot Reading = ");
    Serial.print(PotState);
    Serial.print(", Belt Speed = ");
    Serial.println(WalkingSpeed);
    analogWrite(PWRLEDpin, PotState);  // Change Power LED brightness based of reading, just for fun
    PrevousPotState = PotState;
    RecalcPerturbationProfile = 1;
  }
  
  // Recalc Perturbation profile if speed or mode changes, used for dynamic profiles
  if (RecalcPerturbationProfile == 1) {
    PerturbationProfile(WalkingSpeed, BeltAccel, dT);
    RecalcPerturbationProfile = 0;
  }

  // EStop safety loop logic
  if (EstopSafetyDisable == 1) {
    digitalWrite(Right_InputA_Pin, HIGH);  // Pull Inhibit pin hight to disallow motion without shutting down motors
    digitalWrite(Left_InputA_Pin, HIGH);
    bool LEDstate = 1;
    while (EstopSafetyDisable == 1) {     // Loop untill Belt motion is reset to zero
      PotState = map(analogRead(PotPin), 0, 1024, 0, 255); // Read PotState again so we can exit the loop if it changes
      if (PotState != 125) {
        digitalWrite(RedLEDpin, LEDstate);    // Blink all LEDs so user knows there is an issue
        digitalWrite(GreenLEDpin, LEDstate);
        digitalWrite(PWRLEDpin, LEDstate);
        delay(250);
        LEDstate = !LEDstate;
      }
      else if (PotState == 125) {
        Serial.println("Motion Allowed");
        Serial.println("");
        digitalWrite(RedLEDpin, LOW);
        digitalWrite(GreenLEDpin, LOW);
        digitalWrite(Right_InputA_Pin, LOW);  // Pull Inhibit pin low to allow motion
        digitalWrite(Left_InputA_Pin, LOW);
        EstopSafetyDisable = 0;
      }
    }
  }

  // Calculate PWM duty cycle recievved from motor, only needed if motor HLFB is enabled
  if (LeftHighTime != PrevousLeftHighTime) {
    LeftDutyCycle = ((1 - (LeftHighTime / 22176)) * 1000) - 50;//*1000 instead of 100 because float only has 2 decimals of precision so we get more precision
    //Serial.print('L');
    //Serial.println(LeftDutyCycle);
    PrevousLeftHighTime = LeftHighTime;
  }

  if (RightHighTime != PrevousRightHighTime) {
    RightDutyCycle = ((1 - (RightHighTime / 22176)) * 1000) - 50;//*1000 instead of 100 because float only has 2 decimals of precision so we get more precision
    //Serial.print('R');
    //Serial.println(RightDutyCycle);
    PrevousRightHighTime = RightHighTime;
  }
  
  // Trigger Enable Logic
  if (TriggerISR == 1 && digitalRead(TriggerOnPin) == 0 && digitalRead(TriggerOffPin) == 1 && TriggerMode == 0) {
    Serial.println("Trigger");
    StartMillis = millis(); // Initial Time used in motor timing loop
    digitalWrite(GreenLEDpin, HIGH);  // Turn on trigger led
    TriggerMode = 1;  // Set trigger flag to on
    TriggerISR = 0;   // Set Trigger ISR flag to off
    EIFR = bit (INT5);  //  Clears ISR Flag, needed because otherwise ISR will trigger again once reenabled, INT5 is the address for pin 3 ISR
    attachInterrupt(digitalPinToInterrupt(TriggerOnPin), Trigger_ISR, FALLING); // Reattach interrupt so ISR works again
    if (SelectState == 2) {
      digitalWrite(GreenLEDpin, LOW);
      TriggerMode = 0;
    }
  }

  // Tell belts what to do based on operating mode and trigger state
  switch (OperatingMode) {
    case 1:
      if (TriggerMode == 0 && SelectState == 1) { // If trigger is not engaged and belt select switch is sset to LEFT
        digitalWrite(Right_Enable_Pin, HIGH);   // Enable Movement
        digitalWrite(Left_Enable_Pin, HIGH);
        //MotorSpeed = LeftSpeedPWM [0];
        analogWrite(Right_InputB_Pin, RightSpeedPWM [0]); // Write first value in PWM array to motor so motors travel at constant speed
        analogWrite(Left_InputB_Pin, LeftSpeedPWM [0]);
      }
      else if (TriggerMode == 1 && SelectState == 1) {  // If trigger is engaged go to Mode 1 to run perturbation profle
        Mode1();
      }
      break;
    case 2:
      if (TriggerMode == 0 && SelectState == 1) {
        digitalWrite(Right_Enable_Pin, HIGH);
        digitalWrite(Left_Enable_Pin, HIGH);
        //MotorSpeed = LeftSpeedPWM [0];
        analogWrite(Right_InputB_Pin, RightSpeedPWM [0]);
        analogWrite(Left_InputB_Pin, LeftSpeedPWM [0]);
      }
      else if (TriggerMode == 1 && SelectState == 1) {
        Mode2();
      }
      break;
    case 3:
      if (TriggerMode == 0 && SelectState == 1) {
        digitalWrite(Right_Enable_Pin, HIGH);
        digitalWrite(Left_Enable_Pin, HIGH);
        //MotorSpeed = LeftSpeedPWM [0];
        analogWrite(Right_InputB_Pin, RightSpeedPWM [0]);
        analogWrite(Left_InputB_Pin, LeftSpeedPWM [0]);
      }
      else if (TriggerMode == 1 && SelectState == 1) {
        Mode3();
      }
      break;
    case 4:
      if (TriggerMode == 0 && SelectState == 1) {
        digitalWrite(Right_Enable_Pin, HIGH);
        digitalWrite(Left_Enable_Pin, HIGH);
        //MotorSpeed = LeftSpeedPWM [0];
        analogWrite(Right_InputB_Pin, RightSpeedPWM [0]);
        analogWrite(Left_InputB_Pin, LeftSpeedPWM [0]);
      }
      else if (TriggerMode == 1 && SelectState == 1) {
        Mode4();
      }
      break;
    case 5:
      if (TriggerMode == 0) {
        digitalWrite(Right_Enable_Pin, HIGH);
        digitalWrite(Left_Enable_Pin, HIGH);
        //MotorSpeed = LeftSpeedPWM [0];
        analogWrite(Right_InputB_Pin, RightSpeedPWM [0]);
        analogWrite(Left_InputB_Pin, LeftSpeedPWM [0]);
      }
      else if (TriggerMode == 1 && SelectState == 1) {
        Mode5();
      }
      break;
  }

}

/*
// Old method used to controll motors, used for two way communication between matlab and arduino
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
*/

// Run perturbation profiles
void Mode1() {
  MotorController(NumSpaces1, TestSpeed1L, TestTiming1, TestSpeed1R, TestTiming1);  // Send data for mode 1 to motor controller function
}

void Mode2() {
  MotorController(NumSpaces2, TestSpeed2L, TestTiming2, TestSpeed2R, TestTiming2);
}

void Mode3() {
  MotorController(NumSpaces3, TestSpeed3L, TestTiming3, TestSpeed3R, TestTiming3);
}

void Mode4() {
  MotorController(NumSpaces4, TestSpeed4L, TestTiming4, TestSpeed4R, TestTiming4);
}

void Mode5() {
  MotorController(NumSpaces5, TestSpeed5L, TestTiming5, TestSpeed5R, TestTiming5);
}

/*
// Uncomment this if using two way communication
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
*/

// Motor controller function, tells motors what speeds to go and for how long
void MotorController (int NumSpaces, int LeftSpeedPWM[], int LeftTiming [], int RightSpeedPWM [], int RightTiming []) {

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

  else if (currentMillis - StartMillis >  LeftTiming[LeftStage] && currentMillis - StartMillis <= LeftTiming[LeftStage + 1] && LeftStage >= 1) {
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
  else if (LeftStage == NumSpaces - 1) {
    if (LeftTiming[NumSpaces] >= RightTiming[NumSpaces]) {
      Serial.println("Done");
      Serial.println(LeftTiming[NumSpaces - 2]);
      Serial.println(RightTiming[NumSpaces - 2]);
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
    Serial.print(RightSpeedPWM [RightStage]);
    //MotorDirection(LeftSpeedPWM[LeftStage], RightSpeedPWM[RightStage]);
    Serial.println();
    RightStage = 1;
  }

  else if (currentMillis - StartMillis >  RightTiming[RightStage] && currentMillis - StartMillis <= RightTiming[RightStage + 1] && RightStage >= 1) {
    analogWrite(Right_InputB_Pin, RightSpeedPWM [RightStage]);
    //LeftStage=2;
    Serial.print("Right Stage ");
    Serial.print(RightStage);
    Serial.print(" - ");
    Serial.print(RightSpeedPWM [RightStage]);
    Serial.print(", NumSpaces = ");
    Serial.println(NumSpaces);
    //MotorDirection(LeftSpeedPWM[LeftStage], RightSpeedPWM[RightStage]);
    Serial.println();
    RightStage++;
  }
  else if (RightStage == NumSpaces - 1) {
    if (RightTiming[NumSpaces] >= LeftTiming[NumSpaces]) {

      Serial.println(RightTiming[NumSpaces - 1]);
      Serial.println(LeftTiming[NumSpaces - 1]);
      TriggerMode = 0;
      digitalWrite(GreenLEDpin, LOW);
    }
    RightStage = 0;
    Serial.println("Right Done");
  }
}

// Motor direction function, writes motor direction to serial monitor, ussed for 2 way communication plots
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

// Perturbation Profile function
void PerturbationProfile (float WalkingSpeed, int BeltAccel, float dT) {
  // Function to calculate the belt speed profile from the given inputs and
  // convert that to a PWM value, this function assumes 40 data points per second.

  Serial.println("ProfileBegin");

  // Declare Local Varriables
  float r = 0.0762;             // Radius of the hub (m)
  float BeltThickness = 0.0028; // Thickness of the belt (m)
  int GearRto = 5;            // Gear reduction from the motor to the hub
  int TempBeltAccel;          // Store local versioin of BeltAccel so we can midufy it
  int TempAslow;              // Store local version of aSlow so we can modify it
  //int aSlow = -1;              // Rate to slow down the belt after hitting peak speed (m/s^2)

  if (OperatingMode == 5 || OperatingMode == 4 || OperatingMode == 3 || OperatingMode == 2 || OperatingMode == 1) {
    //for (int i = 0; i < 331; i++) {
    //LeftTiming[i] = TestTiming5[i];
    //RightTiming[i] = TestTiming5[i];
    //LeftSpeedPWM[i] = TestSpeed5[i];
    //RightSpeedPWM[i] = map(TestSpeed5[i], 1, 254, 254, 1);
    //Serial.print("Timing = ");
    //Serial.println(LeftTiming[i]);
    //Serial.println(LeftSpeedPWM[i]);
    //Serial.println(RightSpeedPWM[i]);

    //}
    goto TheEnd;
  }


  float rNet = r + BeltThickness;

  if (WalkingSpeed >= 0) {
    TempBeltAccel = BeltAccel * (-1);
    TempAslow = aSlow * (-1);
  }
  else if (WalkingSpeed < 0) {
    TempBeltAccel = BeltAccel;
    TempAslow = aSlow;
  }

  Serial.print("dT = ");
  Serial.println(dT);
  Serial.print("BeltAccel = ");
  Serial.println(TempBeltAccel);
  Serial.print("aSlow = ");
  Serial.println(TempAslow);

  // Calculate peak velocity
  //float vf = Vmax;
  float vf = WalkingSpeed + TempBeltAccel * dT;
  Serial.print("vf = ");
  Serial.println(vf);

  // Calculate time to return to Steady State Speed from peak velocity

  float dtSlow = abs((WalkingSpeed - vf) / TempAslow);
  Serial.print("dtSlow = ");
  Serial.println(dtSlow);


  // Calculate angular accel of motor from belt acceleration
  // This is the output tp put into Clearpath's Max Accel
  // Rounded up to nearest intiger
  // Output is in units of RPM/s
  int MotorAngAccel = ceil((TempBeltAccel / r) * (60 / (2 * 3.14)) * GearRto);
  Serial.print("MotorAngAccel = ");
  Serial.println(MotorAngAccel);

  // Save Time and Velocity points in array
  float t[3] = {0, dT * 1000, dT * 1000 + dtSlow * 1000};
  float v[3] = {WalkingSpeed, vf, WalkingSpeed};

  // Create array of timing values
  //Serial.println("numSpacesBegin");
  NumSpaces = (dT + dtSlow) * 40;
  Serial.print("NumSpaces = ");
  Serial.println(NumSpaces);


  //float MotorTiming[NumSpaces];
  float TimingDivision = ((dT + dtSlow) / (NumSpaces - 1)) * 1000;
  Serial.print("TimingDivision = ");
  Serial.println(TimingDivision);

  float TimingSum = 0;
  //float MotorVel[NumSpaces];
  float yIntercept = vf - ((float)TempAslow * dT);
  Serial.print("yIntercept = ");
  Serial.println(yIntercept);
  //float MotorRPM[NumSpaces];
  //byte MotorPWM[NumSpaces];


  for (int i = 0; i < NumSpaces; i++) {
    Serial.println(NumSpaces);
    MotorTiming[i] = round(TimingSum);
    LeftTiming[i] = MotorTiming[i];
    RightTiming[i] = MotorTiming[i];
    //Serial.print("LeftMotorTiming [");
    //Serial.print(i);
    //Serial.print("] =  ");
    //Serial.println(LeftTiming[i]);

    TimingSum = TimingSum + TimingDivision;
    if (MotorTiming[i] <= dT * 1000) {
      MotorVel[i] = TempBeltAccel * ((float)MotorTiming[i] / 1000) + WalkingSpeed;
      //Serial.print("Motor Vel [");
      //Serial.print(i);
      //Serial.print("] =  ");
      //Serial.println(MotorVel);
    }
    else if (MotorTiming[i] > dT * 1000) {
      MotorVel[i] = TempAslow * ((float)MotorTiming[i] / 1000) + yIntercept;
      //Serial.print("Motor Vel [");
      //Serial.print(i);
      //Serial.print("] =  ");
      //Serial.println(MotorVel);
    }

    //MotorRPM[i] = (MotorVel[i]/rNet)*(60/(2*3.1415))*GearRto;
    MotorRPM[i] = (MotorVel[i] / rNet) * (9.549297) * GearRto;
    //Serial.print("MotorRPM [");
    //Serial.print(i);
    //Serial.print("] =  ");
    //Serial.println(MotorRPM[i]);



    // add in a variable for min and max motor speeds because it depends on motor voltage
    float TempPWM;
    //(MotorRPM[i] - -MaxMotorRPM) * (254 - 1) / (2 * MaxMotorRPM) + 1;
    TempPWM = round((MotorRPM[i] + MaxMotorRPM) * 253 / (2 * MaxMotorRPM) + 1);
    //Serial.print("TempPWM = ");
    //Serial.println(TempPWM);

    if (TempPWM > 254) {
      MotorPWM[i] = 254;
    }
    else if (TempPWM < 1) {
      MotorPWM[i] = 1;
    }
    else {
      MotorPWM[i] = TempPWM;
    }

    //Serial.print("MotorPWM = ");
    //Serial.println(MotorPWM);

    //Serial.print("Select State = ");
    //Serial.println(SelectState);
    switch (SelectState) {
      case 1:
        //("Left");
        LeftSpeedPWM[i] = MotorPWM[i];
        //map(value, fromLow, fromHigh, toLow, toHigh)
        RightSpeedPWM[i] = map(MotorPWM[0], 1, 254, 254, 1);
        //RightSpeedPWM[i] = map(MotorPWM[0], 1, 254, 254, 1);
        break;
      case 2:
        //("Right");
        RightSpeedPWM[i] = map(MotorPWM[i], 1, 254, 254, 1);
        //RightSpeedPWM[i] = map(MotorPWM[i], 1, 254, 254, 1);
        LeftSpeedPWM[i] = MotorPWM[0];
        //LeftSpeedPWM[i] = MotorPWM[0];
        break;
      case 3:
        //("BOTH");
        LeftSpeedPWM[i] = MotorPWM[i];
        //Serial.print("First Left PWM [");
        //Serial.print(i);
        //Serial.print("] =  ");
        //Serial.println(LeftSpeedPWM[i]);
        RightSpeedPWM[i] = map(MotorPWM[i], 1, 254, 254, 1);
        break;
    }

    //LeftSpeedPWM[i] = MotorPWM[i];

    Serial.print("Left PWM [");
    Serial.print(i);
    Serial.print("] =  ");
    Serial.println(LeftSpeedPWM[i]);

    Serial.print("Right PWM [");
    Serial.print(i);
    Serial.print("] =  ");
    Serial.println(RightSpeedPWM[i]);
  }
TheEnd:
  Serial.println("PROFILE END");
  Serial.println("");

  //*MotorPWM = &LeftSpeedProfile4
  //*MotorTiming = &LeftMotorTiming4
}


/*
  // ISR to read pwm values sent from motor
  // UNCOMMENT IF USING MOTOR HLFB
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

// Trigger ISR, used so trigger always executes regrardless of what program is otherwise doing
void Trigger_ISR () {
  detachInterrupt(digitalPinToInterrupt(TriggerOnPin));
  TriggerISR = 1;
  //Serial.println("ISR");
  //Serial.println(digitalRead(TriggerOffPin));
  //Serial.println(digitalRead(TriggerOnPin));
  //TriggerDebounceStart = millis();
}