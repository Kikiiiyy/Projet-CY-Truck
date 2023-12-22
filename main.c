#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//renvoi 0 si les 2 mots sont les memes     negatif si mot1
int compareStr(char* mot1, char* mot2){
    return strcmp(mot1, mot2);
}

int min(int a,int b){
  if(a<=b){
    return a;
  }
  return b;
}

int max(int a,int b){
  if(a<=b){
    return b;
  }
  return a;
}





typedef struct dataT{
    char nomVille[100];
    int nbVisite;
    int nbDepart;
}DataT;


DataT creationDataT(char* v){
    DataT d;
    strcpy(d.nomVille, v);
    d.nbVisite=1;
    d.nbDepart=0;
    return d;
}


typedef struct AVL_T{
    DataT ville;
    int eq;
    struct AVL_T* fg;
    struct AVL_T* fd;
}AVL_T;

typedef AVL_T* pAVL_T;

void prefixe(pAVL_T a){
  if(a!=NULL){
    printf("%s e=%d \n",a->ville.nomVille);
    prefixe(a->fg);
    prefixe(a->fd);
  }

}

pAVL_T creationAVL_T(char* v){
    pAVL_T a=malloc(sizeof(AVL_T));
    if(a==NULL){
        printf("Erreur 1\n");
        exit(1);
    }
    a->ville=creationDataT(v);
    a->eq=0;
    a->fg=NULL;
    a->fd=NULL;
    return a;
}



pAVL_T rg_T(pAVL_T a){
  if(a==NULL){
    return a;
  }
  int eqa,eqp;
  pAVL_T pivot=a->fd;
  eqa=a->eq;
  eqp=pivot->eq;

  a->fd=pivot->fg;
  pivot->fg=a;

  a->eq=eqa-max(eqp,0)-1;
  pivot->eq=min(eqa-2,min(eqa+eqp-2,eqp-1));
  return pivot;
}

pAVL_T rd_T(pAVL_T a){
  if(a==NULL){
    return a;
  }
  int eqa,eqp;
  pAVL_T pivot=a->fg;
  a->fg=pivot->fd;
  pivot->fd=a;
  eqa=a->eq;
  eqp=pivot->eq;
  a->eq=eqa-min(eqp,0)+1;
  pivot->eq=max(eqa+2,max(eqa+eqp+2,eqp+1));
  return pivot;
}

pAVL_T drg_T(pAVL_T a){
  if(a==NULL){
    return a;
  }
  a->fd=rd_T(a->fd);
  return rg_T(a);
}

pAVL_T drd_T(pAVL_T a){

  if(a==NULL){
    return a;
  }
  a->fg=rg_T(a->fg);
  return rd_T(a);
}




pAVL_T equilibrerAVL_T(pAVL_T a){
  if(a==NULL){
    return a;
  }
  if(a->eq>=2){
    if(a->fd->eq>=0){
      return rg_T(a);
    }
    else{
      return drg_T(a);
    }
  }
  else if(a->eq<=-2){
    if(a->fg->eq<=0){
      return rd_T(a);
    }
    else{
      return drd_T(a);
    }
  }
  return a;
}


pAVL_T ajouterAVL_T(pAVL_T a, char* villeAjt, int* h){
  if(a==NULL){
    *h=1;
    a=creationAVL_T(villeAjt);
    return a;
  }
    int cmp=compareStr(villeAjt, a->ville.nomVille);
  if(cmp<0){
    a->fg=ajouterAVL_T(a->fg, villeAjt, h);
    *h=-*h;
  }
  else if(cmp>0){
    a->fd=ajouterAVL_T(a->fd, villeAjt, h);
  }
  else{
    *h=0;
    return a;
  }
  if(*h!=0){
    a->eq=a->eq+*h;
    a=equilibrerAVL_T(a);
    if(a->eq==0){
      *h=0;
    }
    else{
      *h=1;
    }
  }
  return a;
}





pAVL_T rechercheVilleT(pAVL_T a, char* villeRech){
    if(a==NULL){
        return NULL;
    }
    int cmp=compareStr(villeRech, a->ville.nomVille);
    if(cmp==0){
        return a;
    }
    else if(cmp<0){
        return rechercheVilleT(a->fg, villeRech);
    }
    else if(cmp>0){
        return rechercheVilleT(a->fd, villeRech);
    }
}




pAVL_T monterNbVisiteAVL_T(pAVL_T a, char* villeAjt){
    pAVL_T temp=rechercheVilleT(a, villeAjt);
    if(temp!=NULL){
        temp->ville.nbVisite++;
    }
    else{
        int h=0;
        a=ajouterAVL_T(a, villeAjt,&h);
    }
    return a;
}


pAVL_T formeAVL_T(){
    FILE* fichier1;
    fichier1=fopen("traitement.txt", "r");
    if(fichier1==NULL){
        printf("Erreur 2\n");
        exit(1);
    }

    pAVL_T avlT=NULL;
    char villeLigne[50];
    while(fgets(villeLigne, 100, fichier1)!=NULL){
        //mettre la ville de "ligne" dans "villeLigne", voir avec Anthony ou sont les ";" et tout
        avlT=monterNbVisiteAVL_T(avlT, villeLigne);
    }
  return avlT;
}

void parcoursInfixeVille(pAVL_T a){
  if(a!=NULL){
    parcoursInfixeVille(a->fg);
    printf("%s est visité %d fois et e=%d \n",a->ville.nomVille,a->ville.nbVisite,a->eq);
    parcoursInfixeVille(a->fd);
  }
}




int main(){
  pAVL_T pa=NULL;
  /*
  int *h;
  h=malloc(sizeof(int));
  *h=0;
  pa=ajouterAVL_T(pa, "PARIS", h);
  pa=ajouterAVL_T(pa, "CERGY", h);
  pa=ajouterAVL_T(pa, "MARSEILLE", h);
pa=ajouterAVL_T(pa, "NANTES", h);
  
  pa=ajouterAVL_T(pa, "WOIPPY", h);
  pa=ajouterAVL_T(pa, "SARTROUVILLE", h);
  */
  pa=formeAVL_T();
 parcoursInfixeVille(pa);
 // prefixe(pa);
    return 0;
}


