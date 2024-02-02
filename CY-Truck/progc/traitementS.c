#include "fonctions.h"


//DANS CE FICHIER ON NE DEFINI PAS LES FONCTIONS : ouvrirFichier / min / max CAR ELLES SONT DEJA DANS traitementT.c ET RELIES AVEC LE HEADER fonctions.h


//Renvoie un pointeur vers une string qui est la concaténation de 2 entiers et de 3 floats, séparés par des ';'
char* concatenerDonneesS(int nb1, int nb2, float fl1, float fl2, float fl3) {

	//On calcule la taille qu'il va falloir pour la concatenation
	int tailleConcat = snprintf(NULL, 0, "%d;%d;%f;%f;%f\n", nb1, nb2, fl1, fl2, fl3);

	//Allocation mémoire pour la concatenation
	char* concatenation = (char*)malloc(tailleConcat + 1);

	if (concatenation == NULL) {
		printf("Erreur 17\n");
		exit(1);
	}
    //On sépare tout par des ';' et on met dans concatenation
	snprintf(concatenation, tailleConcat + 1, "%d;%d;%f;%f;%f\n", nb1, nb2, fl1, fl2, fl3);
    return concatenation;
}






//Fonctions constructeurs pour les structures

DataS creationDataS(int id, float mo, float mi, float ma) {
	DataS d;
	d.id = id;
	d.moyenne = mo;
	d.mini = mi;
	d.maxi = ma;
	return d;
}

pAVL_S creationAVL_S(DataS v) {
	pAVL_S a = malloc(sizeof(AVL_S));
	if (a == NULL) {
		printf("Erreur 18\n");
		exit(1);
	}
	a->ville = v;
	a->eq = 0;
	a->fg = NULL;
	a->fd = NULL;
	return a;
}





//Fonctions AVL S

pAVL_S rg_S(pAVL_S a) {
	if (a == NULL) {
		return a;
	}
	int eqa, eqp;
	pAVL_S pivot = a->fd;
	eqa = a->eq;
	eqp = pivot->eq;
	
	a->fd = pivot->fg;
	pivot->fg = a;

	a->eq = eqa - max(eqp, 0) - 1;
	pivot->eq = min(eqa - 2, min(eqa + eqp - 2, eqp - 1));
	return pivot;
}

pAVL_S rd_S(pAVL_S a) {
	if (a == NULL) {
		return a;
	}
	int eqa, eqp;
	pAVL_S pivot = a->fg;
	a->fg = pivot->fd;
	pivot->fd = a;
	eqa = a->eq;
	eqp = pivot->eq;
	a->eq = eqa - min(eqp, 0) + 1;
	pivot->eq = max(eqa + 2, max(eqa + eqp + 2, eqp + 1));
	return pivot;
}

pAVL_S drg_S(pAVL_S a) {
	if (a == NULL) {
		return a;
	}
	a->fd = rd_S(a->fd);
	return rg_S(a);
}

pAVL_S drd_S(pAVL_S a) {
	if (a == NULL) {
		return a;
	}
	a->fg = rg_S(a->fg);
	return rd_S(a);
}

pAVL_S equilibrerAVL_S(pAVL_S a) {
	if (a == NULL) {
		return a;
	}
	if (a->eq >= 2) {
		if (a->fd->eq >= 0) {
			return rg_S(a);
		}
		else {
			return drg_S(a);
		}
	}
	else if (a->eq <= -2) {
		if (a->fg->eq <= 0) {
			return rd_S(a);
		}
		else {
			return drd_S(a);
		}
	}
	return a;
}

pAVL_S ajouterAVL_S(pAVL_S a, DataS villeAjt, int *h) {
	if (a == NULL) {
		*h = 1;
		a = creationAVL_S(villeAjt);
		return a;
	}
	//ATTENTION : On traite le cas ou les max-mini sont égaux (très peu probable mais on sait jamais)
	if ((villeAjt.maxi-villeAjt.mini) < (a->ville.maxi-a->ville.mini) || (villeAjt.maxi-villeAjt.mini) == (a->ville.maxi-a->ville.mini)) {
		a->fg = ajouterAVL_S(a->fg, villeAjt, h);
		*h = -*h;
	}
	else if ((villeAjt.maxi-villeAjt.mini) > (a->ville.maxi-a->ville.mini)) {
		a->fd = ajouterAVL_S(a->fd, villeAjt, h);
	}
	else {
		*h = 0;
		return a;
	}
	if (*h != 0) {
		a->eq = a->eq + *h;
		a = equilibrerAVL_S(a);
		if (a->eq == 0) {
			*h = 0;
		}
		else{
			*h = 1;
		}
	}
	return a;
}




//Forme l'AVL
pAVL_S formeAVL_S() {
	FILE *txtTemp=ouvrirFichier("../temp/traitementS.txt", "r");
	pAVL_S avlS = NULL;
	char ligne[LONGUEUR_LIGNE];

	//Variables dans lesquelles on va stocker les différentes données de chaque ligne pour les envoyer dans l'AVL
	int idTemp;
	float moyTemp;
	float minTemp;
	float maxTemp;
  
	//Compteur de ligne pour indiquer la ligne ou il y a une erreur
	int ctLigne=1;

	//On parcourt chaque ligne du fichier txt envoyé par le shell pour récupérer et envoyer les données dans l'AVL
	while (fgets(ligne, 100, txtTemp) != NULL) {
		//On va recupérer les différents elements de la ligne et les mettre dans eltLigne
		
		//On stocke l'id de la ligne
		char* eltLigne=strtok(ligne, ";");
		if(eltLigne==NULL){
			printf("Erreur 9 ligne %d\n",ctLigne);
			exit(1);
		}
		idTemp = atoi(eltLigne);
		//Si l'id est <=0 il y a un pb (ceci vérifie 2 pb à la fois : si l'id est <=0 et si l'id est une chaine de caractère et pas un nombre car atoi transforme un chaine de caractère en 0)
		if(idTemp<=0){
			printf("Erreur 10 ligne %d\n",ctLigne);
			exit(1);
		}
		
		//On stocke la moyenne de la ligne
		eltLigne = strtok(NULL, ";");
		if(eltLigne==NULL){
			printf("Erreur 11 ligne %d\n",ctLigne);
			exit(1);
		}
		moyTemp = atof(eltLigne);
		//On vérifie les meme problèmes que pour l'id
		if(moyTemp<=0){
			printf("Erreur 12 ligne %d\n",ctLigne);
			exit(1);
		}
		
		//On stocke le min de la ligne
		eltLigne = strtok(NULL, ";");
		if(eltLigne==NULL){
			printf("Erreur 13 ligne %d\n",ctLigne);
			exit(1);
		}
		minTemp = atof(eltLigne);
		//On verifie les meme problèmes
		if(minTemp<=0){
			printf("Erreur 14 ligne %d\n",ctLigne);
			exit(1);
		}
		
		//On stocke le max de la ligne
		eltLigne = strtok(NULL, ";");
		if(eltLigne==NULL){
			printf("Erreur 15 ligne %d\n",ctLigne);
			exit(1);
		}
		maxTemp = atof(eltLigne);
		//On vérifie les meme problèmes
		if(maxTemp<=0){
			printf("Erreur 16 ligne %d\n",ctLigne);
			exit(1);
		}
		
		//On ajoute tout ce qu'on a récupéré dans un noeud dans l'AVL
		int h=0;
		avlS = ajouterAVL_S(avlS, creationDataS(idTemp, moyTemp, minTemp, maxTemp), &h);
		ctLigne++;
	}
	fclose(txtTemp);
	return avlS;
}

//Renvoie le nombre de noeuds dans l'AVL (utile pour afficher le nombre de noeuds dans l'erreur 20)
int compteNoeudsS(pAVL_S a){
	if(a!=NULL){
		return 1+compteNoeudsS(a->fg)+compteNoeudsS(a->fd);
	}
	return 0;
}


//Copie le top 50 dans un fichier txt, on fait un parcours infixe inversé et à l'aide de concatenerDonneesS on copie les infos dans le fichier destination
void envoieTop50(pAVL_S a, int* c, FILE* file){
	if(a!=NULL){
		envoieTop50(a->fd,c,file);
		//si c>0 ça veut dire qu'il reste de la place pour le top 50 et donc ...
		if(*c>0){
			//... on créer la ligne qu'il faut envoyer avec concatenerDonneesS et ...
			char* ligne=concatenerDonneesS(50-(*c),a->ville.id,a->ville.moyenne,a->ville.mini,a->ville.maxi);
			//... on les copie dans le fichier destination (et on oublie pas de free la ligne)
			fputs(ligne,file);
			free(ligne);
			(*c)--;
		}
		envoieTop50(a->fg,c,file);
	}
}



//Fonction qui libere la memoire des noeuds de l'AVL

void libererMemoireAVLS(pAVL_S a) {
	if (a != NULL) {
		libererMemoireAVLS(a->fg);
		libererMemoireAVLS(a->fd);
		free(a);
	}
}

/*/Fonction principale du traitement S
1. On forme l'AVL qui sera la liste de tous les Route ID différents, triées par etapeMax - etapeMin
2. On met dans un pointeur l'adresse du fichier ou on veut renvoyer les infos (dans notre cas on utilise le même fichier que le shell nous as envoyé pour éviter d'avoir a en recréer un)
3. On copie les 50 premières valeurs de l'AVL dans le fichier traitementS.txt
4. On libère tous les noeuds de l'AVL
/*/
void traitementS(){
	//1.
	pAVL_S pa = formeAVL_S();
	int nbNoeuds=compteNoeudsS(pa);
	if(nbNoeuds<50){
		printf("Erreur 20\nIl y a %d villes dans data.csv or ce traitement doit afficher 50 villes.\n",nbNoeuds);
		exit(1);
	}
	//On initialise le compteur à 50, celui ci va permettre de seulement faire des choses avec les 50 premiers noeuds de l'AVL
	int ct50=50;
	//2.
	FILE* renvoie=ouvrirFichier("../temp/traitementS.txt","w");
	//3.
	envoieTop50(pa, &ct50,renvoie);
	fclose(renvoie);
	//4.
	libererMemoireAVLS(pa);
}
