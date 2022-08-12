#ifndef THREAD_TASK_MGR_H_INCLUDED
#define THREAD_TASK_MGR_H_INCLUDED
////////////////////////////////////////////////////////////////////////////////////////////
// libraries
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>

//////////////////////////////////////////////////////////////////////////////////
// definitions

 /** what to do next ?
 1. Check the LINE store point, and how it should work.
 2. How to manage the sequence order inside functions and tasks.
 */

//////////////////////////////////////////////////////////////////////////////////
// enumerations
typedef enum { BitClear = 0, BitSet = 1, FunctionFinished = 2 } FunctionState;
typedef enum { TaskStart = 0, TaskBusy = 1, TaskFinished = 2 } TaskState;

/// Basic function state check
#define                                 	\
    FunctionStart                       	\
    static int function_state = 0;      	\
    static int bit_counter = 0;      	    \
    switch(function_state)              	\
    {                                   	\
        case 0:

#define 									\
    FunctionCheck(bit, bit_state)			\
        do									\
        {									\
            case __LINE__:			        \
            if(bit == bit_state && bit_counter < 2)\
            {                               \
                bit_counter++;              \
                printf("function return BitSet bit_counter %d\n", bit_counter);\
                function_state = __LINE__;	\
                return BitSet;              \
            }                               \
            else{                           \
                bit = 0;      	            \
                bit_counter = 0;      	    \
                printf("function return BitClear\n");\
            }                               \
        }while(0)

#define                                     \
    FunctionEnd                             \
    }                                       \
    function_state = 0; 				    \
    bit_counter = 0;      	     			\
    printf("FUNC DONE# %s = %d\n", __func__, FunctionFinished);\
    return FunctionFinished;                \
    printf("print after FUNC DONE#\n")

/// Task sequence manager
#define                                 \
    TaskStart                           \
    static int task_state = 0;          \
    printf("TASK STARTED# %d\n", task_state);\
    switch(task_state)                  \
    {                                   \
        case 0:

#define 								\
    TaskFunctionSet				        \
            task_state = __LINE__;      \
            case __LINE__:			    \
            printf("TASK STORE POINT# %d\n", task_state)

#define 								\
    CheckTask(bit, bit_state)			\
    do									\
    {                                   \
        if(bit == bit_state)            \
        {                               \
            printf("CheckTask = TaskBusy func# %s, line# %d\n\n",__func__, __LINE__);  \
            return TaskBusy;            \
        }                               \
        else{                           \
            printf("CheckTask = TaskFinished func# %s, line# %d\n\n",__func__, __LINE__); \
        }                               \
    }while(0)

#define                                 \
    TaskEnd                             \
    }                                   \
    task_state = 0; 					\
    printf("TASK DONE# %s = %d\n", __func__, TaskFinished);\
    return TaskFinished;                \
    printf("print after TASK DONE#\n")


// function pointer

// pointers

// variables

//////////////////////////////////////////////////////////////////////////////////
// functions

#endif // THREAD_TASK_MGR_H_INCLUDED
