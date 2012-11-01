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

/**
 * Main function
 */
int main(int argc, char** argv) {

    /*Initialize our application*/
    configureModes(argc,argv);
    mergeDirectories();
    
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
                if( !(s.st_mode & S_IFDIR) ){
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
            if( !(s.st_mode & S_IFDIR) ){
                //not a directory..error
                free(globalArgs.inputDirs);
                free(globalArgs.outDirName);
                fprintf(stderr, "\n%s must be \n\n",argv[argc-1]);
                displayUsage();
            }
        }
        else{
            //new
            mkdir(globalArgs.outDirName, 0751);
        }
                
        
}


void displayUsage( void ){
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

