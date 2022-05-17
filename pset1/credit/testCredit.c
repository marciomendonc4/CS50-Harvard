#include <stdio.h>
#include <cs50.h>

bool iseven(int n);
bool isodd(int n);

int main(void)
{   //USER INPUT FOR A CREDIT CARD NUMBER
    long ccn;
    do
    {
        ccn = get_long("number: \n");
    } while (ccn<0);
    
    long ccn2 = ccn; //STORES THE VALUE OF CREDIT CARD NUMBER
    int sum = 0;
    int sum2 = 0;
    int count = 0;
    
    // CHECK THE AMOUNT OF DIGITS
    while(ccn2 != 0)
    {
        ccn2 /=10;
        count++;
    }
    int count2 = count; //STORES THE VALUE OF COUNT
    int count3 = count2;
    ccn2 = ccn;
    
    // CHECK VALIDITY USING LUNH'S ALGORITHM
    
    if (count == 13 || count == 15)
    {
    
    while(ccn != 0)
    {
        if(iseven(count))
        {
        
           int digit = 2 * (ccn%10);
             int digit2= digit/10 + digit%10;
             sum2 += digit2;
        }
        else
        {
           int digit = ccn%10;
            sum += digit;
          
        }
        
        count--;
        ccn /= 10;
        
    }
    }
    
    if (count == 16)
    {
        while(ccn != 0)
    {
        if(iseven(count))
        {
            int digit = ccn%10;
            sum += digit;
           
        }
        else
        {
            int digit = 2 * (ccn%10);
             int digit2= digit/10 + digit%10;
             sum2 += digit2;
          
        }
        
        count--;
        ccn /= 10;
        
    }
    }
    ccn = ccn2;
    
    int sum_total = sum + sum2;
    
    count = count2;
    
    
    if(sum_total % 10 == 0)
    {
        switch(count)
        {
            case 13:
            if (ccn >= 4e12 && ccn < 5e12 )
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
    
    
    
    printf("sum_total= %i, count = %i\n", sum_total, count);
    //printf("%i ,%i, count = %i, ccn: %ld\n", sum, sum2, count2, ccn);
    //printf("math = %i", math2);
}

bool iseven(int n)
{
    return n % 2 == 0;
}
bool isodd(int n)
{
    return n % 2 == 1;
}