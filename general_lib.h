/* 
 * File:   general_lib.h
 * Author: arnaudmoret
 *
 * Created on November 1, 2012, 4:49 PM
 */

#ifndef GENERAL_LIB_H
#define	GENERAL_LIB_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "sys_headers.h"
#include "globals.h"


    
void copyInfoStructToArray(fileInfos_t tmpFileInfo);
int cp(const char *to, const char *from);
int mkdirp(const char *pathname, mode_t mode);



#ifdef	__cplusplus
}
#endif

#endif	/* GENERAL_LIB_H */

