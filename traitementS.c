#include "fonctions.h"


//Fonctions utiles
FILE* ouvrirFichier(char* nomFichier, char* mode) {
  FILE* fichier = fopen(nomFichier, mode);
  if(fichier==NULL){
    printf("Erreur de l'ouverture de %s\n", nomFichier);
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

char* concatenerDonneesS(int entier1, int entier2, float float1, float float2, float float3) {
    // Calculer la taille nécessaire pour la chaîne résultante
    int tailleResultat = snprintf(NULL, 0, "%d;%d;%f;%f;%f\n", entier1, entier2, float1, float2, float3);

    // Allouer de la mémoire pour la chaîne résultante
    char* resultat = (char*)malloc(tailleResultat + 1);

    if (resultat == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire\n");
        exit(1);
    }

    // Utiliser snprintf pour concaténer les données avec un retour à la ligne
    snprintf(resultat, tailleResultat + 1, "%d;%d;%f;%f;%f\n", entier1, entier2, float1, float2, float3);

    return resultat;
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
    printf("Erreur 1\n");
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

//Fonction principale pour former l'AVL S
pAVL_S formeAVL_S() {
  FILE *fichier1=ouvrirFichier("../temp/traitementS.txt", "r");

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


//Fonction qui copie le top 50 dans un fichier txt

void envoieTop50(pAVL_S a, int* c, FILE* file){
  if(a!=NULL){
    envoieTop50(a->fd,c,file);
    if(*c>0){
    char* ligne=concatenerDonneesS(50-(*c),a->ville.id,a->ville.moyenne,a->ville.mini,a->ville.maxi);
    fputs(ligne,file);
    free(ligne);
      (*c)--;
    }
    envoieTop50(a->fg,c,file);
  }
}

//Fonction qui libere la memoire des noeuds de AVL S

void libererMemoireAVLS(pAVL_S a) {
    if (a != NULL) {
        libererMemoireAVLS(a->fg);
        libererMemoireAVLS(a->fd);
        free(a);
    }
}

//Fonction principale du traitement S

void traitementS(){
  pAVL_S pa = formeAVL_S();
  int c=50;
  FILE* renvoie=ouvrirFichier("../temp/traitementS.txt","w");
  envoieTop50(pa, &c,renvoie);
  fclose(renvoie);
  libererMemoireAVLS(pa);
}
