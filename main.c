#include "fonctions.h"


int main(int argc, char *argv[]){
  char lettre=argv[1][0];
  switch(lettre){
    case 't':
      traitementT();
      break;
    case 's':
      traitementS();
      break;
  }
  return 0;
}
