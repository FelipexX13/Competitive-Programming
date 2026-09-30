from collections import defaultdict
n = int(input())

dicc = defaultdict(int)
res = set()
total = 5*10*n
for _ in range(10*n):
    nums = list(map(int, input().split()))
    for i in nums:
        dicc[i] += 1
        if dicc[i] > 2*n:
            res.add(i)
res = sorted(list(res))
if len(res) == 0:
    print(-1)
else:
    print(*res)
