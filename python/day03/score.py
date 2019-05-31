"""
百分制成绩转等级制成绩
90分以上        A   
80分 - 89分     B
70分 - 79分     C
60分 - 69分     D
60分以下        E
"""

score = int(input("input your score: "))
if score >= 90:
    grade = 'A'
elif score >= 80 and score <= 89:
    grade = 'B'
elif score >= 70 and score <= 79:
    grade = 'C'
elif score >= 60 and score <= 69:
    grade = 'D'
else:
    grade = 'E'

print("%d = %s" % (score, grade))
    
