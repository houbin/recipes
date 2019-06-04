"""
buy chicken
14x + 8y = 200
"""

for x in range(0, 200):
    for y in range(0, 200):
        if 14 * x + 8 * y == 200:
            print('%d %d %d' % (x, y, 100-x-y))


