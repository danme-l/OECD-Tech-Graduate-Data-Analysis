#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"

// this .c file contains functions to generate each report

// Note: For all generateReport functions, country statistics' fields are reset
//       after the computations, so the country array's elements are not 
//       (net) updated and therefore not output parameters

/**********************************************************************************
 * Function: generateReport1()
 *  Purpose: compute the statistics for the report, print them
 *       in: Dynamic array of all the countries (for individual country statistics)
 *       in: Linked List of line structs (for global statistics)
 *   return: N/A  
***********************************************************************************/
void generateReport1(ArrayType *arr, ListType *list){
    int worldL6, worldL7, worldL8, worldAll;
    float col1, col2, col3, col4;
    NodeType *currNode = list->head;

    worldL6 = 0;
    worldL7 = 0;
    worldL8 = 0;
    worldAll = 0;

    //compute the global statistics
    while(currNode !=NULL){
        if(strcmp(currNode->data->gender, "T")){
            if(strcmp(currNode->data->degree, "L6")==0){
                worldL6 += currNode->data->amount;
                worldAll += currNode->data->amount;
            }if(strcmp(currNode->data->degree, "L7")==0){
                worldL7 += currNode->data->amount;
                worldAll += currNode->data->amount;
            }if(strcmp(currNode->data->degree, "L8")==0){
                worldL8 += currNode->data->amount;
                worldAll += currNode->data->amount;
            }
        }
        currNode = currNode->next;
    }

    //compute each individual country's statistics, print them, reset the fields
    for(int i=0;i<arr->size;i++){
        calcCountryByDegree(list, arr->elements[i]);
        col1 = ((float)arr->elements[i]->totalL6 / (float)worldL6)*100;
        col2 = ((float)arr->elements[i]->totalL7 / (float)worldL7)*100;
        col3 = ((float)arr->elements[i]->totalL8 / (float)worldL8)*100;
        col4 = ((float)arr->elements[i]->totalAll / (float)worldAll)*100;

        printf("%25s |   L6: %6.2f %% | L7: %6.2f %% | L8: %6.2f %% | All degrees: %1.2f %%\n",
               arr->elements[i]->country, col1, col2, col3, col4);
        
        clearFields(arr->elements[i]);
    }

    printf("\n\n");
}

/************************************************************************************************
 * Function: generateReport2()
 *  Purpose: compute the statistics for the report, print them
 *       in: Dynamic array of all the countries (for individual country statistics)
 *       in: Linked List of line structs (input for helper function calcCountryByFemaleGrads())
 *   return: N/A  
*************************************************************************************************/
void generateReport2(ArrayType *arr, ListType *list){
    // initialize a new dynamic array for storing the countries in the relevant order 
    ArrayType countriesByWomen;

    countriesByWomen.size = 0;
    countriesByWomen.elements = NULL;

    // compute each individual country's statistics, add them to the array
    for(int i=0;i<arr->size;i++){
        calcCountryByFemaleGrads(list, arr->elements[i]);
        arr->elements[i]->femalePercentage = ((float) arr->elements[i]->totalWomen / (float) arr->elements[i]->totalAll)*100;
        addCountryToArray(&countriesByWomen, arr->elements[i], BY_TOTAL_WOMEN);
    }

    printf("Top 5:\n");
    for(int i=0; i<5; i++){
        printf("%d. %16s |   %1.2f %%\n", i+1,
        countriesByWomen.elements[i]->country, countriesByWomen.elements[i]->femalePercentage);

    }
    printf("Bottom 5:\n");
    for(int i=countriesByWomen.size-1; i>countriesByWomen.size-6; i--){
        printf("%d. %16s |   %1.2f %%\n", i+1,
        countriesByWomen.elements[i]->country, countriesByWomen.elements[i]->femalePercentage);
    }

    // reset the fields
    for(int i=0; i<countriesByWomen.size; i++){
        clearFields(countriesByWomen.elements[i]);
    }

    printf("\n\n");

    // deallocate
    cleanUpArray(&countriesByWomen);
}

/**********************************************************************************
 * Function: generateReport3()
 *  Purpose: compute the statistics for the report, print them
 *       in: Dynamic array of all the countries (for individual country statistics)
 *       in: Linked List of line structs (for global statistics)
 *   return: N/A  
***********************************************************************************/
void generateReport3(ArrayType *arr, ListType *list){
    int world14, world15, world16, world17, worldAll;
    float col1, col2, col3, col4, col5;
    NodeType *currNode = list->head;

    world14 = 0;
    world15 = 0;
    world16 = 0;
    world17 = 0;
    worldAll = 0;

    //compute the global statistics
    while(currNode != NULL){
        if(currNode == list->tail){
            break;
        }
        if(strcmp(currNode->data->gender, "T") == 0){
            if(currNode->data->year == 2014){
                world14 += currNode->data->amount;
                worldAll += currNode->data->amount;
            }
            if(currNode->data->year == 2015){
                world15 += currNode->data->amount;
                worldAll += currNode->data->amount;
            }
            if(currNode->data->year == 2016){
                world16 += currNode->data->amount;
                worldAll += currNode->data->amount;
            }
            if(currNode->data->year == 2017){
                world17 += currNode->data->amount;
                worldAll += currNode->data->amount;
            }
        }    
        currNode = currNode->next; 
    }

    //compute each individual country's statistics, print them, reset the fields
    for(int i=0;i<arr->size;i++){
        calcCountryByYear(list, arr->elements[i]);
        col1 = ((float)arr->elements[i]->total14 / (float)world14)*100;
        col2 = ((float)arr->elements[i]->total15 / (float)world15)*100;
        col3 = ((float)arr->elements[i]->total16 / (float)world16)*100;
        col4 = ((float)arr->elements[i]->total16 / (float)world16)*100;
        col5 = ((float)arr->elements[i]->totalAll / (float)worldAll)*100;

        printf("%25s |   2014: %6.2f %% | 2015: %6.2f %% | 2016: %6.2f %% | 2017: %6.2f %% | All years: %1.2f %%\n",
               arr->elements[i]->country, col1, col2, col3, col4, col5);
        
        clearFields(arr->elements[i]);
    }

    printf("\n\n");

}

/**********************************************************************************
 * Function: generateReport4()
 *  Purpose: compute the statistics for the report, print them
 *       in: Dynamic array of all the countries (for individual country statistics)
 *       in: Linked List of line structs (input for helper functions)
 *       in: number of years to calculate for
 *   return: N/A  
***********************************************************************************/
void generateReport4(ArrayType *arr, ListType *list, int n){
    
    // make sure the user enters a number less than or equal to 4
    if (n > 4){
        printf("Please enter a lower number.\n");
        return;
    }

    // initialize a new dynamic array for storing the countries in the relevant order 
    ArrayType countriesByFemaleGradIncrease;

    countriesByFemaleGradIncrease.size = 0;
    countriesByFemaleGradIncrease.elements = NULL;

    // compute the statistics
    for(int i=0; i<arr->size; i++){
        calcFirstNYears(list, arr->elements[i], n);
        calcRecentNYears(list, arr->elements[i], n);
        arr->elements[i]->difference = (arr->elements[i]->averageRecent - arr->elements[i]->averageFirst);

        addCountryToArray(&countriesByFemaleGradIncrease, arr->elements[i], BY_FEMALE_GRAD_INCREASE);
    }

    // print them
    for(int i=0; i<countriesByFemaleGradIncrease.size;i++){
        printf("%15s: %9.2f difference between first %d years and last %d years\n",
            countriesByFemaleGradIncrease.elements[i]->country,
            countriesByFemaleGradIncrease.elements[i]->difference, n, n);
    }

    printf("\n\n");

    // reset the fields
    for(int i=0; i<countriesByFemaleGradIncrease.size; i++){
        clearFields(countriesByFemaleGradIncrease.elements[i]);
    }

    // deallocate
    cleanUpArray(&countriesByFemaleGradIncrease);
}

/**********************************************************************************
 * Function: generateReport5()
 *  Purpose: compute the statistics for the report, print them
 *       in: Dynamic array of all the countries (for individual country statistics)
 *       in: Linked List of line structs (input for helper function)
 *   return: N/A  
***********************************************************************************/
void generateReport5(ArrayType *arr, ListType *list){
    // initialize a new dynamic array for storing the countries in the relevant order 
    ArrayType countriesByAnnualAverage;

    countriesByAnnualAverage.size = 0;
    countriesByAnnualAverage.elements = NULL;
    
    // compute each country's statistics, add it to the array
    for(int i=0; i<arr->size; i++) {
        calcAvePerYear(list, arr->elements[i]);
        addCountryToArray(&countriesByAnnualAverage, arr->elements[i], BY_ANNUAL_AVE);
    }

    // print the statistics
    for(int i=0; i<countriesByAnnualAverage.size; i++){
        printf("%15s | %1.2f per year\n", 
            countriesByAnnualAverage.elements[i]->country, countriesByAnnualAverage.elements[i]->avePerYear);
    }

    // reset the fields
    for (int i=0; i<arr->size; i++)
    {
        clearFields(arr->elements[i]);
    }

    printf("\n\n");

    // deallocate
    cleanUpArray(&countriesByAnnualAverage);
        
}  