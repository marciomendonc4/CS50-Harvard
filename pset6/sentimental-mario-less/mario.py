# Function that prompts the user
def get_height():
    while True:
        try:
            h = int(input('Height: '))
            # Checking the validity of the input
            if h >= 1 and h <= 8:
                return h
        # Catching any value error
        except ValueError:
            print("Only integers between 1 and 8 are accepted.")
            

height = get_height()

"""
Let's assume that the user prompted number 4 as height:
In the first row we want 3 spaces printed and only 1 hash, in the second row 2 spaces and 2 hashes, and so forth.
Translating that to the algorithm, we have:
FIRST ROW: (4 - 1 - 0) * spaces and (1 + 0) * hash
SECOND ROW: (4 - 1 - 1) * spaces and (1 + 1) * hash
THIRD ROW: (4 - 1 - 2) * spaces and (1 + 2) * hash
FOURTH ROW: (4 - 1 - 3) * spaces and (1 + 3) * hash
"""
for i in range(height):
    print((height - 1 - i) * " ", end="")
    print((i + 1) * "#")