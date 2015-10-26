
 %{ ****** Efect of varying b *************** %}
 forwardTimes = [ 0.11 0.23 0.40 0.58 0.79 0.99 1.18 1.45 1.71 1.94 2.23 2.51 2.78 3.03 3.34 3.58 3.81 4.09 4.35 4.62  ]; 
 backwardTimes = [ 0.80 0.94 1.09 1.24 1.35 1.61 1.75 1.88 2.00 2.10 2.20 2.30 2.43 2.48 2.63 2.74 2.85 2.95 3.02 3.18  ]; 
 totalTimes = [ 0.91 1.18 1.49 1.82 2.13 2.60 2.93 3.32 3.71 4.04 4.43 4.81 5.21 5.51 5.96 6.32 6.66 7.04 7.37 7.81  ]; 
 bValues = [5000 10000 15000 20000 25000 30000 35000 40000 45000 50000 55000 60000 65000 70000 75000 80000 85000 90000 95000 100000  ] ;


 figure (3); 
 plot(bValues, forwardTimes, 'b'); 
 hold on; 
 plot(bValues, backwardTimes, 'r'); 
 hold on; 
 plot(bValues, totalTimes , 'g'); 
 hold off; 
 legend('Tempo forward', 'Tempo Backward', 'Tempo Total'); 
 title('Effect of varying b') ;
 xlabel('Valores de  b') ;
 ylabel('Tempo execução'); 


 

 % Execucao  para k = 6250 , n = 3125