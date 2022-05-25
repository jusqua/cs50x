import csv
import sys

# Ensure correct usage
if len(sys.argv) != 3:
    sys.exit("Usage: python dna.py data.csv sequence.txt")

# Read database
database = []
with open(sys.argv[1], "r") as file:
    readerDict = csv.DictReader(file)
    for person in readerDict:
        database.append(person)

# Setup keys
keys = list(database[0].keys())
keys.remove("name")

# Get sequence
sequence = ''
with open(sys.argv[2], "r") as file:
    sequence = file.readline().replace("\n", "")

# Get STR
STR = {}
for key in keys:
    have = True
    continues = 0
    count = 0
    higher = 0
    for index, char in enumerate(sequence):
        if continues:
            continues -= 1
            continue
        for increment, letter in enumerate(key):
            if (index + increment >= len(sequence)) or sequence[index + increment] != letter:
                have = False
                continues = 0
                break
            else:
                continues += 1
        if have:
            count += 1
            continues -= 1
        else:
            if higher < count:
                higher = count
            count = 0
            have = True
    STR[key] = higher

# Print name
have = True
for person in database:
    have = True
    for key in keys:
        if int(person[key]) != STR[key]:
            have = False
            break
    if have:
        print(person["name"])
        break

# Otherwise
if not have:
    print("No match")
