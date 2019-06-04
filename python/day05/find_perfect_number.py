"""
find perfect number
"""

for x in range(2, 100000):
    sum_divisor = 0
    y = 1
    while y <= x // 2:
        if x % y == 0:
            #print("%d: %d" % (x, y))
            sum_divisor += y
        y += 1
    if sum_divisor == x:
        print("%d" %(x))

        

    

