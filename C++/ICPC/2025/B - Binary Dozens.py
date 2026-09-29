while True:
    b = input()

    if b == "*":
        break

    n = int(b, 2)
    print(n % 12)
