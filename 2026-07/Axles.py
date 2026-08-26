from collections import defaultdict, deque
import math

dicc= defaultdict(list)

n = int(input())

for _ in range(n):
    s, c = map(int, input().split())
    dicc[s].append(c)


diccS = dict()
for key, val in dicc.items():
    diccS[key] = deque(sorted(dicc[key]))

res = 0
for key, val in diccS.items():
    while(len(val) > 1):
        a, b = val.popleft(), val.pop()
        res += math.log(max(a,b)/min(a,b))
print(res)
