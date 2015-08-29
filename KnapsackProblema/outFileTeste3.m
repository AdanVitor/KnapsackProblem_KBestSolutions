
 %{ ****** Efect of varying b *************** %}
 forwardTimes = [ 0.06 0.18 0.36 0.61 0.89 1.22 1.63 2.07 2.49 2.91 3.37 3.79 4.22 4.64 5.07 5.46 5.93 6.35 6.77 7.20  ]; 
 backwardTimes = [ 0.75 1.00 1.25 1.51 1.70 1.91 2.12 2.34 2.56 2.77 3.01 3.28 3.52 3.82 4.07 4.31 4.64 5.00 5.37 5.74  ]; 
 totalTimes = [ 0.81 1.18 1.61 2.12 2.59 3.13 3.74 4.41 5.05 5.68 6.38 7.07 7.75 8.46 9.14 9.77 10.57 11.35 12.15 12.94  ]; 
 bValues = [5000 10000 15000 20000 25000 30000 35000 40000 45000 50000 55000 60000 65000 70000 75000 80000 85000 90000 95000 100000  ] ;


 figure (3); 
 plot(bValues, forwardTimes, 'b'); 
 hold on; 
 plot(bValues, backwardTimes, 'r'); 
 hold on; 
 plot(bValues, totalTimes , 'g'); 
 hold off; 
  legend('Tempo construção da tabela de soluções', 'Tempo construção da lista das K melhores soluções', 'Tempo Total');
 title('Efeito de variar b para k = 6250, n = 3125') ;
 xlabel('Valores de  b') ;
 ylabel('Tempo execução'); 


 

 % Execucao  para k = 6250 , n = 3125