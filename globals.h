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

    /*Default compare mode*/
    #define DEFAULT_COMPARE_MODE MODE_COMPARE_DATE

    #define DEFAULT_OPTION_STRING "lmvicvh?"

    #include "file_headers.h"
  
   
    /*Global arguments structure*/
    struct globalArgs_t {
        int compareMode;      /* -lmc option */
        int verbosity;              /* -v option */
        char *pattern;              /* -i option */
        
        char **inputDirs;          /* input files */
        int nbInputDirs;          /* # of input files */
        
        char *outDirName;    /* outdir.. */
        
    } globalArgs;
    
    /**
     * Inodes + filepath
     */
    struct fileInfos_t{
        ino_t fileInode;
        char * filePath;
    };
    
    /**
     * List of inodes + filepath
     */
    struct filesToMerge_t{
        ino_t *fileInode;
        char **filePath;
    };
    
    typedef struct fileInfos_t myFilesInfos;
    typedef struct filesToMerge_t myFilesToMerge;
   
    /*Global arrays of structs*/
    //files to copy
    myFilesInfos *filesToCopy;
    //files to merge
    myFilesToMerge *filesToMerge;
    //baseDirectory of the input directory currently being explored   
    char* currentDirectory ;
        
typedef struct compareFile{
	unsigned int st_ino;
	unsigned int st_size;
	unsigned int st_mtime;
}lcompareFile_t;


#ifdef	__cplusplus
}
#endif

#endif	/* GLOBALS_H */

