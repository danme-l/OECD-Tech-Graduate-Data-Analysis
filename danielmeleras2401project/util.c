#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"


/**********************************************************************
 * Function: addLineToList()
 *  Purpose: adds a LineType struct to the Linked List
 *   in/out: list type pointer
 *       in: line type pointer
 *   return: list type pointer with the line added
***********************************************************************/
void addLineToList(ListType *list, LineType *line){
    NodeType *currNode;
    NodeType *prevNode;
    NodeType *newNode;

    currNode = list->head;
    prevNode = NULL;

    while (currNode != NULL) {   	//loop ends if we get to the end of the list
        prevNode = currNode;
        currNode = currNode->next;
    }

    newNode = malloc(sizeof(NodeType));
    newNode->data = line;
    newNode->prev = NULL;
    newNode->next = NULL;

    //case: new node is the head
    if (prevNode == NULL)
        list->head = newNode;
    else 
        prevNode-> next = newNode;

    //case: new node is the tail
    if (currNode == NULL)
        list->tail = newNode;
    else{
        newNode-> next = currNode;
        currNode-> prev = newNode;
    }

    newNode->prev = prevNode;
}

/**********************************************************************
 * Function: addCountryToArray()
 *  Purpose: adds a country to the dynamic array by creating a new, 
 *           larger array, copying the elements from the old one with
 *           the new element added and finally disposing of the old one
 *   in/out: list type pointer
 *       in: country type pointer
 *       in: sort type, to specify the method by which to add the country
 *   return: list type pointer with the country added
***********************************************************************/
void addCountryToArray(ArrayType *arr, CountryType *c, SortType s){
    CountryType **newArr;
    int i;

    newArr = calloc(arr->size+1, sizeof(CountryType*));
        
    if(s==NO_CONDITION){
        // simply copies them one at a time and adds the new country at the back
        for (i=0; i<arr->size; i++){
            newArr[i] = arr->elements[i];
        }        

        newArr[i] = c;
    }

    if(s==BY_TOTAL_WOMEN){
        // copies them one at a time until we've copied the last element that 
        // will come before the new one in the updated array
        for (i=0; i<arr->size; i++) {
            if(c->femalePercentage - arr->elements[i]->femalePercentage > 0){
                break;  
            }
            
            newArr[i] = arr->elements[i];
        }

        // add the new item
        newArr[i] = c;        

        // finish copying 
        for (; i<arr->size; i++) {
            newArr[i+1] = arr->elements[i];
        }
    }

    if(s==BY_FEMALE_GRAD_INCREASE){
        // copies them one at a time until we've copied the last element that 
        // will come before the new one in the updated array
        for (i=0; i<arr->size; i++) {
            if(c->difference - arr->elements[i]->difference > 0){
                break;  
            }
            newArr[i] = arr->elements[i];
        }

        // add the new item
        newArr[i] = c;

        // finish copying 
        for (; i<arr->size; i++) {
            newArr[i+1] = arr->elements[i];
        }
    }

    if(s==BY_ANNUAL_AVE){
        // copies them one at a time until we've copied the last element that 
        // will come before the new one in the updated array
        for (i=0; i<arr->size; i++) {
            if(c->avePerYear - arr->elements[i]->avePerYear > 0){
                break;  
            }
            newArr[i] = arr->elements[i];
        }

        // add the new item
        newArr[i] = c;

        // finish copying 
        for (; i<arr->size; i++) {
            newArr[i+1] = arr->elements[i];
        }
    }
    
    // deallocates the memory from the old array
    free(arr->elements);
    arr->elements = newArr;
    ++(arr->size);
}

/**********************************************************************
 * function: displayLine() 
 *  purpose: display line data 
 *       in: line type pointer
 *   return: N/A 
***********************************************************************/
void displayLine(const LineType *l) {
    printf("Country: %s (%s), year: %d --- %5d %s degrees awarded to gender %s\n", 
            l->country, l-> code, l->year, l->amount,
            l->degree, l->gender);
}

/**********************************************************************
 * function: displayList() 
 *  purpose: display linked list data 
 *       in: list type pointer
 *   return: N/A 
***********************************************************************/
void displayList(const ListType *listPtr){
    NodeType *currNode = listPtr->head;
    NodeType *prevNode;

    while(currNode != NULL){
        displayLine(currNode->data);
        prevNode = currNode;
        currNode = currNode->next;
    }
}

/**********************************************************************
 * function: displayCountry() 
 *  purpose: display country data 
 *       in: country type pointer
 *   return: N/A 
***********************************************************************/
void displayCountry(const CountryType *c){
    printf("    %s - %s \n", c->code, c->country);
}

/**********************************************************************
 * function: displayCountryLines() 
 *  purpose: display all the lines in the linked list of lines 
 *           for a specific country 
 *       in: list type pointer
 *       in: the country code for searching, a string
 *   return: N/A 
***********************************************************************/
void displayCountryLines(char *code, ListType *listPtr){
    NodeType *currNode = listPtr->head;
    NodeType *prevNode;

    while(currNode != NULL){
        if((strcmp(currNode->data->gender, "T")==0) 
                && (strcmp(currNode->data->code, code)==0)
                && currNode->data->year > 2013){
                    displayLine(currNode->data);
                }
        prevNode = currNode;
        currNode = currNode->next;
    }

}

/**********************************************************************
 * function: displayArray() 
 *  purpose: display Dynamic Array data 
 *       in: array type pointer
 *   return: N/A 
***********************************************************************/
void displayArray(ArrayType *arr){
    for (int i=0; i<arr->size; i++)
        displayCountry(arr->elements[i]);
}

/**********************************************************************
 * function: displayMenu() 
 *  purpose: displays the main menu for the user interface 
 *   return: N/A 
***********************************************************************/
void displayMenu(){
    printf("    (1) Graduate percentage by country, for all years, by degree type\n");
    printf("    (2) The top five and bottom five countries for percentage of female graduates over the period\n");
    printf("    (3) Graduate percentage by country, for each year from 2014 to 2017 inclusive, for all degrees and both genders\n");
    printf("    (4) All countries ranked in order of increase in female graduates, from the first n years to the last n years of the data\n");
    printf("    (5) All countries ranked in order of average graduates per year, from 2014 to 2017 inclusive\n");
    printf("     (enter 7 to exit)\n");
}

/**********************************************************************
 * function: clearFields() 
 *  purpose: clears the fields of a country type struct once calculations
 *           are finished
 *   in/out: country type pointer we're clearing
 *   return: country type pointer w/fields reset to zero
 *     Note: this function does not reset the firstYear field
 *           as that evidently never needs updating
***********************************************************************/
void clearFields(CountryType *c){
    c->total14 = 0;
    c->total15 = 0;
    c->total16 = 0;
    c->total17 = 0;

    c->totalL6 = 0;
    c->totalL7 = 0;
    c->totalL8 = 0;
    c->totalAll = 0;

    c->totalWomen = 0;
    c->femalePercentage = 0;

    c->averageFirst = 0;
    c->averageRecent = 0;
    c->difference= 0;

    c->avePerYear = 0;
}

