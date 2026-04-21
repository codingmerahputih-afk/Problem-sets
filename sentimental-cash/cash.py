from cs50 import get_float

#done in 2020, redo in 2024


while True:
    dollars = get_float("Change owed: ")
    if dollars >= 0:
        break

cents = int( (dollars * 100) + 0.5)

total = 0
for coin in [25,10,5,1]:
    total += cents // coin
    cents %= coin

print(total)

