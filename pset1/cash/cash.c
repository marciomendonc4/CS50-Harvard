#include <cs50.h>
#include <stdio.h>

int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Ask how many cents the customer is owed
    int cents = get_cents();

    // Calculate the number of quarters to give the customer
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;

    // Calculate the number of dimes to give the customer
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;

    // Calculate the number of nickels to give the customer
    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;

    // Calculate the number of pennies to give the customer
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;

    // Sum coins
    int coins = quarters + dimes + nickels + pennies;

    // Print total number of coins to give the customer
    printf("%i\n", coins);
}
// Function responsible for prompt the user for a valid input
int get_cents(void)
{
    int change;
    do
    {
        change = get_int("Change owed: \n");
    }
    while (change < 0);
    return change;
}

int calculate_quarters(int cents)
{
    int coins = 0;
    // Looping through the amount of cents, decrementing 25 each time
    while (cents >= 25)
    {
        coins++;
        cents -= 25;
    }
    // Returning the amount of coins
    return coins;
}

int calculate_dimes(int cents)
{
    int coins = 0;
    // Looping through the amount of cents, decrementing 10 each time
    while (cents >= 10)
    {
        coins++;
        cents -= 10;
    }
    // Returning the amount of coins
    return coins;
}

int calculate_nickels(int cents)
{
    int coins = 0;
    // Looping through the amount of cents, decrementing 5 each time
    while (cents >= 5)
    {
        coins++;
        cents -= 5;
    }
    // Returning the amount of coins
    return coins;
}

int calculate_pennies(int cents)
{
    int coins = 0;
    // Looping through the amount of cents, decrementing 1 each time, till no money is left
    while (cents >= 1)
    {
        coins++;
        cents -= 1;
    }
    // Returning the amount of coins
    return coins;
}
