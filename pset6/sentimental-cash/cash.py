# Function responsible for prompting the user
def get_change_owed():
    while True:
        try:
            c = float(input("Change owed: "))
            # If it's a valid input, returning the value
            if c > 0:
                return c
        # Catching possible error
        except ValueError:
            print("Invalid input")


# Function that returns the least amount of coins needed
def coin_counter(change):
    coins = 0
    while change >= 25:
        coins += 1
        change -= 25
    while change >= 10:
        coins += 1
        change -= 10
    while change >= 5:
        coins += 1
        change -= 5
    while change >= 1:
        coins += 1
        change -= 1
    return coins


change = get_change_owed()
# Multiplying the change for rounding purpose
coins_needed = coin_counter(change * 100)
# Displaying the result
print(coins_needed)