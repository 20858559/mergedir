/* 
 * File:   options_lib.h
 * Author: arnaud  tim 
 *
 * Created on November 1, 2012, 3:48 PM
 */



#ifndef OPTIONS_LIB_H
#define	OPTIONS_LIB_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include "file_headers.h"
#include "globals.h"
#include "sys_headers.h"
#include "general_lib.h"
    

/**
 * check if two file_path/file_name are identical
 */
int comparePath(char* path1, char* path2) ;


// If -l is chosen then the largest file will be copied to the output directory
void  compareModificationDate (fileInfos_t *files, int nbFiles  );
      
// If -m is chosen then the file with the most-recent modification-time should be copied to the output directory
void  compareFileSize (fileInfos_t *files, int nbFiles  );
    


// If -i then a subdirectory's name contains the indicated pattern, then it should be ignored.
void pattern ( ) ;

#ifdef	__cplusplus
}
#endif

#endif	/* OPTIONS_LIB_H */

