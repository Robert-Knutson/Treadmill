clear;clc;clf

rDrum=0.0762;       % Radius of the hub
BeltThickness = 0.0028;
GearRto = 5.6;    % Gear reduction from the motor to the hub
r=rDrum+BeltThickness;

BeltAccel = 6; % Acceleration of belt, units are m/s^2

% vi = 0;
% aFast =  [    5,    5,    8,     12,   12];
% Vmax =   [  1.5,  1.5,  2.5,    3.6,  3.6];
% dt =     [  0.3,  0.3,  0.3,    0.3,  0.3];
% dtSlow = [dt(1),    4,    6,  dt(4),    8];
% aSlow = [aFast(1)*-1, 0, 0, aFast(4)*-1, 0];

vi = 0;
aFast =  [    0,    0,    0,     0,   0];
Vmax =   [  1.5,  2,  2.5,    3,  3.6];
dt =     [  0.3,  0.3,  0.3,    0.3,  0.3];
dtSlow = [4,    5,    6,  5,    4];
aSlow = [0, 0, 0, 0, 0];

voltage = 220;  % 110 or 220
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

for i=1:5
    if aFast(i) == 0 & Vmax(i) ~= 0
        aFast(i) = (Vmax(i) - vi)/dt(i);
    end
    if aSlow(i) == 0 & dtSlow(i) ~= 0
        aSlow(i) = (vi - Vmax(i))/dtSlow(i);
    end
    disp(sprintf("Mode " + i + ", aFast = " + aFast(i) + ", aSlow = " + aSlow(i)))
     Vmaxnew(i) = vi + aFast(i)*dt(i);
%     dtSlow(i)=abs((Vmax(i)-vi)/aSlow(i));
end
% for i=1:2
%     vf(i,:) = vi + aFast(i).*dt(:);
%     for j=1:3
%         dtSlow(i,j)=(vf(i,j)-vi)/aSlow;
%         
%     end
%     
% end

% for i=1:2
%     dt(i,:) = [0.3, 0.4, 0.5];
% end

% k=1;
% for i=1:2
%     for j=1:3
%         t(k,:)=[0,dt(i,j),dt(i,j) + dtSlow(i,j)]; 
%         v(k,:)=[vi,vf(i,j),vi];
%         k=k+1;
%     end
%    
% end

for i=1:5
    t(i,:)=[0,dt(i),dt(i) + dtSlow(i)];
    v(i,:)=[vi,Vmax(i),vi];
end

subplot(2,1,1)
for i=1:5
    hold on
    plot(t(i,:),v(i,:),'LineWidth',1)
    LegendIndex{i} = sprintf(" Mode " + i + ", Accel = " + aFast(i) + "m/s^2, Decel = " + aSlow(i) + "m/s^2");
end
title("Custom Perturbation Profile, vi = " + vi + "m/s, Accel Time = 0.3s")
xlabel('Time, s')
ylabel('Belt Velocity, m/s')
%xlim([0, 1])
ylim([0, 4])
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

for i=1:5
    tInterp{i,:} = linspace(0,max(t(i,:)),round(max(t(i,:))*40));
    vInterp{i,:} = interp1(t(i,:),v(i,:),tInterp{i});
end

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
    RPMInterp{i,:} = (vInterp{i}/r)*(60/(2*pi))*GearRto;
    PWML{i,:} = (RPMInterp{i} - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    % map(MotorPWM[i], 1, 254, 254, 1);
    %           ((PWML{i} - in_min) * (out_max - out_min)) / ((in_max - in_min) + out_min);
    PWMR{i,:} = ((PWML{i} -    1  ) * (  1     -   254  )) / (  254  -    1  ) +   254  ;
    PWML{i,:} = round(PWML{i,:});
    PWMR{i,:} = round(PWMR{i,:});
    
    for j=1:length(PWML{i,:})
        if PWML{i}(j) > 254
           PWML{i}(j) = 254; 
        end
        if PWMR{i}(j) < 1
           PWMR{i}(j) = 1; 
        end
    end
    
end

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
legend(LegendIndex)
ax = gca;
ax.XAxisLocation = 'origin';
hold off
for i=1:5
    disp(sprintf("Mode " + i + ", Max Belt Speed = " + Vmax(i) + "m/s"))
end


tInterp{5} = round(tInterp{5}*1000);
tInterp{4} = round(tInterp{4}*1000);
tInterp{3} = round(tInterp{3}*1000);
tInterp{2} = round(tInterp{2}*1000);
tInterp{1} = round(tInterp{1}*1000);

for i=1:5
    MotorDataCombined{i,1}(1,:) = PWML{i}(1,:);
    MotorDataCombined{i,1}(2,:) = PWMR{i}(1,:);
    MotorDataCombined{i,1}(3,:) = tInterp{i}(1,:);
end


for i=1:5
    for j=2:length(MotorDataCombined{i,1})
        if MotorDataCombined{i,1}(1,j) ~= MotorDataCombined{i,1}(1,j-1) & MotorDataCombined{i,1}(2,j) ~= MotorDataCombined{i,1}(2,j-1)
            NewMotorDataCombined{i,1}(1,j) = MotorDataCombined{i,1}(1,j);
            NewMotorDataCombined{i,1}(2,j) = MotorDataCombined{i,1}(2,j);
            NewMotorDataCombined{i,1}(3,j) = MotorDataCombined{i,1}(3,j);
            j=j-1;
        end
    end
    NewNewMotorDataCombined{i,1}(1,:) = nonzeros(NewMotorDataCombined{i,1}(1,:));
    NewNewMotorDataCombined{i,1}(2,:) = nonzeros(NewMotorDataCombined{i,1}(2,:));
    NewNewMotorDataCombined{i,1}(3,:) = nonzeros(NewMotorDataCombined{i,1}(3,:));
end

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
% 
% 
% 
writematrix(NewNewMotorDataCombined{1,1}, 'MotorData1.csv')
writematrix(NewNewMotorDataCombined{2,1}, 'MotorData2.csv')
writematrix(NewNewMotorDataCombined{3,1}, 'MotorData3.csv')
writematrix(NewNewMotorDataCombined{4,1}, 'MotorData4.csv')
writematrix(NewNewMotorDataCombined{5,1}, 'MotorData5.csv')


% for i = 1:length(tInterp(5,:))
%     tInterp{5} = tInterp(5,i)*1000;
% end
