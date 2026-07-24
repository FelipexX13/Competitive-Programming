import sys

n = int(input())

for _ in range(n):
    a, b, c, d = map(int, input().split())

    l = max(a, c)
    r = min(b, d)

    print(max(0, r - l))