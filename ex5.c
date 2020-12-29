/******************
* Daniel Bronfman
* 315901173
* 01
* ex5.c
******************/
#include "ex5.h"
struct Student { //student itself
    char *studName;
    int studGrade; //grade in specific class
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
Student *newStud(char studName[], char studGrade[], ClassList *myList);
void updtStud(Student *currentStud, char studGrade[]);
void *newStudNode(char studName[], char studGrade[], StudList *myStudList, ClassList *myList);
void freeStudNode(StudNode *studNode);
void freeStud(Student *aStud);
void freeStudList(StudList *studList);
void freeClass(Class *aClass);
void freeClassNode(ClassNode *classNode);
void freeClassList(ClassList *list);
StudList *newStudList(ClassList *myList);
void removeStud(ClassNode *classNode, char studName[], ClassList *myList);
int memberOf(char studName[], ClassList *myList);
int numClsRmvFrom(char userStr[INPUTLEN]);
int isLglInput(char userStr[INPUTLEN]);
ClassNode *isEnrolled(char userStr[INPUTLEN], ClassList *myList);
int isAlphaLoop(char str[]);
int isDigitLoop(char str[]);
void sortStuds(ClassNode *classNode);
void printClassLoop(Class *class);
void subSwitch(char userChoice, ClassList *myList);
int countGrades(ClassNode *classNode);
int sumGrades(ClassNode *classNode);
int avgGrade(ClassNode *classNode);
int minGrade(ClassNode *classNode);
int maxGrade(ClassNode *classNode);

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

/*******************
 * Function Name:
 *	Input:
 *	Output:None
 *	Function Operation:
*******************/
void subMenuFunc()
{

    printf("Please select the aggregation method:\n"
           "\ta. Average Grade.\n"
           "\tb. Maximal Grade.\n"
           "\tc. Minimal Grade.\n"
           "\td. Sum.\n"
           "\te. Count.\n"
           "\t0. Return to the main menu.\n");
}

/*******************
 * Function Name:
 *	Input:
 *	Output:None
 *	Function Operation:
*******************/
//check if the string is comprised of alphabeticals returns 0 if there are non alpha signs
int isAlphaLoop(char str[])
{

    for (int i = 0; i <= strlen(str) - 1; i++)
    {
        if(((isalpha(str[ i ])) == 0) && str[ i ] != ' ')
        {
            return 0;
        }
    }
    return 1;
}

/*******************
 * Function Name:
 *	Input:
 *	Output:None
 *	Function Operation:
*******************/
//check if the string is comprised of digits, returns 0 if there are non digit signs
int isDigitLoop(char str[])
{

    for (int i = 0; i <= strlen(str) - 1; i++)
    {
        if((isdigit(str[ i ])) == 0 && str[ i ] != ' ')
        {
            return 0;
        }
    }
    return 1;
}

/*******************
 * Function Name:
 *	Input:
 *	Output:None
 *	Function Operation:
*******************/
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

/*******************
 * Function Name:
 *	Input:
 *	Output:None
 *	Function Operation:
*******************/
//create a new student Node
void *newStudNode(char studName[], char studGrade[], StudList *myStudList, ClassList *myList)
{

    StudNode *node = (StudNode *) malloc(sizeof(StudNode)); // we allocate memory for our new node
    if(node == NULL)
    {
        freeClassList(myList);
        exit(1);
    }
    node->aStud = newStud(studName, studGrade, myList);
    node->next = NULL;
    if(myStudList->head == NULL) // if we are adding first node
    {
        myStudList->head = node; //the head of the list will be pointing to our new node
        myStudList->tail = node;//the tail of the list will be pointing to our new node also, it's the only one
    }
    else //if we are adding a node to an existing list
    {
        myStudList->tail->next = node; // we go to the current tail node, and change it's next to be the new node
        myStudList->tail = node; //we change the tail to be the new node
    }
}

/*******************
 * Function Name:
 *	Input:
 *	Output:None
 *	Function Operation:
*******************/
//free a student
void freeStud(Student *aStud)
{

    if(aStud != NULL)
    {
        free(aStud->studName);
        //free(aStud->studGrade);//TODO check me
        free(aStud);
    }
}

/*******************
 * Function Name:
 *	Input:
 *	Output:None
 *	Function Operation:
*******************/
//free a student node
void freeStudNode(StudNode *studNode)
{

    if(studNode != NULL)
    {
        freeStud(studNode->aStud);
        freeStudNode(studNode->next);
    }
}

/*******************
 * Function Name:
 *	Input:
 *	Output:None
 *	Function Operation:
*******************/
//free a student list
void freeStudList(StudList *studList)
{

    if(studList != NULL)
    {
        freeStudNode(studList->head);
        free(studList);
    }
}

/*******************
 * Function Name:
 *	Input:
 *	Output:None
 *	Function Operation:
*******************/
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

/*******************
 * Function Name:
 *	Input:
 *	Output:None
 *	Function Operation:
*******************/
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

/*******************
 * Function Name:
 *	Input:
 *	Output:None
 *	Function Operation:
*******************/
void freeClassList(ClassList *list)
{

    if(list != NULL)
    {
        freeClassNode(list->head);
        free(list);
    }
}

/*******************
 * Function Name:
 *	Input:
 *	Output:None
 *	Function Operation:
*******************/
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

/*******************
 * Function Name:
 *	Input:
 *	Output:None
 *	Function Operation:
*******************/
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

/*******************
 * Function Name:
 *	Input:
 *	Output:None
 *	Function Operation:
*******************/
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

/*******************
 * Function Name:
 *	Input:
 *	Output:None
 *	Function Operation:
*******************/
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

/*******************
 * Function Name:
 *	Input:
 *	Output:None
 *	Function Operation:
*******************/
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
    if(strcmp(className, "-1") != 0)
    {
        if(strlen(className) > CLSNAMELEN)
        {
            errorCount++;
        }
        for (int j = 0; j < strlen(className); j++)
        {
            // if the given id isn't only alphanumerics increment error counter
            if((!isalnum(className[ j ])) && className[ j ] != ' ')
            {
                errorCount++;
            }
        }
    }
    for (int i = 0; i < strlen(classId); i++)//TODO remove loop
    {
        // if the given id isn't only digits increment error counter
        if(isDigitLoop(classId) == 0)
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

/*******************
 * Function Name:
 *	Input:
 *	Output:None
 *	Function Operation:
*******************/
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

/*******************
 * Function Name:
 *	Input:
 *	Output:None
 *	Function Operation:
*******************/
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

/*******************
 * Function Name:
 *	Input:
 *	Output:None
 *	Function Operation:
*******************/
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

/*******************
 * Function Name:
 *	Input:
 *	Output:None
 *	Function Operation:
*******************/
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

/*******************
 * Function Name:
 *	Input:
 *	Output:None
 *	Function Operation:
*******************/
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

/*******************
 * Function Name:
 *	Input:
 *	Output:None
 *	Function Operation:
*******************/
//checks if a student exists in this class, if he exists return his adress
Student *studExists(ClassNode *thisClass, char studName[])
{

    if(thisClass != NULL)
    {
        StudNode *currentStud = thisClass->aClass->studList->head;
        while (currentStud != NULL)
        {
            if(strcmp(currentStud->aStud->studName, studName) == 0)
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

/*******************
 * Function Name:
 *	Input:
 *	Output:None
 *	Function Operation:
*******************/
//counts the classes the student is enrolled in
int memberOf(char studName[], ClassList *myList)
{

    ClassNode *currentNode = myList->head;
    int counter = 0;
    while (currentNode != NULL)
    {
        //every time we find the student we increment the counter
        if(studExists(currentNode, studName))
        {
            counter++;
        }
        currentNode = currentNode->next;
        //if we reached the tail we reached the end
    }
    return counter;
}

/*******************
 * Function Name:
 *	Input:
 *	Output:None
 *	Function Operation:
*******************/
//if we add a new student
Student *newStud(char studName[], char studGrade[], ClassList *myList)
{

    Student *newStud = (Student *) malloc(sizeof(Student));// we allocate memory for the newStud struct
    newStud->studName = (char *) malloc(strlen(studName) + 1); //we allocate memory for the name of the stud string
    newStud->studGrade = malloc(sizeof(int));
    if(newStud->studName == NULL || newStud->studGrade == NULL)
    {
        freeClassList(myList);
        exit(1);
    }
    strcpy(newStud->studName, studName);
    newStud->studGrade = atoi(studGrade);
    return newStud;
}

/*******************
 * Function Name:
 *	Input:
 *	Output:None
 *	Function Operation:
*******************/
//if we add an existing student
void updtStud(Student *currentStud, char studGrade[])
{

    currentStud->studGrade = atoi(studGrade);
}

/*******************
 * Function Name:
 *	Input:
 *	Output:None
 *	Function Operation:
*******************/
//check if the student name and grade are in the format we wanted, if all ok we return 1
int isLglStud(char studName[], char studGrade[])
{

    int grade = atoi(studGrade);
    int errorCount = 0;
    if((isAlphaLoop(studName)) == 0)
    {
        errorCount++;
    }
    if(strlen(studName) > STUDLEN)
    {
        errorCount++;
    }
    //if we sent it to be checked without the need to check the grade
    if(grade != (FLAG))
    {
        if(grade < 0 || grade > 100)
        {
            errorCount++;
        }
        if(strlen(studGrade) > GRADELEN)
        {
            errorCount++;
        }
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
 * Function Name:
 *	Input:
 *	Output:None
 *	Function Operation:
*******************/
//check if the class length and name are in the right format, we return 1 if its lgl
int isLglInput(char userStr[INPUTLEN])
{

    int error = 0;
    char myStr[INPUTLEN];
    strcpy(myStr, userStr);
    char *token = NULL;
    token = strtok(myStr, "\n");
    token = strtok(myStr, ":");
    if(token != NULL)
    {
        if(isLglStud(token, "999") == 0)
        {
            error++;
        }
    }
    while (token != NULL)
    {
        token = strtok(NULL, ",");
        if(token != NULL)
        {
            if((isLglCls(token, "-1")) == 0)
            {
                error++;
            }
        }
    }
    if(error == 0)
    {
        return 1;
    }
    else
    {
        return 0;
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

    char userStr[INPUTLEN], studName[STUDLEN], studGrade[GRADELEN], classId[IDLEN], tokenCpy[STUDLEN], str1[INPUTLEN];
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
        //strncpy(studGrade, tokenCpy, 4);
        strcpy(studGrade, tokenCpy);
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
                    newStudNode(studName, studGrade, currentClass->aClass->studList, myList);
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

/*******************
 * Function Name:
 *	Input:
 *	Output:None
 *	Function Operation:
*******************/
//check to see if the student is enrolled in all the classes given
ClassNode *isEnrolled(char userStr[INPUTLEN], ClassList *myList)
{

    char myStr[INPUTLEN], classId[IDLEN], tokenCpy[STUDLEN], studName[STUDLEN];
    ClassNode *currentNode = NULL;
    strcpy(myStr, userStr);
    char *token = NULL;
    token = strtok(myStr, "\n");
    token = strtok(myStr, ":");
    strcpy(tokenCpy, token);
    rmvSpaces(tokenCpy, strlen(tokenCpy));
    strcpy(studName, tokenCpy);
    while (token != NULL)
    {
        token = strtok(NULL, ",");
        if(token == NULL)
        {
            return NULL;
        }
        strcpy(tokenCpy, token);
        rmvSpaces(tokenCpy, strlen(tokenCpy));
        strcpy(classId, tokenCpy);
        currentNode = classExists(classId, myList);
        //if the student is not enrolled in this class
        if(!studExists(currentNode, studName))
        {
            return currentNode;
        }
    }
    return NULL;
}

/*******************
 * Function Name:
 *	Input:
 *	Output:None
 *	Function Operation:
*******************/
//removes the student from class
void removeStud(ClassNode *classNode, char studName[], ClassList *myList)
{

    StudNode *currentNode = classNode->aClass->studList->head;
    if(currentNode == NULL)
    {
        return;
    }
    StudNode *temp = NULL;
    int counter = 0;
    while (currentNode != NULL)
    {
        //if its the first student
        if(counter == 0 && (strcmp(currentNode->aStud->studName, studName) == 0))
        {
            //if it's the only student
            if(currentNode->next == NULL)
            {
                freeStud(currentNode->aStud);
                classNode->aClass->studList->head = NULL;
                return;
            }
                //there is a student next in the list
            else if(currentNode->next != NULL)
            {
                classNode->aClass->studList->head = currentNode->next;
                freeStud(currentNode->aStud);
                return;
            }
        }
            //the student is not the first
        else if((strcmp(currentNode->next->aStud->studName, studName) == 0))
        {
            //if it's the last student
            if(currentNode->next->next == NULL)
            {
                classNode->aClass->studList->tail = currentNode;
                freeStud(currentNode->next->aStud);
                currentNode->next = NULL;
                return;
            }
                //there is a student next in the list
            else if(currentNode->next->next != NULL)
            {
                //we store the next next node adress in a temp variable to preserve it
                temp = currentNode->next->next;
                freeStud(currentNode->next->aStud);
                currentNode->next = temp;
                return;
            }
        }
        else
        {
            currentNode = currentNode->next;
            counter++;
        }
    }
}

/*******************
 * Function Name:
 *	Input:
 *	Output:None
 *	Function Operation:
*******************/
//check the amount of classes we want to remove the student from
int numClsRmvFrom(char userStr[INPUTLEN])
{

    char myStr[INPUTLEN];
    int counter = 0;
    strcpy(myStr, userStr);
    char *token = NULL;
    token = strtok(myStr, "\n");
    token = strtok(myStr, ":");
    while (token != NULL)
    {
        token = strtok(NULL, ",");
        if(token == NULL)
        {
            return counter;
        }
        rmvSpaces(token, strlen(token));
        if(token != NULL)
        {
            counter++;
        }
    }
    return counter;
}

/*******************
 * Function Name:
 *	Input:
 *	Output:None
 *	Function Operation:
*******************/
//remove student from classes given by user
void studDlt(ClassList *myList) //TODO check length
{

    char userStr[INPUTLEN], studName[STUDLEN], classId[IDLEN], tokenCpy[STUDLEN], myStr1[INPUTLEN], myStr2[INPUTLEN];
    char *token = NULL;
    ClassNode *currentClass = NULL;
    StudNode *currentStud = NULL;
    //get input from user
    fgets(userStr, INPUTLEN, stdin);
    // we remove spaces from the start of the string
    rmvSpaces(userStr, strlen(userStr));
    strcpy(myStr1, userStr);
    strcpy(myStr2, userStr);
    currentClass = isEnrolled(myStr2, myList);
    if(currentClass)
    {
        printf("Error: student is not a member of class \"%s %s\".\n",
               currentClass->aClass->classCode, currentClass->aClass->className);
    }
    if(isLglInput(myStr1) == 0)
    {
        printf("Error: invalid name or class number.\n");
        return;
    }
    // we check to see if the student is enrolles in all the classes we are given
    token = strtok(myStr2, ":");
    if(token != NULL && strlen(token) <= STUDLEN)
    {
        //we get the student name from the user input
        strcpy(tokenCpy, token);
        rmvSpaces(tokenCpy, strlen(tokenCpy));
        strcpy(studName, tokenCpy);
    }

    // if the number of classes we're trying to delete the student is bigger than all his classes, print error
    if(numClsRmvFrom(myStr1) >= memberOf(studName, myList))
    {
        printf("Error: student cannot be removed from all classes.\n");
        return;
    }
    token = strtok(userStr, ":");
    token = strtok(NULL, ",");
    while (token != NULL)
    {
        if(token == NULL || strcmp("\n", token) == 0)
        {
            return;
        }
        strcpy(tokenCpy, token);
        rmvSpaces(tokenCpy, strlen(tokenCpy));
        strcpy(classId, tokenCpy);
        currentClass = classExists(classId, myList);
        //if the student exists in this class the value is his adress
        currentStud = studExists(currentClass, studName);
        removeStud(currentClass, studName, myList);
        printf("Student \"%s\" removed from class \"%s %s\".",
               studName, classId, currentClass->aClass->className);
        token = strtok(NULL, ",");
    }
}

/*******************
 * Function Name:
 *	Input:
 *	Output:None
 *	Function Operation:
*******************/
//sorts the linked list of students
void sortStuds(ClassNode *classNode) //fix sorting loop
{

    int result = 0;
    int isSwapped = 0;
    StudNode *currentStud = NULL;
    Student *temp = NULL;
    do
    {
        isSwapped = 0;
        currentStud = classNode->aClass->studList->head;
        while (currentStud != NULL)
        {

            //if there is a next student we compare them
            if(currentStud->next != NULL)
            {
                //compare current student name with next one
                result = strcmp(currentStud->aStud->studName, currentStud->next->aStud->studName);
                // if the left student is greater than the right we swap them
                if(result >= 1)
                {
                    // we save the next student data address in a temporary pointer
                    temp = currentStud->next->aStud;
                    currentStud->next->aStud = currentStud->aStud;
                    currentStud->aStud = temp;
                    isSwapped++;
                }
                currentStud = currentStud->next;
            }
            else
            {
                currentStud = NULL;
            }
        }
    } while (isSwapped != 0);
}

/*******************
 * Function Name:
 *	Input:
 *	Output:None
 *	Function Operation:
*******************/
// a loop to print all the students in a given class
void printClassLoop(Class *class)
{

    StudNode *currentStud = class->studList->head;
    if(currentStud == NULL)
    {
        printf("Class \"%s %s\" has no students.", class->classCode, class->className);
    }
    printf("Class \"%s, %d\" students:\n", class->classCode, class->className);
    while (currentStud != NULL)
    {
        printf("%s, %d\n", currentStud->aStud->studName, currentStud->aStud->studGrade);
        currentStud = currentStud->next;
    }
}

/*******************
 * Function Name:
 *	Input:
 *	Output:None
 *	Function Operation:
*******************/
//prints the requested class
void printClass(ClassList *myList)
{

    char userStr[INPUTLEN], classId[IDLEN];
    char *token = NULL;
    ClassNode *currentClass = NULL;
    //get input from user
    fgets(userStr, INPUTLEN, stdin);
    // we remove spaces from the start of the string
    rmvSpaces(userStr, strlen(userStr));
    token = strtok(userStr, "\n");
    if(token != NULL)
    {
        strcpy(classId, token);
    }
    // if the class ID we got is legal, we point to it
    if(isLglCls(classId, "-1"))
    {
        currentClass = classExists(classId, myList);
        if(currentClass == NULL)
        {
            printf("Error: invalid class number.\n");
        }
        sortStuds(currentClass);
        printClassLoop(currentClass->aClass);
    }
    else
    {
        printf("Error: invalid class number.\n");
    }
}

/*******************
 * Function Name:
 *	Input:
 *	Output:None
 *	Function Operation:
*******************/
int countGrades(ClassNode *classNode)
{

    StudNode *currentStud = classNode->aClass->studList->head;
    int counter = 0;
    while (currentStud != NULL)
    {
        counter++;
        currentStud = currentStud->next;
    }
    return counter;
}

/*******************
 * Function Name:
 *	Input:
 *	Output:None
 *	Function Operation:
*******************/
int sumGrades(ClassNode *classNode)
{

    StudNode *currentStud = classNode->aClass->studList->head;
    int sum = 0;
    while (currentStud != NULL)
    {
        sum += currentStud->aStud->studGrade;
        currentStud = currentStud->next;
    }
    return sum;
}

/*******************
 * Function Name:
 *	Input:
 *	Output:None
 *	Function Operation:
*******************/
int avgGrade(ClassNode *classNode)
{

    int avg = 0;
    avg = sumGrades(classNode) / countGrades(classNode);
    return avg;
}

/*******************
 * Function Name:
 *	Input:
 *	Output:None
 *	Function Operation:
*******************/
int minGrade(ClassNode *classNode)
{

    StudNode *currentStud = classNode->aClass->studList->head;
    int min = currentStud->aStud->studGrade;
    while (currentStud != NULL)
    {
        if(currentStud->aStud->studGrade < min)
        {
            min = min = currentStud->aStud->studGrade;
        }
        currentStud = currentStud->next;
    }
    return min;
}

/*******************
 * Function Name:
 *	Input:
 *	Output:None
 *	Function Operation:
*******************/
int maxGrade(ClassNode *classNode)
{

    StudNode *currentStud = classNode->aClass->studList->head;
    int max = currentStud->aStud->studGrade;
    while (currentStud != NULL)
    {
        if(currentStud->aStud->studGrade > max)
        {
            max = currentStud->aStud->studGrade;
        }
        currentStud = currentStud->next;
    }
    return max;
}

/*******************
 * Function Name:
 *	Input:
 *	Output:None
 *	Function Operation:
*******************/
void printAll(ClassList *myList, int(*func)(ClassNode *), ClassNode *node)
{

    if(node == myList->tail)
    {
        if(node->aClass->studList == NULL)
        {
            printf("Class \"%s %s\" has no students.\n", node->aClass->classCode, node->aClass->className);
            return;
        }
        printf("%s %s,%d\n", node->aClass->classCode, node->aClass->className, func(node));
        return;
    }
    else
    {
        if(node->aClass->studList == NULL)
        {
            printf("Class \"%s %s\" has no students.\n", node->aClass->classCode, node->aClass->className);
            printAll(myList, func, node->next);
            return;
        }
        printAll(myList, func, node->next);
        printf("%s %s,%d\n", node->aClass->classCode, node->aClass->className, func(node));
        return;
    }
}

/*******************
 * Function Name:
 *	Input:
 *	Output:None
 *	Function Operation:
*******************/
//a function to switch between the functions available to the user
void subSwitch(char userChoice, ClassList *myList)
{

    int (*avgPtr)(ClassNode *) = &avgGrade;
    int (*maxPtr)(ClassNode *) = &maxGrade;
    int (*minPtr)(ClassNode *) = &minGrade;
    int (*sumPtr)(ClassNode *) = &sumGrades;
    int (*countPtr)(ClassNode *) = &countGrades;
    switch (userChoice)
    {
        case 'a':
            printAll(myList, avgPtr, myList->head);
            break;
        case 'b':
            printAll(myList, maxPtr, myList->head);
            break;
        case 'c':
            printAll(myList, minPtr, myList->head);
            break;
        case 'd':
            printAll(myList, sumPtr, myList->head);
            break;
        case 'e':
            printAll(myList, countPtr, myList->head);
            break;
        case '0':
            break;
    }
}

/*******************
 * Function Name:
 *	Input:
 *	Output:None
 *	Function Operation:
*******************/
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
            if(myList->head == NULL)
            {
                printf("Error: there are no classes.\n");
                break;
            }
            subMenuFunc();
            char subChoice, x;
            scanf(" %c", &subChoice);
            scanf("%c", &x);
            subSwitch(subChoice, myList);
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