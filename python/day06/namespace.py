def foo():
    global a
    b = 'hello'
    a = 123 

    def bar():
        c = True
        print(a)
        print(b)
        print(c)
    bar()
    print(a)

if __name__ == '__main__':
    a = 100
    foo()
    print(a)
