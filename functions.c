/**
 * @file functions.c
 * @brief file with implementation of functions described in functions.h header file
 * @author Adonias Vicente da Silva Barros, Enzo Belloto Furlan
 * @version 1.0
 * @date 19 june 2017
 *
 * file with implementation of functions described in functions.h header file
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libexif/exif-data.h>
/**
 * @def SIZE 100
 * @def COMMANDLINESIZE 1000
 * @def MAXNUMBIMAGES 100
 * @def BUFF 1000

 */
#define SIZE 100
#define COMMANDLINESIZE 1000
#define MAXNUMBIMAGES 9999
#define BUFF 1000

/**
 * @struct struct position has informations about the image
 * 
 */
struct position{
	double latitude; /** latitude */
	double longitude; /** longitude */
	char name[SIZE]; /** name */
	int init; /** struct initialization */
};

/* Create the KML header part of the file */
int printmarkplaceinicial(){
		FILE* fp2;
		fp2 = fopen("info.kml","w");
		if(fp2 == NULL){
			perror("Error");
			return -1;
		}
		// printed part
		fprintf(fp2,"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
		"<kml xmlns=\"http://www.opengis.net/kml/2.2\">\n"
		"<Document>\n");

		fclose(fp2);
		return 0;
}

/* Create the KML body file with latitude and longitude photo information */
int printmarkplace(char* positionname, double positionlongitude, double positionlatitude){
		FILE* fp2;
		fp2 = fopen("info.kml","a");

		if(fp2 == NULL){
			perror("Error");
			return -1;
		}

		fprintf(fp2,"<Placemark>\n"
		"	<name>%s</name>\n"
		"	    <visibility>true</visibility>\n"
		"	    <description>&lt;html&gt;\n"
		"		&lt;body&gt;\n"
		"		&lt;img src='kmzphotos/%s' /&gt;\n"
		"		&lt;/body&gt;\n"
		"		&lt;/html&gt;</description>\n"
		"	    <Style>\n"
		"		<IconStyle>\n"
		"		    <scale>1.5</scale>\n"
		"		    <heading>0.0</heading>\n"
		"		</IconStyle>\n"
		"	    </Style>\n"
		"	<Point>\n"
		"		<coordinates>%lf,%lf,0</coordinates>\n"
		"	</Point>\n"
		"</Placemark>\n"
		,positionname,positionname,positionlongitude,positionlatitude);

		fclose(fp2);
		return 0;
}

/* Create the KML bottom part of the file */
int printmarkplacefinal(){
		FILE* fp2;
		fp2 = fopen("info.kml","a");
		if(fp2 == NULL){
			perror("Error");
			return -1;
		}
		// printed part
		fprintf(fp2,"</Document>\n"
		"</kml>");
		
		fclose(fp2);
		return 0;
}

/* Print informations about the app */
void printinformationapp(){
	printf("Photo GPS Application \n");

}

/* Remove spaces on the right of the string */
static void trim_spaces(char *buf)
{
    char *s = buf-1;
    for (; *buf; ++buf) {
        if (*buf != ' '){
            s = buf;
        }
    }
    *++s = 0; /* nul terminate the string on the first of the final spaces */
}

/* Convert GPS format hours,minutes and seconds to coordinate structure */
double convertGPScoord(char *buf){
	double hours=0,minutes=0,seconds=0;
	char dest[SIZE];
	char *s;
	int check=0;
	s = dest;
	while(*buf != '\0'){
		if(*buf == ','){
			*s = '\0';
			if(check==0) hours = atof(dest);
			if(check==1) minutes = atof(dest);
			s = NULL;
			s = dest;
			buf++;
			check = 1;
		}
		else if(*buf == ' '){
			buf++;
		}
		else{
			*s = *buf;
			buf++;s++;
		}
	}
	*s = '\0';
	seconds = atof(dest);
	return hours + (minutes/60) + (seconds/3600);
}

/* Show the tag name and contents if the tag exists */
static void show_tag(ExifData *d, ExifIfd ifd, ExifTag tag)
{
    char buf[1024];
    /* See if this tag exists */
    
    ExifEntry *entry = exif_content_get_entry(d->ifd[ifd],tag);
    if (entry) {
        /* Get the contents of the tag in human-readable form */
        exif_entry_get_value(entry, buf, sizeof(buf));

        /* Don't bother printing it if it's entirely blank */
        trim_spaces(buf);
        if (*buf) {
            printf("%s: %s\n", exif_tag_get_name_in_ifd(tag,ifd), buf);
        }
    }
}


/* Create a struct with photo informations: longitude, latitude, name, init*/
struct position genLocation(char *file)
{
    struct position position;
	
    ExifData *ed;
    ExifEntry *entry;
    char buf[BUFF];

    /* Load an ExifData object from an EXIF file */
    ed = exif_data_new_from_file(file);
    if (!ed) {
        printf("ERROR 5: File not readable or no EXIF data in file %s\n", file);
        position.init = 0;
        return position;
    }
    
    //Getting the latitude entry
    entry = exif_content_get_entry(ed->ifd[EXIF_IFD_GPS], EXIF_TAG_GPS_LATITUDE);
    if (entry) {
    	
        // Get the contents of the manufacturer tag as a string 
        if (exif_entry_get_value(entry, buf, sizeof(buf))) {
            trim_spaces(buf);
            position.latitude = convertGPScoord(buf);
            printf("File %s has valid latitude tag\n",file);	
        }
    }
    else{
    	printf("ERROR 1: File  %s has no latitude tag\n",file);
    	position.init = 0;
    	return position;
    }
    
    // Getting the longitude entry
    entry = exif_content_get_entry(ed->ifd[EXIF_IFD_GPS], EXIF_TAG_GPS_LONGITUDE);
    if (entry) {
        // Get the contents of the longitude tag as a string 
        if (exif_entry_get_value(entry, buf, sizeof(buf))) {
            trim_spaces(buf);
            position.longitude = convertGPScoord(buf);
            printf("File %s has valid longitude tag\n",file);
        }   
    }
    else{
    	printf("ERROR 2: File %s has no Longitude Tag\n",file);
    	position.init = 0;
    	return position;
    }
    strcpy(position.name,file);
    position.init = 1;
    return position;
}

/* Add exif information in the image which has no exif information*/
void addExif(char *file){
	char *buff2 = malloc (BUFF * sizeof(char));
	char *file2 = malloc(strlen(file) * sizeof(char));
	strcpy(file2,file);
	file2[strlen(file2) - 5] = 0;
	strcat(file2,".jpg");
	snprintf(buff2,BUFF-1,"%s%s%s%s","exiftool -tagsFromFile ",file," ",file2);
	printf("command %s\n",buff2);
	system(buff2);
}

