clear;clc

s=serialport('COM4',250000,"Timeout",30);
%s=serialport('COM4',9600);
pause(1);

IncomingData="NA";
Tdiff = zeros(20,1);
i=1;
tic
t=0;
while IncomingData ~= "ERROR"
    t=toc;
    %disp(t)
    IncomingData = strtrim(readline(s));
    disp(IncomingData)
    if (IncomingData == "Trigger") 
        %tic;    % Begin Timer
    elseif (IncomingData == "Done")
        %t=toc;  % Store final time
        %disp(t)
        %AdruinoTime = str2double(strtrim(readline(s)));
        %Tdiff(i) = t-AdruinoTime;
        %disp(Tdiff(i));
        i=i+1;
    end
end


clear s;