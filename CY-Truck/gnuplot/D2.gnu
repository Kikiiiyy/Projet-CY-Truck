set terminal pngcairo enhanced font 'Arial,12' # Changement de la police
set output 'DT1.png' # Nom du futur graphique

set datafile separator ","  # Indique que la virgule est utilisée comme séparateur

rose1 = "#FFB8CE";# Initilaisation d'une couleur
set terminal pngcairo enhanced size 800,800 # Taille du graphique
set style data histogram
set style histogram rowstacked
set style fill solid
set boxwidth 0.75

#initilaisation des titres des axes
set xlabel "Noms"  # Étiquette de l'axe des abscisses
set y2label "Nombre de Trajets"  # Étiquette de l'axe des ordonnées
set size 1, 1
set xtics rotate
set y2tics rotate
unset ytics ; set y2tics mirror

set title "Traitement -d2" # Ajoute un titre et ajuste sa position
plot 'temp/traitement_D2.txt' using 2:xtic(1) axes x1y2 notitle  linecolor rgb rose1
