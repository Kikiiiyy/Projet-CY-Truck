# CY-Truck :
Ce projet a pour objectif de créer une application qui va traiter un fichier de données de trajet pour ensuite afficher des graphiques.

# Pour commencer :
Pour utiliser ce projet, **il faut attribuer les droits de lecture et d'exécution à truck.sh** (dans la racine du projet vous pouvez faire chmod +x truck.sh). Si le répertoire data n'existe pas, créez un répertoire "data" à la racine du projet.

# Utilisation :
Pour utiliser l'application, il faut faire **./Truck.sh **.** Il faut obligatoirement mettre le chemin** du fichier CSV à étudier pour cela vous pouvez tapez la commande pwd dans la racine du projet puis y rajouter /data/data.csv .Il faut ensuite ajouter les différentes options de données souhaitées sous la forme **"-NomOption" soit " NomOption"**
Il est possible d'utiliser **plusieurs options différentes simultanément** (par exemple : -d1 -l -t) ou (par exemple :  d1 l t), **mais si vous essayer d'utiliser plusieurs fois une même option alors celle ci ne se feras qu'une seule fois** (par exemple : -d1 -l -d1).
**Pour vous aider, vous pouvez utiliser l'option -h** qui vous montrera toutes les options possibles et comment les utiliser.
Il y a en tout 5 différentes options : -d1, -d2, -l, -t et -s
- d1 : crée un graphique des conducteurs ayant parcouru le plus de trajets différents. Triée dans l'ordre décroissant du nombre de trajets.
- d2 : crée un graphique des conducteurs ayant parcouru la plus grande distance totale au cours des trajets.
- l : crée un graphique des 10 trajets dont la distance totale est la plus longue, triée dans l'ordre croissant des numéros d'identifiants des trajets.
- t : crée un graphique des 10 villes qui ont été le plus traversées. Avec en abscisse le nom des villes triées par ordre alphabétique et en ordonnée le nombre de trajets.
- s : crée un graphique avec 3 courbes, une pour le minimum, une autre pour le maximum et une troisième pour la moyenne, et ce pour chaque trajet en abscisse.

Ensuite, pour compiler les fichiers sources, il suffit simplement d'exécuter make. Néanmoins, le script Shell se charge de faire cette compilation lorsque c'est nécessaire.

# Erreur d'exécution
En cas d'erreur lors de l'exécution du script Shell ou du programme C, un message d'erreur sera affiché, expliquant la raison de l'erreur.

# Auteurs :
- Anthony Voisin
- Killian Harrois
- Thomas Labbé-Nobili
