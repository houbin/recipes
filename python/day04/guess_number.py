import random

answer = random.randint(1, 100)
counter = 0
while True:
    counter += 1
    number = int(input("please input your number:"))
    if number < answer:
        print("number bigger")
    elif number > answer:
        print("number smaller")
    else:
        print("right number")
        break

print('you guess %d' %(counter))
if counter > 7:
    print('need more smarter')
