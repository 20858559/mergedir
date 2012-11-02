#include "general_lib.h"

void copyInfoStructToArray(fileInfos_t tmpFileInfo){
    fileInfos_t *tmpInfos;
    tmpInfos = (fileInfos_t*) realloc(myfilesToCopy, (nbFilesToCopy+1) * sizeof(fileInfos_t)  );
    if ( tmpInfos != NULL ){
            myfilesToCopy = tmpInfos;
            myfilesToCopy[nbFilesToCopy] = tmpFileInfo;
            //printf("\nAdding #2:  %s\n",tmpFileInfo.filePath);
    }
    else{ 
        printf("Error allocating memory! for result array\n");
        exit(EXIT_FAILURE);
    }
    nbFilesToCopy++;
}

/**
 * @param in output file
 * @param out input file
 * @return -1 if error 0 if success
 */
void copyfile(char in_filename[], char out_filename[])
{
    FILE        *fp_in  = fopen(in_filename,  "r");
    FILE        *fp_out = fopen(out_filename, "w");

//  ENSURE THAT OPENING BOTH FILES HAS BEEN SUCCESSFUL
    if(fp_in != NULL && fp_out != NULL) {

        char    buffer[BUFSIZ];
        size_t  got, wrote;

        while( (got = fread(buffer, 1, sizeof buffer, fp_in)) > 0) {  
            wrote = fwrite(buffer, 1, got, fp_out);
            if(wrote != got) {
                printf("error copying files\n");
                exit(EXIT_FAILURE);
            }
        }

    }

//  ENSURE THAT WE ONLY CLOSE FILES THAT ARE OPEN
    if(fp_in != NULL)
        fclose(fp_in);
    if(fp_out != NULL)
        fclose(fp_out);
    
    //finally set modification date
    struct utimbuf ubuf;
    struct stat fin;
    stat(in_filename,&fin);
    ubuf.modtime = fin.st_mtime;
    utime(out_filename,&ubuf);
}

/* taken from http://niallohiggins.com/2009/01/08/mkpath-mkdir-p-alike-in-c-for-unix/   */
/* Function with behaviour like `mkdir -p', recursive mkdir  */
int mkdirp(const char *pathname, mode_t mode){
  char parent[PATH_MAX], *p;
  /* make a parent directory path */
  strncpy(parent, pathname, sizeof(parent));
  parent[sizeof(parent) - 1] = '\0';
  for(p = parent + strlen(parent); *p != '/' && p != parent; p--);
  *p = '\0';
  /* try make parent directory */
  if(p != parent && mkdirp(parent, mode) != 0)
    return -1;
  /* make this one if parent has been made */
  if(mkdir(pathname, mode) == 0)
    return 0;
  /* if it already exists that is fine */
  if(errno == EEXIST)
    return 0;
  return -1;
}