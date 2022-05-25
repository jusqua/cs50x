from cs50 import get_int
from math import log10


def main():
    # Get card number from input
    number = get_int("Number: ")

    # Setup sum
    sumValue = sumCheck(number)

    # Print card name
    print(cardCheck(number, sumValue))


def sumCheck(number):
    product = 0
    sumValue = 0
    digit = 100

    # Luhn’s Algorithm at work
    for i in range(8):
        product = ((number % digit) // (digit // 10)) * 2
        sumValue += (product // 10) + (product % 10)
        digit *= 100

    digit = 10
    for i in range(8):
        sumValue += (number % digit) // (digit // 10)
        digit *= 100

    return sumValue


def cardCheck(number, sumValue):
    # Check invalid
    if sumValue % 10:
        return "INVALID"

    # Start process
    length = round(log10(number)) % 100
    digit = 10**length
    index = (number % digit) // (digit // 100)

    # Get card
    if length == 16:
        if index > 50 and index < 56:
            return "MASTERCARD"
        elif (index // 10) == 4:
            return "VISA"
        else:
            return "INVALID"
    elif length == 15 and (index == 34 or index == 37):
        return "AMEX"
    elif length == 13 and (index // 10 == 4):
        return "VISA"
    else:
        return "INVALID"


# Start
if __name__ == "__main__":
    main()
