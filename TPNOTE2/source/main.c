#include "stdio.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "stdlib.h"
#include <regex.h> 
#include <dirent.h>
#include <string.h>
#include <libgen.h>
#define CHUNK 128 /* on lit 128 caractere à la fois */

/*
*
*la fonction cpi copier les contenu d src dans dest si src n'existe pas elle s'arrete
* sinnon si dest n'exite pas elle le cree puis remplit avec le src content ,
*.       sinnon dest existe elle l'ecrase
*/
void cpi(char *src,char *dest){
	char buf[CHUNK];//le buffer ou on lit les données
	size_t nread;//la taille du block retourné par nread
    int fileDescriptorSrc = open(src, O_RDONLY);
    int fileDescriptorDest= open(dest,O_CREAT|O_WRONLY);
	if(fileDescriptorSrc<0||fileDescriptorDest<0){
		printf("une erreur est survenue à l'ouverture du fichier source ou à la creation ou ouverture du fichier destination\n");
		exit(EXIT_FAILURE);
	}
	else{
		while((nread=read(fileDescriptorSrc,buf,CHUNK))>0){
	    write(fileDescriptorDest,buf,nread);
	    
	}

	}
	close(fileDescriptorSrc);
	close(fileDescriptorDest);
}

/*
*le fonction cpiMode permet de changer les mode st_mode du fichier dest à celui du fichier src
*
*/
void cpiMode(char *src,char *dest){
	struct stat srcState;
	stat(src,&srcState);
	chmod(dest,srcState.st_mode);
}

/*
*la fonction cpiMode fait le meme boulot que cpi sauf en conservant le mode
*
*/

void cpiFiable(char *src,char *dest){
       cpi(src,dest);
       cpiMode(src,dest);

}
/*
*la fonction construitpath c'est pour la construction du chemin complet d'un fichier  
*ou d'un reoertoire le delimiter par defaut est un "/" dir est le chemin donnée avec ou sans /
*file c'est le nom du fichier ou nom du repertoire à concatener
*/
char *constructPath(char *dir,char *file,char *delimiter){
	regex_t regex;
    regcomp (&regex, "/$", REG_EXTENDED);
    char *res=(char *)malloc(strlen(dir)+strlen(file)+1);
    strcpy(res,dir);
    if(regexec(&regex, dir, 0, NULL, 0)){
         return strcat(strcat(res,delimiter),file);
    }
    else{
    	
    	return strcat(res,file);
    }
	return NULL;


}
/*
*la fonction copie AllFiles permet de copier tous les fichier d'un repertoir source
*dirsrc supposé ne contient que des fichier vers un repertoir destination dirdest
*le transfert de chaque fichier se fait par appel à la fonction cpiFiable definie precedement
*/
void copieAllFiles(char *dirsrc,char *dirdest){
	  DIR *rep = opendir(dirsrc);
	  struct dirent *lecture;
	  while ((lecture = readdir (rep)))
	  {
	  	if(!strcmp(lecture->d_name,".") && !strcmp(lecture->d_name,"..")){
	  		char *src=constructPath(dirsrc,lecture->d_name,"/");
		  	char *dest=constructPath(dirdest,lecture->d_name,"/");
		  	printf("%s\n",src );
		  	printf("%s\n",dest );
		    cpiFiable(src,dest);
	  	}
}
}



/*
*la fonction copieContenuRecursif permet de copier recursivement le contenu d'un repertoire source dirsrc
*vers un repertoire destination dirdest pour les fichier il seront copier en appelant la fonction cpiFiable
*et pour les sous-repertoires il sont à leurs tours recopiés recursivement toute en gardant les noms et 
*les mode st_mode
*/

void copieContenuRecursif(char *dirsrc,char *dirdest){
DIR *rep = opendir(dirsrc);
struct dirent *lecture;
	  while ((lecture = readdir (rep)))
	  {
	  	if(!(strcmp(lecture->d_name,".")==0) && !(strcmp(lecture->d_name,"..")==0)){
	  		char *src=constructPath(dirsrc,lecture->d_name,"/");
		  	char *dest=constructPath(dirdest,lecture->d_name,"/");
		  	struct stat st;
            stat(src,&st);
            
            if(lecture->d_type==DT_DIR)//oubien if((st.st_mode & S_IFMT)==S_IFDIR)
            {
            	mkdir(dest,st.st_mode);
            	copieContenuRecursif(src,dest);
            }
            else{
            	cpiFiable(src,dest);
            }
		    
	  	}

}
}
/*
*cette fonction inclut 3 fonctionnalité 
*1-copier un fichier dans un fichier tout en utilisant cpiFiable definie dessous
*2-copier un fichier dans un repertoire en gardant le nom et le st_mode(droits d'acces)
*si le fichier existe il sera ecraser sinnon créé
*3-copier un repertoire(pas seulement le contenu)dans un autre repertoire
****les deux paramettre fournis sont les paths des deux entités (fichier ou repertoire)
*remarque la fonction genere une erreur si la source est un repertoire et la destination est un fichier
*car c'est paratiquement impossible
*/
//copier un fichier vers un repertoire
void copierVers(char *src,char *dest){
    struct stat stsrc;
    stat(src,&stsrc);
    struct stat stdest;
    stat(dest,&stdest);
    char *copyTo=constructPath(dest,basename(src),"/");

    switch(stsrc.st_mode & S_IFMT){
    	case S_IFDIR:
    	   switch(stdest.st_mode & S_IFMT){
    	   	case S_IFDIR:
    	   	//la source est un repertoire aussi la destination
                  
                  mkdir(copyTo,stsrc.st_mode);
                  copieContenuRecursif(src,copyTo);
                  printf("copie du repertoire%s dans le repertiore%s réussite\n",src,dest );
                  free(copyTo);
                  break;
            default:
            //la source est un repertoire la destination est un fichier
                   printf("ERROR :vous vouler copier un contenu d'un repertoire dans un fichier\n");
                   free(copyTo);
                   exit(EXIT_FAILURE);
                   break;

    	   }
    	   break;
    	default:
    	   switch(stdest.st_mode & S_IFMT){
    	   	   case S_IFDIR:
    	   	   //la source est un fichier la destination est un repertoir
    	   	   //si un fichier portant le meme nom existe dans le repertoire de dstination 
    	   	   //il sera ecrasé

                    cpiFiable(src,copyTo);
                    printf("copie du fichier %s le repertoire %s réussite\n",src,dest );
                    free(copyTo);
                    break;
               default:
               //les deux sont fichier dans ce cas là le contenu du fichier dest sera ecraser
               //et si il n'esiste pas il sera créé puis remplit avec le contenu du fichier source
                    cpiFiable(src,dest);
                    printf("copie du fichier %s dans le fichier %s réussite\n",src ,dest);
                    free(copyTo);
                    break;
    	   	     
    	   }
    	   break;

    }
}

void test(){
	printf("nous avons dejas construit l'arborescence suivante\n");
	system("tree");
	printf("copier un fichier dans un dossier le fichier n'existe pas avant\n");
	//*1-fichier vers un fichier vers un repertoire
	//le resultats est qu'une copie du fichier nomé file.txt sera créé dans le repertoire dest avec file.txt
	//comme nom 
    char *src="src/file.txt";
    char *dest="dest/";
    copierVers(src,dest);
    system("tree");
    printf("on remarque la creation du fichier file.txt dans le repertoir dest\n");
    

    //*2-copier d'un fichier dans un autre avec le nom du fichier fournie
    printf("********copie d'un fichier dans un autre\n");
    src="src/file.txt";
    dest="dest/filecopie.txt";//le fichier aura comme nom filecopie.txt
    copierVers(src,dest);
    system("tree");
    printf("on remarque la creation du fichier filecopie.txt dans le repertoir dest\n");


    //*3-copier un repertoir dans un autre
    src="src";
    dest="dest";
    copierVers(src,dest);
    system("tree");
    printf("observant que le repertoire src ainsi son contenue dont injecter dans le repertoir dest\n");

    //*4- on essaie de copier un repertoire dans fichier cela est imposibele un msg d'erreur est affiche
    src="src";
    dest="src/file.txt";
    copierVers(src,dest);
    system("tree");
    printf("observons que rien n'a changé dan l'arborescence\n");
}


int main(int argc, char const *argv[])
{
if(argv[1]!=NULL && argv[2]!=NULL) {
	char *src=(char *)malloc(strlen(argv[1]));
    char *dest=(char *)malloc(strlen(argv[2]));
    strcpy(src,argv[1]);
    strcpy(dest,argv[2]);
	copierVers(src,dest);
	free(src);
	free(dest);
}

else{
	printf("la syntaxe est fausse\n le programme %s à la syntaxe suivante\n%s path_source path_dest",argv[0],argv[0]);
}
return 0;
}




