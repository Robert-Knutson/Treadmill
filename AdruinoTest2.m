clear;
clc;
clf;

LivePlot = 0; %Specify 1 for live plotting, 0 for plot only after data collection
NumTrials = 10; %The tunber of trials before data collection is complete

data=zeros(7,1000,NumTrials+1);
%{
Data row 1 = Source Data 
Data row 2 = Time of Measurement
Data row 3 = Derivative of Source Data WRT Time
Data row 4 = Direction (1 for CW rotation, -1 for CCW rotation)
Data row 5 = Modified Data
Data row 6 = Derivative of Modified Data WRT Time
Data row 7 = Data Modification mode identifier, used in troubleshooting 
%}

% Serial object
%s=serial('COM4','Baudrate', 115200);
s=serialport('COM4',115200);

% Open Serial Port
%fopen(s);
pause(2)

% Plotting Data
% direction = 1 for CW rotation, -1 for CCW rotation
i=3;
t=0;
tMax = 20;
PrevousDirection = 0;
direction = 0;
CurrentCommand = "NA";
MaxAccel = 20000;
DataEnable = 0;
Trial = 1;
iMax = 0;
h=plot(NaN,NaN,'r');
f=figure(1);
%if (~exist('button','var'))
%    button = uicontrol('Style','togglebutton','String','Stop',...
%        'Position',[0 0 50 25], 'parent',f);
%end
%disp(h.Value)
%(t<=tMax)
while (Trial<=NumTrials)
    
    IncomingData = strtrim(readline(s));  % This trims the read string of leading and trailing unnessicary characters
    %data(1,i) = IncomingData;
    
    % extractAfter(data,"R") % Removes everything after R in the string
    % contains(data,"R") % Returns logical true if read string contains R
    
    if contains(IncomingData,"R") == 1
        IncomingData = extractAfter(IncomingData,"R"); % Removes everything after R in the string, this is case sensitive
        disp("this works")
    elseif contains(IncomingData,"L") == 1
        IncomingData = extractAfter(IncomingData,"L"); % Removes everything after R in the string, this is case sensitive
        disp("this also works")
    end
 
    if IncomingData == "CW"
        PrevousDirection = direction;
        direction = 1;
        %disp(direction)
        i=i-1;
    elseif IncomingData == "CCW"
        PrevousDirection = direction;
        direction = -1;
        %disp(direction)
        i=i-1;
    elseif IncomingData == "Position 1"
        OperatingMode = 1;
        disp("Operating Mode 1")
        i=i-1;
    elseif IncomingData == "Position 2"
        OperatingMode = 2;
        disp("Operating Mode 2")
        i=i-1;
    elseif IncomingData == "Position 3"
        OperatingMode = 3;
        disp("Operating Mode 3")
        i=i-1;
    elseif IncomingData == "Position 4"
        OperatingMode = 4;
        disp("Operating Mode 4")
        i=i-1;
    elseif IncomingData == "Position 5"
        OperatingMode = 5;
        disp("Operating Mode 5")
        i=i-1;
    elseif (IncomingData == "Trigger") & (CurrentCommand ~="Trigger")
        tic;
        CurrentCommand = "Trigger";
        DataEnable = 1;
        disp("Begining Data Collection")
        i=3;
    elseif IncomingData == "Done"
        DataEnable = 0;
        CurrentCommand = "Done";
        disp("Data Collection Complete")
        SampleSpeed(Trial) = i/t;
        Trial = Trial + 1;
        %t=tMax+1;
        iMax = max(i,iMax);
        i=i-1;
    elseif DataEnable == 1
        t=toc;
        data(1,i,Trial) = IncomingData;
        data(4,i,Trial) = direction;
        data(2,i,Trial) = t;
    
    end
       
    %data(1,i) = readline(s);
    
    %data(1,i) = str2double(fscanf(s))
    % (data(1,i) > data(1,i-1) + 200) |
    if  (data(1,i,Trial) > 1200) | (data(1,i,Trial) < -1200 )
        data(1,i,Trial) = 0;
    end
    if abs(data(1,i,Trial) - data(1,i-1,Trial)) > 1000
        data(1,i,Trial) = data(1,i-1,Trial);
    end
    
    % 3 point backward finite difference (derivative) using taylor series
    % expansion
    data(3,i,Trial) = (data(1,i-2,Trial)+((-4)*data(1,i-1,Trial))+(3*data(1,i,Trial)))/(data(2,i,Trial)-data(2,i-2,Trial));
    %data(3,i) = (data(1,i-1) - data(1,i))/(data(2,i-1) - data(2,i)); % Backward Derivative
    
    % Decreasing, should be below zero
    if (data(4,i,Trial) == -1) & (PrevousDirection ==1 | PrevousDirection == 0) & ((data(1,i-1,Trial)-data(1,i,Trial)) < 0) & (data(7,i-1,Trial) ~=5)
        data(5,i,Trial) = data(1,i,Trial)*-1;
        data(3,i,Trial) = (data(1,i-2,Trial)+((-4)*data(1,i-1,Trial))+(3*data(1,i,Trial)))/(data(2,i,Trial)-data(2,i-2,Trial));
        data(7,i,Trial) = 1;
    % Increasing, should be below zero
    elseif (data(4,i,Trial) == 1) & (PrevousDirection == -1)& ((data(1,i-1,Trial)-data(1,i,Trial)) > 0)
        data(5,i,Trial) = data(1,i,Trial)*-1;
        data(3,i,Trial) = (data(1,i-2,Trial)+((-4)*data(1,i-1,Trial))+(3*data(1,i,Trial)))/(data(2,i,Trial)-data(2,i-2,Trial));
        data(7,i,Trial) = 2;
   % Decreasing, should be above zero
    elseif (data(7,i-1,Trial) ~= 1) & (data(7,i-1,Trial) ~=4) & (data(4,i,Trial) == -1) & (PrevousDirection == 1)
        data(5,i,Trial) = data(1,i,Trial);
        data(7,i,Trial) = 3.5;
    % Should be above zero
    elseif (data(7,i-1,Trial) ~= 1) & (data(7,i-1,Trial) ~=4) & (data(4,i,Trial) == 1)
        data(5,i,Trial) = data(1,i,Trial);
        data(7,i,Trial) = 3;
    end
    
    % At Constant CCW value
    if ((data(3,i,Trial) > -500) & (data(3,i,Trial) < 500)) & (data(4,i,Trial) == -1) & (data(7,i-1,Trial) ~=5 & data(7,i-1,Trial) ~=3)
        data(5,i,Trial) = (-1)*abs(data(1,i,Trial));
        data(7,i,Trial) = 4;
    % At Constant CW Value
    elseif ((data(3,i,Trial) > -500) & (data(3,i,Trial) < 500)) & (data(4,i,Trial) == 1) & (data(7,i-1,Trial) ~=4)% At constant CW value
        data(5,i,Trial) = data(5,i,Trial);
        data(7,i,Trial) = 5;
    end
    
    data(6,i,Trial) = (data(5,i-2,Trial)+((-4)*data(5,i-1,Trial))+(3*data(5,i,Trial)))/(data(2,i,Trial)-data(2,i-2,Trial));
    if data(7,i,Trial) == 0
        data(5,i,Trial) = data(5,i-1,Trial);
    elseif abs(data(6,i,Trial)) > MaxAccel
        data(1,i,Trial) = data(1,i-1,Trial);
        data(3,i,Trial) = data(3,i-1,Trial);
        data(5,i,Trial) = data(5,i-1,Trial);
        data(6,i,Trial) = data(6,i-1,Trial);
        %data(6,i) = (data(5,i-2)+((-4)*data(5,i-1))+(3*data(5,i)))/(data(2,i)-data(2,i-2));
    end
     data(6,i,Trial) = (data(5,i-2,Trial)+((-4)*data(5,i-1,Trial))+(3*data(5,i,Trial)))/(data(2,i,Trial)-data(2,i-2,Trial));
    %if abs(data(6,i)
    %plot(data(2,:),data(1,:));
    %ylim([-10 10]);
    %xlim([0 10]);
    
    %data(1,i) = ax;
    %axes(handles.axes1);
    
    if LivePlot == 1
        set(h, 'XData', data(2,1:i,Trial),'YData',data(5,1:i,Trial));
        ylim([-1000 1000]);
        xlim([0 tMax]);
        drawnow
    end
    
    i=i+1;
end
data=data(:,1:iMax-1,:);
data=data(:,:,1:NumTrials);

subplot(2,1,1);
hold on
for i = 1:NumTrials
    plot(data(2,:,i),data(1,:,i),'r');
    plot(data(2,:,i),data(5,:,i),'b');
end
% plot(data(2,:,1),data(1,:,1),'r');
% plot(data(2,:,1),data(5,:,1),'b');
% plot(data(2,:,2),data(1,:,2),'r');
% plot(data(2,:,2),data(5,:,2),'b');
% plot(data(2,:,3),data(1,:,3),'r');
% plot(data(2,:,3),data(5,:,3),'b');
% plot(data(2,:,4),data(1,:,4),'r');
% plot(data(2,:,4),data(5,:,4),'b');
% plot(data(2,:,5),data(1,:,5),'r');
% plot(data(2,:,5),data(5,:,5),'b');
ylim([min(data(5,:)) max([data(5,:),data(1,:)])]);
legend("Original Data","Modified Data");
xlim([min(data(2,:)) max(data(2,:))]);
ylabel("RPM, CW+")
xlabel("Time (s)")
title("RPM vs. Time")
hold off

subplot(2,1,2);
hold on
for i = 1:NumTrials
    plot(data(2,:,i),data(3,:,i),'r');
    plot(data(2,:,i),data(6,:,i),'b');
end

% plot(data(2,:,2),data(3,:,2),'r');
% plot(data(2,:,2),data(6,:,2),'b');
% plot(data(2,:,3),data(3,:,3),'r');
% plot(data(2,:,3),data(6,:,3),'b');
% plot(data(2,:,4),data(3,:,4),'r');
% plot(data(2,:,4),data(6,:,4),'b');
% plot(data(2,:,5),data(3,:,5),'r');
% plot(data(2,:,5),data(6,:,5),'b');
xlim([min(data(2,:)) max(data(2,:))]);
ylabel("(d/dt)RPM")
xlabel("Time (s)")
title("Angular Acceleration vs. Time")
legend("Original Data","Modified Data")
hold off

SampleSpeed

%{
instrfind() %find if serial port is not closed
fclose(ans) % Close open serial port
%}

clear s;

%openPort=instrfind(); % find if serial port is not closed
%fclose(openPort) % Close open serial port
