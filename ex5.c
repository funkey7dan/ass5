/******************
* Daniel Bronfman
* 315901173
* 01
* ex5.c
******************/
#include "ex5.h"
struct Student { //student itself
    char *studName;
    int* studGrade; //grade in specific class
};
//typedef struct Student Student;
struct StudNode {
    Student *aStud; // the data of the student
    StudNode *next; //the next class in the student list
};
//typedef struct StudNode StudNode;
struct StudList {
    struct StudNode *head, *tail; // our first student and last student
};
//typedef struct StudList StudList;
struct Class { // course with the name of the class and the id of the class, and list of students in an array
    char *className; //name of the class
    char *classCode; // identifying code of class
    StudList *studList; // list of students belonging to a class
};
//typedef struct Class Class; // class node  in the list with info about class and the next node
struct ClassNode {
    Class *aClass; // the data of the class
    Class *next; //the next class in the class list
};
//typedef struct ClassNode ClassNode;
struct ClassList {
    ClassNode *head, *tail; // our first class and last class
};
//typedef struct ClassList ClassList;
void rmvSpaces(char *str, int len);
Class *newClass(const char *name, char *classId, ClassList *newList);
ClassNode *newClassNode(Class *newClass, ClassList *myList);
void moveAllLeft(char str[], int len, int num, int index);
int countSigns(char str[], char sign, int end);
int firstAlpha(char str[], int len);
ClassNode *classExists(char classId[], ClassList *myList);
int classCounter(ClassList *myList);
int isLglCls(char classId[], char className[]);
int isLglStud(char studName[], char studGrade[]);
Student *studExists(ClassNode *thisClass, char studName[]);
Student *newStud(char studName[], char studGrade[],ClassList *myList);
void updtStud(Student *currentStud, char studGrade[]);
void *newStudNode(char studName[], char studGrade[], StudList *myStudList, ClassList *myList);
void freeStudNode(StudNode *studNode);
void freeStud(Student *aStud);
void freeStudList(StudList *studList);
void freeClass(Class *aClass);
void freeClassNode(ClassNode *classNode);
void freeClassList(ClassList *list);
StudList *newStudList(ClassList *myList);


/*******************
 * Function Name: menuFunc
 *	Input:
 *	Output:None
 *	Function Operation: prints function to the user
*******************/
//func to print the menu
void menuFunc()
{

    printf("Please select an operation:\n"
           "\t0. Exit.\n"
           "\t1. Insert or update a class.\n"
           "\t2. Insert or update a student.\n"
           "\t3. Remove a student from classes.\n"
           "\t4. Print a class.\n"
           "\t5. Print all classes with their computed scores.\n"
           "\t6. Print the menu.\n");
}

//creates the list of students
StudList *newStudList(ClassList *myList)
{

    StudList *newList = (StudList *) malloc(sizeof(struct StudList)); // we allocate heap space for our new List
    if(newList == NULL)
    {
        freeClassList(myList);
        exit(1);
    }
    newList->head = NULL; // we have no nodes yet so set head to NULL
    newList->tail = NULL; // we have no nodes yet so set tail to NULL
    return newList;
}

//create a new student Node
void *newStudNode(char studName[], char studGrade[],StudList *myStudList,ClassList *myList)
{

    StudNode *node = (StudNode *) malloc(sizeof(StudNode)); // we allocate memory for our new node
    if(node == NULL)
    {
        freeClassList(myList);
        exit(1);
    }
    node->aStud = newStud(studName,studGrade,myList);
    node->next = NULL;
    if(myStudList->head == NULL) // if we are adding first node
    {
        myStudList->head = node; //the head of the list will be pointing to our new node
        myStudList->head = node;//the tail of the list will be pointing to our new node also, it's the only one
    }
    else //if we are adding a node to an existing list
    {
        myStudList->tail->next = node; // we go to the current tail node, and change it's next to be the new node
        myStudList->tail = node; //we change the tail to be the new node
    }
}

//free a student
void freeStud(Student *aStud)
{

    if(aStud != NULL)
    {
        free(aStud->studName);
        free(aStud->studGrade);
        free(aStud);
    }
}

//free a student node
void freeStudNode(StudNode *studNode)
{

    if(studNode != NULL)
    {
        freeStud(studNode->aStud);
        freeStudNode(studNode->next);
    }
}

//free a student list
void freeStudList(StudList *studList)
{

    if(studList != NULL)
    {
        freeStudList(studList->head);
        free(studList);
    }
}

//free a class
void freeClass(Class *aClass)
{

    if(aClass != NULL)
    {
        free(aClass->classCode);
        free(aClass->className);
        freeStudList(aClass->studList);
    }
}

//free a class node
void freeClassNode(ClassNode *classNode)
{

    if(classNode != NULL)
    {
        freeClass(classNode->aClass);
        freeClassNode(classNode->next);
        free(classNode);
    }
}

void freeClassList(ClassList *list)
{

    freeClassNode(list->head);
    free(list);
}

//creates the list of classes
ClassList *newClassList(void)
{

    ClassList *newList = (ClassList *) malloc(sizeof(struct ClassList)); // we allocate heap space for out new List
    if(newList == NULL)
    {
        exit(1);
    }
    newList->head = NULL; // we have no nodes yet so set head to NULL
    newList->tail = NULL; // we have no nodes yet so set tail to NULL
    return newList;
}

// creates a new Node
ClassNode *newClassNode(Class *newClass, ClassList *myList)
{

    ClassNode *node = (ClassNode *) malloc(sizeof(ClassNode)); // we allocate memory for our new node
    if(node == NULL)
    {
        freeClassList(myList);
        exit(1);
    }
    node->aClass = newClass;
    node->next = NULL;
    if(myList->head == NULL) // if we are adding first node
    {
        myList->head = node; //the head of the list will be pointing to our new node
        myList->tail = node;//the tail of the list will be pointing to our new node also, it's the only one
    }
    else //if we are adding a node to an existing list
    {
        myList->tail->next = node; // we go to the current tail node, and change it's next to be the new node
        myList->tail = node; //we change the tail to be the new node
    }
}

//func to create a new class
Class *newClass(const char *name, char *classId, ClassList *myList)
{

    Class *newClass = (Class *) malloc(sizeof(Class));// we allocate memory for the newClass struct
    newClass->className = (char *) malloc(strlen(name) + 1); //we allocate memory for the name of the class string
    newClass->classCode = (char *) malloc(strlen(classId) + 1);//we allocate memory for the id of the class string
    // we create a 10 student array
    newClass->studList = newStudList(myList);// we create a new student list
    if(newClass->className == NULL || newClass->classCode == NULL || newClass->studList == NULL)
    {
        freeClassList(myList);
        exit(1);
    }
    strcpy(newClass->classCode, classId);
    strcpy(newClass->className, name);
    return newClass;
}

// a function to count existing classes in the list
int classCounter(ClassList *myList)
{
    // we iterate through the list while there are nodes in it, and each node we increment the counter, to return it
    int counter = 0;
    ClassNode *current = myList->head;
    while (current != NULL)
    {
        counter++;
        current = current->next; //we move to the next node
    }
    return counter;
}

//we check if the input for the new class is legal
int isLglCls(char classId[], char className[])
{

    int errorCount = 0;
    // if the given id is longer than allowed increment error counter
    if(strlen(classId) > IDLEN)
    {
        errorCount++;
    }
    // if the given name is longer than allowed increment error counter
    if(strlen(className) > CLSNAMELEN)
    {
        errorCount++;
    }
    for (int i = 0; i < strlen(classId); i++)
    {
        // if the given id isn't only digits increment error counter
        if(!(isdigit(classId[ i ])))
        {
            errorCount++;
        }
    }
    for (int j = 0; j < strlen(className); j++)
    {
        // if the given id isn't only alphanumerics increment error counter
        if((!isalnum(className[ j ])) && className[ j ] != ' ')
        {
            errorCount++;
        }
    }
    if(errorCount)
    {
        return 0;
        //if there were no errors return 1
    }
    else if(errorCount == 0)
    {
        return 1;
    }
}

//checks if a class exists
ClassNode *classExists(char classId[], ClassList *myList)
{
    // we set the current to be the head of the list
    ClassNode *current = myList->head;

    //while there is a node
    while (current != NULL)
    {

        //if we find a class with the same ID, we return the pointer to it
        if(strcmp(classId, current->aClass->classCode) == 0)
        {
            return current;
        }
        // if not, we move to the next node in the list
        current = current->next;
    }
    // if we didnt find any matching ID's we return a 0
    return 0;
}

//finds first letter in string and returns its location
int firstAlpha(char str[], int len)
{

    for (int i = 0; i < len; ++i)
    {
        if(isalnum(str[ i ])) //if we find a letter we return its location
        {
            return i;
        }
    }
    return -1;
}

// count the signs
int countSigns(char str[], char sign, int end)
{

    int counter = 0;
    //we run the loop for the length of the string
    for (int i = 0; i <= end; i++)
    {
        //each time we find the sign we increment the counter
        if(str[ i ] == sign)
        {
            counter++;
        }
    }
    return counter;
}

//num-how many empty spaces we have. index - from where we move
void moveAllLeft(char str[], int len, int num, int index)
{

    for (int i = num; i > 0; i--)
    {
        for (int j = index; j <= len + 1; j++)
        {
            str[ j - 1 ] = str[ j ];
        }
        index--;
    }
}

//removes spaces from the beginning of the string
void rmvSpaces(char *str, int len)
{

    if(str[ 0 ] != ' ')
    {
        return;
    }
    moveAllLeft(str, len, countSigns(str, ' ', firstAlpha(str, len)), firstAlpha(str, len));
}

/*******************
 * Function Name: classMod
 *	Input:
 *	Output:None
 *	Function Operation: adds or updates a class
*******************/
void classMod(ClassList *myList)
{

    char className[CLSNAMELEN], classId[IDLEN], userStr[INPUTLEN];
    char *token;
    fgets(userStr, 200, stdin);
    if(userStr[ 0 ] == ' ')
    {
        rmvSpaces(userStr, strlen(userStr));
    }// we remove spaces from the start of the string
    token = strtok(userStr, " ");// we break the string into part using spaces
    if(token != NULL)
    {
        strcpy(classId, token);
        token = strtok(NULL, "\n");// we break the string into part using spaces
        strcpy(className, token);
    }
    //if all the input is legal
    if(isLglCls(classId, className))
    {
        if(myList->head == NULL)//if its the first class we are adding
        {
            //create a new class node and add it to our list
            newClassNode(newClass(className, classId, myList), myList);
            printf("Class \"%s %s\" added.\n", classId, className);
        }
            //if not the first class
        else
        {
            //if the class doesn't exist
            if(!(classExists(classId, myList)))
            {
                //if there is already 5 or more
                if(classCounter(myList) >= 5)
                {
                    printf("Unfortunately, there is no room for more classes.\n");
                    return;
                }
                newClassNode(newClass(className, classId, myList), myList);
                printf("Class \"%s %s\" added.\n", classId, className);
            }
            else
            {
                // we create a new pointer to point to the existing class
                ClassNode *existingClass = NULL;
                existingClass = classExists(classId, myList);
                strcpy(existingClass->aClass->className, className);
                printf("Class \"%s %s\" updated.\n", classId, className);
            }
        }
    }
        //if the input we received was wrong
    else
    {
        printf("Error: invalid class number or name.\n");
        return;
    }
}

//checks if a student exists
Student *studExists(ClassNode *thisClass, char studName[])
{

    if(thisClass != NULL)
    {
        StudNode *currentStud = thisClass->aClass->studList->head;
        while (currentStud != NULL)
        {
            if(strcmp(currentStud, studName) == 0)
            {
                return currentStud;
            }
            else
            {
                currentStud = currentStud->next;
            }
        }
    }
    return 0;
}
//if we add a new student

Student *newStud(char studName[], char studGrade[],ClassList *myList)
{

    Student *newStud = (Student *) malloc(sizeof(Student));// we allocate memory for the newStud struct
    newStud->studName = (char *) malloc(strlen(studName) + 1); //we allocate memory for the name of the stud string
    newStud->studGrade = (int *) malloc(sizeof(int));
    if(newStud->studName == NULL || newStud->studGrade == NULL)
    {
        freeClassList(myList);
        exit(1);
    }
    strcpy(newStud->studName, studName);
    newStud->studGrade = atoi(studGrade);
    return newStud;
}

//if we add an existing student
void updtStud(Student *currentStud, char studGrade[])
{

    currentStud->studGrade = atoi(studGrade);
}

//check if the student name and grade are in the format we wanted
int isLglStud(char studName[], char studGrade[])
{

    int grade = atoi(studGrade);
    int errorCount = 0;
    if(strlen(studGrade) > GRADELEN)
    {
        errorCount++;
    }
    if((isalpha(*studName))==0)
    {
        errorCount++;
    }
    if(strlen(studName) > STUDLEN)
    {
        errorCount++;
    }
    if(grade < 0 || grade > 100)
    {
        errorCount++;
    }
    if(errorCount != 0)
    {
        return 0;
    }
    else if(errorCount == 0)
    {
        return 1;
    }
}

/*******************
 * Function Name: studentMod
 *	Input:
 *	Output:None
 *	Function Operation: adds or updates a student and his grades
*******************/
void studMod(ClassList *myList)
{

    char userStr[INPUTLEN], studName[STUDLEN], studGrade[GRADELEN], classId[IDLEN], tokenCpy[STUDLEN];
    ClassNode *currentClass = NULL;
    Student *currentStud = NULL;
    char *token = NULL;
    //get input from user
    fgets(userStr, INPUTLEN, stdin);
    // we remove spaces from the start of the string
    rmvSpaces(userStr, strlen(userStr));
    token = strtok(userStr, "\n");
    token = strtok(userStr, ":");
    if(token != NULL && strlen(token) <= STUDLEN)
    {
        //we get the student name from the user input
        strcpy(tokenCpy, token);
        rmvSpaces(tokenCpy, strlen(tokenCpy));
        strcpy(studName, tokenCpy);
    }
    while (token != NULL)
    {
        //we get the class ID from the user input
        token = strtok(NULL, ",");
        if(token == NULL)
        {
            return;
        }
        if(token != NULL && strlen(token) <= IDLEN)
        {
            //we get the classID from the user input
            strcpy(tokenCpy, token);
            rmvSpaces(tokenCpy, strlen(tokenCpy));
            strcpy(classId, tokenCpy);
            currentClass = classExists(classId, myList);//if the class exists the value is its adress
            currentStud = studExists(currentClass, studName);//if the student exists the value is his adress
        }
        token = strtok(NULL, ";");
        //we get the student grade from the user input
        strcpy(tokenCpy, token);
        rmvSpaces(tokenCpy, strlen(tokenCpy));
        strncpy(studGrade, tokenCpy, 4);
        //token = strtok(NULL, "\n");
        if(isLglStud(studName, studGrade))
        {
            //if there such a class
            if((currentClass))
            {
                //check if student exists
                if(currentStud)
                {
                    updtStud(currentStud, studGrade);
                    printf("Student %s updated on class %s%s with grade %s.\n",
                           currentStud->studName, classId, currentClass->aClass->className, currentStud->studGrade);
                }
                    //if a new student
                else if(!currentStud)
                {
                    newStudNode(studName, studGrade, currentClass->aClass->studList,myList);
                    printf("Student \"%s\" added to class \"%s %s\" with grade %s.\n",
                           studName, classId, currentClass->aClass->className, studGrade);
                }
            }
            else
            {
                printf("Error: invalid name, class number or grade.\n");
                return;
            }
        }
        else
        {
            printf("Error: invalid name, class number or grade.\n");
            return;
        }
    }
}

void studDlt()
{
}

void printClass()
{
}

void printAll()
{
}

void menuSwitch(char userChoice, ClassList *myList)//func to invoke function according to user choice
{

    switch (userChoice)
    {
        case '0':
            freeClassList(myList);
            exit(0);
        case '1':
            classMod(myList);
            break;
        case '2':
            studMod(myList);
            break;
        case '3':
            studDlt(myList);
            break;
        case '4':
            printClass(myList);
            break;
        case '5':
            printAll(myList);
            break;
        case '6':
            menuFunc();
            break;
        default:
            printf("Error: unrecognized operation.\n");
            printf("Select the next operation (insert 6 for the entire menu):\n");
            break;
    }
}