"""
用户身份验证
"""

username = input('input username: ')
password = input('input password: ')

if username == 'houbin' and password == '123456':
    print("auth ok")
else:
    print("auth error")
