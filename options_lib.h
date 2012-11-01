/* 
 * File:   options_lib.h
 * Author: arnaud  tim 
 *
 * Created on November 1, 2012, 3:48 PM
 */

#include "log.h"
#include "file_headers.h"

#ifndef OPTIONS_LIB_H
#define	OPTIONS_LIB_H

#ifdef	__cplusplus
extern "C" {
#endif
    

    

/**
 * check if two file_path/file_name are identifical
 */
int comparePath(char* path1, char* path2) ;


/**
 * If -l is chosen then the largest file will be copied to the output directory
 */
void compareFileSize (struct stat file1, struct stat file2) ;
// If -m is chosen then the file with the most-recent modification-time should be copied to the output directory
void  compareModificationSize (struct stat file1, struct stat file2  );
// If -v then enable verbose, and report (to stdout) the full pathname of each file being copied to the output directory
void verbose () ;
// If -i then a subdirectory's name contains the indicated pattern, then it should be ignored.
void pattern ( ) ;





#ifdef	__cplusplus
}
#endif

#endif	/* OPTIONS_LIB_H */

