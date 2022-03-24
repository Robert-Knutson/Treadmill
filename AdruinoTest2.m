clear;clc;clf;

%% Global Controlls
% LivePlot controlls when data is plotted
% LivePlot = 1 to plot data in real time (Needs fast computer!!!)
% LivePlot = 0 to plot only after each trial is complete
%            The data will still plotted at the end of each run
LivePlot = 0; 

% NumTrials is the number of trials before data collection is complete
% Once the data collection loop starts it will only stop when the
% adequite number of trials has happened.  The software will hang or time
% out if the number of trials specified is not reached.
NumTrials = 5; 

%% Preallocate arrays, used to speed up code execution
Ldata=zeros(7,1000,NumTrials+1);
Rdata=zeros(7,1000,NumTrials+1);
SampleSpeed = zeros(NumTrials,1);
%{
Data row 1 = Source Data 
Data row 2 = Time of Measurement
Data row 3 = Derivative of Source Data WRT Time
Data row 4 = Direction (1 for CW rotation, -1 for CCW rotation)
Data row 5 = Modified Data
Data row 6 = Derivative of Modified Data WRT Time
Data row 7 = Data Modification mode identifier, used in troubleshooting 
%}
%% Create serial port object, used to read from serial port
%s=serial('COM4','Baudrate', 115200);
s=serialport('COM4',250000);
pause(1);

%% Preallocate valiables used in loop
% direction = 1 for CW rotation, -1 for CCW rotation
i=3;    % Loop index counter for L Motor
j=3;    % Loop index counter for R Motor
t=0;    % Time of measurement
tMax = 20;  % Maximum loop time
RPrevousDirection = 0;  % Prevous Direction tracker for R motor
Rdirection = 0;         % Current Direction tracker for R motor
LPrevousDirection = 0;  % Prevous Direction tracker for L motor
Ldirection = 0;         % Current Direction tracker for L motor
CurrentCommand = "NA";
MaxAccel = 20000;   % Maximum acceleratoin of motors, used to sort out bad data
DataEnable = 0;     % Flag to identify when to srart collecting data
Trial = 1;          % Used so sucessive trails can be recorded
iMax = 0;           % Used to truncate data based on the trial with the most samples
h=plot(NaN,NaN,'r');% Preallocate plot object, used to spped up plotting speed
%f=figure(1);
%if (~exist('button','var'))
%    button = uicontrol('Style','togglebutton','String','Stop',...
%        'Position',[0 0 50 25], 'parent',f);
%end
%disp(h.Value)
%(t<=tMax)

%% Begin looping over sucessive data revieved over serial port
while (Trial<=NumTrials)
    %% Read incoming serial port data
    % strtrim() trims the read string of leading and trailing unnessicary characters
    IncomingData = strtrim(readline(s));  
    
    %% Read operating mode, trigger, and done commands, command not motor specific
    if IncomingData == "Position 1"
        OperatingMode = 1;
        disp("Operating Mode 1")
        %i=i-1;  % Dont count this toward data collection index
    elseif IncomingData == "Position 2"
        OperatingMode = 2;
        disp("Operating Mode 2")
        %i=i-1;
    elseif IncomingData == "Position 3"
        OperatingMode = 3;
        disp("Operating Mode 3")
        %i=i-1;
    elseif IncomingData == "Position 4"
        OperatingMode = 4;
        disp("Operating Mode 4")
        %i=i-1;
    elseif IncomingData == "Position 5"
        OperatingMode = 5;
        disp("Operating Mode 5")
        %i=i-1;
    elseif (IncomingData == "Trigger") & (CurrentCommand ~="Trigger")
        tic;    % Begin Timer
        CurrentCommand = "Trigger";
        DataEnable = 1;     % Allow Data Collection to begin
        disp("Begining Data Collection for Trial = " + num2str(Trial))
        i=3;
        j=3;
    elseif IncomingData == "Done"
        DataEnable = 0;     % Stop Data Collection
        CurrentCommand = "Done";
        disp("Data Collection Complete")
        SampleSpeed(Trial,1) = i/t;   % Calculate average data collection rate over all trials
        SampleSpeed(Trial,2) = j/t;   % Calculate average data collection rate over all trials
        if LivePlot == 0
            hold on
            plot(Ldata(2,:,Trial),Ldata(5,:,Trial));
            plot(Rdata(2,:,Trial),Rdata(5,:,Trial));
            hold off
        end
        Trial = Trial + 1;      % Iterate Trial index
        %t=tMax+1;
        iMax = max([i,j,iMax]);     % Store maximum number of data points
        %i=i-1;
        %j=j-1;
        
    %% Read Data specific to Right Motor
    elseif contains(IncomingData,"R") == 1  %contains(data,"R") Returns logical true if read string contains R
        IncomingData = extractAfter(IncomingData,"R"); % Removes everything after R in the string, this is case sensitive
        %disp("this works")
        if IncomingData == "CW"
            RPrevousDirection = Rdirection;
            Rdirection = 1;
            %disp(Rdirection)
            %i=i-1;
        elseif IncomingData == "CCW"
            RPrevousDirection = Rdirection;
            Rdirection = -1;
            %disp(Rdirection)
            %i=i-1;
        elseif DataEnable == 1  % Store data for R motor in Rdata
            t=toc;
            j=j+1;
            Rdata(1,j,Trial) = IncomingData;
            Rdata(4,j,Trial) = Rdirection;
            Rdata(2,j,Trial) = t;
            %i=i+1;
        end
        
    %% Read Data Specific to Left Motor
    elseif contains(IncomingData,"L") == 1
        IncomingData = extractAfter(IncomingData,"L"); % Removes everything after L in the string, this is case sensitive
        %disp("this also works")
        if IncomingData == "CW"
            LPrevousDirection = Ldirection;
            Ldirection = 1;
            %disp(Rdirection)
            %i=i-1;
        elseif IncomingData == "CCW"
            LPrevousDirection = Ldirection;
            Ldirection = -1;
            %disp(Ldirection)
            %i=i-1;
        elseif DataEnable == 1
            t=toc;
            i=i+1;
            Ldata(1,i,Trial) = IncomingData;
            Ldata(4,i,Trial) = Ldirection;
            Ldata(2,i,Trial) = t;
        end
    end
 
    %% Remove easily identifiable bad data from L and R data streans
    if  (Ldata(1,i,Trial) > 1200) | (Ldata(1,i,Trial) < -1200 ) % Read data should never be greater then 1000
        Ldata(1,i,Trial) = 0;
    elseif abs(Ldata(1,i,Trial) - Ldata(1,i-1,Trial)) > 1000
        Ldata(1,i,Trial) = Ldata(1,i-1,Trial);
    elseif (Rdata(1,j,Trial) > 1200) | (Rdata(1,j,Trial) < -1200 ) % Read data should never be greater then 1000
        Rdata(1,j,Trial) = 0;
    elseif abs(Rdata(1,j,Trial) - Rdata(1,j-1,Trial)) > 1000
        Rdata(1,j,Trial) = Rdata(1,j-1,Trial);
    end
    %% Calculate Derivative of motor speed WRT time
    % 3 point backward finite difference (derivative) using taylor series expansion
    Ldata(3,i,Trial) = (Ldata(1,i-2,Trial)+((-4)*Ldata(1,i-1,Trial))+(3*Ldata(1,i,Trial)))/(Ldata(2,i,Trial)-Ldata(2,i-2,Trial));
    Rdata(3,j,Trial) = (Rdata(1,j-2,Trial)+((-4)*Rdata(1,j-1,Trial))+(3*Rdata(1,j,Trial)))/(Rdata(2,j,Trial)-Rdata(2,j-2,Trial));
    %data(3,i) = (data(1,i-1) - data(1,i))/(data(2,i-1) - data(2,i)); % Backward Derivative
    
    %% Logic to filter data based on which direction it should be moving
    % Decreasing, should be below zero
    if (Ldata(4,i,Trial) == -1) & (LPrevousDirection ==1 | LPrevousDirection == 0) & ((Ldata(1,i-1,Trial)-Ldata(1,i,Trial)) < 0) & (Ldata(7,i-1,Trial) ~=5)
        Ldata(5,i,Trial) = Ldata(1,i,Trial)*-1;
        Ldata(3,i,Trial) = (Ldata(1,i-2,Trial)+((-4)*Ldata(1,i-1,Trial))+(3*Ldata(1,i,Trial)))/(Ldata(2,i,Trial)-Ldata(2,i-2,Trial));
        Ldata(7,i,Trial) = 1;
    % Increasing, should be below zero
    elseif (Ldata(4,i,Trial) == 1) & (LPrevousDirection == -1)& ((Ldata(1,i-1,Trial)-Ldata(1,i,Trial)) > 0)
        Ldata(5,i,Trial) = Ldata(1,i,Trial)*-1;
        Ldata(3,i,Trial) = (Ldata(1,i-2,Trial)+((-4)*Ldata(1,i-1,Trial))+(3*Ldata(1,i,Trial)))/(Ldata(2,i,Trial)-Ldata(2,i-2,Trial));
        Ldata(7,i,Trial) = 2;
   % Decreasing, should be above zero
    elseif (Ldata(7,i-1,Trial) ~= 1) & (Ldata(7,i-1,Trial) ~=4) & (Ldata(4,i,Trial) == -1) & (LPrevousDirection == 1)
        Ldata(5,i,Trial) = Ldata(1,i,Trial);
        Ldata(7,i,Trial) = 3.5;
    % Should be above zero
    elseif (Ldata(7,i-1,Trial) ~= 1) & (Ldata(7,i-1,Trial) ~=4) & (Ldata(4,i,Trial) == 1)
        Ldata(5,i,Trial) = Ldata(1,i,Trial);
        Ldata(7,i,Trial) = 3;
    % At Constant CCW value
    elseif ((Ldata(3,i,Trial) > -500) & (Ldata(3,i,Trial) < 500)) & (Ldata(4,i,Trial) == -1) & (Ldata(7,i-1,Trial) ~=5 & Ldata(7,i-1,Trial) ~=3)
        Ldata(5,i,Trial) = (-1)*abs(Ldata(1,i,Trial));
        Ldata(7,i,Trial) = 4;
    % At Constant CW Value
    elseif ((Ldata(3,i,Trial) > -500) & (Ldata(3,i,Trial) < 500)) & (Ldata(4,i,Trial) == 1) & (Ldata(7,i-1,Trial) ~=4)% At constant CW value
        Ldata(5,i,Trial) = Ldata(5,i,Trial);
        Ldata(7,i,Trial) = 5;
    end
    
    % Repeat for R motor
    % Decreasing, should be below zero
    if (Rdata(4,j,Trial) == -1) & (RPrevousDirection ==1 | RPrevousDirection == 0) & ((Rdata(1,j-1,Trial)-Rdata(1,j,Trial)) < 0) & (Rdata(7,j-1,Trial) ~=5)
        Rdata(5,j,Trial) = Rdata(1,j,Trial)*-1;
        Rdata(3,j,Trial) = (Rdata(1,j-2,Trial)+((-4)*Rdata(1,j-1,Trial))+(3*Rdata(1,j,Trial)))/(Rdata(2,j,Trial)-Rdata(2,j-2,Trial));
        Rdata(7,j,Trial) = 1;
    % Increasing, should be below zero
    elseif (Rdata(4,j,Trial) == 1) & (RPrevousDirection == -1)& ((Rdata(1,j-1,Trial)-Rdata(1,j,Trial)) > 0)
        Rdata(5,j,Trial) = Rdata(1,j,Trial)*-1;
        Rdata(3,j,Trial) = (Rdata(1,j-2,Trial)+((-4)*Rdata(1,j-1,Trial))+(3*Rdata(1,j,Trial)))/(Rdata(2,j,Trial)-Rdata(2,j-2,Trial));
        Rdata(7,j,Trial) = 2;
   % Decreasing, should be above zero
    elseif (Rdata(7,j-1,Trial) ~= 1) & (Rdata(7,j-1,Trial) ~=4) & (Rdata(4,j,Trial) == -1) & (RPrevousDirection == 1)
        Rdata(5,j,Trial) = Rdata(1,j,Trial);
        Rdata(7,j,Trial) = 3.5;
    % Should be above zero
    elseif (Rdata(7,j-1,Trial) ~= 1) & (Rdata(7,j-1,Trial) ~=4) & (Rdata(4,j,Trial) == 1)
        Rdata(5,j,Trial) = Rdata(1,j,Trial);
        Rdata(7,j,Trial) = 3;
    % At Constant CCW value
    elseif ((Rdata(3,j,Trial) > -500) & (Rdata(3,j,Trial) < 500)) & (Rdata(4,j,Trial) == -1) & (Rdata(7,j-1,Trial) ~=5 & Rdata(7,j-1,Trial) ~=3)
        Rdata(5,j,Trial) = (-1)*abs(Rdata(1,j,Trial));
        Rdata(7,j,Trial) = 4;
    % At Constant CW Value
    elseif ((Rdata(3,j,Trial) > -500) & (Rdata(3,j,Trial) < 500)) & (Rdata(4,j,Trial) == 1) & (Rdata(7,j-1,Trial) ~=4)
        Rdata(5,j,Trial) = Rdata(5,j,Trial);
        Rdata(7,j,Trial) = 5;
    end
    
    %% Calculate Derivative of Modified Data WRT Time and apply some filters
    Ldata(6,i,Trial) = (Ldata(5,i-2,Trial)+((-4)*Ldata(5,i-1,Trial))+(3*Ldata(5,i,Trial)))/(Ldata(2,i,Trial)-Ldata(2,i-2,Trial));
    if Ldata(7,i,Trial) == 0
        Ldata(5,i,Trial) = Ldata(5,i-1,Trial);
    elseif abs(Ldata(6,i,Trial)) > MaxAccel
        Ldata(1,i,Trial) = Ldata(1,i-1,Trial);
        Ldata(3,i,Trial) = Ldata(3,i-1,Trial);
        Ldata(5,i,Trial) = Ldata(5,i-1,Trial);
        Ldata(6,i,Trial) = Ldata(6,i-1,Trial);
        %data(6,i) = (data(5,i-2)+((-4)*data(5,i-1))+(3*data(5,i)))/(data(2,i)-data(2,i-2));
    end
    % Update Derivative in case it changed
    Ldata(6,i,Trial) = (Ldata(5,i-2,Trial)+((-4)*Ldata(5,i-1,Trial))+(3*Ldata(5,i,Trial)))/(Ldata(2,i,Trial)-Ldata(2,i-2,Trial));
    
    % Repeat for R motor
    Rdata(6,j,Trial) = (Rdata(5,j-2,Trial)+((-4)*Rdata(5,j-1,Trial))+(3*Rdata(5,j,Trial)))/(Rdata(2,j,Trial)-Rdata(2,j-2,Trial));
    if Rdata(7,j,Trial) == 0
        Rdata(5,j,Trial) = Rdata(5,j-1,Trial);
    elseif abs(Rdata(6,j,Trial)) > MaxAccel
        Rdata(1,j,Trial) = Rdata(1,j-1,Trial);
        Rdata(3,j,Trial) = Rdata(3,j-1,Trial);
        Rdata(5,j,Trial) = Rdata(5,j-1,Trial);
        Rdata(6,j,Trial) = Rdata(6,j-1,Trial);
        %data(6,j) = (data(5,j-2)+((-4)*data(5,j-1))+(3*data(5,j)))/(data(2,j)-data(2,j-2));
    end
    % Update Derivative in case it changed
    Rdata(6,j,Trial) = (Rdata(5,j-2,Trial)+((-4)*Rdata(5,j-1,Trial))+(3*Rdata(5,j,Trial)))/(Rdata(2,j,Trial)-Rdata(2,j-2,Trial));
    
    if LivePlot == 1
        set(h, 'XData', Ldata(2,1:i,Trial),'YData',Ldata(5,1:i,Trial));
        set(h, 'XData', Rdata(2,1:j,Trial),'YData',Rdata(5,1:j,Trial));
        ylim([-1000 1000]);
        xlim([0 tMax]);
        drawnow
    end
    
    %i=i+1;  % Increase loop index
end

%% Clean up data to prepare and plot
Ldata=Ldata(:,1:iMax-1,:);      % Remove all data points past the last largest loop index
Ldata=Ldata(:,:,1:NumTrials);   % Remove the final data plane, needed because the "Done" command always extends the plane by 1
Rdata=Rdata(:,1:iMax-1,:);
Rdata=Rdata(:,:,1:NumTrials);

% Plot Motor Speeds WRT Time
subplot(2,1,1);
hold on
for i = 1:NumTrials
    plot(Ldata(2,:,i),Ldata(1,:,i),'r');
    plot(Ldata(2,:,i),Ldata(5,:,i),'b');
    plot(Rdata(2,:,i),Rdata(1,:,i),'g');
    plot(Rdata(2,:,i),Rdata(5,:,i),'m');
end
ylim([min([Ldata(5,:),Rdata(5,:)]) max([Ldata(5,:),Ldata(1,:),Rdata(5,:),Rdata(1,:)])]);
legend("L Original Data","L Modified Data","R Original Data","R Modified Data");
xlim([min([Ldata(2,:),Rdata(2,:) ]) max([Ldata(2,:),Rdata(2,:)])]);
ylabel("RPM, CW+")
xlabel("Time (s)")
title("RPM vs. Time")
hold off

% Plot Motor Accelerations WRT Time
subplot(2,1,2);
hold on
for i = 1:NumTrials
    plot(Ldata(2,:,i),Ldata(3,:,i),'r');
    plot(Ldata(2,:,i),Ldata(6,:,i),'b');
    plot(Rdata(2,:,i),Rdata(3,:,i),'g');
    plot(Rdata(2,:,i),Rdata(6,:,i),'m');
end
xlim([min([Ldata(2,:),Rdata(2,:)]) max([Ldata(2,:),Rdata(2,:)])]);
ylabel("(d/dt)RPM")
xlabel("Time (s)")
title("Angular Acceleration vs. Time")
legend("L Original Data","L Modified Data","R Original Data","R Modified Data")
hold off

SampleSpeed   % Display final sample speed for all trials, used to make sure code is running fast enough


%% Closes the serial port so other things can use it
% IF THE PROGRAM FAILS TO COMPLETE, LIKE CRASHES OR ERRORS OUT, YOU HAVE TO COPY AND
% PASTE THIS INTO THE COMMAND WINDOW, OTHERWISE NOTHING ELSE CAN USE THE
% SERIAL PORT!!!!!!!!!!!!!!!!!
clear s;

