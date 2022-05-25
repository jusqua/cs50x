from cs50 import get_int

# Get height from user input
height = 0

while height < 1 or height > 8:
    height = get_int("Height: ")

# Print stairs based on height
for i in range(height):
    print((" " * (height - i - 1)) + ("#" * (i + 1)) + "  " + ("#" * (i + 1)))
