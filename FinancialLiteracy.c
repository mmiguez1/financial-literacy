/* Created: Maygan Miguez, 13 April 2020, CMPS 1600 Lab section 2
 * FinancialLiteracy simulates how much money financially literate person vs. non-financially literate
 * person has after 40 years. Provides functions for computing a year's rent, a year's savings balance after interest,
 * a year's debt payments, a year's worth of rent payments, a year's worth of mortgage payments, and a 40 year
 * simulation of these functions.
 */
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

struct financialIdentity {
    double savings; //savings account
    double checkings; //checking account
    double debt; //debt balance
    double loan; //mortgage loan amount
    int yearsWithDebt; //number of years in debt
    int yearsRented; //number of years renting apartment
    double debtPaid; //amount of debt that's been paid
};
struct financialIdentity *fl; //Financially literate person
struct financialIdentity *nfl; //Non-financially literate person

//Update savings account balance after one year
//Parameters:
//person
//savings interest rate (fl = 7%, nfl = 1%)
void savingsPlacement(struct financialIdentity *person, double interestRate) {
    person->savings = person->savings * (1 + (interestRate/100));
}

//Compute amount left in debt and balance left in accounts for one year of debt payments
//Parameters:
//person
//debt interest rate (20%)
//additional payment - fl ($15), nfl ($1)
void debt(struct financialIdentity *person, double interestRate, double addlPay) {
    //12 months of payments
    for (int i=0;i<12; i++) {
        double payment = (person->debt * 0.03) + addlPay;
        if (person->debt > 0.0) {
            person->debt = person->debt - payment;
            person->debtPaid = person->debtPaid + payment;
            if (person->checkings >= payment) {
                person->checkings = person->checkings - payment;
            }
            else {
                person->savings = person->savings - payment;
            }
        }
    }
    if (person->debt > 0.0) {
        person->yearsWithDebt++;
        person->debt = person->debt * (1 + (interestRate / 100));
    }
}

//Compute balance left in checking account after one year of renting apartment
//Parameters:
//person
//Rent amount ($850)
void rent(struct financialIdentity *person, double rentAmt) {
    //12 months of payments
    for (int i=0;i<12; i++) {
        if (person->checkings < rentAmt) {
            person->checkings = person->checkings - rentAmt;
            double remainingAmt = person->checkings;
            if (person->checkings < 0) {
                person->savings = person->savings + remainingAmt;
                person->checkings = person->checkings - remainingAmt;
            }
        } else {
            person->checkings = person->checkings - rentAmt;
        }
    }
    person->yearsRented++;

}

//Compute balance left in checking account after one year of mortgage payments
//Parameters:
//person
//mortgageAmount = House Price - Down Payment
//interestRate - fl (4.5%), nfl (5%)
//mortgageTerm (30 years)
void house(struct financialIdentity *person, double mortgageAmount, double interestRate, double mortgageTerm) {
    //mortgage formula
    double numOfPay = 12 * mortgageTerm;
    double interest = (interestRate/100) / 12;
    double discountFactor = (pow(1+interest, numOfPay) - 1) / (interest * pow(1+interest,numOfPay));
    double payment = mortgageAmount / discountFactor;

    //12 months of payments
    for (int i = 0;i<12;i++) {
        person->loan = person->loan - payment;
        person->loan = person->loan + (person->loan * interest) ;
        if (person->checkings < payment) {
            person->checkings = person->checkings - payment;
            double remainingAmt = person->checkings;
            if (person->checkings < 0) {
                person->savings = person->savings + remainingAmt;
                person->checkings = person->checkings - remainingAmt;
            }
        } else {
            person->checkings = person->checkings - payment;
        }
    }
}

//Simulation of fl & nfl that computes their wealth after 40 years using parameters from input file
//and printing wealth after 40 years to output file.
//Parameters:
//person
//yearly salary ($59,000)
//financially literate boolean (fl = true, nfl = false)
//input file name
//output file name
int simulate(struct financialIdentity *person, double yearlySalary, bool financiallyLiterate,
        const char *inputFileName, const char *outputFileName) {
    person->debtPaid = 0;
    person->checkings = 0;
    person->savings = 5000.00;
    person->debt = 30100.00;
    bool houseBought = false;

    static double savingsInterestRate, mortgageInterestRate, debtInterestRate, debtAdditionalPayment,
            rentAmount, mortgageAmount, mortgageTerm, housePrice;

    //Take in input file parameters
    FILE *in_file;
    in_file= fopen(inputFileName, "r");
    fscanf(in_file,"Debt Interest Rate: %lf\n", &debtInterestRate);
    fscanf(in_file,"Debt Additional Payment: %lf\n",&debtAdditionalPayment);
    fscanf(in_file,"Rent Amount: %lf\n",&rentAmount);
    fscanf(in_file, "Savings Interest Rate: %lf\n", &savingsInterestRate);
    fscanf(in_file,"House Price: %lf\n", &housePrice);
    fscanf(in_file,"Mortgage Interest Rate: %lf\n", &mortgageInterestRate);
    fscanf(in_file,"Mortgage Term: %lf",&mortgageTerm);

    //close input file
    fclose(in_file);


    static int arr[41];
    FILE *out_file;
    out_file = fopen(outputFileName,"w");

    if (person == (struct financialIdentity *) &fl) {
        fprintf(out_file, "Person is financially literate.\n");
    }
    else if (person == (struct financialIdentity *) &nfl) {
        fprintf(out_file, "Person is not financially literate.\n");
    }

    for (int year = 0; year<41; year++) {

        //write each array element to output file
        int wealth = (int) person->checkings + (int) person->savings - (int) person->debt - (int) person->loan;
        arr[year] = wealth;
        fprintf(out_file,"year %d: %d\n", year, arr[year]);

        //Put 20% of income into savings account & 30% of income into checking account
        person->savings = person->savings + (yearlySalary * 0.20);
        person->checkings = person->checkings + (yearlySalary * 0.30);

        //Non-financially literate person
        if (!financiallyLiterate) {
            mortgageAmount = housePrice - (housePrice * 0.05);
            debt((struct financialIdentity *) &nfl, debtInterestRate, debtAdditionalPayment);

            if (person->savings < (housePrice * 0.05) && !houseBought) {
                    rent((struct financialIdentity *) &nfl, rentAmount);
                }
            else if (person->savings >= (housePrice * 0.05) && !houseBought ) {
                person->loan = mortgageAmount;
                    house((struct financialIdentity *) &nfl, mortgageAmount, mortgageInterestRate, mortgageTerm);
                    houseBought = true;
            }
            else if (houseBought && person->loan > 0) {
                house((struct financialIdentity *) &nfl, mortgageAmount, mortgageInterestRate, mortgageTerm);
            }
            savingsPlacement((struct financialIdentity *) &nfl, savingsInterestRate);
        }

        //Financially literate person
        if (financiallyLiterate) {
            mortgageAmount = housePrice - (housePrice * 0.20);
            debt((struct financialIdentity *) &fl, debtInterestRate, debtAdditionalPayment);

            if (person->savings < (housePrice * 0.20) && !houseBought) {
                rent((struct financialIdentity *) &fl, rentAmount);
            }
            else if (person->savings >= (housePrice * 0.20) && !houseBought) {
                person->loan = mortgageAmount;
                house((struct financialIdentity *) &fl, mortgageAmount, mortgageInterestRate, mortgageTerm);
                houseBought = true;
            }
            else if (houseBought && person->loan > 0) {
                    house((struct financialIdentity *) &fl, mortgageAmount, mortgageInterestRate, mortgageTerm);
                }

            savingsPlacement((struct financialIdentity *) &fl, savingsInterestRate);
        }

    }
    //close output file
    fclose(out_file);
    return (int) arr; //return array
}



