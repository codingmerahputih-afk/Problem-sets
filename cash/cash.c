#include <cs50.h>
#include <stdio.h>
#include <math.h>


int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    //
    // Prompt the user for change owed, in cents
    int cents;
    do
    {
        cents = get_int("Change owed: ");
    }
    while (cents < 0);

    // Calculate how many quarters you should give customer
    int quarters = calculate_quarters(cents);

    // Subtract the value of those quarters from cents
    cents = cents - (quarters * 25);

    // Calculate the number of dimes to give to the customer
    int dimes = calculate_dimes(cents);
    cents = cents - (dimes * 10);

    //Calculate the number of nickles to give the customer
    int nickels = calculate_nickels(cents);
    cents = cents - (nickels * 5);

    //Calculate the number of pennies to give the customer
    int pennies = calculate_pennies(cents);
    cents = cents - (pennies * 1);

    //Sum coins
    int coins = quarters + dimes + nickels + pennies;

    //Print total number of coins to give to customer
    printf("%i\n", coins);
}

int calculate_quarters(int cents)
{

    // Hitung berapa quarter yang diberikan kepada customer
    int quarters = 0;
    while (cents >= 25)
    {
        quarters++;
        cents = cents - 25;
    }
    return quarters;


}

int calculate_dimes(int cents)
{
    // Calculate how many dimes you should give customer
    int dimes = 0;
    while (cents >= 10)
    {
        dimes++;
        cents = cents - 10;
    }
    return dimes;


}

int calculate_nickels(int cents)
{
    // Calculate how many nickles you should give customer
    int nickels = 0;
    while (cents >= 5)
    {
        nickels++;
        cents = cents - 5;
    }
    return nickels;


}

int calculate_pennies(int cents)
{
    // Calculate how many pennies you should give customer

    int pennies = 0;
    while (cents >= 1)
    {
        pennies++;
        cents = cents - 1;
    }
    return pennies;


}

