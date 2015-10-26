
 %{ ****** Efect of varying K *************** %}
 % Execucao  para n = 3450 , b = 69000
 forwardTimes = [ 4.56 4.53 4.53 4.55 4.54 4.52 4.52 4.49 4.50 4.48 4.48 4.61 4.52 4.46 4.45 4.44 4.45 4.45 4.57 4.48  ]; 
 backwardTimes = [ 2.18 3.03 3.92 4.92 5.91 6.91 7.91 8.75 9.66 10.69 11.83 14.07 14.48 15.16 16.29 17.46 18.69 20.03 21.67 22.36  ]; 
 totalTimes = [ 6.74 7.56 8.45 9.47 10.45 11.42 12.43 13.25 14.17 15.17 16.31 18.68 19.00 19.62 20.73 21.90 23.14 24.48 26.24 26.85  ]; 
 kValues = [1150 2300 3450 4600 5750 6900 8050 9200 10350 11500 12650 13800 14950 16100 17250 18400 19550 20700 21850 23000  ] ;


 figure (1); 
 plot(kValues, forwardTimes, 'b'); 
 hold on; 
 plot(kValues, backwardTimes, 'r'); 
 hold on; 
 plot(kValues, totalTimes , 'g'); 
 hold off; 
 legend('Tempo forward', 'Tempo Backward', 'Tempo Total'); 
 title('Effect of varying k') ;
 xlabel('Valores de  k') ;
 ylabel('Tempo execução'); 


 