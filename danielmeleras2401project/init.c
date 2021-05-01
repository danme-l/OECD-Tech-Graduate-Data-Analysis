#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"

/****************************************************************************
 * Function: initData()
 *  Purpose: retrieves the data from the file and adds it
 *           to the Linked List and Dynamic Array
 *   in/out: Linked List
 *   in/out: Array
 *   return: fully filled Linked List and Dynamic Array as output parameters
*****************************************************************************/
void initData(ListType *list, ArrayType *arr){
    LineType *line; 
    CountryType *newCountry;
    FILE *f;

    char code[4], country[MAX_STRING], gender[2], degree[3];
    int year, amount, n=0;
    char currCode[4];

    f = fopen("grad.dat", "r");
    if(!f){
        printf("Error: could not open file\n");
        exit(1);
    }

    while (1){
        fscanf(f, "%s %s %s %s %d %d\n", 
            code, country, gender, degree ,
            &year, &amount);
        
        //Create an Array of country structures
        // Note: this if condition triggers when the current line's country code is new
        if(strcmp(code, currCode) != 0){ 
            initCountry(code, country, year, &newCountry); 
            addCountryToArray(arr, newCountry, NO_CONDITION);
            strcpy(currCode, code); //change the current code to the new country's
        }

        //Create an linked list of line structures
        initLine(code, country, gender, degree, year, amount, &line);
        addLineToList(list,line);

        if(feof(f))
            break;
    }

    fclose(f);
}

/****************************************************************************
 * Function: initLine()
 *  Purpose: dynamically allocate memory for a LineType struct, initialize its fields
 *      out: LineType Struct, a double pointr
 *       in: Country Code, a String
 *       in: Country Name, a String
 *       in: the line's gender, a String
 *       in: the line's degree type, a String
 *       in: the line's year, an int
 *       in: the amount of degrees awarded for the 
 *           country, year, gender and degree type combination, an int
 *   return: double pointer to LineType
*****************************************************************************/
void initLine(char *inpCode, char *inpCountry, char *inpGen, char *inpDeg, int inpYear, int inpAmount, LineType **l){
    *l = (LineType*) malloc(sizeof(LineType));
    strcpy((*l)->code, inpCode);
    strcpy((*l)->country, inpCountry);
    strcpy((*l)->gender, inpGen);
    strcpy((*l)->degree, inpDeg);
    (*l)->year = inpYear;
    (*l)->amount = inpAmount;
}

/**********************************************************************************
 * Function: initList()
 *  Purpose: dynamically allocate memory for a ListType struct, initialize its fields
 *      out: the list's head, a node
 *      out: the list's tail, a node
 *      out: double pointer to initialized list
 *   return: initialized list as output parameter
***********************************************************************************/
void initList(NodeType *h, NodeType *t, ListType **list){
  
  *list = (ListType *) malloc(sizeof(ListType));

  (*list)->head = h;
  (*list)->tail = t;
}

/**************************************************************************************************
 * Function: initLine()
 *  Purpose: dynamically allocate memory for a CountryType struct, initialize its fields to zero
 *      out: CountryType Struct, a double pointer
 *       in: Country Code, a String
 *       in: Country Name, a String
 *       in: first year for which the country has data, an int
 *   return: double pointer to CountryType
***************************************************************************************************/
void initCountry(char *inpCode, char *inpCountry, int inpYear, CountryType **c){
    *c = (CountryType *) malloc(sizeof(CountryType));

    strcpy((*c)->code, inpCode);
    strcpy((*c)->country, inpCountry);

    // All the statistics fields get initialized to zero
    (*c)->total14 = 0;
    (*c)->total15 = 0;
    (*c)->total16 = 0;
    (*c)->total17 = 0;

    (*c)->totalL6 = 0;
    (*c)->totalL7 = 0;
    (*c)->totalL8 = 0;
    (*c)->totalAll = 0;

    (*c)->totalWomen = 0;
    (*c)->femalePercentage = 0;

    (*c)->averageFirst = 0;
    (*c)->averageRecent = 0;
    (*c)->difference = 0;

    (*c)->firstYear = inpYear;
    (*c)->avePerYear = 0;
}