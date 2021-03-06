/******************
* Daniel Bronfman
* 315901173
* 01
* ex5.h
******************/
#ifndef EX5_H
#define EX5_H
#endif //ASS5_EX5_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define IDLEN 6
#define CLSNAMELEN 31
#define INPUTLEN 200
#define STUDLEN 21
#define GRADELEN 4
#define FLAG 999

///**************************************
struct Student;
typedef struct Student Student;
struct StudNode;
typedef struct StudNode StudNode;
struct StudList;
typedef struct StudList StudList;
struct Class ;
typedef struct Class Class; // class node  in the list with info about class and the next node
struct ClassNode;
typedef struct ClassNode ClassNode;
struct ClassList ;
typedef struct ClassList ClassList;
///**************************************
ClassList *newClassList(void);
void classMod(ClassList* myList);
void studMod(ClassList* myList);
void studDlt(ClassList* myList);
void printClass(ClassList* myList);
void printAll(ClassList *myList,int(*func)(ClassNode*));
void menuFunc(void);
void subMenuFunc(void );
void menuSwitch(char userChoice,ClassList* myList);
void freeClassList(ClassList *list);




