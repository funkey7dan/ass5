/******************
* Daniel Bronfman
* 315901173
* 01
* main.c
******************/
#include "ex5.h"

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
        if(userChoice!='6')
            printf("Select the next operation (insert 6 for the entire menu):\n");
    } while (userChoice != '0');
    //freeClassList(myList); // we free all the allocated memory, we should free students first or something
    return 0;
}
