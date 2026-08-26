from collections import defaultdict

n = int(input())

state = defaultdict(int)
ans = 'yes'

for _ in range(n):
    inst, item = input().split()

    if inst == 'pickup':
        if state[item] != 0:
            ans = 'no'
            break
        state[item] = 1

    else:
        if state[item] != 1:
            ans = 'no'
            break
        state[item] = 2

if any(x != 2 for x in state.values()):
    ans = 'no'

print(ans)