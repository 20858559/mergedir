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
        baseDirectory = globalArgs.inputDirs[i];
        buildListOfInodesToCopy(globalArgs.inputDirs[i]);
    }
    merge();
}

/**
 * Recursively traverse a directory
 * @param dirName the dirname
 * @param isNew false if first call true otherwise
 */
void buildListOfInodesToCopy(char* dirName){
    DIR* curDir = NULL;
    struct dirent *curEntry=NULL;
    char  curPath[PATH_MAX],*tmpPath=NULL;
    const char *d_name ;
    
    //open the directory
    curDir = opendir(dirName);

   
 
        
    //iterates
    while((curEntry = readdir(curDir))){
        //skip special files
        if(strcmp(curEntry->d_name,".") == 0  || strcmp(curEntry->d_name, ".." ) == 0){
            continue;
        }
        
        d_name = curEntry->d_name;
    
                
        //if directory..call itself
        if(  S_ISDIR(curEntry->d_type) ){
            int path_length;
            char path[PATH_MAX];
            //printf("%s",d_name);
            path_length = snprintf (path, PATH_MAX,"%s/%s", dirName, d_name);
            //call recursively
            buildListOfInodesToCopy(path);
            if (path_length >= PATH_MAX) {
                fprintf (stderr, "Maximum path length was exceeded.\n");
                exit (EXIT_FAILURE);
            }
        }
        else{

            //create our struct
            //printf ("File name %s Dirname %s\n", d_name,dirName);
            //create short path
            tmpPath = strtok(dirName,"/");
            strcpy(curPath,"");
            while(tmpPath!=NULL){
                if(strcmp(tmpPath,baseDirectory)!=0){
                    strcat(curPath,tmpPath);
                    strcat(curPath,"/");
                    
                }
                tmpPath = strtok( NULL, "/" );
            }
            //finally add the d name
            
            char dirPath[strlen(curPath)+1]; //use c99 VLAs
            strcpy(dirPath, curPath);
            //dirPath = strdup(curPath);
            //dirPath[strlen(dirPath)-1] = '\0';
            strcat(curPath,d_name);
            
            //check if we already have the file (=> merge list) or not (=>copy list)
            placeFile(curPath,baseDirectory,dirPath);
            //free(dirPath);
            
        }
        
       
                

    }
    
    
    //free(curPath);
    closedir (curDir);
    
}

int placeFile(char *filePath,char *baseDir, char *dirPath){
    //create our entry
    fileInfos_t tmpFileInfo;
    //to resize arrays
        
    
    tmpFileInfo.baseDir = malloc(strlen(baseDirectory)*sizeof(char));
    tmpFileInfo.filePath = malloc(strlen(filePath)*sizeof(char));
    tmpFileInfo.dirPath = malloc(strlen(dirPath)*sizeof(char));
    strcpy(tmpFileInfo.filePath,filePath);
    strcpy(tmpFileInfo.baseDir,baseDir);
    strcpy(tmpFileInfo.dirPath,dirPath);
    
    
    
    //
    
    //printf("\nProcessing: %s |%s \n",tmpFileInfo.filePath,tmpFileInfo.baseDir);
    
    //explore files to merge array first
    if(nbFilesToMerge >0 ){
        for(int i=0;i<nbFilesToMerge;++i){
            //add the new value into the array
            for(int j=0;j<myFilesToMerge[i].nbFiles;++j){
                if( strcmp(myFilesToMerge[i].files[j].filePath,tmpFileInfo.filePath) ==0){
                        //filepath equal => add to merge array
                        //printf("\n%s equals %s\n",myFilesToMerge[i].files[j].filePath,tmpFileInfo.filePath);
                        copyArrayMergeStructToArray(i,tmpFileInfo);
                        return TRUE;
                }
                
            }
            //puts("======= END OF PROCESSING MERGED");
            return TRUE;
        }
    }
    
    
    
    //if no files in files to copy just copy the file (initial)
    if( nbFilesToCopy == 0){
        myfilesToCopy = malloc(sizeof(fileInfos_t)*1);
        myfilesToCopy[nbFilesToCopy] = tmpFileInfo;
        nbFilesToCopy++;
        //printf("\nAdding #1: %s\n",tmpFileInfo.filePath);
        return TRUE;
    }
    else{
        
        
    
        //otherwise files to copy
        for(int i=0;i<nbFilesToCopy;++i){
            if( strcmp(myfilesToCopy[i].filePath,tmpFileInfo.filePath) ==0){
                //filepath equal => add to merge array
                //printf("\n%s equals %s\n",myfilesToCopy[i].filePath,tmpFileInfo.filePath);
                //add into the merge and remove copy entry
                copySingleMergeStructToArray(tmpFileInfo,myfilesToCopy[i]);
                //free(myfilesToCopy->filePath);
                memset( myfilesToCopy, '\0', sizeof( myfilesToCopy[i] ) );
 
                //puts("======= END OF PROCESSING");
                return TRUE;
            }
            else{
                //new file to copy
                copyInfoStructToArray(tmpFileInfo);
                //puts("======= END OF PROCESSING");
                return TRUE;
            }
                    
           
        }
    }
    
    
    return FALSE;
    
    
    
    
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
            
            //printf("\nAdding #3:  %s\n",myFilesToMerge[i].files[myFilesToMerge[i].nbFiles].filePath);
            myFilesToMerge[i].nbFiles++;
    }
    else{ 
        fprintf (stderr,"Error allocating memory! for result array\n");
        exit(EXIT_FAILURE);
    }
}


void merge(){
    for(int i=0;i<nbFilesToMerge;++i){
        
        //switch mode to execute
        switch(globalArgs.compareMode){
            case MODE_COMPARE_DATE:
                compareModificationDate(myFilesToMerge[i].files,myFilesToMerge[i].nbFiles);
                break;
            case MODE_COMPARE_SIZE:
                compareFileSize(myFilesToMerge[i].files,myFilesToMerge[i].nbFiles);
                break;
            case MODE_SHOW_CONFLICTS:
                break;
                        
            
        }
    }
    //dont copy if mode conflict
    if(globalArgs.compareMode != MODE_SHOW_CONFLICTS){
        copyFiles();
    }
    
}
/**
 * Just iterates over our array of files to copy
 */
void copyFiles(){
    for(int i=0;i<nbFilesToCopy;++i){
        //detect the null entries
        if(myfilesToCopy[i].filePath!=NULL){
            
            char* fullPath = malloc(strlen(myfilesToCopy[i].baseDir)+4+strlen(myfilesToCopy[i].filePath));
            int length = sprintf(fullPath,"./%s/%s",myfilesToCopy[i].baseDir,myfilesToCopy[i].filePath); 
            char* outputPath = malloc(strlen(globalArgs.outDirName)+1+strlen(myfilesToCopy[i].filePath));
            int length2 = sprintf(outputPath,"%s/%s",globalArgs.outDirName,myfilesToCopy[i].filePath);
            char* dirToCreate = malloc(strlen(globalArgs.outDirName)+1+strlen(myfilesToCopy[i].dirPath));
            int length3 = sprintf(dirToCreate,"%s/%s",globalArgs.outDirName,myfilesToCopy[i].dirPath);
            //printf("\nCopying %s into %s\n",fullPath,outputPath);
            if(globalArgs.verbosity == TRUE){
                //should check length..


                printf("\nCopying %s into %s\n",fullPath,outputPath);
                
            }
            
            //create folder if it does not exists
            if(strcmp(myfilesToCopy[i].dirPath,"") >0){
                printf("create dir %s",myfilesToCopy[i].dirPath);
                mkdirp(dirToCreate, 0751);
            }
            
            cp(outputPath,fullPath);
            
        }
    }
    
}