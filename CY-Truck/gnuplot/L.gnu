set terminal pngcairo enhanced font 'Arial,10'
set output 'L.png'

rose1 = "#FFB8CE"; # Initialisation d'une couleur

set title "Traitement -l" # Changement du titre
set size 1,1 # Ajuste la largeur de l'histogramme
set style data histograms 
set style fill solid

# Initialisation des titres des axes
set xlabel "ID" 
set ylabel "Distance (km)"

set title "Traitement L" offset 0,1  # Ajoute un titre et ajuste sa position

plot "temp/traitement_L.txt" using 2:xtic(1) notitle linecolor rgb rose1

