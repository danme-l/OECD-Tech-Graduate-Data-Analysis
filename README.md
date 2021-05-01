# OECD-Tech-Graduate-Data-Analysis
This is the complete C code for my final Project for COMP 2401: Intro to Systems Programming at Carleton University.

This program runs calculations on an OECD data set of technology graduates. The data set includes: 
 - data for some or all of the years from 2010 to 2017, inclusive, depending on the country
 - the quantity of male, female and total degree earners, for each of three degree types: L6, L7, and L8

The program reads the file, and presents the user with a series of options for reports to generate. The report that the 
user selects is then assembled and the results are printed to the screen.

The program includes the following files:
 - main.c: the driver file. this file contains the main user interface.
 - init.c: this file contains the functions to initialize and allocate memory for all of the data types used in the program.
 - util.c: this file contains utility functions that are needed by other functions over the course of the program's running.
 - calc.c: this file contains functions to perform the computations of statistics for each report.
 - reports.c: this file contains the functions that generate each of the five reports.
 - cleanUp.c: this file contains functions to deallocate all the memory that is allocated for the data types that are initialized over the course of the program's running.
 - defs.h: this contains the function prototypes as well as the struct definitions.
 - Makefile: a make file for linking and compilation.

To compile, simply navigate into the directory where the program files are contained and enter "make" into the shell. The 
Makefile will compile and link the files with the GNU compiler collection (gcc)

REPORTS
 (1) The graduate percentage in each country, by degree. All the coutries will be presented in a table, where the columns
        will contain the percentage of L6, L7, L8 and total degree earners (respectively) that are from the country.

 (2) The top five and bottom five countries for female participation. The top and bottom 5 countries will be listed,
        with the percentage of that country's graduates that are women, for all degree types and all years.

 (3) The graduate percentage in each country, by year. All the coutries will be presented in a table, where the columns
        will contain the percentage of 2014, 2015, 2016, 2017 and total degree earners (respectively) that are from the country.

 (4) The difference in female participation for the first n years and the last n years. The countries will be displayed 
        (in alphabetical order by country code, not by country name), and the difference between the average number of 
        female degree earners for the first n years compared to the last n years of the data set will be given. 
        The user can choose the number of years.
     Note: the maximum number of years that can be chosen is set to 4, this is because there are only 4 years of data 
           for Costa Rica, the country with the lowest number of years, so this maximum ensures accurate data for 
           every country in the data set.

 (5) Every country ranked in order of average number of graduates per year. The countries will be displayed in a top-down 
        list where the country with the highest average annual number of graduates, of any degree type and for both genders,
        at the top, and continuing in descending fashion.
