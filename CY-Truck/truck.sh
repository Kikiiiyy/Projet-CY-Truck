#!/bin/bash

# 
chemin_du_fichier="$1"
repertoire=$(pwd)

# Fonction qui affiche un  message d'erreur
affichage_erreur(){
        echo "Usage: $0 chemin_du_fichier data.csv -option"
}

# Deplace les fichier temporaire
dossier_temp(){
	repertoire=$(pwd)
	dossier_source="${repertoire}/demo/txt_temp"
	dossier_temp="${repertoire}/temp"

	# Vérifiez si le dossier source existe
	if [ -d "$dossier_source" ]; then
	    # Copiez tous les fichiers du dossier source vers le dossier destination
	    cp "${dossier_source}/${1}" "$dossier_temp"
	else
	    echo "Le dossier source n'existe pas."
	fi

}
# Deplace le fichier finaux txt dans demo/txt_final
deplacer_fichier_finaux(){
	repertoire=$(pwd)
	
	dossier_temp="${repertoire}/temp"
	
	dossier_finaux="${repertoire}/demo/txt_final"
	
	if [ ! -d "$dossier_finaux" ]; then
		mkdir -p "$dossier_finaux"
    	fi
    	fichier_final="${dossier_temp}/${1}"
    	mv "$fichier_final" "$dossier_finaux"
}

# Fonction qui copie tout les fichier temporaire dans le dossier demo/txt_temp
deplacer_fichier_initiaux(){
	repertoire=$(pwd)
	
	dossier_temp="${repertoire}/temp"
	
	dossier_initiaux="${repertoire}/demo/txt_temp"
	
	if [ ! -d "$dossier_initiaux" ]; then
		mkdir -p "$dossier_initiaux"
    	fi
    	fichier_temp="${dossier_temp}/${1}"
    	cp "$fichier_temp" "$dossier_initiaux"
}

deplacer_graphique() {
    # Spécifiez le chemin complet du dossier du projet
    repertoire=$(pwd)

    # Dossier images
    dossier_images="${repertoire}/images"

    # Dossier demo
    dossier_demo="${repertoire}/demo"

   
    # Vérifiez si le dossier "demo" existe, sinon créez-le
    if [ ! -d "$dossier_demo" ]; then
        mkdir -p "$dossier_demo"
    fi

    # Chemin complet du graphique à déplacer
    graphique_complet="${repertoire}/${1}"

    # Vérifiez si le fichier du graphique existe
    if [ -f "$graphique_complet" ]; then
        # Déplacez l'ancien graphique du dossier "images" vers le dossier "demo"
        ancien_graphique="$dossier_images/$(basename "$graphique_complet")"
        if [ -f "$ancien_graphique" ] ; then 
        	mv "$ancien_graphique" "$dossier_demo"
        fi 

        # Déplacez le nouveau graphique vers le dossier "images"
        mv "$graphique_complet" "$dossier_images"
    fi
}

# Permet de verifier si il y a au moins 2 arguments
if [ "$#" -lt 1 ]; then
    affichage_erreur
    exit 1
fi

# Verifie si le fichier data.csv existe bien 
if [[ ! -f "$chemin_du_fichier" ]]; then
    affichage_erreur 
    echo "Le fichier data.csv n'existe pas dans le répertoire de travail."
    exit 1
fi

# Permet de créer le dossier images si il n'existe pas 
if [[ ! -d "$repertoire/images" ]]; then
    mkdir images
fi

if [[ ! -d "$repertoire/progc" ]]; then
    mkdir progc
    echo "Veuillez mettre les fichiers c et le makefile dans le dossier progc"
    exit
fi

if [[ ! -d "$repertoire/images" ]]; then
    mkdir images
fi

if [[ ! -d "$repertoire/temp" ]]; then
    mkdir temp
else 
	rm -r "$repertoire/temp"
	mkdir temp
fi



# Fonction qui verifie si l'excutable c existe et le crée si il n'existe pas
verification_executable(){
	
	if [ ! -x "programme_c" ]; then
		if [ -e "makefile" ] && [ -e "traitementS.c" ] &&  [ -e "main.c" ] &&  [ -e "traitementT.c" ]; then
			make 
			rm traitementS.o 
			rm traitementT.o
			rm main.o
			echo "Compilation terminée"
		else 
			echo "Le makefile ou les fichiers c ne sont pas dans le dossier progc"
			exit 
		fi
	fi

}


# Ensemble des fonctions utilisées pour les traitements


# Fonction pour le traitement S
traitement_S() { 
        echo "Option -S spécifiée"
	LC_NUMERIC=C awk -F";" 'NR > 1{compteur[$1] += $5; nombre[$1]+=1; if(min[$1] == "" || min[$1] > $5) min[$1]=$5;if(max[$1] == "" || max[$1] < $5) max[$1]=$5} END {for (ligne in compteur) print ligne ";" compteur[ligne]/nombre[ligne] ";" min[ligne]";"max[ligne]}' data/data.csv > temp/traitementS.txt
	deplacer_fichier_initiaux "traitementS.txt"
	cd progc # changement de dossier 
        verification_executable
        ./programme_c s
        cd .. #retour à la racine du projet
	gnuplot gnuplot/S.gnu # creation du graphique
	deplacer_graphique "S.png"
	deplacer_fichier_finaux "traitementS.txt"
	dossier_temp "traitementS.txt" 

}

# Fonction pour le traitement T
traitement_T() {
        echo "Option -T spécifiée"
        awk -F';' '!visited[$1,$3]++ { count[$3]++ } !visited[$1,$4]++ { count[$4]++ } $2 == 1 {counta[$3]++ } END { for (city in count) print city,";",count[city],";",counta[city]}' data/data.csv > temp/traitementT.txt
        sed -i 's/ *; */;/g' temp/traitementT.txt
        deplacer_fichier_initiaux "traitementT.txt"
        cd progc  # changement de dossier 
        verification_executable
        ./programme_c t
        cd .. #retour à la racine du projet
        gnuplot gnuplot/T.gnu # creation du graphique
     	deplacer_graphique "T.png"
     	deplacer_fichier_finaux "traitementT.txt"
     	dossier_temp "traitementT.txt" # Permet de remplir le dossier temp avec tout les fichier temporaire utilisé lors de tout les traitement
	
}

# Fonction pour le traitement L
traitement_L() {
        echo "Option -L spécifiée"
        awk -F ';' 'NR > 1 {distance[$1] += $5} END {for (trajet in distance) print trajet, distance[trajet]}' data/data.csv | sort -k2,2nr | head -n 10 | sort -k1n > temp/traitement_L.txt
	gnuplot gnuplot/L.gnu
	deplacer_graphique "L.png"
	deplacer_fichier_initiaux "traitement_L.txt"
	deplacer_fichier_finaux "traitement_L.txt"
	dossier_temp "traitement_L.txt" # Permet de remplir le dossier temp avec tout les fichier temporaire utilisé lors de tout les traitement
}

# Fonction pour le traitement D1
traitement_D1() {
        echo "Option -D1 spécifiée"
	grep ";1;" data/data.csv|cut -d";" -f6  | uniq -c |sort -d -k1 | cut -d" " -f7,8,9 | awk -F',' '{ compteur[$1]++ } END { for (mot in compteur) print mot ",", compteur[mot] }' |sort -n -r -k4|head -10| cut -d" " -f2,3,4   > temp/traitement_D1.txt
	gnuplot gnuplot/D1.gnu # creation du graphique
	convert -rotate 90 DT2.png D1.png # rotation du graphique
	rm DT2.png #suppression du premier graphique
	deplacer_graphique "D1.png"
	deplacer_fichier_initiaux "traitement_D1.txt"
	deplacer_fichier_finaux "traitement_D1.txt"
	dossier_temp "traitement_D1.txt" # Permet de remplir le dossier temp avec tout les fichier temporaire utilisé lors de tout les traitement
}

# Fonction pour le traitement D2
traitement_D2(){
echo "Option -D2 spécifiée"
	awk -F';' 'NR > 1 {distance[$6] += $5} END {for (conducteur in distance) print distance[conducteur],",", conducteur}' data/data.csv | sort -nr | head -n 10 | awk -F',' 'BEGIN {OFS=","} {print $2, $1}' > temp/traitement_D2.txt
	gnuplot gnuplot/D2.gnu  # Rotation du graphique
	convert -rotate 90 DT1.png D2.png # Suppression du premier graphique
	rm DT1.png # Suppression du premier graphique
	deplacer_graphique "D2.png"
	deplacer_fichier_initiaux "traitement_D2.txt"
	deplacer_fichier_finaux "traitement_D2.txt"
	dossier_temp "traitement_D2.txt" # Permet de remplir le dossier temp avec tout les fichier temporaire utilisé lors de tout les traitement
}

# Verifie si l'argument h est donné par l'utilisateur
for arg in "$@"; do
    if [ "$arg" == "-h" ]|| [ "$arg" == "h" ]; then
    	affichage_erreur
        echo "-d1 : affiche un graphique des conducteurs ayant effectué le plus grand nombre de trajets différents."
        echo "-d2 : affiche un graphique des conducteurs ayant parcouru la plus grande distance totale au cours de tous ses trajets."
        echo "-l : affiche un graphique des 10 plus longs trajets."
        echo "-t : affiche un graphique des 10 villes qui ont été les plus traversées, tous trajets confondus. Et affiche le nombre de fois que ces villes ont été ville de départ."
        echo "-s : affiche un graphique des 50 trajets qui ont le plus grand écart entre les distances de leur plus longue et plus courte etape. Affiche la plus longue, la plus courte étape et la moyenne des distance des étapes pour ces trajets."
        exit 1
    fi
done

shift # Permet de passer à l'argument suivant 

# Initialisation des compteurs
option_s=false
option_t=false
option_l=false
option_d1=false
option_d2=false
compte=0
# Parcourir tous les arguments et executer les traitements
for arg in "$@"; do
	((compte++))
	if [ "$compte" -eq "20" ] ; then
		echo "au moin 20 argument ont été mit fin de l'execution'"
		exit 1
	fi
	if [ "$option_s" = true ] && [ "$option_t" = true ] && [ "$option_l" = true ] && [ "$option_d1" = true ] && [ "$option_d2" = true ]; then
		echo "Les graphiques ont été réalisés avec succès. Retrouvez les dans le dossier images."
 		exit
	fi
	debut=$(date +%s.%N) # Retient le temps avant l'éxecution
	if [ "$arg" == "-t" ]|| [ "$arg" == "t" ]; then
		if [ "$option_t" = false ]; then
		        option_t=true
		        traitement_T
		        fin=$(date +%s.%N)
	    		temps_final=$(echo "$fin - $debut" | bc)
			echo "Le traitement T a mis ${temps_final} secondes à s'exécuter."
			echo " "
			
		    else
		        echo "Option -t déjà traitée."
		        echo " "
		        
		    fi


	elif [ "$arg" == "-s" ]|| [ "$arg" == "s" ] ; then
		if [ "$option_s" = false ]; then
		        option_s=true
		        traitement_S
		        fin=$(date +%s.%N) # Retient le temps apres l'execution
	    		temps_final=$(echo "$fin - $debut" | bc) # Calcule le temps que le traitement a prit # bc permet de calculer plus precisement
			echo "Le traitement S a mis ${temps_final} secondes à s'exécuter." #affiche le temps
			echo " "
			
		    else
		        echo "Option -s déjà traitée."
		        echo " "
		        
		    fi
		    
	elif [ "$arg" == "-l" ]|| [ "$arg" == "l" ] ; then 
		# Vérifier si l'option -l a déjà été traitée
		    if [ "$option_l" = false ]; then
		        option_l=true
		        traitement_L
		        fin=$(date +%s.%N)
	    		temps_final=$(echo "$fin - $debut" | bc)
			echo "Le traitement L a mis ${temps_final} secondes à s'exécuter."
			echo " "
			
		    else
		        echo "Option -l déjà traitée."
		        echo " "
		        
		    fi
	
	elif [ "$arg" == "-d1" ]|| [ "$arg" == "d1" ] ; then 
		# Vérifier si l'option -d1 a déjà été traitée
		    if [ "$option_d1" = false ]; then
		        option_d1=true
		        traitement_D1
		        fin=$(date +%s.%N)
	    		temps_final=$(echo "$fin - $debut" | bc)
			echo "Le traitement D1 a mis ${temps_final} secondes à s'exécuter."
			echo " "
			
		    else
		        echo "Option -d1 déjà traitée."
		        echo " "
		        
		    fi
	elif [ "$arg" == "-d2" ]|| [ "$arg" == "d2" ] ; then 
		if [ "$option_d2" = false ]; then
		        option_d2=true
		        traitement_D2
		        fin=$(date +%s.%N)
	    		temps_final=$(echo "$fin - $debut" | bc)
			echo "Le traitement D2 a mis ${temps_final} secondes à s'exécuter."
			echo " "
			
		    else
		        echo "Option -d2 déjà traitée."
		        echo " "
		        
		    fi
		echo "Option invalide. Utilisez -h pour afficher les options disponibles."
		echo " "
		affichage_erreur
	fi

done
echo "Les graphiques ont été réalisés avec succès. Retrouvez les dans le dossier images."
