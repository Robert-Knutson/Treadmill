%%  Function to monitor serial port for Arduino communication
% When a perturbation is triggered on the treadmill speed values are
% incremented based on the Arduino’s internal timer.  This program was
% created to verify the exactness of the Arduino's internal timer.
% *******************IMPORTANT*************************
% If the program crashes or errors out, you have to paste clear s; 
% into the command window, otherwise you will be unable to 
% connect to the board again
 
% Robert Knutson 
% 5 August 2022
 
clear;clc
 
%% Create Serial Object
s=serialport('COM4',250000,"Timeout",30);
% The first input is the com port the Arduino is plugged into on your computer, this needs
% to match the actual port name.  For a list of the ports currently
% connected use serialportlist in the command window.
 
% The second input is the baud rate.  This needs to match whatever
% is entered into the Arduinos Serial.begin command.  I've found the practical
% maximum is 250000 on my setup.
 
% The third input is miscellaneous modifiers, I set a timeout of 30 seconds
% to close the port if no data is received for 30 seconds.
 
pause(1);   % Wait for 1 second, I found that garbage is transmitted when the port is initially connected
 
%% Initialize variables
IncomingData="NA";  
Tdiff = zeros(20,1);    
i=1;
%tic     % Begin timer
t=0;
 
%% Read Data
while IncomingData ~= "ERROR"       % If error is reported on Arduino, exit loop
    t=toc;  % Store timer value in temp variable
    %disp(t)
    IncomingData = strtrim(readline(s));    % read data from the serial port, get rid of carriage returns and unnessicary characters
    disp(IncomingData)  % Print incoming data to the command window
    if (IncomingData == "Trigger")  % Begin timer when "Trigger" is sent over the serial port
        tic;    % Begin Timer
    elseif (IncomingData == "Done")
        t=toc;  % Store final time
        disp(t) % Print final time to command window
        AdruinoTime = str2double(strtrim(readline(s))); % Read the last line of data to get Arduino reported final time & convert to number
        Tdiff(i) = t-AdruinoTime;   % Calculate the difference between Arduino time and Matlab time, should be similar
        disp(Tdiff(i)); % Display difference in command window
        i=i+1;  % increment index
    end
end
 
 
clear s; % Close serial port if program completes sucessfully
