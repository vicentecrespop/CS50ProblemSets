from cs50 import get_float
while (True):
    # Gets change
    cash = get_float("Change owed: ")
    # If valid change break out of the loop
    if (cash >= 0):
        break
# Coins avaliable
coins = [0.25, 0.10, 0.05, 0.01]
coins_count = 0
for i in coins:
    # While change is bigger than the coin does change - coin
    while (cash >= i):
        cash -= i
        cash = round(cash, 2)
        coins_count += 1
print(coins_count)