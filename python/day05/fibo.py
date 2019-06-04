"""
fibo
"""

x, y = 1, 1
print(x)
print(y)

for i in range(101):
    print(x+y)
    temp=x
    x = y
    y = temp+y
   
