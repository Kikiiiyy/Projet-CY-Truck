#include "fonctions.h"


int main(int argc, char *argv[]){
  (void)argc;
  char lettre=argv[1][0];
  if(lettre=='t' || lettre=='T'){
  	traitementT();
  }
  else if(lettre=='s' || lettre=='S'){
  	traitementS();
  }
  else{
  	printf("Erreur 1\n");
  	exit(1);
  }
  return 0;
}
