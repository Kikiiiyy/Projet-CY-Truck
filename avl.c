#include "avl.h"




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




pAVLville creationAVLville(DataT v){
//déclaration du Chainon
	pAVLville a = malloc(sizeof(AVLville));
	if(a==NULL){
		exit(1);
	}
	a->ville=v;
	a->fg=NULL;
	a->fd=NULL;
	a->eq=0;
	return a;
}

int filsGaucheVille(pAVLville a){
	if(a==NULL){
		return -1;
	}
	if(a->fg==NULL){
		return 0;
	}
	return 1; 
}

int filsDroitVille(pAVLville a){
	if(a==NULL){
		return -1;
	}
	if(a->fd==NULL){
		return 0;
	}
	return 1; 
}

int equilibreVille(pAVLville a){
	if(a==NULL){
		return 0;
	}
	if(a->eq<-1 || a->eq>1){
		return-1;
	}
	return 1+equilibreVille(a->fg)+equilibreVille(a->fd);
}

pAVLville rechercheVille(pAVLville a,char* e){
	if(a==NULL){
		return NULL;
	}
	else if(strcmp(a->ville.nomVille,e)==){     //verifier si c'est la meme string
		return a;
	}
	else if(strcmp(a->ville.nomVille,e)==){     //verifier si e est avant
		return recherche(a->fg,e);
	}
	else{
		return recherche(a->fd,e);
	}
}

pAVLville RGville(pAVLville a){
	if(a==NULL){
		return a;
	}
	int eqa,eqp;
	pArbre pivot=a->fd;
	a->fd=pivot->fg;
	pivot->fg=a;
	eqa=a->eq;
	eqp=pivot->eq;
	a->eq=eqa-min(eqp,0)+1;
	pivot->eq=max(eqa+2,max(eqa+eqp+2,eqp+1));
	return pivot;
}

pAVLville RDville(pAVLville a){
	if(a==NULL){
		return a;
	}
	int eqa,eqp;
	pArbre pivot=a->fg;
	a->fg=pivot->fd;
	pivot->fd=a;
	eqa=a->eq;
	eqp=pivot->eq;
	a->eq=eqa-min(eqp,0)+1;
	pivot->eq=max(eqa+2,max(eqa+eqp+2,eqp+1));
	return pivot;
}

pAVLville DRGville(pAVLville a){
	if(a==NULL){
		return a;
	}
	a->fd=RDville(a->fd);
	return RGville(a);
}

pAVLville DRDville(pAVLville a){
	if(a==NULL){
		return a;
	}
	a->fg=RGville(a->fg);
	return RDville(a);
}

pAVLville equilibrerAVLville(pAVLville a){
	if(a==NULL){
		return a;
	}
	if(a->eq>=2){
		if(a->fd->eq>=0){
			return RGville(a);
		}
		else{
			return DRGville(a);
		}
	}
	else if(a->eq<=-2){
		if(a->fg->eq<=0){
			return RDville(a);
		}
		else{
			return DRDville(a);
		}
	}
	return a;
}

pAVLville insertAVLville(pAVLville a, DataT e,int* h){
	pAVLville new = malloc(sizeof(AVLville));
	if(a==NULL){
		*h=1;
		a=creationAVLville(e);
		return a;
	}
	else if(strcmp(e.nomVille,a->DataT.nomVille)==){            //verifier si e est avant
		a->fg=insertAVLville(a->fg,e,h);
		*h=-*h;
	}
	else if(strcmp(e.nomVille,a->DataT.nomVille)==){            //verifier si e est apres
		a->fd=insertAVLville(a->fd,e,h);
	}
	else{
		*h=0;
		return a;
	}
	if(*h!=0){
		a->eq=a->eq+*h;
		a=equilibrerAVLville(a);
		if(a->eq==0){
			*h=0;
		}
		else{
			*h=1;
		}
	}
	return a;
}

void parcoursInfixeVille(pAVLville a){
	if(a!=NULL){
		parcoursInfixeVille(a->fg);
		printf("%s e=%d \n",a->ville.nomVille,a->eq);
		parcoursInfixeVille(a->fd);
	}
}

void parcoursPrefixeVille(pAVLvisite a){
	if(a!=NULL){
		printf("%s e=%d \n",a->villz.nomVille,a->eq);
		parcoursPrefixeVille(a->fg);
		parcoursPrefixeVille(a->fd);
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




pAVLvisite creationAVL(int nb){
//déclaration du Chainon
	pAVLvisite a = malloc(sizeof(AVLvisite));
	if(a==NULL){
		exit(1);
	}
	a->nbVisite=nb;
	a->fg=NULL;
	a->fd=NULL;
	a->eq=0;
	return a;
}

int filsGauche(pAVLvisite a){
	if(a==NULL){
		return -1;
	}
	if(a->fg==NULL){
		return 0;
	}
	return 1; 
}

int filsDroit(pAVLvisite a){
	if(a==NULL){
		return -1;
	}
	if(a->fd==NULL){
		return 0;
	}
	return 1; 
}

int equilibre(pAVLvisite a){
	if(a==NULL){
		return 0;
	}
	if(a->eq<-1 || a->eq>1){
		return-1;
	}
	return 1+equilibre(a->fg)+equilibre(a->fd);
}

pAVLvisite recherche(pAVLvisite a,int e){
	if(a==NULL){
		return NULL;
	}
	else if(a->nbVisite==e){
		return a;
	}
	else if(e<a->nbVisite){
		return recherche(a->fg,e);
	}
	else{
		return recherche(a->fd,e);
	}
}

pAVLvisite rechercheVilleVisite(pAVLvisite a,char* e){
	if(a==NULL){
		return NULL;
	}
	else if(a->nbVisite==e){
		return rechercheVille(a->listeVille, e);
	}
	else if(e<a->nbVisite){
		return rechercheVilleVisite(a->fg,e);
	}
	else{
		return rechercheVilleVisite(a->fd,e);
	}
}


pAVLvisite RG(pAVLvisite a){
	if(a==NULL){
		return a;
	}
	int eqa,eqp;
	pArbre pivot=a->fd;
	a->fd=pivot->fg;
	pivot->fg=a;
	eqa=a->eq;
	eqp=pivot->eq;
	a->eq=eqa-min(eqp,0)+1;
	pivot->eq=max(eqa+2,max(eqa+eqp+2,eqp+1));
	return pivot;
}

pAVLvisite RD(pAVLvisite a){
	if(a==NULL){
		return a;
	}
	int eqa,eqp;
	pArbre pivot=a->fg;
	a->fg=pivot->fd;
	pivot->fd=a;
	eqa=a->eq;
	eqp=pivot->eq;
	a->eq=eqa-min(eqp,0)+1;
	pivot->eq=max(eqa+2,max(eqa+eqp+2,eqp+1));
	return pivot;
}

pAVLvisite DRG(pAVLvisite a){
	if(a==NULL){
		return a;
	}
	a->fd=RD(a->fd);
	return RG(a);
}

pAVLvisite DRD(pAVLvisite a){
	if(a==NULL){
		return a;
	}
	a->fg=RG(a->fg);
	return RD(a);
}

pAVLvisite equilibrerAVL(pAVLvisite a){
	if(a==NULL){
		return a;
	}
	if(a->eq>=2){
		if(a->fd->eq>=0){
			return RG(a);
		}
		else{
			return DRG(a);
		}
	}
	else if(a->eq<=-2){
		if(a->fg->eq<=0){
			return RD(a);
		}
		else{
			return DRD(a);
		}
	}
	return a;
}

pAVLvisite insertAVL(pAVLvisite a, int e,int* h){
	pAVLvisite new = malloc(sizeof(AVLvisite));
	if(a==NULL){
		*h=1;
		a=creationAVL(e);
		return a;
	}
	else if(e<a->nbVisite){
		a->fg=insertAVL(a->fg,e,h);
		*h=-*h;
	}
	else if(e>a->nbVisite){
		a->fd=insertAVL(a->fd,e,h);
	}
	else{
		*h=0;
		return a;
	}
	if(*h!=0){
		a->eq=a->eq+*h;
		a=equilibrerAVL(a);
		if(a->eq==0){
			*h=0;
		}
		else{
			*h=1;
		}
	}
	return a;
}

void parcoursInfixe(pAVLvisite a){
	if(a!=NULL){
		parcoursInfixe(a->fg);
		printf("%d e=%d \n",a->nbVisite,a->eq);
		parcoursInfixe(a->fd);
	}
}

void parcoursPrefixe(pAVLvisite a){
	if(a!=NULL){
		printf("%d e=%d \n",a->nbVisite,a->eq);
		parcoursPrefixe(a->fg);
		parcoursPrefixe(a->fd);
	}
}


int main(){
	int *h;
	h=malloc(sizeof(int));
	*h=0;
	pArbre a=NULL;
	a=insertAVL(a,10,h);
	a=insertAVL(a,5,h);
	a=insertAVL(a,6,h);
	a=insertAVL(a,13,h);
	a=insertAVL(a,1,h);
	a=insertAVL(a,19,h);
	a=insertAVL(a,33,h);
	printf("%d \n",equilibre(a));
	parcoursInfixe(a);
	return 0;
}







