
 %{ ****** Efect of varying n *************** %}
 % Execucao  para k = 5900 , b = 59000
 forwardTimes = [ 1.54 1.61 1.95 2.11 2.48 2.83 2.80 3.29 3.38 3.60 4.21 4.49 4.99 5.33 5.54 5.96 6.00 6.55 6.41 6.99  ]; 
 backwardTimes = [ 1.74 2.01 3.06 3.23 4.19 4.59 4.39 5.20 5.21 5.35 6.48 6.78 7.61 8.12 8.21 8.72 8.65 9.49 9.28 9.80  ]; 
 totalTimes = [ 3.28 3.61 5.01 5.34 6.67 7.42 7.19 8.48 8.59 8.96 10.69 11.27 12.60 13.45 13.75 14.68 14.65 16.04 15.69 16.79  ]; 
 nValues = [295 590 885 1180 1475 1770 2065 2360 2655 2950 3245 3540 3835 4130 4425 4720 5015 5310 5605 5900  ] ;


 figure (2); 
 plot(nValues, forwardTimes, 'b'); 
 hold on; 
 plot(nValues, backwardTimes, 'r'); 
 hold on; 
 plot(nValues, totalTimes , 'g'); 
 hold off; 
 legend('Tempo forward', 'Tempo Backward', 'Tempo Total'); 
 title('Effect of varying n') ;
 xlabel('Valores de  n') ;
 ylabel('Tempo execução'); 


 