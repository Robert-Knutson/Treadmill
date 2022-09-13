%% Drag & Drop Perturbation Profile Creator
% This function creates a custom perturbation profile from a drag and drop graph
% And save the resulting motor speed and timing values to a csv file
% Copyright Robert Knutson 9/12/2022
clear;clc;clf   % Clear all workspace variables
global t v tInterp vInterp PWML DPS voltage  % Define global variables that can be shared between functions

%% Directions For Use
% Follow the prompts on the screen to declare the number of draggable points and total perturbation time
% This function will create a graph and save the values created to a CSV file
% open this file with Notepad, DO NOT USE EXCEL and paste values into the Arduino code and upload to the board.
% The CSV file is named Custom_Mode.csv

%% CSV File Data Structure
% When you open the CSV vile the the first row is the Left Belt Speed
% The second row is the Right Belt Speed
% The third row is the timing values

%% Variables, YOU CAN CHANGE THESE!
% DPS is data points per second for the output PWM signal
% more points = closer approximation to line but also requires more storage on arduino.
DPS = 200;   

% Denote what voltage the machine is running on, changes PWM values to suit
% Can be 110 or 220
voltage = 220; 

%% Calculations
% Everything beyond this point should not be modified, do so at your own risk
%% Create popup for inital data entry
NumPoints = inputdlg({'How many points on the graph would you like?'},...
              'Points Prompt'); 
NumPoints = str2num(NumPoints{1});
TotalTime = inputdlg({'How long should the total perturbation last?'},...
              'Total Time');
TotalTime = str2num(TotalTime{1});

%% Interactive Graph With Calculate Button
t=[zeros(1,NumPoints)];
v=[zeros(1,NumPoints)];

for i=2:NumPoints
    t(i) = t(i-1) + TotalTime/(NumPoints-1);
    v(i) = v(i-1) + 0.25;
    if i==NumPoints
        v(i) = 0;
    end
end

figure
plot(t,v,'-o','buttondownfcn',{@Mouse_Callback,'down'});
title('Custom Perturbation Profile')
xlabel('Time, s')
ylabel('Belt Velocity, m/s')
%xlim([0 5])
ylim([-3.3 3.3])
ax = gca;
ax.XAxisLocation = 'origin';
ax.YAxisLocation = 'origin';
c = uicontrol('Style','pushbutton','String','Calculate Profile',...
    'Position',[20 20 120 20], 'Callback',@calcButtonPushed);

% Callback function for each point
function Mouse_Callback(hObj,~,action)
global t v
persistent curobj xdata ydata ind 
pos = get(gca,'CurrentPoint');
switch action
  case 'down'
      curobj = hObj;
      xdata = get(hObj,'xdata');
      ydata = get(hObj,'ydata');
      [~,ind] = min(sum((xdata-pos(1)).^2+(ydata-pos(3)).^2,1));
      set(gcf,...
          'WindowButtonMotionFcn',  {@Mouse_Callback,'move'},...
          'WindowButtonUpFcn',      {@Mouse_Callback,'up'});
  case 'move'
      % vertical move
      ydata(ind) = pos(3);
      set(curobj,'ydata',ydata)
      
      % Horizontal Move
      xdata(ind) = pos(1);
      set(curobj,'xdata',xdata)
  case 'up'
      set(gcf,...
          'WindowButtonMotionFcn',  '',...
          'WindowButtonUpFcn',      '');
end

t=curobj.XData;
v=curobj.YData;
end

%% Calculate resulting PWM value based on values from interactive plot
function calcButtonPushed(~,~)
global t v tInterp vInterp PWML DPS voltage

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


%% Convert velocity values to PWM
% Interpolate points from graph at, in preperation for converting velocity
% to PWM, points per seconds denoted by DPS in variables section
tInterp = linspace(0,max(t),round(max(t)*DPS));
vInterp = interp1(t,v,tInterp);

% Plot Interpolated Values
figure(3)
subplot(3,1,1)
sgt = sgtitle('Motor Data Plots');  % Title for subplot group
sgt.FontSize = 20;
plot(tInterp,vInterp)
title('Interpolated Values')
xlabel('Time, s')
ylabel('Belt Velocity, m/s')
ax = gca;
% ax.XAxisLocation = 'origin';
% ax.YAxisLocation = 'origin';

%% Convert to Motor RPM
RPMInterp{1,:} = (vInterp/r)*(60/(2*pi))*GearRto;    % Convert velocity to RPM
PWML = (RPMInterp{1} - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;    % Convert RPM to PWM
PWMR = ((PWML -    1  ) * (  1     -   254  )) / (  254  -    1  ) +   254  ;   % Mirror Left PWM value so both belts go in same direction
PWML = round(PWML);   % Rounds values, the Arduino analog write function cant handle decimal places in the values.
PWMR = round(PWMR);

% Eliminate out or range data, a byte can only be a number 1-255
for j=1:length(PWML)
    if PWML(j) > 254
        PWML(j) = 254;
    end
    if PWMR(j) < 1
        PWMR(j) = 1;
    end
end

% Plot PWM signal
subplot(3,1,2)
hold on
plot(tInterp,PWML,'LineWidth',1)
title("Calulated PWM Values")
xlabel('Time, s')
ylabel(["PWM Value","0 is max CW, 255 is max CCW"])
ax = gca;
ax.XAxisLocation = 'origin';
ax.YAxisLocation = 'origin';
hold off

%% Optomize Data and Safe to File
% Convert intepolated time values to milliseconds
tInterp = round(tInterp*1000);

% Create single array for housing data
MotorDataCombined(1,:) = PWML(1,:);
MotorDataCombined(2,:) = PWMR(1,:);
MotorDataCombined(3,:) = tInterp(1,:);

% Data optimization
% Remove unnessicary data points, reduces Arduino storage utilization
% If data point is the same as the data point before it remove it
for j=2:length(MotorDataCombined)
    if MotorDataCombined(1,j) ~= MotorDataCombined(1,j-1) & MotorDataCombined(2,j) ~= MotorDataCombined(2,j-1)
        NewMotorDataCombined(1,j) = MotorDataCombined(1,j);
        NewMotorDataCombined(2,j) = MotorDataCombined(2,j);
        NewMotorDataCombined(3,j) = MotorDataCombined(3,j);
        j=j-1;
    end
end

NewNewMotorDataCombined(1,:) = nonzeros(NewMotorDataCombined(1,:));   % Gets rid of zeros
NewNewMotorDataCombined(2,:) = nonzeros(NewMotorDataCombined(2,:));   % And writes to new
NewNewMotorDataCombined(3,:) = nonzeros(NewMotorDataCombined(3,:));   % Array

%% Plot optimized data
subplot(3,1,3)
hold on
plot(NewNewMotorDataCombined(3,:),NewNewMotorDataCombined(1,:),'r','LineWidth',1)
%plot(MotorDataCombined(3,:),MotorDataCombined(1,:),'b','LineWidth',1)
%legend("New","Old")
title("Storage Optimized PWM Values")
xlabel('Time, s')
ylabel(["PWM Value","0 is max CW, 255 is max CCW"])
hold off

% Save data as CSV, it will be in the same folder as the as
% The program is currently running in
writematrix(NewNewMotorDataCombined(:,:), 'Custom_Mode.csv')
end
