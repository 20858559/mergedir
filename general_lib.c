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
 * Take from http://stackoverflow.com/questions/2180079/how-can-i-copy-a-file-on-unix-using-c
 * @param to output file
 * @param from input file
 * @return -1 if error 0 if success
 */
int cp(const char *to, const char *from){
    int fd_to, fd_from;
    char buf[4096];
    ssize_t nread;
    int saved_errno;

    fd_from = open(from, O_RDONLY);
    if (fd_from < 0){
        
        printf("from<0");
        return -1;
    }

    fd_to = open(to, O_WRONLY | O_CREAT | O_EXCL, 0666);
    if (fd_to < 0)
        goto out_error;

    while (nread = read(fd_from, buf, sizeof buf), nread > 0){
        char *out_ptr = buf;
        ssize_t nwritten;

        do {
            nwritten = write(fd_to, out_ptr, nread);
            
            if (nwritten >= 0){
                nread -= nwritten;
                out_ptr += nwritten;
            }
            else if (errno != EINTR){
                goto out_error;
            }
        } while (nread > 0);
    }

    if (nread == 0)
    {
        if (close(fd_to) < 0){
            fd_to = -1;
            goto out_error;
        }
        close(fd_from);

        /* Success! */
        return 0;
    }

  out_error:
    saved_errno = errno;

    close(fd_from);
    if (fd_to >= 0)
        close(fd_to);

    errno = saved_errno;
    return -1;
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