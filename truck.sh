#!/bin/bash


if [[ -f "data.csv" ]]; then
    echo "Le fichier data.csv existe dans le répertoire de travail."
    repertoire=$(cd "$(dirname "$0")" && pwd)

	while getopts ":STLD:" option; do
	    case $option in
	    
	    	S) # Option -S
		    echo "Option -S spécifiée"
		    exit ;;
		    
	    	T) # Option -T
		    echo "Option -T spécifiée"
		    grep ";1;" data.csv |awk -F ';' '{ noms[$3]++ } END { for (nom in noms) print nom,";",noms[nom] }' > TownAstep1.txt
		    fichier_a_deplacer="$repertoire/TownAstep1.txt"
		    mv "$fichier_a_deplacer" traitement-T
		    exit ;;
		    
		 L) # Option -L
		    echo "Option -L spécifiée"
		    awk -F ';' '!($1 FS $2 in seen) {seen[$1 FS $2]; print}' data.csv |awk -F';' 'NR > 1 {distance[$1] += $5} END {for (trip in distance) print trip, distance[trip]}' | sort -k2,2nr | head -n 10 > t.txt
		    gnuplot L.gnu
		    rm t.txt 
		    fichier_a_deplacer="$repertoire/L.png"
		    mv "$fichier_a_deplacer" graphique
		    exit ;;
		    
	    	 D)
		    case $OPTARG in
		        1)
		            echo "Option -D1 spécifiée"
		            grep ";1;" data.csv|cut -d";" -f6  | uniq -c |sort -d -k1 | cut -d" " -f7,8,9  > datatemp.csv #cut car ily a des espace en trop
		            awk -F',' '{ count[$1]++ } END { for (word in count) print word ",", count[word] }' datatemp.csv |sort -n -r -k4|head -10| cut -d" " -f2,3,4   > DP.txt
		            gnuplot D1.gnu
		            convert -rotate 90 DT2.png D1.png
		            rm DP.txt
		            rm DT2.png
		            fichier_a_deplacer="$repertoire/D1.png"
		    	    mv "$fichier_a_deplacer" graphique
		            # Faites ce que vous souhaitez pour l'option -D1
		            exit ;;
		        2)
		            echo "Option -D2 spécifiée"
		            awk -F';' 'NR > 1 {distance[$6] += $5} END {for (driver in distance) print distance[driver],",", driver}' data.csv | sort -nr | head -n 10  > Dtemp.txt
		            awk -F',' 'BEGIN {OFS=","} {print $2, $1}' Dtemp.txt > D.txt
			    gnuplot D2.gnu
		            convert -rotate 90 DT1.png D2.png
		            rm DT1.png
		            rm D.txt
		            # Faites ce que vous souhaitez pour l'option -D2
		            fichier_a_deplacer="$repertoire/D2.png"
		    	    mv "$fichier_a_deplacer" graphique
		            exit ;;
		        *)
		            echo "Option -D avec argument invalide: $OPTARG" >&2
		            exit 1 ;;
		    esac ;;
		\?)
		    echo "Option invalide: -$OPTARG" >&2
		    exit 1 ;;
		:)
		    echo "L'option -$OPTARG nécessite un argument." >&2
		    exit 1 ;;
	    esac
	done
else
    echo "Le fichier data.csv n'existe pas dans le répertoire de travail."
fi
