/*
Financial literacy simulation 

@author Sam Traylor 
@version 1.0
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>


typedef struct financialIdentity_struct {
	double savings;
	double checking; //money used to pay mortagage
	double debt; //from credit cards
	double loan; //from house loans
	int yearsWithDebt;
	int yearsRented;
	double debtPaid; //actual money used to pay off the debt

	//Below are values added to struct so that they can be specified by file//

	double savingsInterest;
	double loanInterest;
	double additionalPay;
	double yearsSimulated;

} financialIdentity;

void printPerson(financialIdentity* person) {
	printf("Savings: %lf Checking: %lf debt: %lf\n", person->savings, person->checking, person->debt);
}

void savingsPlacement(financialIdentity* person, double interestRate) {
	double adjustedRate;

	if (interestRate >= 1.0) {
		adjustedRate = interestRate / 100.0; //if taken in form '7', convert to 1.07
		adjustedRate += 1.0;
	}
	else {  // if given in form 0.07, convert to 1.07
		adjustedRate = interestRate + 1.0;
	}
	person->savings *= adjustedRate;
}


void debt(financialIdentity* person, double interestRate, double addlpay) {
	int x = 0;
	double adjustedRate;

	if (interestRate >= 1.0) {
		adjustedRate = interestRate / 100.0; //if taken in form '7', convert to 1.07
		adjustedRate += 1.0;
	}
	else {  // if given in form 0.07, convert to 1.07
		adjustedRate = interestRate + 1.0;
	}

	while(person->debt > 0.0 && x < 12) {
		person->yearsWithDebt++;
		double monthDebt = (person->debt * 0.03) + addlpay;
		double payment;

		if(monthDebt > person->debt) {
			payment = monthDebt - person->debt;
			person->checking -= payment;
			if(person->checking < 0.0) { //if this made checking neg, put enough back to make checking 0 and charge rest to savings
				person->savings -= (person->checking * -1.0);
				person->checking = 0.0; 

			}
			person->debt = 0.0;
			person->debtPaid += payment;  //add to debt paid
		}
		else{ 

			person->debtPaid += monthDebt;  //add to debt paid
			person->debt -= monthDebt;	     //subtract from debt
			person->checking -= (monthDebt);   //take payment from checking
			if(person->checking < 0.0) { //if this made checking neg, put enough back to make checking 0 and charge rest to savings
				person->savings -= (person->checking * -1.0);
				person->checking = 0.0; 
			}
		x++;
		}
	}
	person->debt *= adjustedRate;
} 

void rent(financialIdentity* person, double rentAmt) {
	int x = 0;
	while(x < 12) {
		person->yearsRented++;
		if((person->checking - rentAmt) > 0.0) { //If taking from checking would make negative
			person->savings -= (rentAmt - person->checking); //take the difference and subtract from savings
			person->checking = 0.0; //set checking 0
		}
		else {
			person->checking -= rentAmt;
		}
		x++;
	}
}

void house(financialIdentity* person, double housePrice, double interestRate, double mortgageTerm) {
	double adjustedRate;

	if (interestRate >= 1.0) {
		adjustedRate = interestRate / 100.0; //if taken in form '7', convert to 1.07
		adjustedRate += 1.0;
	}
	else {  // if given in form 0.07, convert to 1.07
		adjustedRate = interestRate + 1.0;
	}

	int month = 0;
	int payments = mortgageTerm * 12;
	double interest = adjustedRate / 12;
	double discountFactor = ((pow( (1 + interest), payments) - 1) / (interest * pow((1 + interest),payments)));
	double monthlyMortgagePayment = person->loan / discountFactor;

	while(month < 12 && person->loan > 0) {
		if (person->checking < monthlyMortgagePayment) {
			int leftOver = monthlyMortgagePayment - person->checking;
			person->checking = 0.0;
			person->savings -= leftOver;
		}
		else {
			person->checking -= monthlyMortgagePayment;
		}
		person->loan -= monthlyMortgagePayment;
		person->loan *= interest;
		month++;
	}
	
}

int* simulate(financialIdentity* person, double yearlySalary, bool financiallyLiterate) {
	int arr[41];
	int wealth;
	int year = 0;
	double savingsInterest;
	double loanInterest;
	double additionalPay;
	double downPayment;
	bool renting = true;
	bool loanAssigned = false;

	if(financiallyLiterate) {
		savingsInterest = 7.0;
		additionalPay = 15.0;
		downPayment = 0.20;
		loanInterest = 4.5;
	}
	else {
		savingsInterest = 1.0;
		additionalPay = 1.0;
		downPayment = 0.05;
		loanInterest = 5.0;
	}

	while(year < person->yearsSimulated) {

		if(year == 0) {
			arr[year] = (person->checking + person->savings) - person->debt - person->loan;
		}
		else {
			person->checking += (yearlySalary * 0.3);
			person->savings += (yearlySalary * 0.2);

			savingsPlacement(person, person->savingsInterest);
			debt(person,20.0,person->additionalPay);

			if(person->savings > (downPayment * 175000.0) && loanAssigned == false) {
				renting = false;
				person->savings -= downPayment * 175000.0;
				person->loan = 175000.0 - (downPayment * 175000.0);
				loanAssigned = true;
			}
			else if(renting == true) {
				rent(person, 850.0);
			}
			else if (renting == false && person->loan > 0.0) {
				house(person, 175000.0, person->loanInterest,30);
			}
			wealth = (person->checking + person->savings) - (person->debt + person->loan);
			arr[year] = wealth;
		}
		year++;
	}
	return arr;
}


int main(void) {

	char fileName[50];
	double doubs[8]; 
	int linesRead = 0;  

	printf("Please enter the name of your input file: \n");
	scanf("%s", fileName);

	FILE* f = fopen(fileName,"r");

	while(linesRead < 8) {
		fscanf(f, "%lf", &doubs[linesRead]);
		linesRead++;

	} 
	fclose(f);

	financialIdentity* person= NULL;
	person = (financialIdentity*)malloc(sizeof(financialIdentity));

	double yearlySalary = doubs[0];
	person->savings = doubs[1]; 
	person->checking = doubs[2];
	person->debt = doubs[3];
	person->debtPaid = 0.0; 
	person->loan = 0.0;
	person->yearsWithDebt = 0.0;
	person->yearsRented = 0.0;
	person->savingsInterest = doubs[4];
	person->loanInterest = doubs[5];
	person->additionalPay = doubs[6];
	person->yearsSimulated = doubs[7];

	int* array = simulate(person,yearlySalary,false);

	printf("Please specify desired name of output file: \n");
	scanf("%s",fileName);

	f = fopen(fileName,"w");
	int x;

	for(x = 0; x < yearsSimulated; x++) {
		fprintf(f, "Wealth: %d\n", array[x]);
	} 
}