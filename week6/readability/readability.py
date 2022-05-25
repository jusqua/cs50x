# Setup variables
checklist = [' ', ',', '.', '!', '?']
letters, words, sentences = 0, 0, 0
lastchar = ' '

# Get text from user input
text = input("Text: ")

# Setup letters, words and sentences
for char in text:
    if char in checklist:
        if lastchar not in checklist:
            words += 1
        if char in checklist[2:]:
            sentences += 1
    elif char != '\'':
        letters += 1

    lastchar = char

# Generating Coleman-Liau formula
colliau = (0.0588 * (letters * 100 / words)) - (0.296 * (sentences * 100 / words)) - 15.8

# Print grade
if colliau < 1:
    print("Before Grade 1")
elif colliau > 16:
    print("Grade 16+")
else:
    print(f"Grade {colliau:.0f}")
