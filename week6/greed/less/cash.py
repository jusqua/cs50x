from cs50 import get_float

# Setup varibles
coins = [25, 10, 5, 1]
changeOwed = -1
remaning = 0
amount = 0

# Get change
while changeOwed < 0:
    changeOwed = round(100 * get_float("Change owed: "))

# Setup amount
for coin in coins:
    amount += changeOwed // coin
    remaning = changeOwed // coin
    changeOwed -= coin * remaning

# Print result
print(amount)
