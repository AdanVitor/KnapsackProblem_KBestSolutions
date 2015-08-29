
 %{ ****** Efect of varying n *************** %}
 % Execucao  para k = 5900 , b = 59000
 forwardTimes = [ 0.48 0.95 1.36 1.77 2.15 2.50 2.87 3.24 3.62 3.92 4.27 4.65 5.01 5.27 5.67 6.01 6.37 6.58 6.94 7.22  ]; 
 backwardTimes = [ 1.16 1.88 2.26 2.89 3.21 4.08 4.41 4.84 5.23 5.10 5.47 7.05 6.92 7.22 7.76 8.64 8.15 8.48 10.20 10.09  ]; 
 totalTimes = [ 1.64 2.83 3.63 4.66 5.35 6.59 7.28 8.08 8.85 9.02 9.75 11.71 11.93 12.49 13.43 14.65 14.53 15.07 17.13 17.31  ]; 
 nValues = [295 590 885 1180 1475 1770 2065 2360 2655 2950 3245 3540 3835 4130 4425 4720 5015 5310 5605 5900  ] ;


 figure (2); 
 plot(nValues, forwardTimes, 'b'); 
 hold on; 
 plot(nValues, backwardTimes, 'r'); 
 hold on; 
 plot(nValues, totalTimes , 'g'); 
 hold off; 
 legend('Tempo construção da tabela de soluções', 'Tempo construção da lista das K melhores soluções', 'Tempo Total');
 title('Efeito de variar n para k = 5900, b = 59000') ;
 xlabel('Valores de  n') ;
 ylabel('Tempo execução(s)'); 


 