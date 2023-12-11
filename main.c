#include <stdio.h>
#include <stdlib.h>


typedef struct dataT{
    char nom;
    int nbVisite;
}DataT;

dataT creationT(){
    DataT n=malloc(sizeof(DataT));
    if(n==NULL){
        printf("Erreur zebi");
        exit(1);
    }
    n.nom="";
    n.nbVisite=0;
    return n;
}


dataD1 recupData(char villeRecherche){
    FILE *fichier;
    fichier = fopen("nom.txt", "r");
    if(fichier==NULL){
        printf("Erreur : impossible d ouvrir le fichier txt.");
        return 0;
    }
    DataT v=creationT();
    char ligne[100];
    char villeA[50];
    char villeB[50];
    int idEtape;

    while(fgets(ligne, sizeof(ligne), fichier) != NULL){
        sscanf(ligne, "%[^;];%[^;];%d", villeA, villeB, &idEtape);

        if(idEtape==1){
            if(strcmp(villeRecherche, villeA)==0){
                v.nbVisite++;
            }
        }
        if(strcmp(villeRecherche, villeB)==0){
            v.nbVisite++;
        }
    }
    return v;
}

pArbre ajtArbre(){
    while(fgets(ligne, sizeof(ligne), fichier) != NULL){
        #mettre la ville de la ligne dans la variable ville
        if(rechercheAVL(avl, ville)!=1){
            dataT v = recupData(ville);
            if(rechercheMinAvl()<v.nbVisite){
                #ajouter dans avl v
            }
        }
    }
}











int main(){
    return 0;
}