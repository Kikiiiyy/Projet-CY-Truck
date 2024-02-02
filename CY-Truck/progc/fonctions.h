#ifndef FONCTIONS
#define FONCTIONS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define LONGUEUR_LIGNE 100
#define LONGUEUR_VILLE 50


//fonctions communes aux 2 traitements

FILE* ouvrirFichier(char* nomFichier, char* mode);

int min(int a, int b);

int max(int a, int b);


//structures T

typedef struct dataT {
  char nomVille[100];
  int nbVisite;
  int nbDepart;
} DataT;

typedef struct AVL_T {
  DataT ville;
  int eq;
  struct AVL_T *fg;
  struct AVL_T *fd;
} AVL_T;

typedef AVL_T *pAVL_T;

typedef struct AVL_T2 {
  DataT ville;
  int eq;
  struct AVL_T2 *fg;
  struct AVL_T2 *fd;
} AVL_T2;

typedef AVL_T2 *pAVL_T2;


//fonctions T

char* concatenerDonneesT(char* mot, int nb1, int nb2);


DataT creationDataT(char *v, int vis, int dep);

pAVL_T creationAVL_T(DataT v);

pAVL_T rg_T(pAVL_T a);

pAVL_T rd_T(pAVL_T a);

pAVL_T drg_T(pAVL_T a);

pAVL_T drd_T(pAVL_T a);

pAVL_T equilibrerAVL_T(pAVL_T a);

pAVL_T ajouterAVL_T(pAVL_T a, DataT villeAjt, int *h);

pAVL_T formeAVL_T();

int compteNoeudsT(pAVL_T a);


pAVL_T2 creationAVL_T2(DataT v);

pAVL_T2 rg_T2(pAVL_T2 a);

pAVL_T2 rd_T2(pAVL_T2 a);

pAVL_T2 drg_T2(pAVL_T2 a);

pAVL_T2 drd_T2(pAVL_T2 a);

pAVL_T2 equilibrerAVL_T2(pAVL_T2 a);

pAVL_T2 ajouterAVL_T2(pAVL_T2 a, DataT villeAjt, int *h);

pAVL_T2 transfertAVL2(pAVL_T a, pAVL_T2 b, int* c);


void envoieTop10(pAVL_T2 a, FILE* file);

void libererMemoireAVLT1(pAVL_T a);

void libererMemoireAVLT2(pAVL_T2 a);

void traitementT();



//structures S

typedef struct dataS {
  int id;
  float moyenne;
  float mini;
  float maxi;
} DataS;

typedef struct AVL_S {
  DataS ville;
  int eq;
  struct AVL_S *fg;
  struct AVL_S *fd;
} AVL_S;

typedef AVL_S *pAVL_S;


//fonctions S

char* concatenerDonneesS(int nb1, int nb2, float fl1, float fl2, float fl3);


DataS creationDataS(int id, float mo, float mi, float ma);

pAVL_S creationAVL_S(DataS v);

pAVL_S rg_S(pAVL_S a);

pAVL_S rd_S(pAVL_S a);

pAVL_S drg_S(pAVL_S a);

pAVL_S drd_S(pAVL_S a);

pAVL_S equilibrerAVL_S(pAVL_S a);

pAVL_S ajouterAVL_S(pAVL_S a, DataS villeAjt, int *h);

pAVL_S formeAVL_S();

int compteNoeudsS(pAVL_S a);


void envoieTop50(pAVL_S a, int* c, FILE* file);

void libererMemoireAVLS(pAVL_S a);

void traitementS();

#endif
