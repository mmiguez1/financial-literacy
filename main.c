/* Created: Maygan Miguez, 13 April 2020, CMPS 1600 Lab section 2
 * Main function calls simulate function in FinancialLiteracy.c
 */
#include "FinancialLiteracy.c"

//To call simulate function, specify if person is fl or nfl, yearly salary,
// 'true' if fl or 'false' if nfl, file location\name of input file, file location\name
// of output file
int main() {
    simulate((struct financialIdentity *) &fl, 120000, true,
             "in_person4.txt","out_person4.txt");
    simulate((struct financialIdentity *) &nfl, 120000, false,
             "in_person3.txt","out_person3.txt");

    return 0;
}
