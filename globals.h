/* 
 * File:   globals.h
 * Author: arnaud  tim 
 *
 * Created on November 1, 2012, 3:47 PM
 */

#ifndef GLOBALS_H
#define	GLOBALS_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    /*Boolean types*/
    #define TRUE 1
    #define FALSE 0

    /*Exclusive mode types*/
    #define MODE_COMPARE_DATE 0
    #define MODE_COMPARE_SIZE 1 
    #define MODE_SHOW_CONFLICTS 2

    /*MaX path size*/
    #define PATH_MAX 255

    /*Default compare mode*/
    #define DEFAULT_COMPARE_MODE MODE_COMPARE_DATE

    #define DEFAULT_OPTION_STRING "lmvicvh?"

    #include "file_headers.h"
  
   
    /*Global arguments structure*/
    struct globalArgs_t {
        int compareMode;      /* -lmc option */
        int verbosity;              /* -v option */
        char *pattern;              /* -i option */
        int ignore;
        
        char **inputDirs;          /* input files */
        int nbInputDirs;          /* # of input files */
        
        char *outDirName;    /* outdir.. */
        
    } globalArgs;
    
    /**
     * basedir + short filepath
     */
    typedef struct fileInfos {
        char* baseDir;
        char* filePath;
        char* dirPath;
    }fileInfos_t;
    
    /**
     * List of inodes + filepath
     */
    typedef struct filesToMerge{
        fileInfos_t* files;
        int nbFiles;
    }filesToMerge_t;
 
   
    /*Global arrays of structs*/
    //files to copy
    fileInfos_t *myfilesToCopy;
    int nbFilesToCopy;
    //files to merge
    filesToMerge_t* myFilesToMerge;
    int nbFilesToMerge;
    //baseDirectory and currentDirectory of the input directory currently being explored   
    char* currentDirectory ;
    char* baseDirectory ;
        
    //Compare File size for -l
     typedef struct compareFile{
	unsigned int st_ino;
	unsigned int st_size;
     }compareFile_t;

     


#ifdef	__cplusplus
}
#endif

#endif	/* GLOBALS_H */

