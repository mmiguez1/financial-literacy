# Financial Literacy Project
Financial Literacy Project simulates how much money a financially literate person versus a non-financially literate person would have after 40 years of financial decisions. 
      

## To Run FinancialLiteracy.c: 

1. Open main.c file

2. Call simulate function( ) function from FinancialLiteracy.c with added file parameters
    (specify file location and file name in the file parameters)
```
	simulate(struct financialIdentity *person, double yearlySalary, 
		bool financiallyLiterate, const char *inputFileName, 
		const char *outputFileName)
```

## Input & Output
Example file results from calling simulate function for several people provided. The example input file names are in_person1.txt, in_person2.txt, in_person3.txt, and in_person4.txt. The example output file names for running the function on these four files are respectively out_person1.txt, out_person2.txt, out_person3.txt, and out_person4.txt.
        
The input files for person 1 and 2 use original values from simulation. The input files for person 3 and 4 use new values and a different yearly income than original simulation. All output files specify if person is financially literate or non-financially literate and lists a person's wealth amount for years 0 - 40.
         
## To Create Your Own Input File: 

Input file allows you to choose your own values for debt interest rate, additional
amount paid on each debt payment, rent payment amount, savings interest rate, house price,
mortgage interest rate, and mortgage term.

(Example input file below)
```
Debt Interest Rate: 20
Debt Additional Payment: 30
Rent Amount: 1000
Savings Interest Rate: 7
House Price: 175000
Mortgage Interest Rate: 4.5
Mortgage Term: 30
```
*Note: There is one space between each word, no space before the colon, & one space
       in between the colon and number. 
