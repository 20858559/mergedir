#include "merge_dir.h"

/**
 * Main function, iterate over the repositories and copy the correct files
 */
void mergeDirectories(){
    //for each input directory
    for(int i=0;i<globalArgs.nbInputDirs;++i){
        //build our list of files to be copied/compared
        currentDirectory = globalArgs.inputDirs[i];
        buildListOfInodesToCopy(globalArgs.inputDirs[i],FALSE);
    }
}

/**
 * Recursively traverse a directory
 * @param dirName the dirname
 * @param isNew false if first call true otherwise
 */
void buildListOfInodesToCopy(char* dirName,int isNew){
    DIR* curDir = NULL;
    struct dirent *curEntry=NULL;
    char *baseDir, *curPath = NULL;
    
    
    //open the directory
    curDir = opendir(dirName);
        
        
    //init path 
    if(isNew == TRUE){
        printf("%s",dirName);
        curPath=malloc( (strlen(dirName) )* sizeof(char*));
        strcpy(curPath,dirName);
    }
 
        
    //iterates
    while((curEntry = readdir(curDir))){
        //skip special files
        if(strcmp(curEntry->d_name,".") == 0  || strcmp(curEntry->d_name, ".." ) == 0){
            continue;
        }
                
        //build the new path 
        if(isNew == TRUE){
            //have to add base_dir 
            curPath = realloc(curPath, (strlen(curPath)+ strlen(curEntry->d_name) + 1) * sizeof(char)  );
            strcat(curPath,"/");
            strcat(curPath,curEntry->d_name);
        }
        else{
            //only the filename
            curPath = malloc( strlen(curEntry->d_name)   * sizeof(char)  );
            strcpy(curPath,curEntry->d_name);
        }
        
        //if directory..call itself
        if(curEntry->d_type == DT_DIR ){
            currentDirectory = realloc(currentDirectory, (strlen(currentDirectory)+ strlen(curEntry->d_name) + 1) * sizeof(char)  );
            strcat(currentDirectory,"/");
            strcat(currentDirectory,curEntry->d_name);
            buildListOfInodesToCopy(currentDirectory,TRUE);
        }
        else{
            //create our struct
            
            //check if we already have the file (=> merge list) or not (=>copy list)
            //placeFile(curPath,curEntry->d_ino);
            
        }
        
        
                

    }
    
    closedir (curDir);
    
}

void placeFile(char *filePath,ino_t fileINode){
    //first check if we have to merge
    
    if(filesToMerge != NULL){
        for(int i=0;i<sizeof(filesToMerge);++i){
            struct filesToMerge_t tmpFilesToMerge = filesToMerge[i];
        }
    }
}

void copyFiles(){
    
}