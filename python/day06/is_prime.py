def is_prime(num):
    if num == 1:
        return False

    for factor in range(2, num, 1):
        if num % factor == 0:
            return False

    return True

print('123: %s' %(is_prime(123)))
print('23: %s' %(is_prime(23)))
print('234: %s' %(is_prime(234)))
