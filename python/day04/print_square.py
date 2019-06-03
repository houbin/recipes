import math

for x in range(0, 6):
    y = 0
    while y <= x:
        print('*', end='')
        y += 1
    print()

print()

for x in range(0, 6):
    for y in range(0, 6):
        if y < x:
            print(' ', end = '')
        elif y >= x:
            print('*', end = '')
    print()

print()

for x in range(0, 5):
    for y in range(0, 10):
        if abs(y - 4) <= x:
            print('*', end = '')
        else:
            print(' ', end = '')
    print()



