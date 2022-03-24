clear;clc;clf;

%s=serialport('COM4',250000);
s=serialport('COM4',9600);
pause(1);

IncomingData="NA";
i=1;
ReadBeltSpeed=0;
WriteBeltSpeed=0;
NewBeltSpeed="50 50 50 50";
ReadNewBeltSpeed=0;
%NewBeltSpeed=[50,50,50,50];

while IncomingData ~= "Position 5"
    
    IncomingData = strtrim(readline(s));
    disp(IncomingData)
    if IncomingData == "Position 5"
        ReadBeltSpeed=1;
    end
end

while ReadBeltSpeed==1
    IncomingData = strtrim(readline(s));
    CurrentBeltSpeed(i)=IncomingData;
    if IncomingData == "Done"
       CurrentBeltSpeed(i) = []; 
       ReadBeltSpeed=0;
       WriteBeltSpeed=1;
    end
    i=i+1;
end

while WriteBeltSpeed==1
    disp("Sending " + NewBeltSpeed)
    for i=1:4
        writeline(s,NewBeltSpeed);
        if i==4
            WriteBeltSpeed=0;
            ReadNewBeltSpeed=1;
        end
    end 
end

while ReadNewBeltSpeed==1
    for i=1:4
        IncomingData = strtrim(readline(s));
        EchoBeltSpeed(i)=IncomingData;
        if i==4
            ReadNewBeltSpeed=0;
        end
    end
end

clear s;
