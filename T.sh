#!/bin/bash

#awk -F ';' 'NR >1{printf "%s;%s\n", $1,$5}' data.csv > TownAstep1.txt

# Utilisation de awk pour extraire les informations des colonnes pertinentes
#awk -F';' '$2 == 1 {count[$3]++} {total[$4]++} END {for (city in total) print city, ";",total[city] + count[city],";", count[city] }' data.csv > villes_stats.txt
#sed -i 's/ *; */;/g' villes_stats.txt

awk -F';' '!visited[$1,$3]++ { count[$3]++ } !visited[$1,$4]++ { count[$4]++ } $2 == 1 {counta[$3]++ } END { for (city in count) print city,";",count[city],";",counta[city]}' data.csv > villes_stats.txt
sed -i 's/ *; */;/g' villes_stats.txt
