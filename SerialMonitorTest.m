clear;clc;clf;

s=serialport('COM4',250000,"Timeout",60);
%s=serialport('COM4',9600);
pause(1);

IncomingData="NA";

while IncomingData ~= "Done"
    IncomingData = strtrim(readline(s));
    disp(IncomingData)
end

clear s;