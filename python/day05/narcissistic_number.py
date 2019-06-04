"""
narcissistic number
"""

loop = 0
for i in range(100, 999):
    hundred_digit = i // 100
    tens_digit = (i % 100) // 10
    single_digit = i % 10
    
    if hundred_digit ** 3 + tens_digit ** 3 + single_digit ** 3 == i:
        print('%d: %d' % (loop, i))
        loop += 1

