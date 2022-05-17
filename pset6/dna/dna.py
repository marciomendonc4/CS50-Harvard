import csv
import sys


def main():

    # TODO: Check for command-line usage
    if not len(sys.argv) == 3:
        print("Usage: python dna.py data.csv sequence.txt")
    # TODO: Read database file into a variable
    db = open(sys.argv[1], "r")
    # Reading the first line of the CSV file
    db1 = db.readline()
    # Removing the \n character and then spliting the string into different words
    data = db1.rstrip("\n")
    strs = data.split(",")
    # Deleting the first element "name"
    strs.pop(0)
    # TODO: Read DNA sequence file into a variable
    seq = open(sys.argv[2], "r")
    sequence = seq.read()
    # TODO: Find longest match of each STR in DNA sequence
    matches_list = longest_matches_list(sequence, strs)
    # TODO: Check database for matching profiles
    matching_profile(db, matches_list)

    db.close()
    seq.close()
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


def longest_matches_list(sequence, strs):
    # Creating a dictionary that will attribute each sequence with its respective longest_match
    dna = dict()
    # Creating a list that will store all the dictionaries created
    dna_list = list()
    for seq in strs:
        dna['seq'] = seq
        dna['long_rep'] = longest_match(sequence, dna['seq'])
        dna_list.append(dna.copy())
    # Creating a list that will store only the value of the longest matches found
    dna_rep_list = list()
    for dna in dna_list:
        for values in dna.values():
            # We're interested only in integers
            if type(values) == int:
                dna_rep_list.append(values)
    return dna_rep_list


def matching_profile(file, matches):
    lines = file.readlines()
    for line in lines:
        # Removing the '\n' character of the end of the string
        temp_line = line.rstrip("\n")
        # Dividing it in sets of words
        words = temp_line.split(",")
        # Saving the NAME for later return
        name = words.pop(0)
        # The list is currently made of string, converting all the items with the .map() method
        numbers_map = map(int, words)
        numbers = list(numbers_map)
        if matches == numbers:
            print(name)
            return
    # If no match was found
    print("No match.")


main()

