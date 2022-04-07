from cs50 import get_string

# Gets text from user
text = get_string("Text: ")
words = 0
letters = 0
sentences = 0

# Calculates number os words, letters and sentences in the text
for i, items in enumerate(text):
    if (items.isspace()):
        words += 1
    if (items.isalpha()):
        letters += 1
    if (items == "!" or items == "?" or items == "."):
        sentences += 1
        if (i == len(text) - 1):
            words += 1

# Average number os letters and sentences per 100 words in the text
L = letters * 100 / words
S = sentences * 100 / words

# Coleman-Liau formula
formula = float(0.0588 * L - 0.296 * S - 15.8)
decimal = formula - int(formula)

# Rounds Coleman-Liau formula to the nearest integer
if (decimal > 0.50):
    formula = round(formula + 0.5)
else:
    formula = round(formula - 0.5)

# Prints Grade
if (formula < 1):
    print("Before Grade 1")
elif (formula >= 16):
    print("Grade 16+")
else:
    print(f"Grade {formula}")