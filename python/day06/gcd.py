def gcd(x, y):
    (x, y) = (x > y) ? (y, x) : (x, y)
    for factor in range(x, 0, 1):
        if x % factor == 0 and y % factor == 0:
            return factor

def lcm(x, y):
    return x * y // gcd(x, y)
