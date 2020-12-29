/******************
* Daniel Bronfman
* 315901173
* 01
* main.c
******************/
#include "ex5.h"


/*
 *TODO remove
 * SELF NOTE:
 *  out data is myList(struct with head and tail) -> has ClassNodes (with class data and info about the next node)
 *  -> Has Class (has name,code, and an array of students) -> array of studs (has students) ->
 *  -> each student has name and grade for the class he is in
 *  we add new nodes to the end of the list
 */

/*******************
 * Function Name: Main
 *	Input:
 *	Output:None
 *	Function Operation:
*******************/
int main(void)
{
    ClassList* myList = newClassList(); // we initialize our list
    char userChoice,x;
    menuFunc();
    do
    {

        scanf(" %c", &userChoice);
        scanf("%c",&x);
        menuSwitch(userChoice,myList);
        printf("Select the next operation (insert 6 for the entire menu):\n");
    } while (userChoice != '0');
    //freeAll(myList); // we free all the allocated memory, we should free students first or something
    return 0;
}
