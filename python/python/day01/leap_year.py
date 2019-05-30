"""
判断输入的年份是否为闰年
闰年: 年份能够被4整除, 不能被100整除，能被400整除
"""
year = int(input("input year: "))

is_leap_year=(year % 4 == 0 and year % 100 != 0 or year % 400 == 0)

print('是否为闰年: %s' % is_leap_year)

