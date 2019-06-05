def is_palindrome(num):
    temp = num
    total = 0
    while temp > 0:
        total = total * 10 + temp % 10
        temp = temp // 10

    return total == num

print('123: %s' %(is_palindrome(123)))
print('12321: %s' %(is_palindrome(12321)))

