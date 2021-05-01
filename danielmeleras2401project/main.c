#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"

/** 
 * Final project - Daniel Meleras - 100938884
 * gotta parse through the input list grad.data
 * 
*/

int main(){
    char str1[3], str2[3], str3[3];
    int choice, choice2, choice3;

    ListType *gradData;

    NodeType *head = NULL;
    NodeType *tail = NULL;

    ArrayType countries;

    countries.size = 0;
    countries.elements = NULL;

    initList(head, tail, &gradData);

    initData(gradData, &countries);

    //----------------------------------------------------------------------------------
    //DRIVER CODE BEGINS HERE
    


    printf("    Welcome to the OECD Technology Graduate Analysis.\n\nThis program analyzes the OECD data set on graduates in technology-related fields, including Computer Science, in participating countries between 2010 and 2017, inclusive.\n");
    printf("Please enter the number of the report you wish to view, from the options below ");
    printf("(At any time, you may enter 6 to exit or 0 to prompt the menu again).\n");
    displayMenu();
    fgets(str1, sizeof(str1), stdin);
    sscanf(str1, "%d", &choice);

    do{    
    
		switch (choice){

			case 1:
				generateReport1(&countries, gradData);
                choice = 0;
				break;
		
			case 2:
                printf("Please note that gender data was unavailable for Russia for L8 degrees.\n");
				generateReport2(&countries, gradData);
                choice = 0;
                break;
				
							
			case 3: 
				generateReport3(&countries, gradData);  
                choice = 0;
				break;

            case 4:
                printf("Please enter number of years to compare. For example, entering 2 will compare the first 2 years of the data with the last 2 years.\n\n");
                printf("Please note that gender data was unavailable for Russia for L8 degrees.\n");
                printf("In addition, note that the country's have varying amounts of years for which data is available.\nThis means that results may be skewed if you enter a number more than half the size of a country. For example, \nCosta Rica has data from only 2014 to 2017, entering 3 will compare the data from 2014 to 2016 with the data from 2015 to 2017.\n");
                printf("Enter number:");
                fgets(str3, sizeof(str3), stdin);
                sscanf(str3, "%d", &choice3);
                
                generateReport4(&countries, gradData, choice3);
                choice = 0;
                break;

            case 5:
                generateReport5(&countries, gradData);
                choice = 0;
                break;

            case 6:
                displayMenu();
                choice = 0;
                break;
			
			case 7: 
                printf(" *** Thank you and thanks for a very interesting COMP 2401!!! ***\n");
                
                cleanUpList(gradData);
                for(int i=0;i<countries.size; i++){
                    cleanUpCountry(countries.elements[i]);
                }
                cleanUpArray(&countries);

				exit(0);
				
			break;
		}
		
        printf(" Enter another choice (1-5), 6 to display the menu again, or 7 to exit\n");

		fgets(str1, sizeof(str1), stdin);
		sscanf(str1, "%d", & choice);
		
		
	}while(choice != -1); 

    
    //----------------------------------------------------------------------------------

    //displayList(gradData);
    //displayArray(&countries);


    

    return 0;
}   
