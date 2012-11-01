/* 
 * File:   merge_dir.h
 * Author: arnaudmoret
 *
 * Created on November 1, 2012, 4:22 PM
 */

#ifndef MERGE_DIR_H
#define	MERGE_DIR_H

#ifdef	__cplusplus
extern "C" {
#endif

    #include "globals.h"
    #include "sys_headers.h"
    #include "log.h"
    
    /*Main function of our program*/
    void mergeDirectories();
    /*Get the list of files to process*/
    void buildListOfInodesToCopy(char *dirName,int isNew);
    /*Place the file in the right array*/
    void placeFile(char *filePath,ino_t fileINode);
    
    


#ifdef	__cplusplus
}
#endif

#endif	/* MERGE_DIR_H */

