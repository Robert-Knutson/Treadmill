% Plot a line and points
clear;clc;clf
global x1 y1
x1=[0,1,2,3,4,5];
y1=[0,1,2,3,4,5];
figure
plot(x1,y1,'-o','buttondownfcn',{@Mouse_Callback,'down'});
title('Custom Perturbation Profile')
xlabel('Time, s')
ylabel('Belt Velocity, m/s')
xlim([0 5])
ylim([-10 10])
ax = gca;
ax.XAxisLocation = 'origin';
ax.YAxisLocation = 'origin';

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
