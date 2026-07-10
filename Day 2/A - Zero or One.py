a, b, z = list(map(int, input().split()))

if 0<(a+b+z)< 3:
    if (a+b+z == 2 and a == 0) or (a+b+z == 1 and a == 1):
        print("A")
    if (a+b+z == 2 and b == 0) or (a+b+z == 1 and b == 1):
        print("B")
    if (a+b+z == 2 and z == 0) or (a+b+z == 1 and z == 1):
        print("C")
else:
    print('*')
