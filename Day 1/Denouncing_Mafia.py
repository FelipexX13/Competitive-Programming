import copy
import sys

sys.setrecursionlimit(10**6)
m, k = list(map(int, input().split()))
entry = list(map(int, input().split()))

currMemb = 1
dicc = {1: []}
for node in entry:
    currMemb += 1
    if node in dicc:
        dicc[node] = dicc[node] + [currMemb]
    else:
        dicc[node] = [currMemb]

visited = set()
ans = []

def rec(curr, depth, prev):
    global visited, ans
    if curr in dicc:
        children = dicc[curr]
        first = True
        leafsDepth = []
        for son in children:
            newDep = rec(son, depth + 1, curr)
            leafsDepth.append(newDep)
        leafsDepth.sort(reverse=True)
        max = leafsDepth.pop(0)
        for i in leafsDepth:
            ans.append(i - depth)
        return max
    else:
        return depth
ans.append(rec(1, 1, None))
ans.sort(reverse=True)
sum = 0

curr = 0
while(curr < k and curr < len(ans)):
    sum+=ans[curr]
    curr+=1

print(sum)
