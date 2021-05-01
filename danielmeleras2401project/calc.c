#include <stdio.h>
#include <string.h>
#include "defs.h"

// this .c file contains functions to run the calculations for each report

/**********************************************************************************
 * Function: calcCountryByDegree()
 *  Purpose: counts the quantity of people who earned each type of degree in
 *           the country, as well as the total for all degrees
 *       in: Linked List of line structs 
 *   in/out: pointer to the CountryType struct we're computing statistics for
 *   return: pointer to the CountryType struct w/ fields updated
***********************************************************************************/
void calcCountryByDegree(ListType *list, CountryType *c){
    NodeType *currNode = list->head;

    while(currNode !=NULL){
        // this if condition triggers if the line is (a) both genders, (b) the current working country 
        // each internal if condition triggers if the line is for the correct degree type
        if((strcmp(currNode->data->gender, "T")==0) && (strcmp(currNode->data->code, c->code)==0)){
            if(strcmp(currNode->data->degree, "L6")==0){
                c->totalL6 += currNode->data->amount;
                c->totalAll += currNode->data->amount;
            }if(strcmp(currNode->data->degree, "L7")==0){
                c->totalL7 += currNode->data->amount;
                c->totalAll += currNode->data->amount;
            }if(strcmp(currNode->data->degree, "L8")==0){
                c->totalL8 += currNode->data->amount;
                c->totalAll += currNode->data->amount;
            }
        }
        currNode = currNode->next;
    }
}

/**********************************************************************************
 * Function: calcCountryByFemaleGrads()
 *  Purpose: counts the quantity of women who earned any level of degree in
 *           for the country, as well as the total for both
 *       in: Linked List of line structs 
 *   in/out: pointer to the CountryType struct we're computing statistics for
 *   return: pointer to the CountryType struct w/ fields updated
***********************************************************************************/
void calcCountryByFemaleGrads(ListType *list, CountryType *c){
    NodeType *currNode = list->head;

    while(currNode !=NULL){
        // this if condition triggers if the line is (a) female, (b) the current working country 
        if((strcmp(currNode->data->gender, "F") == 0) && (strcmp(currNode->data->code, c->code)==0)){
                c->totalWomen += currNode->data->amount;
            }
        // this if condition triggers if the line is (a) both genders, (b) the current working country 
        if((strcmp(currNode->data->gender, "T") == 0) && (strcmp(currNode->data->code, c->code)==0)){
                c->totalAll += currNode->data->amount;
            }
        currNode = currNode->next;
    }
}

/**********************************************************************************
 * Function: calcCountryByYear()
 *  Purpose: counts the quantity of people who earned any level of degree per year
 *           for the country, as well as the total for all years
 *       in: Linked List of line structs 
 *   in/out: pointer to the CountryType struct we're computing statistics for
 *   return: pointer to the CountryType struct w/ fields updated
 *     Note: this function only tabulates for the years 2014 to 2017, inclusive;
 *           these are the years for which we have data for every country
***********************************************************************************/
void calcCountryByYear(ListType *list, CountryType *c){
    NodeType *currNode = list->head;

    while(currNode !=NULL){
        // this if condition triggers if the line is (a) both genders, (b) the current working country 
        // each internal if condition triggers if the line is for the correct year
        if((strcmp(currNode->data->gender, "T")==0) && (strcmp(currNode->data->code, c->code)==0)){
            if(currNode->data->year == 2014){
                c->total14 += currNode->data->amount;
                c->totalAll += currNode->data->amount;
            }if(currNode->data->year == 2015){
                c->total15 += currNode->data->amount;
                c->totalAll += currNode->data->amount;
            }if(currNode->data->year == 2016){
                c->total16 += currNode->data->amount;
                c->totalAll += currNode->data->amount;
            }if(currNode->data->year == 2017){
                c->total17 += currNode->data->amount;
                c->totalAll += currNode->data->amount;
            }
        }
        currNode = currNode->next;
    }
}

/**********************************************************************************
 * Function: calcFirstNYears()
 *  Purpose: counts the quantity of women who earned any level of degree in the first
 *           n years for the country, computes the average over those years
 *       in: Linked List of line structs 
 *       in: number of years we're calculating for
 *   in/out: pointer to the CountryType struct we're computing statistics for
 *   return: pointer to the CountryType struct w/ fields updated
***********************************************************************************/
void calcFirstNYears(ListType *list, CountryType *c, int n){
    NodeType *currNode = list->head;
    float average;
    int firstYear = c->firstYear;
    int y = 0;

    while(currNode != NULL){
        // this if condition triggers if the line is (a) female, (b) the current working country 
        // and (c) within the most first n years
        if((strcmp(currNode->data->gender, "F")==0) 
            && (strcmp(currNode->data->code, c->code)==0)
            && (currNode->data->year < firstYear + n)){
                c->totalWomen += currNode->data->amount;
        }
        currNode = currNode->next;
    }
    
    c->averageFirst = (float) c->totalWomen / n;
}

/**********************************************************************************
 * Function: calcRecentNYears()
 *  Purpose: counts the quantity of women who earned any level of degree in the most
 *           recent n years for the country, computes the average over those years
 *       in: Linked List of line structs 
 *       in: number of years we're calculating for
 *   in/out: pointer to the CountryType struct we're computing statistics for
 *   return: pointer to the CountryType struct w/ fields updated
***********************************************************************************/
void calcRecentNYears(ListType *list, CountryType *c, int n){
    NodeType *currNode = list->tail;   // since we're iterating backwards this time
    float average;

    while(currNode != NULL){
        // this if condition triggers if the line is (a) female, (b) the current working country 
        // and (c) within the most recent n years
        if((strcmp(currNode->data->gender, "F")==0) 
            && (strcmp(currNode->data->code, c->code)==0)
            && (currNode->data->year > 2017 - n)){
                c->totalWomen += currNode->data->amount;
        }
        currNode = currNode->prev;
    }
    
    c->averageRecent = (float) c->totalWomen / n;
}

/******************************************************************************************
 * Function: calcAvePerYear()
 *  Purpose: computes the average quantity of degree earners from 2014 to 2017, inclusive
 *       in: Linked List of line structs 
 *       in: number of years we're calculating for
 *   in/out: pointer to the CountryType struct we're computing statistics for
 *   return: pointer to the CountryType struct w/ fields updated
 *     Note: this function only tabulates for the years 2014 to 2017, inclusive;
 *           these are the years for which we have data for every country
*******************************************************************************************/
void calcAvePerYear(ListType *list, CountryType *c){
    NodeType *currNode = list->head;
    int total = 0, n = 0; 

    while(currNode != NULL){
            // this if condition triggers if the line is (a) both genders, (b) the current working country and (c) 2014 or later
            if((strcmp(currNode->data->gender, "T")==0) 
                && (strcmp(currNode->data->code, c->code)==0)
                && (currNode->data->year > 2013)){
                    total += currNode->data->amount;
                    n++;
                }
       
        currNode = currNode->next;
    }

    c->avePerYear = (float) total / (float) (n/3);  

}