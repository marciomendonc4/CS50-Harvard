
def is_even(x):
    return x % 2 == 0


# Function responsible for the user input
def get_cc():
    while True:
        n = input("Number: ")
        if len(n) >= 13 and len(n) <= 16:
            return n
        else:
            print("INVALID")
            break


# Function that checks the validity of a credit card number accordingly with Luhn's Algorithm
def luhns_algorithm(ccn, digits):
    sum_even = 0
    sum_odd = 0
    if digits == 13 or digits == 15:
        while ccn > 0:
            if is_even(digits):
                digit = 2 * (ccn % 10)
                # In case of a 2 digits number, adding them together
                sum_even += int((digit / 10)) + (digit % 10)
            else:
                digit = ccn % 10
                sum_odd += digit
            digits -= 1
            ccn = int(ccn / 10)
    else:
        while ccn > 0:
            if is_even(digits):
                digit = ccn % 10
                sum_even += digit
            else:
                digit = 2 * (ccn % 10)
                # In case of a 2 digits number, adding them together
                sum_odd += int((digit / 10)) + (digit % 10)
            digits -= 1
            # Decrementing variable
            ccn = int(ccn / 10)
    # To be a valid credit card, the sum of the digits must return a number ended in 0
    sum_total = sum_even + sum_odd
    return sum_total % 10 == 0


# Once the validity was confirmed, this function attributes a brand to the credit card number
def print_brand(ccn):

    if (ccn >= 4e12 and ccn < 5e12) or (ccn >= 4e15 and ccn < 5e15):
        print("VISA")
    elif (ccn >= 34e13 and ccn < 35e13) or (ccn >= 37e13 and ccn < 38e13):
        print("AMEX")
    elif ccn >= 51e14 and ccn < 56e14:
        print("MASTERCARD")
    else:
        printf("INVALID")


ccn = get_cc()
# calculating the amount of digits
digits_amt = len(ccn)
# converting the string to and int data type
ccn = int(ccn)

is_valid = luhns_algorithm(ccn, digits_amt)

if is_valid:
    print_brand(ccn)
else:
    print("INVALID")
