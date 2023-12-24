#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
FONCTIONS UTILES  ↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
*/
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
/*
FIN FONCTIONS UTILES  ↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑
*/


/*
STRUCTURES ET CONSTRUCTEURS
*/

typedef struct dataT {
  char nomVille[100];
  int nbVisite;
  int nbDepart;
} DataT;


/*
Créer le DataT d'une ville. Si dep<0 alors on augmente juste nbVisite.
Si dep>0, dep correspond au nbDepart de la ville donc on augment aussi nbDepart
*/
DataT creationDataT(char *v, int dep) {
  DataT d;
  strcpy(d.nomVille, v);
  if(dep<0){
    d.nbDepart=0;  //Ici on peut mettre nbDepart à 0 car dans tout les cas le 2eme txt est traité après le premier, et si on est ici c'est que la ville n'a jamais été ville de départ dans le 1er txt
    d.nbVisite=-dep;
    return d;
  }
  d.nbVisite = dep;
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

pAVL_T creationAVL_T(char *v, int dep) {
  pAVL_T a = malloc(sizeof(AVL_T));
  if (a == NULL) {
    printf("Erreur 1\n");
    exit(1);
  }
  a->ville = creationDataT(v, dep);
  a->eq = 0;
  a->fg = NULL;
  a->fd = NULL;
  return a;
}


typedef struct AVL_T2 {
  DataT ville;
  int eq;
  struct AVL_T2 *fg;
  struct AVL_T2 *fd;
} AVL_T2;

typedef AVL_T2 *pAVL_T2;

pAVL_T2 creationAVL_T2(DataT ville2) {
  pAVL_T2 a = malloc(sizeof(AVL_T2));
  if (a == NULL) {
    printf("Erreur 404\n");
    exit(1);
  }
  a->ville = ville2;
  a->eq = 0;
  a->fg = NULL;
  a->fd = NULL;
  return a;
}




/*
FONCTIONS NECESSAIRES POUR GERER AVL_T  ↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
*/

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

pAVL_T ajouterAVL_T(pAVL_T a, char *villeAjt, int *h, int dep) {
  if (a == NULL) {
    *h = 1;
    a = creationAVL_T(villeAjt, dep);
    return a;
  }
  int cmp = compareStr(villeAjt, a->ville.nomVille);
  if (cmp < 0) {
    a->fg = ajouterAVL_T(a->fg, villeAjt, h, dep);
    *h = -*h;
  } else if (cmp > 0) {
    a->fd = ajouterAVL_T(a->fd, villeAjt, h, dep);
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
/*
FIN FONCTIONS NECESSAIRES POUR GERER AVL_T  ↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑
*/



/*
Recherche si une ville est dans le 1er AVL, si c'est le cas return un pointeur vers ce noeud de
l'AVL. Sinon return NULL (on peut donc identifier si une ville est dans l'AVL ou non,
et si elle l'est, on peut directement agir sur ce noeud.)
*/
pAVL_T rechercheVilleT(pAVL_T a, char *villeRech) {
  if (a == NULL) {
    return NULL;
  }
  int cmp = compareStr(villeRech, a->ville.nomVille);
  if (cmp == 0) {
    return a;
  } else if (cmp < 0) {
    return rechercheVilleT(a->fg, villeRech);
  } else if (cmp > 0) {
    return rechercheVilleT(a->fd, villeRech);
  }
}

/*
Fonction appellée pour chaque ligne des document txt. Va ajouter la ville dans l'AVL si elle
n'y est pas ou incrémenter son nbVisite si elle y est déjà.
*/
pAVL_T monterNbVisiteAVL_T(pAVL_T a, char *villeAjt, int dep) {
  pAVL_T temp = rechercheVilleT(a, villeAjt);
  if (temp != NULL) {
    if (dep < 0) {  //Si dep<0 la donnée provient du 2eme txt et on monte juste nbVisite
      temp->ville.nbVisite-=dep;
    }
    else {          //Sinon, la donnée provient du 1er txt et il faut aussi monter nbDepart
      temp->ville.nbVisite+=dep;
      temp->ville.nbDepart+=dep;
    }
  }
  else{  //Si la ville n'est pas dans l'AVL, on l'ajoute
    int h = 0;
    a = ajouterAVL_T(a, villeAjt, &h, dep);
  }
  return a;
}

/*
Cette fonction va former le 1er AVL dont chaque noeud va contenir les données d'une ville (une 
structure DataT) à savoir nbVisite, nbDepart et le nom de la ville. Il y a donc autant de noeud que de villes et les noeuds de l'AVL sont triés par rapport aux noms des villes.
On forme cet AVL en traitant 2 fichiers txt:
      -TownAstep1.txt
          chaque ligne est constitué d'une ville et d'un nombre. Le nombre correspond au nombre
          de fois que la ville est Town A et son stepId est 1. (c'est à dire nous savons pour
          toutes les villes combien de fois elles ont été ville de départ).
      -TownB.txt
          chaque ligne est aussi constitué d'une ville et d'un nombre. Le nombre correspond
          au nombre de fois que cette ville apparaît dans la colonne Town B peut importe son
          stepId. (c'est à dire nous savons pour chaque ville combien de fois elle est visité
          sans compter quand elle est ville de départ).
Pour chacune des 2 boucles ou on traite les fichiers txt, depTemp va stocker le nombre de la ligne
étudiée et on va changer son signe en fonction du fichier étudié pour que dans la fonction
monterNbVisiteAVL_T, nous puissions identifier si la donnée provient du 1er ou du 2eme fichier txt.
Cela permettra d'incrémenter nbVisite ET nbDepart si depTemp viens du 1er fichier, mais
d'incrémenter UNIQUEMENT nbVisite si depTemp viens du 2eme fichier.
*/
pAVL_T formeAVL_T() {
  FILE *fichier1=ouvrirFichier("Traitements/TownAstep1.txt", "r");

  pAVL_T avlT = NULL;
  char ligne[100];
  char villeLigne[50];
  int depTemp;

  
  while (fgets(ligne, 100, fichier1) != NULL) {
    sscanf(ligne, "%[^;];%d", villeLigne, &depTemp);
    avlT = monterNbVisiteAVL_T(avlT, villeLigne, depTemp);
  }
  fclose(fichier1);

  fichier1 = ouvrirFichier("Traitements/TOwnB.txt", "r");

  
  while(fgets(ligne, 100, fichier1) != NULL){
    sscanf(ligne, "%[^;];%d", villeLigne, &depTemp);
    avlT=monterNbVisiteAVL_T(avlT, villeLigne, -depTemp);
  }
  fclose(fichier1);
  return avlT;
}


/*
Fonction juste pour les tests (pas utile au fonctionnement du traitement T).
Renvoie la ville la plus visité du 1er AVL (car le 1er AVL est trié par rapport aux
noms des villes et pas par rapport à nbVisite).
*/
void trouverMaxAVL_T(pAVL_T a){
  if(a==NULL){
    printf("AVL vide\n");
    return;
  }
  while(a->fd!=NULL){
    a=a->fd;
  }
  printf("%s est visité %d fois dont %d en départ !!!!!!", a->ville.nomVille, a->ville.nbVisite, a->ville.nbDepart);
}








/*
FONCTIONS NECESSAIRE POUR GERER AVL_T2  ↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
*/
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
    } else {
      return drg_T2(a);
    }
  } else if (a->eq <= -2) {
    if (a->fg->eq <= 0) {
      return rd_T2(a);
    } else {
      return drd_T2(a);
    }
  }
  return a;
}

pAVL_T2 ajouterAVL_T2(pAVL_T2 a, DataT villeAjt, int *h) {
  if (a == NULL) {
    *h = 1;
    a = creationAVL_T2(villeAjt);
    return a;
  }
  //On traite le cas ou les nbVisite sont égaux
  if (villeAjt.nbVisite < a->ville.nbVisite || villeAjt.nbVisite==a->ville.nbVisite) {
    a->fg = ajouterAVL_T2(a->fg, villeAjt, h);
    *h = -*h;
  } else if (villeAjt.nbVisite > a->ville.nbVisite) {
    a->fd = ajouterAVL_T2(a->fd, villeAjt, h);
  } else {
    *h = 0;
    return a;
  }
  if (*h != 0) {
    a->eq = a->eq + *h;
    a = equilibrerAVL_T2(a);
    if (a->eq == 0) {
      *h = 0;
    } else {
      *h = 1;
    }
  }
  return a;
}
/*
FIN DES FONCTIONS NECESSAIRE POUR GERER AVL_T2  ↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑
*/

/*
Créer le 2eme AVL. Comme pour le 1er AVL, chaque noeud correspond à une ville mais cette fois
les noeuds sont triés par rapport à nbVisite (si il y a plusieurs memes nbVisite, les noeuds
sont triés par nom des villes).
Ajoute tous les noeuds du 1er AVL dans le 2eme.
*/
pAVL_T2 formeAVL_T2(pAVL_T2 a, pAVL_T b) {
  if (b != NULL) {
    int h=0;
    a=ajouterAVL_T2(a, b->ville,&h);
    a=formeAVL_T2(a, b->fg);
    a=formeAVL_T2(a, b->fd);
  }
  return a;
}



/*
Fais un parcours infixe inversé et parcours les 10 plus grands
noeuds du 2eme AVL (par rapport au nbVisite). Puis print les infos de ce noeud.
*/
void afficheTop10(pAVL_T2 a, int* c){
  if(a!=NULL){
    afficheTop10(a->fd,c);
    if(*c>0){
    printf("%s est visité %d fois dont %d fois en départ.\n",a->ville.nomVille, a->ville.nbVisite, a->ville.nbDepart);
      (*c)--;
    }
    afficheTop10(a->fg,c);
  }
}



int main() {
  pAVL_T pa = NULL;
  pa = formeAVL_T();
  pAVL_T2 pb=NULL;
  pb=formeAVL_T2(pb, pa);

  int c=10;
  afficheTop10(pb,&c);
  
  return 0;
}
