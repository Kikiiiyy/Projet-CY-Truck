set terminal png size 800,800 enhanced font "Arial,10" # Changement de la police
set output 'T.png' # Nom du futur graphique

set title "Traitement -t"
set datafile separator ";" # Indique que le point virgule est utilisée comme séparateur
rose1 = "#FFB8CE"; rose2 = "#FA739D"; # Initilaisation des couleur
set style data histogram
set style histogram cluster gap 1
set style fill solid
set boxwidth 0.9

#initilaisation des titres des axes
set xtics format ""
set grid ytics
set xtic rotate
set xlabel "Villes"
set ylabel "Nombre Visites"

plot "temp/traitementT.txt" using 2:xtic(1) title "Nb total" linecolor rgb rose1,   \
     "temp/traitementT.txt" using 3 title "Nb départs" linecolor rgb rose2,   \


