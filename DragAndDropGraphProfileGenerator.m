% Plot a line and points
clear;clc;clf
NumPoints = inputdlg({'How many points on the graph would you like?'},...
              'Points Prompt'); 
NumPoints = str2num(NumPoints{1});
global x1 y1 %x2 y2
x1=[zeros(1,NumPoints)];
y1=[zeros(1,NumPoints)];
% x2=[zeros(1,NumPoints)];
% y2=[zeros(1,NumPoints)];
for i=2:NumPoints
    x1(i) = x1(i-1)+0.25;
    y1(i) = y1(i-1)+0.25;
    if i==NumPoints
        y1(i) = 0;
    end
%     x2(i) = x1(i-1)+0.5;
%     y2(i) = y1(i-1)+1;
end

figure
plot(x1,y1,'-o','buttondownfcn',{@Mouse_Callback,'down'});
title('Custom Perturbation Profile')
xlabel('Time, s')
ylabel('Belt Velocity, m/s')
%xlim([0 5])
ylim([-4 4])
ax = gca;
ax.XAxisLocation = 'origin';
ax.YAxisLocation = 'origin';
% hold on
% plot(x2,y2,'-o','buttondownfcn',{@Mouse_Callback,'down'});
fig = uifigure;
        selection = uiconfirm(fig,"Well your no fun.",":(");
%button = uibutton(

% Callback function for each point
function Mouse_Callback(hObj,~,action)
global x1 y1
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

x1=curobj.YData;
y1=curobj.XData;
end
