#ifndef FONCTIONS
#define FONCTIONS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


typedef struct dataT{
    char nomVille[100];
    int nbDepart;
}DataT;


typedef struct AVLville{
	DataT ville;

	int eq;
	struct AVLville* fg;
	struct AVLville* fd;
}AVLville;

typedef AVLville* pAVLville;



typedef struct AVLvisite{
	int nbVisite;
    pAVLville listeVille;

	int eq;
	struct AVLvisite* fg;
	struct AVLvisite* fd;
}AVLvisite;

typedef AVLvisite* pAVLvisite;












int min(int a,int b);

int max(int a,int b);

pAVLvisite creationAVL(int nb);

int filsGauche(pAVLvisite a);

int filsDroit(pAVLvisite a);

int equilibre(pAVLvisite a);

pAVLvisite recherche(pAVLvisite a,int e);

pAVLvisite RG(pAVLvisite a);

pAVLvisite RD(pAVLvisite a);

pAVLvisite DRG(pAVLvisite a);

pAVLvisite DRD(pAVLvisite a);

pAVLvisite equilibrerAVL(pAVLvisite a);

pAVLvisite insertAVL(pAVLvisite a, int e,int* h);

void parcoursInfixe(pAVLvisite a);

void parcoursPrefixe(pAVLvisite a);

#endif