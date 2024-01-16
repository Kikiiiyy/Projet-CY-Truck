#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//FONCTIONS UTILES

char* concatenerDonnees(const char* chaine, int entier1, int entier2) {
    // Calculer la taille nécessaire pour la chaîne résultante
    int tailleResultat = snprintf(NULL, 0, "%s;%d;%d\n", chaine, entier1, entier2);

    // Allouer de la mémoire pour la chaîne résultante
    char* resultat = (char*)malloc(tailleResultat + 1);

    if (resultat == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire\n");
        exit(1);
    }

    // Utiliser snprintf pour concaténer les données avec un retour à la ligne
    snprintf(resultat, tailleResultat + 1, "%s;%d;%d\n", chaine, entier1, entier2);

    return resultat;
}


int compareStr(char *mot1, char *mot2) {
  return strcmp(mot1, mot2);
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

FILE* ouvrirFichier(char* nomFichier, char* mode) {
  FILE* fichier = fopen(nomFichier, mode);
  if(fichier==NULL){
    printf("Erreur de l'ouverture de %s\n", nomFichier);
    exit(1);
  }
  return fichier;
}




//STRUCTURES ET CONSTRUCTEURS

typedef struct dataT {
  char nomVille[100];
  int nbVisite;
  int nbDepart;
} DataT;

DataT creationDataT(char *v, int vis, int dep) {
  DataT d;
  strcpy(d.nomVille, v);
  d.nbVisite = vis;
  d.nbDepart = dep;
  return d;
}


typedef struct AVL_T {
  DataT ville;
  int eq;
  struct AVL_T *fg;
  struct AVL_T *fd;
} AVL_T;

typedef AVL_T *pAVL_T;

pAVL_T creationAVL_T(DataT v) {
  pAVL_T a = malloc(sizeof(AVL_T));
  if (a == NULL) {
    printf("Erreur 1\n");
    exit(1);
  }
  a->ville = v;
  a->eq = 0;
  a->fg = NULL;
  a->fd = NULL;
  return a;
}




//FONCTIONS AVL

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
    } else {
      return drg_T(a);
    }
  } else if (a->eq <= -2) {
    if (a->fg->eq <= 0) {
      return rd_T(a);
    } else {
      return drd_T(a);
    }
  }
  return a;
}

pAVL_T ajouterAVL_T(pAVL_T a, DataT villeAjt, int *h) {
  if (a == NULL) {
    *h = 1;
    a = creationAVL_T(villeAjt);
    return a;
  }
  //On traite le cas ou les nbVisite sont égaux
  if (villeAjt.nbVisite < a->ville.nbVisite || villeAjt.nbVisite==a->ville.nbVisite) {
    a->fg = ajouterAVL_T(a->fg, villeAjt, h);
    *h = -*h;
  } else if (villeAjt.nbVisite > a->ville.nbVisite) {
    a->fd = ajouterAVL_T(a->fd, villeAjt, h);
  } else {
    *h = 0;
    return a;
  }
  if (*h != 0) {
    a->eq = a->eq + *h;
    a = equilibrerAVL_T(a);
    if (a->eq == 0) {
      *h = 0;
    } else {
      *h = 1;
    }
  }
  return a;
}




//FONCTION PRINCIPALE

pAVL_T formeAVL_T() {
  FILE *fichier1=ouvrirFichier("traitementT.txt", "r");

  pAVL_T avlT = NULL;
  
  char ligne[100];
  
  char villeTemp[50];
  int visTemp;
  int depTemp;


  while (fgets(ligne, 100, fichier1) != NULL) {
    char* token=strtok(ligne, ";");
    strcpy(villeTemp, token);

    token = strtok(NULL, ";");
    visTemp = atoi(token);
    
    token = strtok(NULL, ";");
    if(token!=NULL){
      depTemp=atoi(token);
    }
    else{
      depTemp=0;
    }
    int h=0;
    avlT = ajouterAVL_T(avlT, creationDataT(villeTemp, visTemp, depTemp), &h);
  }
  fclose(fichier1);
  return avlT;
}




//FONCTIONS AFFICHAGE + MEMOIRE

void afficheTop10(pAVL_T a, int* c, FILE* file){
  if(a!=NULL){
    afficheTop10(a->fd,c,file);
    if(*c>0){
    char* ligne=concatenerDonnees(a->ville.nomVille, a->ville.nbVisite, a->ville.nbDepart);
    fputs(ligne,file);
    free(ligne);
      (*c)--;
    }
    afficheTop10(a->fg,c,file);
  }
}

void parcoursPrefixe(pAVL_T a){
  if(a!=NULL){
    printf("%s est visité %d fois dont %d départs`\n", a->ville.nomVille, a->ville.nbVisite, a->ville.nbDepart);
    parcoursPrefixe(a->fg);
    parcoursPrefixe(a->fd);
  }
}



int compteNoeud(pAVL_T a){
  if(a==NULL){
    return 0;
  }
  else{
    return 1+compteNoeud(a->fg)+compteNoeud(a->fd);
  }
}

void libererMemoireAVL(pAVL_T a) {
    if (a != NULL) {
        libererMemoireAVL(a->fg);
        libererMemoireAVL(a->fd);
        free(a);
    }
}

void traitementT(){
  pAVL_T pa = formeAVL_T();
  int c=10;
  FILE* renvoie = ouvrirFichier("traitementT.txt","w");
  afficheTop10(pa, &c, renvoie);
  fclose(renvoie);
  libererMemoireAVL(pa);
}




//MAIN

int main() {
  traitementT();
  return 0;
}
