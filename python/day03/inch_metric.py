"""
英制与公制的转换
inch = metric / 2.54
metric = inch * 2.54
"""

value = float(input("input value: "))
unit = input('input unit: ')

if unit == 'in':
    print('%f inch = %f metric' %(value, value * 2.54))
else:
    print('%f inch = %f metric' %(value / 2.54, value))

