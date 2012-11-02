/* 
 * File:   main.c
 * Author: arnaud tim
 *
 * Created on November 1, 2012, 3:46 PM
 */

/**
 * List of the project headers
 */
#include <string.h>

#include "sys_headers.h"
#include "globals.h"
#include "file_headers.h"
#include "general_lib.h"

/**
 * Configure the application mode
 * @param argc number of arguments
 * @param argv arguments
 */
void configureModes(int argc, char**argv);

/**
 * displayUsage .. dislay the usage of mergedir
 */
void displayUsage();
/**
 * Main function
 * @param argc
 * @param argv
 * @return 
 */

void print_debug();

/**
 * Main function
 */
int main(int argc, char** argv) {

    /*Initialize our application*/
    configureModes(argc,argv);
    mergeDirectories();
    
    
    //free globals
    //print debug
    
    //print_debug();
    free(myfilesToCopy);
    free(myFilesToMerge);
    
    return (EXIT_SUCCESS);
}


/**
 * Configure the application mode
 * @param argc number of arguments
 * @param argv arguments
 */

void configureModes(int argc, char**argv){
        /* variables for getopt*/
        int optionIndex=0;
        int hasExclusiveMode = FALSE;
        int nbDirs = 0;
        struct stat s;
                
        /*Init global struct with 0 values*/
        globalArgs.compareMode = DEFAULT_COMPARE_MODE;
        globalArgs.verbosity  = FALSE;
        globalArgs.pattern = NULL;
        globalArgs.inputDirs = NULL;
        globalArgs.nbInputDirs = 0;
        globalArgs.outDirName = NULL;

 
        /*Get the list of options*/
	while ((optionIndex = getopt (argc, argv, DEFAULT_OPTION_STRING)) != -1){
                switch (optionIndex){
                    
                    case 'l':
                        //assert only one of the exclusive modes
                        if(hasExclusiveMode == TRUE){
                            fprintf(stderr, "\n-l -m -c are mutually exclusive, please select only one option\n\n");
                            displayUsage();
                            exit(EXIT_FAILURE);
                        }
                        else{
                            globalArgs.compareMode = MODE_COMPARE_SIZE;
                            hasExclusiveMode = TRUE;
                        }
                        break;
                    case 'm':
                        //assert only one of the exclusive modes
                        if(hasExclusiveMode == TRUE){
                            fprintf(stderr, "\n-l -m -c are mutually exclusive, please select only one option\n\n");
                            displayUsage();
                            exit(EXIT_FAILURE);
                        }
                        else{
                            //default mode..this statement is not really needed
                            globalArgs.compareMode = MODE_COMPARE_DATE;
                            hasExclusiveMode = TRUE;
                        }
                                
                        break;
                    case 'v':
                        printf("-v option \n");
                        globalArgs.verbosity = TRUE;
                        break;
                    case 'i':
                        printf("-i option with value %s \n",optarg);
                        break;
                        //assert only one of the exclusive modes
                    case 'c':
                        //assert only one of the exclusive modes
                        if(hasExclusiveMode == TRUE){
                            fprintf(stderr, "\n-l -m -c are mutually exclusive, please select only one option\n\n");

                            displayUsage();
                            exit(EXIT_FAILURE);
                        }
                        else{
                            globalArgs.compareMode = MODE_SHOW_CONFLICTS;
                            hasExclusiveMode = TRUE;
                        }
                        
                        break;
                        
                    /*Unknown -> exit*/
                    case 'h':    
                    case '?':
                        displayUsage();       
                        exit(EXIT_FAILURE);
                    /*Should not ever reach that statement*/
                    default:
                        exit(EXIT_FAILURE);
                        break;
                    
     		}
                
            }
        
        /*Validate file input*/
        nbDirs = argc - optind;
        /*At least 2 directories*/
        if(nbDirs <2  ){
            fprintf(stderr, "\nminimum one input and one output directories\n\n");
            displayUsage();
        }
        
        /*we can allocate the memory for the input directories variable*/
        globalArgs.inputDirs = malloc( (argc-1) * sizeof(char*));
        
        /*Check that input directories are directory..*/
        for(int i=optind;i<argc-1;++i){
            
            if( stat(argv[i],&s) == 0 ){
                /*path does not exists*/
                if( !S_ISDIR(s.st_mode ) ){
                    /*Not a directory*/
                    free(globalArgs.inputDirs);
                    fprintf(stderr, "\n%s should be a directory\n\n",argv[i]);
                    displayUsage();
                    
                }
                else{
                    /*Add the directory*/
                    globalArgs.inputDirs[globalArgs.nbInputDirs] = malloc(strlen(argv[i])* sizeof(char*));
                    strcpy( globalArgs.inputDirs[globalArgs.nbInputDirs] , argv[i]);
                    globalArgs.nbInputDirs++;
                }
            }
            else{
                free(globalArgs.inputDirs);
                fprintf(stderr, "\n%s must be a directory\n\n",argv[i]);
                displayUsage();
            }
        }
        
                
        //get output directory
        globalArgs.outDirName = malloc(strlen(argv[argc-1])* sizeof(char*));
        strcpy(globalArgs.outDirName,argv[argc-1]);
        
        //if not new create it
        if( stat(argv[argc-1],&s) == 0 ){
            if( !S_ISDIR(s.st_mode ) ){
                //not a directory..error
                free(globalArgs.inputDirs);
                free(globalArgs.outDirName);
                fprintf(stderr, "\n%s must be \n\n",argv[argc-1]);
                displayUsage();
            }
        }
        else{
            //new
            mkdirp(globalArgs.outDirName, 0751);
        }
                
        
}


void displayUsage( ){
    puts( "mergedirs [options] indirectory1 [indirectory2 ....] outdirectory " );
    puts( "List of options: ");
    puts("-l: ");
    puts("-m: ");
    puts("-c: ");
    puts("-i: ");
    puts("-v: ");
    puts("-h: displays the usage ");
    puts("-?: displays the usage ");
    puts("-l -m and -c are mutually EXCLUSIVE. eg only one can be used at a time. ");
    puts("At least One input directory and one output directory are required.");
    puts("input directory MUST exists");
    puts("output directory may be created");
    
    exit( EXIT_FAILURE );
}



void print_debug(){
    printf("\n=====DEBUG OUTPUT OF FILES TO COPY====\n");
    if(nbFilesToCopy>0){
        for(int i=0;i<nbFilesToCopy;++i){
            printf("\n-%s\n",myfilesToCopy[i].filePath);
        }
    }
    else{
        puts ("files to copy empty");
    }
    printf("\n=====END DEBUG OUTPUT OF FILES TO COPY====\n");
    
     printf("\n=====DEBUG OUTPUT OF FILES TO MERGE====\n");
    if(nbFilesToMerge>0){
        for(int i=0;i<nbFilesToMerge;++i){
            for(int j=0;j<myFilesToMerge[i].nbFiles;++j){
                printf("\n-%s |%s \n",myFilesToMerge[i].files[j].baseDir,myFilesToMerge[i].files[j].filePath);
            }
        }
    }
    else{
        puts ("MERGE to copy empty");
    }
    printf("\n=====END DEBUG OUTPUT OF FILES TO MERGE====\n");
}