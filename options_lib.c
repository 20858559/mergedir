#include "options_lib.h"



    void compareModificationDate(fileInfos_t *files,int nbFiles){

        long maxModificationDate=0;
        int filePos=0;
        struct stat tmpStat;
        fileInfos_t *tmpInfos;
        
        //recreate full path
        
        
        for(int i=0;i<nbFiles;i++){
            char* fullPath = malloc(strlen(files[i].baseDir)+1+strlen(files[i].filePath));
            int length = sprintf(fullPath,"%s/%s",files[i].baseDir,files[i].filePath);            
            if(stat(fullPath,&tmpStat) < 0){
                printf("Error while stat");
                exit(EXIT_FAILURE);
            }
            else{
                printf("Stat ok");
            }
        
             
            if (tmpStat.st_mtime > maxModificationDate ){
                maxModificationDate = tmpStat.st_mtime;
                filePos = i;
            }
        }
        
        printf("We chose the file %s",files[filePos].baseDir);
	//update the copy array
        copyInfoStructToArray(files[filePos]);
        
    }
    
    
    void compareFileSize(fileInfos_t *files,int nbFiles){

        off_t maxSize=0;
        int filePos=0;
        struct stat tmpStat;
        for(int i=0;i<nbFiles;i++){
            char* fullPath = malloc(strlen(files[i].baseDir)+1+strlen(files[i].filePath));
            int length = sprintf(fullPath,"%s/%s",files[i].baseDir,files[i].filePath);

            if(stat(fullPath,&tmpStat) == -1){
                exit(EXIT_FAILURE);
            }
            if (tmpStat.st_size > maxSize ){
                maxSize = tmpStat.st_size;
                filePos = i;
            }
        }
        
        printf("We chose the file %d",filePos);
		   
    }