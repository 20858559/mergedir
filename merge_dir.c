#include "merge_dir.h"

/**
 * Main function, iterate over the repositories and copy the correct files
 */
void mergeDirectories(){
    //init global counters
    
    nbFilesToCopy=0;
    nbFilesToMerge=0;
    
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
    char  *curPath = NULL;
    
    
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
            placeFile(curPath,curEntry->d_ino);
            
        }
        
       
                

    }
    
    
    free(curPath);
    closedir (curDir);
    
}

int placeFile(char *filePath,ino_t fileINode){
    //create our entry
    fileInfos_t tmpFileInfo;
    //to resize arrays
    
    filesToMerge_t *tmpMerge;
    
    
    tmpFileInfo.fileInode = fileINode;
    tmpFileInfo.filePath = malloc(strlen(filePath)*sizeof(char));
    strcpy(tmpFileInfo.filePath,filePath);
    
    printf("\nProcessing: %s |%lu \n",tmpFileInfo.filePath,(unsigned long)tmpFileInfo.fileInode);
    
    //explore files to merge array first
    if(nbFilesToMerge >0 ){
        for(int i=0;i<nbFilesToMerge;++i){
            //add the new value into the array
            for(int j=0;j<myFilesToMerge[i].nbFiles;++j){
                if( strcmp(myFilesToMerge[i].files[j].filePath,tmpFileInfo.filePath) ==0){
                        //filepath equal => add to merge array
                        printf("\n%s equals %s\n",myFilesToMerge[i].files[j].filePath,tmpFileInfo.filePath);
                        copyArrayMergeStructToArray(i,tmpFileInfo);
                        return TRUE;
                }
                
            }
            puts("======= END OF PROCESSING MERGED");
            return TRUE;
        }
    }
    
    
    
    //if no files in files to copy just copy the file (initial)
    if( nbFilesToCopy == 0){
        myfilesToCopy = malloc(sizeof(fileInfos_t)*1);
        myfilesToCopy[nbFilesToCopy] = tmpFileInfo;
        nbFilesToCopy++;
        printf("\nAdding #1: %s\n",tmpFileInfo.filePath);
        return TRUE;
    }
    else{
        
        
    
        //otherwise files to copy
        for(int i=0;i<nbFilesToCopy;++i){
            if( strcmp(myfilesToCopy[i].filePath,tmpFileInfo.filePath) ==0){
                //filepath equal => add to merge array
                printf("\n%s equals %s\n",myfilesToCopy[i].filePath,tmpFileInfo.filePath);
                //add into the merge and remove copy entry
                copySingleMergeStructToArray(tmpFileInfo,myfilesToCopy[i]);
                //free(myfilesToCopy->filePath);
                memset( myfilesToCopy, '\0', sizeof( myfilesToCopy[i] ) );
 
                puts("======= END OF PROCESSING");
                return TRUE;
            }
            else{
                //new file to copy
                copyInfoStructToArray(tmpFileInfo);
                puts("======= END OF PROCESSING");
                return TRUE;
            }
                    
           
        }
    }
    
    
    return FALSE;
    
    
    
    
}

void copyInfoStructToArray(fileInfos_t tmpFileInfo){
    fileInfos_t *tmpInfos;
    tmpInfos = (fileInfos_t*) realloc(myfilesToCopy, (nbFilesToCopy+1) * sizeof(fileInfos_t)  );
    if ( tmpInfos != NULL ){
            myfilesToCopy = tmpInfos;
            myfilesToCopy[nbFilesToCopy] = tmpFileInfo;
            printf("\nAdding #2:  %s\n",tmpFileInfo.filePath);
    }
    else{ 
        printf("Error allocating memory! for result array\n");
        exit(EXIT_FAILURE);
    }
    nbFilesToCopy++;
}

void copySingleMergeStructToArray(fileInfos_t tmpFileInfo,fileInfos_t tmpFileInfo_old){
    //init the new structure
    
    if(nbFilesToMerge == 0){
        myFilesToMerge = malloc(sizeof(filesToMerge_t) * 1);
        myFilesToMerge[0].nbFiles=2;
    }
    
    myFilesToMerge[nbFilesToMerge].files = malloc(sizeof(tmpFileInfo)+sizeof(tmpFileInfo_old)) ;
    myFilesToMerge[nbFilesToMerge].files[0] = tmpFileInfo;
    myFilesToMerge[nbFilesToMerge].files[1] = tmpFileInfo_old;
    nbFilesToMerge++;
    
}

void copyArrayMergeStructToArray(int i,fileInfos_t tmpFileInfo){
    fileInfos_t *tmpInfos;
    tmpInfos = (fileInfos_t*) realloc(myFilesToMerge[i].files, (myFilesToMerge[i].nbFiles+1) * sizeof(fileInfos_t)  );
    
    if ( tmpInfos != NULL ){
            myFilesToMerge[i].files = tmpInfos;
            myFilesToMerge[i].files[myFilesToMerge[i].nbFiles] = tmpFileInfo;
            
            printf("\nAdding #3:  %s\n",myFilesToMerge[i].files[myFilesToMerge[i].nbFiles].filePath);
            myFilesToMerge[i].nbFiles++;
    }
    else{ 
        printf("Error allocating memory! for result array\n");
        exit(EXIT_FAILURE);
    }
}


void copyFiles(){
    
}