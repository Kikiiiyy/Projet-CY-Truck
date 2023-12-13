#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100


typedef struct dataT{
    char* nom;
    int nbVisite;
}DataT;

DataT* creationT(){
    DataT* n=malloc(sizeof(DataT));
    if(n==NULL){
        printf("Erreur 1");
        exit(1);
    }
    n->nom=(char*)malloc(sizeof(char)*100);
    if(n->nom==NULL){
    	printf("Erreur 2");
    	exit(1);
    }
    n->nbVisite=0;
    return n;
}


DataT* recupData(char* villeRecherche){
    FILE *fichier;
    fichier = fopen("traitementT.txt", "r");
    if(fichier==NULL){
        printf("Erreur : impossible d ouvrir le fichier txt.");
        exit(1);
    }
    DataT* v=creationT();
    char ligne[100];
    char villeA[50];
    char villeB[50];
    int idEtape;

    while(fgets(ligne, MAX_LINE_LENGTH, fichier) != NULL){
    	/*/
    	jsp pourquoi ca marche quand ya		villeA;villeB;idEtape
    	mais pas
    						idEtape;villeA,villeB
    	/*/
        sscanf(ligne, "%d;%49[^;];%49[^;\n]", &idEtape, villeA, villeB);

        if(strcmp(villeRecherche, villeA)==0 && idEtape==1){
             v->nbVisite++;
        }
        if(strcmp(villeRecherche, villeB)==0){
            v->nbVisite++;
        }
    }
    
    
    fclose(fichier);
    return v;
}


pArbre ajtArbre(){
    char* ville;
    ville = (char *)malloc(sizeof(char) * 100);



    while(fgets(ligne, sizeof(ligne), fichier) != NULL){
        #mettre la ville de la ligne dans la variable ville
        sscanf(ligne, "%*[^;];%*[^;];%[^;];", ville);

        if(rechercheAVL(avl, ville)!=1){
            dataT v = recupData(ville);
            if(rechercheMinAvl()<v.nbVisite){
                #ajouter dans avl v
            }
        }
    }
}



int main(){
	DataT* test=creationT();
	test=recupData("CESTAS");
	printf("%d\n", test->nbVisite);
	return 0;
}