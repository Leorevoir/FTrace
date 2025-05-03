/*
** EPITECH PROJECT, 2025
** Ftrace
** File description:
** macro.h
*/

#ifndef MACRO_H_H
    #define MACRO_H_H

    #define SUCCESS         0
    #define ERROR           84

    #define START           0

    #define STRACE_NO_ARG "ftrace: must have PROG [ARGS] or -p PID"
    #define STRACE_TRY "Try 'ftrace -h' for more information."

    #define FAILED          0
    #define INDIRECT_CALL   1
    #define DIRECT_CALL     1

    #define ERR             -1

    #define GREEN      	    "\033[1;32m"
    #define RED        	    "\033[1;31m"
    #define ILC			    "\033[3m"
    #define ORANGE     	    "\033[38;5;214m"
    #define RST		   	    "\033[0m"

#endif /* MACRO_H_H */
