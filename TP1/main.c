/*******
*********   TP noté systeme d'exploitation
*********   Nom  :BAA
********    Prenom :Hamza
                          **********/
#include <stdlib.h>
#include <string.h>
#include <stdio.h> 

/*
1-le code ne marchera pas car en c on ne peut pas 
créer un tableau avec un taille variable 
(la taille qui est une variable) ;
la taille du tableau doit être définie au préalable , 
il existe un autre moyen de le faire en utilisant 
l’allocation dynamique via les fonction malloc ,calloc ou realloc 
ns la bibliothèque stdlib.h
*/

void liberer_tableau(int *tab){
	free(tab);
}


int *allouer_tableau(int dimension,int val) {

	int *tab=malloc(dimension*sizeof(int));
	for(int i=0;i<dimension;i++){
		tab[i]=val;
	}
	return tab;
}

void afficher_tableau(int *tab,int dimension){
	printf("|");
	for(int i = 0 ; i < dimension ; i++ )
	{
		printf(" %d |",*(tab+i));
		
	}
	printf("\n");
}

//test pour allouer_tableau()
void test_allouer_tableau(){

	printf("****  test allouer tablea de dimmension 10 valeur 3 :  ****\n");
	int taille=10;
	int val=3;
    int *tab=allouer_tableau(taille,3);
    afficher_tableau(tab,taille);
    liberer_tableau(tab);
}


int *lire_n_entier(int n){

	//on initialise le tableau de dimmension n à o
	int *tab=allouer_tableau(n,0);
	for (int i=0 ;i<n ;i++){

        	printf("veuillez saisir le %d  eme element(entier)\n",i+1 );
        	scanf("%d", (tab+i));
	}
	return tab;
}




void test_lire_n_entier(){

	printf("***  test lire n entier ici on a choisi n=5 : ***\n");
	//le nombre d'entier à lire ici on donne 5
	int n=5;
    int *tab=lire_n_entier(n);
    afficher_tableau(tab,n);
    liberer_tableau(tab);
}





//test pour afficher tableau
void test_afficher_tableau(){
	printf("*******   test de l'affichage d'un tableau : **********\n");
	int tab[7]={1,4,0,24,24,3,5};
	//on a la taille du tableau est 7
	int taille=7;
    afficher_tableau(tab,taille);
}

int *lire_entiers(void){
	int dimension=4;
	int *tab=allouer_tableau(dimension,sizeof(int));
	int plein=0;
	int stop=0;
	int cpt=0;
	while((cpt<dimension) && !plein && !stop){
        printf("veuiller saisir le prochain elt (entier) ou 0 pour arreter\n");
		scanf("%d",(tab+cpt));
		
		if(*(tab+cpt)!=0) {
		//le tableau est plein
			  cpt++;
		      if(cpt==dimension) plein=1;
        //
		      if(plein){
			//on alloue plus d espace
		      	        dimension=dimension*2;
			            tab=realloc(tab,dimension*sizeof(int));
			//on double la dimension
			            
			            plein=0;

		}
        }
        else {
			stop=1;
			cpt++;
		}
	}
	afficher_tableau(tab,cpt);
	return tab;
}

//test pour lire_entiers
 void test_lire_entiers(){
 	printf("**** test de lecture d'une serie d'entiers on s'arete quand on lit 0 : ***\n");
 	int *tab=lire_entiers();
 	liberer_tableau(tab);
 }

void afficher_matrice(int **matrice ,int lignes ,int colonnes){
	for (int i = 0; i < lignes; ++i)
	{
		/* code */
		printf("\n|");
		for (int j = 0; j < colonnes; ++j)
		{
			/* code */
			printf(" %d |",matrice[i][j] );
		}
		printf("\n");
	}
	
}

//allouer une matrice
int **allouer_matrice(int lignes, int colonnes ,int val){
	int **matrice=malloc(lignes*sizeof(int*));
	for(int i=0 ; i<lignes ;i++){
		matrice[i]=malloc(colonnes*sizeof(int));
				for (int j = 0; j < colonnes; ++j)
		{
			/* code */
			matrice[i][j]=val;
		}

	}
	return matrice;
}

void liberer_matrice(int **m, int ligne)
{
  for (int i=0; i<ligne; i++)
    free(m[i]);
  free(m);
}


//test pour allouer_matrice

void test_allouer_matrice(){
	printf("****   test de allouer matrice 4 lignes 5 colonnes valeur 7   ***\n");
	int lignes=4;
	int colonnes=5;
	int val=7;
	int **matrice=allouer_matrice(lignes,colonnes,val);
	afficher_matrice(matrice,lignes,colonnes);
	liberer_matrice(matrice,lignes);
}






/********************EXO 2****************************/

int *initialiser_tableau_v1(int n, int valeur,int *acc) {
	int len = 1;
	//int *tab = malloc(n*sizeof(int));
	tab[0]=valeur;
	while (2 * len <= n) {
		memcpy((tab+len),tab,len*sizeof(int));
		len=len*2;
	}
	//il se peut que des case restent à completer
	for (int i = len; i < n ; ++i)
	{
		/* code */
		tab[i]=valeur;
	}
	return tab;
}
//test initialiser_tableau_v

void test_initialiser_tableau_v(){

	printf("****  test initialiser un tableau de taille n avec un valeur v :  ***\n");
	//on initialise la dimension et la valeur
	int dim=20;
	int val=5;
	//on cree le tableau
	int *tab=initialiser_tableau_v1(dim,val);
	//on affiche le tableau
    afficher_tableau(tab,dim);
    //on libere la memoire
    liberer_tableau(tab);
}

char *initialiser_tableau_char(int dimension, char c){

	char *tab=(char *)malloc(dimension*sizeof(char));
	return memset(tab, c, dimension*sizeof(char));
}

void afficherChar(char *tab,int dimension){
	printf("|");
	for (int i = 0; i < dimension; ++i)
	{
		/* code */
		printf(" %c |",tab[i] );
	}
	printf("\n");
}

//test AfficherChar
void test_afficherChar(){
	printf("\n");
	printf("****   test pour afficherChar :   ****\n");
	char tab[7]={'H','a','m','z','a','8','2'};
	afficherChar(tab,7);
}

//test initialiser_tableau_char

void test_initialiser_tableau_char(){
	printf("***  test initialiser un tableau de caracteres avec la fonction memeset:\n");
	int dim=13;
	char c='h';
	char *tab=initialiser_tableau_char(dim,c);
	afficherChar(tab,dim);
	free(tab);
}

/*
*on utilise memmove parcequ on ne peut pas utiliser memcpy 
*car cette dernierre ne permet pas un chevauchement entre les deux zonnes
*or que nous dans notre cas les deux zonnes se chevauchent 
*vu que c est un deplacement d'une position de la zonne 
*vers une autre position dans elle meme
*/
void copier_chaine(char *tab, int s1, int taille, int s2){
      memmove(tab+s2,tab+s1,taille);
}



//test copier_chaine

void test_copier_chaine(){
	    char nom[]={'h','a','m','z','a'};
        copier_chaine(nom,2,3,5);
        //cela devra afficher hamzamza+un char qu'on ne sait pas
        afficherChar(nom,9);
}



int main(int argc, char *argv[]) { 
	   printf("********  code du TP noté 2019 BAA Hamza   ******\n");
       printf("c'est parti :\n");
	   test_afficher_tableau();
	   printf("\n");
	   test_allouer_tableau();
	   printf("\n");
	   test_lire_n_entier();
	   printf("\n");
	   test_lire_entiers();
	   printf("\n");
	   test_allouer_matrice();
	   printf("\n");
       test_afficherChar();
       printf("\n");
       test_initialiser_tableau_char();
       printf("\n");
       test_copier_chaine();
       printf("c'est fini  ! :\n");
       return 0;
}

