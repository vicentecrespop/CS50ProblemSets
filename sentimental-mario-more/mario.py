from cs50 import get_int
while (True):
    # Gets height
    height = get_int("Height: ")
    # If height is integer between 1 and 8 break out of the loop
    if (height >= 1 and height <= 8):
        break
# Print pyramid
for i in range(height):
    blocks = i + 1
    print(" " * (height - blocks), end="")
    print("#" * blocks, end="  ")
    print("#" * blocks)
