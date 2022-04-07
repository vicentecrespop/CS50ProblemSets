import csv
import sys


def main():

    # Check for command-line usage
    if (len(sys.argv) != 3):
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    # Read database file into a variable
    database = {}
    dna_profile = []
    with open(sys.argv[1]) as file:
        reader = csv.reader(file)
        for row in reader:
            database[row[0]] = row[1:]
    str_list = database.get('name')

    # Read DNA sequence file into a variable
    with open(sys.argv[2]) as dna_file:
        dna = dna_file.read().strip("\n")

    # Find longest match of each STR in DNA sequence
    for str in str_list:
        dna_profile.append(f'{longest_match(dna, str)}')

    # Check database for matching profiles
    for key, value in database.items():
        if dna_profile == value:
            print(key)
            return
    print("No match")
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


main()
