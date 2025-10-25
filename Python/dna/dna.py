import csv
import sys

""" Define new type """
class person:
    def __init__(self, name, samples, occursions):
        self.name = name
        self.occursions = dict(zip(samples, occursions))
    def convert(self):
        for key in self.occursions:
            self.occursions[key] = int(self.occursions[key])

def main():

    # Done-0: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python DATABASE SEQUENCE")
        sys.exit(1)

    # Done-0: Read database file into a variable
    people = []

    with open(sys.argv[1], 'r') as file:
        reader = csv.reader(file)
        for row in reader:
            samples = row[1:]
            break

        for row in reader:
            one = person(row[0], samples, row[1:])
            people.append(one)

    # Done-0: Read DNA sequence file into a variable
    with open(sys.argv[2], 'r') as file:
        reader = csv.reader(file)
        for row in reader:
            sequence = row[0]
            break

    # Done-0: Find longest match of each STR in DNA sequence
    lengths = []

    for sample in samples:
        length = longest_match(sequence, sample)
        lengths.append(length)
    longests = dict(zip(samples, lengths))


    # Done-0: Check database for matching profiles
    for i in range(len(people)):
        people[i].convert()
        if people[i].occursions == longests:
            print(people[i].name)
            break
    else:
        print("no match")

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
