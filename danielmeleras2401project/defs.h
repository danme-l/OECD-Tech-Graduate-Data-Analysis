#define MAX_STRING 40

typedef struct {
    char code[4];
    char country[MAX_STRING];
    char gender[2];
    char degree[3];
    int year;
    int amount;
} LineType;

typedef struct {
  char code[4];
  char country[MAX_STRING];
  int totalL6, totalL7, totalL8, totalAll;
  int totalWomen;
  float femalePercentage;
  int total14, total15, total16, total17;
  float averageFirst, averageRecent, difference;
  float avePerYear;
  int firstYear;
} CountryType;

typedef struct Node {
  LineType *data;
  struct Node *prev;
  struct Node *next;
} NodeType;

typedef struct {
	NodeType *head;
	NodeType *tail;
} ListType;

typedef struct { 
	int size;
	CountryType **elements;
} ArrayType;

typedef enum {
  NO_CONDITION,
  BY_TOTAL_WOMEN,
  BY_FEMALE_GRAD_INCREASE,
  BY_ANNUAL_AVE
} SortType;

//INIT
void initData(ListType*, ArrayType*);
void initLine(char*, char*, char*, char*, int, int, LineType**);
void initList(NodeType*, NodeType*, ListType**);
void initCountry(char*, char*, int, CountryType**);

//UTIL
void addLineToList(ListType*, LineType*);
void addLineToList2(ListType*, LineType*);
void addCountryToArray(ArrayType*, CountryType*, SortType);
void clearFields(CountryType*);

//DISPLAY
void displayLine(const LineType*);
void displayList(const ListType*);
void displayCountry(const CountryType*);
void displayCountryLines(char*, ListType*);
void displayArray(ArrayType*);
void displayMenu();

//CALC
void calcCountryByDegree(ListType*, CountryType*);
void calcCountryByFemaleGrads(ListType* , CountryType*);
void calcCountryByYear(ListType*, CountryType*);
void calcFirstNYears(ListType*, CountryType*, int);
void calcRecentNYears(ListType*, CountryType*, int);
void calcAvePerYear(ListType*, CountryType*);

//REPORTS
void generateReport1(ArrayType*, ListType*);
void generateReport2(ArrayType*, ListType*);
void generateReport3(ArrayType*, ListType*);
void generateReport4(ArrayType*, ListType*, int);
void generateReport5(ArrayType*, ListType*);

//CLEAN UP
void cleanUpList(ListType*);
void cleanUpArray(ArrayType*);
void cleanUpCountry(CountryType*);