"""
将华氏温度转为摄氏温度
F = 1.8C+32
"""

f = float(input('请输出摄氏温度'))
c = float((f - 32) / 1.8)
print('%.1f摄氏度 = %.1f华氏度' % (c, f))
