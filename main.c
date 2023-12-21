#include "avl.h"

#define MAX_LINE_LENGTH 100







DataT creationT(char* nomVille){
    DataT n;
    strncpy(n.nom,nomVille);
    n.nbDepart=0;
    return n;
}


Chainon* avlVilleVisite(){
    Chainon* pliste=NULL;

    FILE *fichier1;
    fichier1 = fopen("texteT1.txt", "r");
    if(fichier1==NULL){
        printf("Erreur : impossible d ouvrir le fichier txt.");
        exit(1);
    }

    char ligne[100];
    char villeTemp[50];


    pAVLvisite a=NULL;

    while(fgets(ligne, MAX_LINE_LENGTH, fichier1) != NULL){
        villeTemp = strtok(ligne, ";");
        DataT v=creationT(villeTemp);
        pAVLville h;

        if(rechercheVilleVisite(a,villeTemp,&h)==0){
            if(recherche(a, 1)==0){
                insertAVL(a,1,v);
            }
            else{
                insertAVLat(a,1,v);
            }
        }
        else{
            v.nbDepart=h->ville.nbDepart+1;
            deleteAVLville();
        }
    }
    fclose(fichier1);



    FILE *fichier2;
    fichier2 = fopen("texteT2.txt", "r");
    if(fichier2==NULL){
        printf("Erreur : impossible d ouvrir le fichier txt.");
        exit(1);
    }

    while (fgets(ligne, MAX_LINE_LENGTH, fichier2) != NULL) {
        int count = 0;
        int i = 0;
        int start_pos = 0;
        int end_pos = 0;

        while (ligne[i] != '\0' && ligne[i] != '\n') {
            if (ligne[i] == ';') {
                count++;
                if (count == 3) {
                    start_pos = i + 1; // Position de départ de la quatrième donnée
                } else if (count == 4) {
                    end_pos = i; // Position de fin de la quatrième donnée
                    break;
                }
            }
            i++;
        }

        if (count >= 4) {
            strncpy(villeTemp, ligne + start_pos, end_pos - start_pos);
            villeTemp[end_pos - start_pos] = '\0'; // Assure la terminaison de la chaîne
            if(rechercheListe(villeTemp)==0){
                ajouteListe(villeTemp);
            }
            else{
                addNbvisite(villeTemp);
            }
        }
    }
    fclose(fichier2);
    return pListe;
}




int main(){
	return 0;
}