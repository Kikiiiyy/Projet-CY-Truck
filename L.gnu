# Contenu du fichier plot_script.gnu
set terminal pngcairo enhanced font 'Arial,10'
set output 'L.png'

set size 1,1 # Ajuste la largeur de l'histogramme
set style data histograms
set style fill solid

set title "Traitement L" offset 0,1  # Ajoute un titre et ajuste sa position

plot 't.txt' using 2:xtic(1)notitle 
