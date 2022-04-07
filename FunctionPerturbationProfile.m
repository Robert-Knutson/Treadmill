function [PWM,tInterp, MotorAngAccel] = FunctionPerturbationProfile(vi,BeltAccel,dT,MaxMotorRpm)
%{ 
FunctionPerturbationProfile 

SUMMARY:
Function to calculate the belt speed profile from the given inputs and
convert that to a PWM value, this function assumes 40 data points per
second.

INPUTS: format is variable name = datatype, explination
vi = (Intiger), the belt steady state speed, dictated by the potentiameter
BeltAccel = (Intiger), the desired acceleration rate, dictated by the mode switch
dT = (Intiger), the amount of time the belt should be accelerating
MaxMotorRpm = (Intiger), The max motor speed as set by the Clearpath software
              This should be 1000 for 110v and 1500 for 220v
              THIS MUST MATCH WHAT IS INPUT INTO CLEARPATH!!!!!

OUTPUTS:
PWM = [Array], The PWM signal to send to the motor, dictates the speed of the motor
tInterp = [Array], Time values corresponding to PWM values
MotorAngAccel = (Intiger), Maximum Angular Acceleration required, this should always
                be less then the value input into Clearpath
%}

% Values for testing, these should be commented out when running
clear;clc;
vi = -1.2;
BeltAccel = 5;
dT = 0.5;

% Maximum Motor Speed 
% this is dependent on the motor voltage and must 
% match whats entered into the clearpath software, the PWM signal that 
% we output is proportional to the max speed
% Should be 1000 for 110v and 1500 for 220v
MaxMotorRpm = 1000; 

% End of values for testing


% Constants
r = 0.0762;     % Radius of the hub (m)
BeltThickness = 0.0028; % Thickness of the belt (m)
GearRto = 5;    % Gear reduction from the motor to the hub
aSlow = 1;      % Rate to slow down the belt after hitting peak speed (m/s^2)
r=r+BeltThickness;

% Calculate peak velocity
vf= vi + BeltAccel*dT;

% Calculate time to return to Steady State Speed from peak velocity
dtSlow=(vf-vi)/aSlow;

% Calculate angular accel of motor from belt acceleration
% This is the output tp put into clearpath's Max Accel
% Output rounded up to next whole number
% Output is in units of RPM/s
MotorAngAccel = ceil((BeltAccel/r)*(60/(2*pi))*5);

% Save Time and Velocity points in array
t=[0,dT,dT + dtSlow];
v=[vi,vf,vi];

% Create linearly spaced array of time values from 0 to largest t value
tInterp= linspace(0,max(t),round(max(t)*40));   % 40 samples per second

% Linear Interpolate function t(v) at points defined by tInterp
vInterp= interp1(t,v,tInterp);  

% Calculate Motor RPM from belt Speed
RPMInterp = (vInterp/r)*(60/(2*pi))*GearRto;

% Convert RPM values to PWM values
% THE IN_MIN AND MAX VALUES MUST MATCH WHATS INPUT INTO THE CLEARPATH
% SOFTWARE!!!!!!!!!!!!!!!
%MaxMotorRpm = 1000;     % Max Speed in CW direction
MinMotorRpm = -1*MaxMotorRpm;   % MinSpeed should be the negative of max speed it speed limits are symmetric
% A PWM signal of 0 corresponds to MinMotorRpm (Maximum speed in CCW direction)
% A PWM signal of 255 corresponds to MaxMotorRpm (Maximum speed in CW direction)
PWM = (RPMInterp - MinMotorRpm) * 255 / (MaxMotorRpm - MinMotorRpm);

% Round PWM values to nearest whole number, needed because the Arduino int
% data type can only store whole numbers.
PWM = round(PWM);

% If the caucluated velocity is greater then what the motors can do then
% replace that value with the max velocity
for j=1:length(PWM)
    if PWM(j) > 255
        PWM(j) = 255;
    elseif PWM(j) < 0
        PWM(j) = 0;
    end
end

tInterp = round(tInterp*1000);

plot(tInterp,PWM,'LineWidth',1)
    
end




