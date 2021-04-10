"""
This paradox tells us that if we have 23 people, the chance of 2 people having the same birthday is approximately 50%.

Demonstration
"""

import random

# test x times
x = 500000

# number of times 2 people had the same birthday
successful = 0
for z in range(x):

    # create birthdays
    birthdays = []

    people_count = 23

    for i in range(people_count):
        birthdays.append(random.randint(1, 365))

    # check for 2 people with same birthday
    success = False
    for y in range(people_count):
        if success:
            break
        for n in range(people_count):
            if (y != n):
                if (birthdays[y] == birthdays[n]):
                    successful += 1
                    success = True
                    break

chance = successful/x

print(str(chance * 100) + "%")
