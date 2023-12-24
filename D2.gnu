set terminal pngcairo enhanced font 'Arial,12'
set output 'DT1.png'

set datafile separator ","  # Indique que la virgule est utilisée comme séparateur

set terminal pngcairo enhanced size 800,800
set style data histogram
set style histogram rowstacked
set style fill solid
set boxwidth 0.75
set xlabel "Noms"  # Étiquette de l'axe des abscisses
set y2label "Nombre de Trajets"  # Étiquette de l'axe des ordonnées
set size 1, 1
set xtics rotate
set y2tics rotate

unset ytics ; set y2tics mirror
set title "Traitement D1" offset 0,1  # Ajoute un titre et ajuste sa position
plot 'D.txt' using 2:xtic(1) axes x1y2 notitle
