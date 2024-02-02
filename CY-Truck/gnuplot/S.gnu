set terminal pngcairo size 1000,800 enhanced font 'Arial,12'
set output 'S.png' # Nom du futur graphique

rose1 = "#FFB8CE"; noir = "#333031"  # Initilaisation des couleur

set datafile separator ";" # Indique que le point virgule est utilisée comme séparateur
set title "Traitement -s"  #  Changement du titre

#initilaisation des titres des axes
set xlabel "ID"
set ylabel "Distance (km)"
set style data lines
set xtic rotate

# Tracer les courbes et afficher les points
plot 'temp/traitementS.txt' using 1:4:5  with filledcurves linecolor rgb rose1 notitle,\
 ""using 3:xticlabel(2) linecolor rgb noir notitle


