/**
 * @file main.c
 * @brief Photo GPS, Geolocalized Photos header file. 
 * @author Adonias Vicente da Silva Barros, Enzo Belloto Furlan
 * @version 1.0
 * @date 26 avril 2017
 *
 * Photo GPS, Geolocalized Photos main function
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <libexif/exif-data.h>
#include "functions.h"


int main(int argc, char* argv[]) {
	if(argc<2){
		printf("EXIT: No file was provided\n");
		exit(1);
	}
	int n = 0, i=0, j=0, length;
	struct position images[MAXNUMBIMAGES]; // array of image informations
	DIR *dp = NULL; // directory 
	struct dirent *dptr = NULL; // informations about the directory
	char *buff = malloc (BUFF * sizeof(char)); // buffer
	char *buff2 = malloc (BUFF * sizeof(char)); // buffer  
	char ** directory = malloc(MAXNUMBIMAGES * sizeof(char*)); // array of file names
	for(i=0;i<MAXNUMBIMAGES;i++){ directory[i] = malloc (BUFF * sizeof(char)); }
	char ** exifs = malloc(MAXNUMBIMAGES * sizeof(char*)); // array of exif names
	for(i=0;i<MAXNUMBIMAGES;i++){ exifs[i] = malloc (BUFF * sizeof(char)); }
	
	
	printinformationapp(); // print informations about the app
	
    	system("mkdir kmzphotos");
    	system("mkdir kmzphotos/photos");
	memset(buff,0,sizeof(buff));
	//Copy the path set by the user
	strcpy(buff,argv[1]);
	//Open the directory stream
	if(NULL == (dp = opendir(argv[1])) )
    	{
		printf("ERROR 4: Cannot open Input directory [%s]\n",argv[1]);
		exit(1);
    	}
    	else{
    	    i=0, n=0;
    	    //read the directory contents
            while(NULL != (dptr = readdir(dp)) )
            {   // read only if the file ends with .jpg or .exif
                length = strlen(dptr->d_name);
                if(strncmp(dptr->d_name + length - 4, ".jpg", 4) == 0){
                    snprintf(buff,BUFF-1,"%s%s%s",argv[1],"/",dptr->d_name);
                    strcpy(directory[n],buff);
                    //resize image to a smaller size
                    printf("\n##################### Resizing  image ###########################\n");
		    printf("name image %s\n",dptr->d_name);
		    // resizes the image to a smaller size
		    snprintf(buff2,BUFF-1,"%s%s%s%s%s%s","convert ",argv[1],"/",dptr->d_name," -resize 200 kmzphotos/photos/",dptr->d_name);
		    system(buff2);
                    n++;
                }
                else if(strncmp(dptr->d_name + length - 5, ".exif", 5) == 0){
                    snprintf(buff,BUFF-1,"%s%s%s",argv[1],"/",dptr->d_name);
                    printf("\n##################### Exif file detected ########################\n");
                    printf("name exif %s\n",dptr->d_name);
                    strcpy(exifs[i],buff);
		    i++;
                }
            }
    	}
	
	for(j=0; j < i; j++){
		printf("\n################ Adding exif to the image #######################\n");
		addExif(exifs[j]); //add exif information in the image
	}
	
	printmarkplaceinicial();//print first part of the markplace
	for(i=0; i < n ; i++){
		printf("\n############ Getting information from image #####################\n");
		if(strncmp(directory[i] + strlen(directory[i]) - 4, ".jpg", 4) == 0){		
			images[i] = genLocation(directory[i]); //generates an exif.txt file with the image's information		
			printf("\n\nposition name %s\n\n",images[i].name);
		}
		
		if(images[i].init == 1){ // only print markplace if struct was initialized
			printmarkplace(images[i].name,images[i].longitude, images[i].latitude); // generates a .KML file (markplace)
		}
		else{
			printf("ERROR 3: Struct not initialized\n"); //when it is not possible to create the file
		}
	}
	printmarkplacefinal(); //print last part of the markplace
	
	//there is one error here, segmentation fault
	closedir(dp);
	printf("\n#################### Generating KMZ file ########################\n");
	system("mv info.kml kmzphotos/");
	system("zip -r kmzphotos.zip kmzphotos");
	system("mv kmzphotos.zip kmzphotos.kmz");	
	exit(0);
}
