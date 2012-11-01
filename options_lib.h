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
 * check if two file_path/file_name are identical
 */
int comparePath(char* path1, char* path2) ;


// If -l is chosen then the largest file will be copied to the output directory
void compareFileSize (struct stat file1, struct stat file2) ;
      
// If -m is chosen then the file with the most-recent modification-time should be copied to the output directory
// must change struct to array to allow for n files to compare
void  compareModificationSize (struct stat file1, struct stat file2  );
    
    modificationSize = malloc(nbFiles*sizeof(compareModi_t));
    
    struct stat compareFile;
    for(int i=0;i<nbfiles;i++){
    unsigned int st_ino=0 ,st_mtime=0;
    if ( stat(file_name, &compareFile) != 0 ) return(0);
        return( compareFile.st_size );
    else {
         for(int j=0;j<results;j++){      
		//calc modification time of each file in 
		modiSize1 = (stat ()); st_mtime; += modiSize1;
		modiSize2 = (stat ()); st_mtime; += modiSize2;
                //calculate newest file
               
                diff = modiSize1 - modiSize2;
			if(diff>0){
                                    
                        filetocopy = modifile2     
                        }
			}
			else if(diff <0){
                                    
                        filetocopy = modifile1
				
                                
			}
			else{ 
			//files are the same just copy first file
                        filetocopy = modifile1
			}
		
        
    };




// If -v then enable verbose, and report (to stdout) the full pathname of each file being copied to the output directory
void verbose () ;

// If -i then a subdirectory's name contains the indicated pattern, then it should be ignored.
void pattern ( ) ;

#ifdef	__cplusplus
}
#endif

#endif	/* OPTIONS_LIB_H */

