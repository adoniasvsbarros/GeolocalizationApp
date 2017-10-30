#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
/**
 * @file functions.h
 * @brief header file with declaration of all the functions
 * @author Adonias Vicente da Silva Barros, Enzo Belloto Furlan
 * @version 1.0
 * @date 26 avril 2017
 *
 * Header file with declaration of all the functions
 *
 */

#include "functions.c"

struct position;

/** 
 * Create the KML header part of the file 
 */
int printmarkplaceinicial();

/** Create the KML body file with latitude and longitude photo information
 * @param positionname
 * @param positionlongitude
 * @param positionlatitude
 * @return 0 if the info.kml file was created and -1 in error
 */
int printmarkplace(char* positionname, double positionlongitude, double positionlatitude);

/** 
 * Print the last part of a markplace
 */
int printmarkplacefinal();

/** 
 * Print general informations about the app
 */
void printinformationapp();

/** Convert GPS format hours,minutes and seconds to coordinate structure
 * @param buf
 * @return coordinate value 
 */
double convertGPScoord(char *buf);


/** Print informations about the app in an exif.txt
 * @param .jpg file
 * @return struct position from the photo given in file with values of latitude, longitude, name and initialization
 */
struct position genLocation(char *file);

/**
 * Print informationd about the app in an exif.txt from a .exif file
 * @param .exif file
 * @return struct position from the photo given in file with values of latitude, longitude, name and initialization
 *
 */
struct position genLocationFromExif(char *file);
 
/** 
 * Erase spaces inside the string given by buf
 * @param buf
 */
 
static void trim_spaces(char *buf);

/**
 * Add exif information in the image which has no exif information
 * @param file
 */
void addExif(char *file);


#endif // FUNCTIONS_H_INCLUDED
