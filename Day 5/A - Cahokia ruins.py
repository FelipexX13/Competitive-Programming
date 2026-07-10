h, w = list(map(int,input().split()))

left = list(map(int,input().split()))
right = list(map(int,input().split()))

mins = float("inf")
for i in range(len(right)):
    x = w - right[i]
    mins = min(mins, x-left[i])

if mins // 2 == mins / 2:
    print(int(mins/2))
else:
    print(mins/2)