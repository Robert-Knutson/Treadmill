%% Custom Perturbation Profile Creator
% This function creates a custom perturbation profile 
% Based on the velocities and accelereations provided 
% Coypright Robert Knutson, 8/18/2022
clear;clc;clf

%% Directions For Use
% Enter the desired profile in the Profile Entry Section

% This function will create a graph and save the values created to a CSV
% file, open this file with Notepad, DO NOT USE EXCEL
% and paste values into the Arduino code and upload to the board.

% The CSV files are named Mode_1, Mode_2, Mode_3, ...

%% CSV File Data Structure
% When you open the CSV vile the the first row is the Left Belt Speed
% The second row is the Right Belt Speed
% The third row is the timing values

%% Profile Entry
% Enter the desired perturbation profiles here
% There are two ways you can define the acceleeration period
% They are by acceleration rate and duration or max speed and duration.
% This is denoted by entering zeros in the value you are not using 

% For example if you want to define the profile by max speed and durration, then put
% zeros in for the values of the fast acceleration, and the software will
% calculate the missing values

% The deceleration period can be defined by either decel time or decel
% rate, using the same zero nomencalture as above.

% vi = 0;   % The initial velocity, leave to zero if its controlled by the microcontroller
% aFast =  [5, 5, 8, 12, 12];           % Fast acceleration, units m/s^2
% Vmax =   [1.5, 1.5, 2.5, 3.6, 3.6];   % Max velocity of fast acceleration, units m/s
% dt =     [0.3, 0.3, 0.3, 0.3, 0.3];   % Duration of fast acceleration period, units seconds
% dtSlow = [dt(1), 4, 6, dt(4), 8];     % Duration of the slow acceleration period, units seconds
% aSlow =  [aFast(1)*-1, 0, 0, aFast(4)*-1, 0]; % Deceleration rate, units m/s^2

%% Test Data
% Used for debug whipe preserving actual profiles
vi = 0.0;
aFast =  [3, 9, 12, 12, 15];
Vmax =   [1.5, 2, 2.5, 2.7, 0];
dt =     [0.2, 0.3, 0.4, 0.2, 0.2];
dtSlow = [0, 0, 0, 0, 0];
aSlow =  [3, 3, 3, 3, 3];


%% Variables, you can change these!
DPS = 40;   % Data points per second for the output PWM signal, 
% more points = closer approximation to line but also requires more storage on arduino.

% Acceleration of belt, used for max motor angular acceleration, units are m/s^2
% This value should match or be less then the value entered into clearpath
BeltAccel = 6; % Acceleration of belt, used for max motor angular acceleration, units are m/s^2

% Denote what voltage the machine is running on, changes PWM values to suit
voltage = 220;  % 110 or 220

%% Constants, dont change these!!
rDrum=0.0762;       % Radius of the hub
BeltThickness = 0.0028; % Belt Thickness
GearRto = 5.6;    % Gear reduction from the motor to the hub

%% Calculations
r=rDrum+BeltThickness;  % Raduis of combined drum and belt, needed for RPM calculations

% Change min and max motor rpm based on voltage input
if voltage == 110
    in_min = -1000; % 1000 for 110
    in_max = 1000;
    out_min = 0;
    out_max = 255;
elseif voltage == 220
    in_min = -2210;
    in_max = 2210;
    out_min = 1;
    out_max = 254;
end

% Calculate missing speed and acceleration values using the zero
% nomencalture noted in Profile Entry
for i=1:5
    if aFast(i) == 0 & Vmax(i) ~= 0
        aFast(i) = (Vmax(i) - vi)/dt(i);
    end
    if aSlow(i) == 0 & dtSlow(i) ~= 0
        aSlow(i) = (vi - Vmax(i))/dtSlow(i);
    end
    % Write valvulatd values to command window for verificcation
    disp(sprintf("Mode " + i + ", aFast = " + aFast(i) + ", aSlow = " + aSlow(i)))
    Vmaxnew(i) = vi + aFast(i)*dt(i);
    if dtSlow(i) == 0 & aSlow(i) ~= 0
        dtSlow(i) = abs((Vmaxnew(i)-vi)/aSlow(i));
    end
    
end

% Consolidate data into time and velocity arrays, used to plot
for i=1:5
    t(i,:)=[0,dt(i),dt(i) + dtSlow(i)];
    v(i,:)=[vi,Vmaxnew(i),vi];
end

%% Plot Velocity Data
subplot(2,1,1)
for i=1:5
    hold on
    plot(t(i,:),v(i,:),'LineWidth',1)
    %LegendIndex{i} = sprintf(" Mode " + i + ", Accel = " + aFast(i) + "m/s^2, Decel = " + aSlow(i) + "m/s^2");
    LegendIndex{i} = sprintf(" Mode " + i + ", Accel = " + aFast(i) + "m/s^2");
end
%title("Custom Perturbation Profile, vi = " + vi + "m/s, Accel Time = 0.3s")
title("Custom Perturbation Profile, vi = " + vi )
xlabel('Time, s')
ylabel('Belt Velocity, m/s')
%xlim([0, 1])
%ylim([-1, 4])
L = legend(LegendIndex);
L.FontSize = 8;
ax = gca;
ax.XAxisLocation = 'origin';
hold off

RPM = (60/(2*pi*r))*v*GearRto;   % Calculate Motor RPM from belt Speed

% Calculate angular accel of motor from belt acceleration
% This is the output tp put into clearpath's Max Accel
% Output rounded up to next whole number
% Output is in units of RPM/s
MotorAngAccel = ceil((BeltAccel/r)*(60/(2*pi))*5);

%% Convert velocity values to PWM
% Interpolate points from graph at, in preperatio for converting velocity
% to PWM, points per seconds denoted by DPS in variables section
for i=1:5
    tInterp{i,:} = linspace(0,max(t(i,:)),round(max(t(i,:))*DPS));
    vInterp{i,:} = interp1(t(i,:),v(i,:),tInterp{i});
end

% UNCOMMENT IF YOU WANT TO SEE HOW CLOSELY INTERPOLATED DATA MATCHES
% DESIRED DATA
% subplot(2,2,2)
% hold on
% for i=1:5
%     plot(tInterp{i},vInterp{i})
% end
% title('Interpolated Values, vi = -0.6m/s, decel rate = 1m/s^2')
% xlabel('Time, s')
% ylabel('Belt Velocity, m/s')
% xlim([0, 3.5])
% ylim([-1.5, 3])
% legend("a=5,dt=0.3","a=5,dt=0.4","a=5,dt=0.5","a=6,dt=0.3","a=6,dt=0.4")
% ax = gca;
% ax.XAxisLocation = 'origin';
% hold off

%% Convert to Motor RPM
for i=1:5
    RPMInterp{i,:} = (vInterp{i}/r)*(60/(2*pi))*GearRto;    % Convert velocity to RPM
    PWML{i,:} = (RPMInterp{i} - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;    % Convert RPM to PWM
    PWMR{i,:} = ((PWML{i} -    1  ) * (  1     -   254  )) / (  254  -    1  ) +   254  ;   % Mirror Left PWM value so both belts go in same direction
    PWML{i,:} = round(PWML{i,:});   % Rounds values, the Arduino analog write function cant handle decimal places in the values.
    PWMR{i,:} = round(PWMR{i,:});
    
    % Eliminate out or range data, a byte can only be a number 1-255
    for j=1:length(PWML{i,:})
        if PWML{i}(j) > 254
           PWML{i}(j) = 254; 
        end
        if PWMR{i}(j) < 1
           PWMR{i}(j) = 1; 
        end
    end
    
end

% Plot PWM signal
subplot(2,1,2)
hold on
for i=1:5
    plot(tInterp{i},PWML{i},'LineWidth',1)
    LegendIndex{i} = sprintf(" Mode " + i + ", Accel = " + aFast(i) + "m/s^2 Decel = " + aSlow(i) + " m/s^2");
end
title("Calulated PWM Values, vi = " + vi + "m/s, Accel Time = 0.3 s")
xlabel('Time, s')
ylabel('PWM Value, 0 is max CW, 255 is max CCW')
%xlim([0, 1])
%ylim([0,255])
L=legend(LegendIndex);
L.FontSize = 8;
ax = gca;
ax.XAxisLocation = 'origin';
hold off

% Write Max velt speed to command window for verrification
for i=1:5
    disp(sprintf("Mode " + i + ", Max Belt Speed = " + Vmax(i) + "m/s"))
end

%% Optomize Data and Safe to File
% Convert intepolated time values to milliseconds
tInterp{5} = round(tInterp{5}*1000);
tInterp{4} = round(tInterp{4}*1000);
tInterp{3} = round(tInterp{3}*1000);
tInterp{2} = round(tInterp{2}*1000);
tInterp{1} = round(tInterp{1}*1000);

% Create single array for housing data
for i=1:5
    MotorDataCombined{i,1}(1,:) = PWML{i}(1,:);
    MotorDataCombined{i,1}(2,:) = PWMR{i}(1,:);
    MotorDataCombined{i,1}(3,:) = tInterp{i}(1,:);
end

% Data optimization
% Remove unnessicary data points, reduces Arduino storage utilization
% If data point is the same as the data point before it remove it
for i=1:5
    for j=2:length(MotorDataCombined{i,1})
        if MotorDataCombined{i,1}(1,j) ~= MotorDataCombined{i,1}(1,j-1) & MotorDataCombined{i,1}(2,j) ~= MotorDataCombined{i,1}(2,j-1)
            NewMotorDataCombined{i,1}(1,j) = MotorDataCombined{i,1}(1,j);
            NewMotorDataCombined{i,1}(2,j) = MotorDataCombined{i,1}(2,j);
            NewMotorDataCombined{i,1}(3,j) = MotorDataCombined{i,1}(3,j);
            j=j-1;
        end
    end
    NewNewMotorDataCombined{i,1}(1,:) = nonzeros(NewMotorDataCombined{i,1}(1,:));   % Gets rid of zeros
    NewNewMotorDataCombined{i,1}(2,:) = nonzeros(NewMotorDataCombined{i,1}(2,:));   % And writes to new 
    NewNewMotorDataCombined{i,1}(3,:) = nonzeros(NewMotorDataCombined{i,1}(3,:));   % Array
end

% UNCOMMENT IF YOU WANT TO VIEW OPTIMIZED PWM DATA
% clf;
% figure(2)
% for i=2:5
% subplot(5,1,i-1)
% hold on
% plot(NewNewMotorDataCombined{i,1}(3,:),NewNewMotorDataCombined{i,1}(1,:),'r','LineWidth',1)
% plot(MotorDataCombined{i,1}(3,:),MotorDataCombined{i,1}(1,:),'b','LineWidth',1)
% legend("New","Old")
% hold off
% end

% Save data as CSV, it will be in the same folder as the as
% The program is currently running in
writematrix(NewNewMotorDataCombined{1,1}, 'Mode_1.csv')
writematrix(NewNewMotorDataCombined{2,1}, 'Mode_2.csv')
writematrix(NewNewMotorDataCombined{3,1}, 'Mode_3.csv')
writematrix(NewNewMotorDataCombined{4,1}, 'Mode_4.csv')
writematrix(NewNewMotorDataCombined{5,1}, 'Mode_5.csv')

