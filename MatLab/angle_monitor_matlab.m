%CodeStart--------------------------------------------------------
%Resetting MATLAB environment

UDPComIn=udp('192.168.43.204', 1377,'LocalPort', 1366);
fopen(UDPComIn);
set(UDPComIn,'Timeout',600);
plotGrid = 'on';                % 'off' to turn off grid
min = -20;                     % set y-min
max = 20;                      % set y-max
min1 = -100;                     % set y-min
max1 =  100;                      %r set y-max
min2 = -35;                     % set y-min
max2 = 35;                      % set y-max
scrollWidth = 13;               % display period in plot, plot entire data log if <= 0


time = 0;
data = 0;
count = 0;
accel_y = 0;
dt = 0;
roll(1) = 10;
roll_set(1) = 10;
roll(2) = 20;
roll_set(2) = 10;
pitch(1) = 10;
pitch_set(1) = 10;
pitch(2) = 20;
pitch_set(2) = 10;

y(:, 1) = roll;
y(:, 2) = roll_set;
x(:, 1) = time;
x(:, 2) = time;
y1(:, 1) = pitch;
y1(:, 2) = pitch_set;
x1(:, 1) = time;
x1(:, 2) = time;



figure;
h1 = subplot(2,2,1);
rollGraph = plot(x,y);
plotTitle = 'roll';  % plot title
xLabel = 'time (sec)';    % x-axis label
yLabel = 'angle / set point';                % y-axis label

title(plotTitle,'FontSize',12);
xlabel(xLabel,'FontSize',10);
ylabel(yLabel,'FontSize',10);
axis([0 10 min max]);
grid(plotGrid);

h2 = subplot(2,2,2);
pitchGraph = plot(x1,y1);
plotTitle = 'pitch';  % plot title
xLabel = 'time (sec)';    % x-axis label
yLabel = 'angle / set point';                % y-axis label

title(plotTitle,'FontSize',12);
xlabel(xLabel,'FontSize',10);
ylabel(yLabel,'FontSize',10);
axis([0 10 min max]);
grid(plotGrid);


h3 = subplot(2,2,3);
accGraph = plot(time,accel_y, 'r', 'LineWidth', 2);
plotTitle = 'accelerometer y';  % plot title
xLabel = 'time (sec)';    % x-axis label
yLabel = 'acceleration (g)';                % y-axis label

title(plotTitle,'FontSize',12);
xlabel(xLabel,'FontSize',10);
ylabel(yLabel,'FontSize',10);
axis([0 10 min2 max2]);
grid(plotGrid);



h4 = subplot(2,2,4);
dtGraph = plot(time, dt, 'r', 'LineWidth', 2);
plotTitle = 'data frequency';  % plot title
xLabel = 'time (sec)';    % x-axis label
yLabel = 'frequency (hz)';                % y-axis label

title(plotTitle,'FontSize',12);
xlabel(xLabel,'FontSize',10);
ylabel(yLabel,'FontSize',10);
axis([0 10 min1 max1]);
grid(plotGrid);

tic
  while ishandle(rollGraph)
    piData=fscanf(UDPComIn);
    scandata=textscan(piData,'%f %f %f %f %f %f','Delimiter',';');
    
    count = count + 1;    
    time(count) = toc;    %Extract Elapsed Time
    roll(count) = cell2mat(scandata(1));
    pitch(count) = cell2mat(scandata(2));
    roll_set(count) = cell2mat(scandata(3));
    pitch_set(count) = cell2mat(scandata(4));
    accel_y(count) = cell2mat(scandata(5));
    dt(count) = cell2mat(scandata(6));
    %display(roll);
    if(scrollWidth > 0)
        set(rollGraph,{'XData'},{(time(time > time(count)-scrollWidth)); ...
            (time(time > time(count)-scrollWidth))},  {'YData'}, {(roll(time > time(count)-scrollWidth)); ...
            (roll_set(time > time(count)-scrollWidth))}, {'Color'}, {'r'; 'b'}, {'LineWidth'}, {2;2}); 
        subplot(2,2,1);
       axis([time(count)-scrollWidth time(count) min max]);
        
        
        set(pitchGraph,{'XData'},{(time(time > time(count)-scrollWidth)); ...
            (time(time > time(count)-scrollWidth))},  {'YData'}, {(pitch(time > time(count)-scrollWidth)); ...
            (pitch_set(time > time(count)-scrollWidth))}, {'Color'}, {'r'; 'b'}, {'LineWidth'}, {2;2}); 
        subplot(2,2,2);
       axis([time(count)-scrollWidth time(count) min max]);
       
        set(accGraph,'XData',time(time > time(count)-scrollWidth), 'YData', accel_y(time > time(count)-scrollWidth)); 
        subplot(2,2,3);
        axis([time(count)-scrollWidth time(count) min2 max2]);
        
        set(dtGraph,'XData',time(time > time(count)-scrollWidth), 'YData', dt(time > time(count)-scrollWidth)); 
        subplot(2,2,4);
        axis([time(count)-scrollWidth time(count) min1 max1]);
       
       
    else
            
        set(rollGraph,{'XData'},{time; time},{'YData'},{roll; roll_set}); 
        
        subplot(2,2,1);
       axis([time(count)-scrollWidth time(count) min max]);
        
        set(pitchGraph,{'XData'},{time; time},{'YData'},{pitch; pitch_set});
         
        subplot(2,2,2);
       axis([time(count)-scrollWidth time(count) min max]);
       
        set(accGraph,'XData', time,'YData', accel_y);
         
        subplot(2,2,3);
       axis([time(count)-scrollWidth time(count) min2 max2]);
       
        set(dtGraph,'XData', time,'YData', dt);
         
        subplot(2,2,3);
       axis([time(count)-scrollWidth time(count) min1 max1]);
       
    end
        
   pause(0.01);
    end
%Closing UDP communication
  fclose(UDPComIn);
%Deleting UDP communication
  delete(UDPComIn)
  
%CodeEnd----------------------------------------------------------