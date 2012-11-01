#include "merge_dir.h"

/**
 * Main function, iterate over the repositories and copy the correct files
 */
void mergeDirectories(){
    //for each input directory
    for(int i=0;i<globalArgs.nbInputDirs;++i){
        //build our list of files to be copied/compared
        buildListOfInodesToCopy(globalArgs.inputDirs[i]);
    }
}


void buildListOfInodesToCopy(char* dirName){
    DIR* curDir = NULL;
    struct dirent *curEntry=NULL;
    char *baseDir, *curPath = NULL, *buff=NULL;
    int length=0;
    
    
    //open the directory
    curDir = opendir(dirName);
    //init path
    baseDir=malloc( (strlen(dirName) )* sizeof(char*));
    curPath=malloc( (strlen(dirName)+1 )* sizeof(char*));
    
    
    strcpy(baseDir,dirName);
    strcpy(curPath,dirName);
    
    //iterates
    while((curEntry = readdir(curDir))){
        //skip special files
        if(strcmp(curEntry->d_name,".") == 0  || strcmp(curEntry->d_name, ".." ) == 0){
            continue;
        }
        
        //check if the file already exists
        
        
        //build the new path       
        curPath = realloc(curPath, (strlen(curPath)+ strlen(curEntry->d_name) + 1) * sizeof(char)  );         
        strcpy(curPath,dirName);
        strcat(curPath,"/");
        strcat(curPath,curEntry->d_name);
        
        if(curEntry->d_type == DT_DIR ){
            buildListOfInodesToCopy(curPath);
        }
        
        
        printf("\nCurrent filename: %s",curPath);
        printf("\ninode: %lu",(unsigned long)curEntry->d_ino);
        

    }
    
    closedir (curDir);
    
}

void copyFiles(){
    
}