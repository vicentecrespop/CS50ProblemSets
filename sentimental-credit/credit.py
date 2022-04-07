from cs50 import get_string

# Gets number of card
card = get_string("Number: ")
size = len(card)
sum = 0

# Calculates Luhn's Algorithm
for i in range(size - 2, -1, -2):
    if (int(card[i]) * 2 > 9):
        sum += (int(card[i]) * 2) % 10
        sum += 1
    else:
        sum += int(card[i]) * 2
for i in range(size - 1, -1, -2):
    sum += int(card[i])

# Checks if the card is valid and which card it is
if (sum % 10 == 0):
    if (size == 15 and (card[:2] == "34" or card[:2] == "37")):
        print("AMEX")
    elif (size == 16 and (card[:2] == "51" or card[:2] == "52" or card[:2] == "53" or card[:2] == "54" or card[:2] == "55")):
        print("MASTERCARD")
    elif ((size == 13 or size == 16) and card[0] == "4"):
        print("VISA")
    else:
        print("INVALID")
else:
    print("INVALID")



