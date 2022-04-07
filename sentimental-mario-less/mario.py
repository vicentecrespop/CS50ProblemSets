from cs50 import get_int
while (True):
    # Gets height
    height = get_int("Height: ")
    # If height is between 1 and 8 breaks out of the loop
    if (height >= 1 and height <= 8):
        break
# Prints half pyramid
for i in range(height):
    blocks = i + 1
    print(" " * (height - blocks), end="")
    print("#" * blocks)