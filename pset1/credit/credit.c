#include <stdio.h>
#include <cs50.h>

bool iseven(int n);

int main(void)
{
    //USER INPUT FOR A CREDIT CARD NUMBER
    long ccn;
    do
    {
        ccn = get_long("number: \n");
    }
    while (ccn < 0);

    long ccn2 = ccn; //STORES THE VALUE OF CREDIT CARD NUMBER
    int sum = 0;
    int sum2 = 0;
    int count = 0; //VARIABLE USED TO STORE THE AMOUNT OF DIGITS

    // CHECK THE AMOUNT OF DIGITS

    while (ccn2 != 0)
    {
        ccn2 /= 10;
        count++;
    }
    int count2 = count; //STORES THE VALUE OF COUNT
    ccn2 = ccn;

    // CHECK VALIDITY USING LUNH'S ALGORITHM

    if (count == 13 || count == 15)
    {

        while (ccn != 0) //WHEN COUNTER IS EQUAL TO 0, THE LOOP IS ENDED
        {
            if (iseven(count)) //WHEN THE COUNTER IS EVEN
            {

                int digit = 2 * (ccn % 10);
                int digit2 = digit / 10 + digit % 10;
                sum2 += digit2;
            }
            else // WHEN THE COUNTER IS ODD
            {
                int digit = ccn % 10;
                sum += digit;

            }
            count--; //COUNTER DECREASES BY 1
            ccn /= 10; // EXCLUDES THE LAST DIGIT
        }
    }

    // CHECK VALIDITY USING LUNH'S ALGORITHM

    if (count == 16)
    {
        while (ccn != 0) //WHEN COUNTER IS EQUAL TO 0, THE LOOP IS ENDED
        {
            if (iseven(count)) //WHEN THE COUNTER IS EVEN
            {
                int digit = ccn % 10;
                sum += digit;
            }
            else // WHEN THE COUNTER IS ODD
            {
                int digit = 2 * (ccn % 10);
                int digit2 = digit / 10 + digit % 10;
                sum2 += digit2;
            }
            count--; //COUNTER DECREASES BY 1
            ccn /= 10; // EXCLUDES THE LAST DIGIT
        }
    }

    ccn = ccn2; //RETRIEVES VALUE
    int sum_total = sum + sum2; // TOTAL SUM OF THE DIGITS
    printf("\n\nSUM: %i\n\n", sum_total);
    count = count2;

    // PRINT OUT THE CREDIT CARD BRAND

    if (sum_total % 10 == 0)
    {
        switch (count)
        {
            case 13:
                if (ccn >= 4e12 && ccn < 5e12)
                {
                    printf("VISA\n");
                    break;
                }
            case 15:
                if ((ccn >= 34e13 && ccn < 35e13) || (ccn >= 37e13 && ccn < 38e13))
                {
                    printf("AMEX\n");
                    break;
                }
            case 16:
                if (ccn >= 51e14 && ccn < 56e14)
                {
                    printf("MASTERCARD\n");
                    break;
                }
                else if (ccn >= 4e15 && ccn < 5e15)
                {
                    printf("VISA\n");
                    break;
                }
            default:
                printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }

}

bool iseven(int n)
{
    return n % 2 == 0;
}