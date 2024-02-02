#include "fonctions.h"


//Fonctions utiles

//Renvoie un pointeur vers le fichier qu'on souhaite ouvrir avec un mode précisé
FILE* ouvrirFichier(char* nomFichier, char* mode) {
	FILE* fichier = fopen(nomFichier, mode);
	if(fichier==NULL){
		printf("Erreur lors de l'ouverture de %s\n", nomFichier);
		exit(1);
	}
	return fichier;
}

int min(int a, int b) {
	if (a <= b) {
		return a;
	}
	return b;
}

int max(int a, int b) {
	if (a <= b) {
		return b;
	}
	return a;
}

//Renvoie un pointeur vers une string qui est la concaténation d'une string et 2 entiers, séparés par des ';'
char* concatenerDonneesT(char* mot, int nb1, int nb2) {
    //On calcule la taille qu'il va falloir pour la concatenation
	int tailleConcat = snprintf(NULL, 0, "%s;%d;%d\n", mot, nb1, nb2);

	//Allocation mémoire pour la concatenation
	char* concatenation = (char*)malloc(tailleConcat + 1);
	if (concatenation == NULL) {
		printf("Erreur 6\n");
		exit(1);
	}
	
    //On sépare tout par des ';' et on met dans concatenation
	snprintf(concatenation, tailleConcat + 1, "%s;%d;%d\n", mot, nb1, nb2);
	return concatenation;
}





//Fonctions constructeurs pour les structures

DataT creationDataT(char *v, int vis, int dep) {
	DataT d;
	strcpy(d.nomVille, v);
	d.nbVisite = vis;
	d.nbDepart = dep;
	return d;
}

pAVL_T creationAVL_T(DataT v) {
	pAVL_T a = malloc(sizeof(AVL_T));
	if (a == NULL) {
		printf("Erreur 7\n");
		exit(1);
	}
	a->ville = v;
	a->eq = 0;
	a->fg = NULL;
	a->fd = NULL;
	return a;
}





//Fonctions AVL T1

pAVL_T rg_T(pAVL_T a) {
	if (a == NULL) {
		return a;
	}
	int eqa, eqp;
	pAVL_T pivot = a->fd;
	eqa = a->eq;
	eqp = pivot->eq;
	a->fd = pivot->fg;
	pivot->fg = a;
	
	a->eq = eqa - max(eqp, 0) - 1;
	pivot->eq = min(eqa - 2, min(eqa + eqp - 2, eqp - 1));
	return pivot;
}

pAVL_T rd_T(pAVL_T a) {
	if (a == NULL) {
		return a;
	}
	int eqa, eqp;
	pAVL_T pivot = a->fg;
	a->fg = pivot->fd;
	pivot->fd = a;
	eqa = a->eq;
	eqp = pivot->eq;
	a->eq = eqa - min(eqp, 0) + 1;
	pivot->eq = max(eqa + 2, max(eqa + eqp + 2, eqp + 1));
	return pivot;
}

pAVL_T drg_T(pAVL_T a) {
	if (a == NULL) {
		return a;
	}
	a->fd = rd_T(a->fd);
	return rg_T(a);
}

pAVL_T drd_T(pAVL_T a) {
	if (a == NULL) {
		return a;
	}
	a->fg = rg_T(a->fg);
	return rd_T(a);
}

pAVL_T equilibrerAVL_T(pAVL_T a) {
	if (a == NULL) {
		return a;
	}
	if (a->eq >= 2) {
		if (a->fd->eq >= 0) {
			return rg_T(a);
		}
		else {
			return drg_T(a);
		}
	}
	else if (a->eq <= -2) {
		if (a->fg->eq <= 0) {
			return rd_T(a);
		}
		else {
			return drd_T(a);
		}
	}
	return a;
}

//Dans le 1er AVL, on trie en fonction de nbVisite
pAVL_T ajouterAVL_T(pAVL_T a, DataT villeAjt, int *h) {
	if (a == NULL) {
		*h = 1;
		a = creationAVL_T(villeAjt);
		return a;
	}
	//ATTENTION : On traite aussi le cas ou les nbVisite sont égaux (si c'est le cas, on peut envoyer soit dans le fd soit dans le fg, dans notre cas on envoie dans le fg)
	if (villeAjt.nbVisite < a->ville.nbVisite || villeAjt.nbVisite==a->ville.nbVisite) {
		a->fg = ajouterAVL_T(a->fg, villeAjt, h);
		*h = -*h;
	}
	else if (villeAjt.nbVisite > a->ville.nbVisite) {
		a->fd = ajouterAVL_T(a->fd, villeAjt, h);
	}
	else {
		*h = 0;
		return a;
	}
	if (*h != 0) {
		a->eq = a->eq + *h;
		a = equilibrerAVL_T(a);
		if (a->eq == 0) {
			*h = 0;
		}
		else {
			*h = 1;
		}
	}
	return a;
}

//Forme le 1er AVL,
pAVL_T formeAVL_T() {
	FILE *txtTemp=ouvrirFichier("../temp/traitementT.txt", "r");
	pAVL_T avlT = NULL;
	
	char ligne[LONGUEUR_LIGNE];
	
	//Variables dans lesquelles on va stocker les différentes données de chaque ligne pour les envoyer dans l'AVL
	char villeTemp[LONGUEUR_VILLE];
	int visTemp;
	int depTemp;
	
	//Compteur de ligne pour indiquer la ligne ou il y a une erreur
	int ctLigne=1;
	
	//On parcourt chaque ligne du fichier txt envoyé par le shell pour récupérer et envoyer les données dans le 1er AVL
	while (fgets(ligne, 100, txtTemp) != NULL) {
		//On va recupérer les différents elements de la ligne et les mettre dans eltLigne
		
		//On stocke le nom de la ville de la ligne
		char* eltLigne=strtok(ligne, ";");
		if(eltLigne==NULL){
			printf("Erreur 2 ligne %d\n",ctLigne);
			exit(1);
		}
		strcpy(villeTemp, eltLigne);
		
		//On stocke le nombre "visite" de la ligne
		eltLigne = strtok(NULL, ";");
		if(eltLigne==NULL){
			printf("Erreur 3 ligne %d\n",ctLigne);
			exit(1);
		}
		visTemp = atoi(eltLigne);
		//A chaque fois on vérifie que les données sont correctes (voir les codes erreurs) ici si visTemp==0 ça veut dire que soit le nb de visite est égal à 0, ce qui n'est pas normal vu que le shell ne devrait dans ce cas pas le mettre dans le fichier txt, soit visTemp n'était pas un nombre mais une chaine de caractère avant le atoi, et dans ce cas il y a un pb aussi
		if(visTemp==0){
			printf("Erreur 4 ligne %d\n",ctLigne);
			exit(1);
		}
		
		//On stocke le nombre "départ" de la ligne
		eltLigne = strtok(NULL, ";");
		//On vérifie si il y a la donnée du nombre de fois que la ville est ville de départ, si il y a l'info on met depTemp à cette valeur, sinon on met depTemp à 0
		if(eltLigne!=NULL){
			depTemp=atoi(eltLigne);
		}
		else{
			depTemp=0;
		}
		
		//On ajoute tout ce qu'on a récupéré dans un noeud dans l'AVL
		int h=0;
		avlT = ajouterAVL_T(avlT, creationDataT(villeTemp, visTemp, depTemp), &h);
		ctLigne++;
	}
	fclose(txtTemp);
	return avlT;
}

//Renvoie le nombre de noeuds dans l'AVL (utile pour afficher le nombre de noeuds dans l'erreur 19)
int compteNoeudsT(pAVL_T a){
	if(a!=NULL){
		return 1+compteNoeudsT(a->fg)+compteNoeudsT(a->fd);
	}
	return 0;
}






//Fonctions AVL T2

pAVL_T2 creationAVL_T2(DataT v) {
	pAVL_T2 a = malloc(sizeof(AVL_T2));
	if (a == NULL) {
		printf("Erreur 8\n");
		exit(1);
	}
	a->ville = v;
	a->eq = 0;
	a->fg = NULL;
	a->fd = NULL;
	return a;
}

pAVL_T2 rg_T2(pAVL_T2 a) {
	if (a == NULL) {
		return a;
	}
	int eqa, eqp;
	pAVL_T2 pivot = a->fd;
	eqa = a->eq;
	eqp = pivot->eq;
	a->fd = pivot->fg;
	pivot->fg = a;
	a->eq = eqa - max(eqp, 0) - 1;
	pivot->eq = min(eqa - 2, min(eqa + eqp - 2, eqp - 1));
	return pivot;
}

pAVL_T2 rd_T2(pAVL_T2 a) {
	if (a == NULL) {
		return a;
	}
	int eqa, eqp;
	pAVL_T2 pivot = a->fg;
	a->fg = pivot->fd;
	pivot->fd = a;
	eqa = a->eq;
	eqp = pivot->eq;
	a->eq = eqa - min(eqp, 0) + 1;
	pivot->eq = max(eqa + 2, max(eqa + eqp + 2, eqp + 1));
	return pivot;
}

pAVL_T2 drg_T2(pAVL_T2 a) {
	if (a == NULL) {
		return a;
	}
	a->fd = rd_T2(a->fd);
	return rg_T2(a);
}

pAVL_T2 drd_T2(pAVL_T2 a) {
	if (a == NULL) {
		return a;
	}
	a->fg = rg_T2(a->fg);
	return rd_T2(a);
}

pAVL_T2 equilibrerAVL_T2(pAVL_T2 a) {
	if (a == NULL) {
		return a;
	}
	if (a->eq >= 2) {
		if (a->fd->eq >= 0) {
			return rg_T2(a);
		}
		else{
			return drg_T2(a);
		}
	}
	else if (a->eq <= -2) {
		if (a->fg->eq <= 0) {
			return rd_T2(a);
		}
		else {
			return drd_T2(a);
		}
	}
	return a;
}

pAVL_T2 ajouterAVL_T2(pAVL_T2 a, DataT villeAjt, int *h) {cteurs ayant réalisé le plus de trajets différents. - d2 : crée un graphique des conducteurs ayant parcouru la plus grande distance totale au cours des trajets. - l : crée un graphique des 10 trajets dont la distance totale est la plus l
	if (a == NULL) {
		*h = 1;
		a = creationAVL_T2(villeAjt);
		return a;
	}
	//ATTENTION : On traite aussi le cas ou les villes ont le meme nom, c'est à dire si strcmp == 0 (impossible mais on sait jamais)
	if(strcmp(villeAjt.nomVille,a->ville.nomVille)>=0){
		a->fg = ajouterAVL_T2(a->fg, villeAjt, h);
		*h = -*h;
	}
	else if (strcmp(villeAjt.nomVille,a->ville.nomVille)<0) {
		a->fd = ajouterAVL_T2(a->fd, villeAjt, h);
	}
	else {
		*h = 0;
		return a;
	}
	if (*h != 0) {
		a->eq = a->eq + *h;
		a = equilibrerAVL_T2(a);
		if (a->eq == 0) {
			*h = 0;
		}
		else {
			*h = 1;
		}
	}
	return a;
}


//Transfert les c premiers noeuds de AVL T1 dans AVL T2, on fait un parcours infixe inversé et si c>0 on ajoute la ville de ce noeud dans AVL T2
pAVL_T2 transfertAVL2(pAVL_T a, pAVL_T2 b, int* c){
	if(a!=NULL){
		b = transfertAVL2(a->fd,b,c);
		//Si c>0 on ajoute la ville de ce noeud dans l'AVL T2
		if(*c>0){
			int h=0;
			b = ajouterAVL_T2(b,a->ville,&h);
			(*c)--;
		}
		b = transfertAVL2(a->fg,b,c);
	}
	return b;
}

//Copie le top 10 dans un fichier txt, on fait un parcours infixe inversé et à l'aide de concatenerDonneesT on copie les infos dans le fichier destination
void envoieTop10(pAVL_T2 a, FILE* destination){
	if(a!=NULL){
		envoieTop10(a->fd,destination);
		//On créer la ligne qu'il faut envoyer avec concatenerDonneesT et ...
		char* ligne=concatenerDonneesT(a->ville.nomVille, a->ville.nbVisite, a->ville.nbDepart);
		//... on les copie dans le fichier destination (et on oublie pas de free la ligne)
		fputs(ligne,destination);
		free(ligne);
		envoieTop10(a->fg,destination);
	}
}




//Fonctions qui liberent la memoire des noeuds de AVL T1 et AVL T2 (tout simplement des parcours postfixe ou on libère les 2 fils et ensuite on libère la racine)

void libererMemoireAVLT1(pAVL_T a) {
	if (a != NULL) {
		libererMemoireAVLT1(a->fg);
		libererMemoireAVLT1(a->fd);
		free(a);
	}
}

void libererMemoireAVLT2(pAVL_T2 a) {
	if (a != NULL) {
		libererMemoireAVLT2(a->fg);
		libererMemoireAVLT2(a->fd);
		free(a);
	}
}



/*/Fonction principale du traitement T
1. On forme le 1er AVL qui sera la liste de toutes les villes triées par nombre de visite
2. On met dans un pointeur l'adresse du fichier ou on veut renvoyer les infos (dans notre cas on utilise le même fichier que le shell nous as envoyé pour éviter d'avoir a en recréer un)
3. On transfere les 10 premiers noeuds du 1er AVL dans le 2eme AVL qui lui est trié par ordre alphabétique
4. On copie les 10 valeurs du 2eme AVL dans le fichier traitementT.txt
5. On libère tous les noeuds des 2 AVL
/*/
void traitementT(){
	//1.
	pAVL_T pa = formeAVL_T();
	int nbNoeuds=compteNoeudsT(pa);
	if(nbNoeuds<10){
		printf("Erreur 19\nIl y a %d villes dans data.csv or ce traitement doit afficher les 10 villes les plus visitées.\n",nbNoeuds);
		exit(1);
	}
	//2.
	FILE* renvoie = ouvrirFichier("../temp/traitementT.txt","w");
	//3.
	//on met un compteur à 10 qui va permettre de transferer 10 valeur de l'AVL 1 dans l'AVL 2
	int ct10=10;
	pAVL_T2 pb=NULL;
	pb = transfertAVL2(pa,pb, &ct10);
	//4.
	envoieTop10(pb, renvoie);
	fclose(renvoie);
	//5.
	libererMemoireAVLT1(pa);
	libererMemoireAVLT2(pb);
}
