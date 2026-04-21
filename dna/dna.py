import sys
import csv

def main():
    # Validate command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py <database.csv> <sequence.txt>")
        sys.exit(1)

    database_path = sys.argv[1]
    sequence_path = sys.argv[2]

    # Read database CSV and cast counts to int
    with open(database_path, "r", newline="") as f:
        reader = csv.DictReader(f)
        STRs = reader.fieldnames[1:]  # skip the "name" column
        database = []
        for row in reader:
            person = {"name": row["name"]}
            for s in STRs:
                person[s] = int(row[s])
            database.append(person)

    # Read DNA sequence and strip whitespace/newlines
    with open(sequence_path, "r") as f:
        sequence = f.read().strip()

    # Compute longest run for each STR in the sequence
    counts = {s: longest_match(sequence, s) for s in STRs}

    # Compare against each person in the database
    for person in database:
        if all(person[s] == counts[s] for s in STRs):
            print(person["name"])
            return

    print("No match")


def longest_match(sequence: str, subsequence: str) -> int:
    """
    Return length of the longest run of 'subsequence' in 'sequence'.
    (CS50 reference logic, robust to overlaps by advancing in subsequence-length steps)
    """
    longest_run = 0
    sub_len = len(subsequence)
    seq_len = len(sequence)

    for i in range(seq_len):
        count = 0
        # Check for consecutive runs of subsequence starting at i
        while True:
            start = i + count * sub_len
            end = start + sub_len
            if end > seq_len:
                break
            if sequence[start:end] == subsequence:
                count += 1
            else:
                break

        longest_run = max(longest_run, count)

    return longest_run


if __name__ == "__main__":
    main()
