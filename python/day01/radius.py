"""
输入圆的半径，计算周长和面积
l = 2πr
s = πr*r
"""

import math

r=float(input('input r:'))
perimeter = 2 * math.pi * r
area = math.pi * r * r
print('周长: %.2f, 面积: %.2f' % (perimeter, area))
