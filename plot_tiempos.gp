set terminal pngcairo size 800,500
set output "grafico_tiempos.png"
set title "Comparativa Algoritmos de Ordenamiento O(n^2)"
set xlabel "Tamaño del Arreglo (N)"
set ylabel "Tiempo Promedio (segundos)"
set datafile separator ","
set key left top

plot "tiempos_ordenamiento.csv" every ::1 using 1:2 with linespoints linewidth 2 title "Bubble Sort", \
     "tiempos_ordenamiento.csv" every ::1 using 1:3 with linespoints linewidth 2 title "Insertion Sort", \
     "tiempos_ordenamiento.csv" every ::1 using 1:4 with linespoints linewidth 2 title "Selection Sort", \
     "tiempos_ordenamiento.csv" every ::1 using 1:5 with linespoints linewidth 2 title "Cocktail Shaker"
