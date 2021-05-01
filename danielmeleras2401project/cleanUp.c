#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

/************************************************************************
 * Function: cleanUpList()
 *  Purpose: deallocate the memory for a linked list, as well as its data
 *       in: ListType pointer
 *   return: N/A
*************************************************************************/
void cleanUpList(ListType *list){
    NodeType *currNode = list->head;
    NodeType *nextNode;

    while (currNode != NULL) {
        nextNode = currNode->next;
        if(currNode->data != NULL){
            free(currNode->data);
        }
        free(currNode);
        currNode = nextNode;
    }

    free(list);
}

/************************************************************************
 * Function: cleanUpCountry()
 *  Purpose: deallocate the memory for a country struct, as well as its data
 *       in: CountryType pointer
 *   return: N/A
*************************************************************************/
void cleanUpCountry(CountryType *c){
    clearFields(c); //just in case
    free(c);
}

/**********************************************************************
 * Function: cleanUpArray()
 *  Purpose: deallocate the memory for an array
 *       in: ArrayType pointer
 *   return: N/A
***********************************************************************/
void cleanUpArray(ArrayType *arr){

    free(arr->elements);
    arr->elements = NULL;
    arr->size = 0;
}

