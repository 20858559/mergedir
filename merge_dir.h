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
    #include "general_lib.h"
    
    /*Main function of our program*/
    void mergeDirectories();
    /*Get the list of files to process*/
    void buildListOfInodesToCopy(char *dirName);
    /*Place the file in the right array*/
    int placeFile(char *filePath,char *baseDir,char *dirPath);
    /*Copy file info struct to array*/
    void copyInfoStructToArray(fileInfos_t f);
    /*Copy merge file struct to array and remove it from info array*/
    void copySingleMergeStructToArray(fileInfos_t f,fileInfos_t f_old);
    /**/
    void copyArrayMergeStructToArray(int i,fileInfos_t f);
    /**/
    void merge();
    /***/
    void copyFiles();


#ifdef	__cplusplus
}
#endif

#endif	/* MERGE_DIR_H */

