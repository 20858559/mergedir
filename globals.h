/* 
 * File:   globals.h
 * Author: arnaud  tim 
 *
 * Created on November 1, 2012, 3:47 PM
 */

#ifndef GLOBALS_H
#define	GLOBALS_H

#ifdef	__cplusplus
extern "C" {
#endif
/*Boolean types*/
#define TRUE 1
#define FALSE 0

/*Exclusive mode types*/
#define MODE_COMPARE_DATE 0
#define MODE_COMPARE_SIZE 1 
#define MODE_SHOW_CONFLICTS 2
    
/*Default compare mode*/
#define DEFAULT_COMPARE_MODE MODE_COMPARE_DATE
    
/*Current compare mode (Default at start of execution..)*/
#define CURRENT_COMPARE_MODE DEFAULT_COMPARE_MODE
    
/*non exclusive modes*/
#define MODE_IGNORE FALSE
#define MODE_VERBOSE FALSE
    

        


#ifdef	__cplusplus
}
#endif

#endif	/* GLOBALS_H */

