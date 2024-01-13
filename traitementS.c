#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))

//FONCTIONS UTILES

FILE* ouvrirFichier(char* nomFichier, char* mode) {
  FILE* fichier = fopen(nomFichier, mode);
  if(fichier==NULL){
    printf("Erreur de l'ouverture de %s\n", nomFichier);
    exit(1);
  }
  return fichier;
}




//STRUCTURES ET CONSTRUCTEURS

typedef struct dataS {
  int id;
  float moyenne;
  float mini;
  float maxi;
} DataS;

DataS creationDataS(int id, float mo, float mi, float ma) {
  DataS d;
  d.id = id;
  d.moyenne = mo;
  d.mini = mi;
  d.maxi = ma;
  return d;
}


typedef struct AVL_S {
  DataS ville;
  int eq;
  struct AVL_S *fg;
  struct AVL_S *fd;
} AVL_S;

typedef AVL_S *pAVL_S;

pAVL_S creationAVL_S(DataS v) {
  pAVL_S a = malloc(sizeof(AVL_S));
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
    } else {
      return drg_S(a);
    }
  } else if (a->eq <= -2) {
    if (a->fg->eq <= 0) {
      return rd_S(a);
    } else {
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
  //On traite le cas ou les max-mini sont égaux (très peu probable mais on sait jamais)
  if ((villeAjt.maxi-villeAjt.mini) < (a->ville.maxi-a->ville.mini) || (villeAjt.maxi-villeAjt.mini) == (a->ville.maxi-a->ville.mini)) {
    a->fg = ajouterAVL_S(a->fg, villeAjt, h);
    *h = -*h;
  } else if ((villeAjt.maxi-villeAjt.mini) > (a->ville.maxi-a->ville.mini)) {
    a->fd = ajouterAVL_S(a->fd, villeAjt, h);
  } else {
    *h = 0;
    return a;
  }
  if (*h != 0) {
    a->eq = a->eq + *h;
    a = equilibrerAVL_S(a);
    if (a->eq == 0) {
      *h = 0;
    } else {
      *h = 1;
    }
  }
  return a;
}




//FONCTION PRINCIPALE

pAVL_S formeAVL_S() {
  FILE *fichier1=ouvrirFichier("resultats.txt", "r");

  pAVL_S avlS = NULL;

  char ligne[100];

  int idTemp;
  float moyTemp;
  float minTemp;
  float maxTemp;


  while (fgets(ligne, 100, fichier1) != NULL) {
    char* token=strtok(ligne, ";");
    idTemp = atoi(token);

    token = strtok(NULL, ";");
    moyTemp = atof(token);

    token = strtok(NULL, ";");
    minTemp = atof(token);

    token = strtok(NULL, ";");
    maxTemp = atof(token);
    
    int h=0;
    avlS = ajouterAVL_S(avlS, creationDataS(idTemp, moyTemp, minTemp, maxTemp), &h);
  }
  fclose(fichier1);
  return avlS;
}




//FONCTIONS AFFICHAGE + MEMOIRE

void afficheTop50(pAVL_S a, int* c){
  if(a!=NULL){
    afficheTop50(a->fd,c);
    if(*c>0){
    printf("%d;%f;%f;%f\n",a->ville.id, a->ville.mini, a->ville.moyenne, a->ville.maxi);
      (*c)--;
    }
    afficheTop50(a->fg,c);
  }
}





void libererMemoireAVL(pAVL_S a) {
    if (a != NULL) {
        libererMemoireAVL(a->fg);
        libererMemoireAVL(a->fd);
        free(a);
    }
}

void traitementS(){
  pAVL_S pa = formeAVL_S();
  int c=50;
  afficheTop50(pa, &c);
  libererMemoireAVL(pa);
}




//MAIN

int main() {
  traitementS();
  return 0;
}
