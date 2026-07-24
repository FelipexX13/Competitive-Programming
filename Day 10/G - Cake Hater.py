n = int(input())

a, b = list(map(int, input().split()))

donts = set(map(int, input().split()))

sol = False
for i in range(n):
    ingreds = list(map(int, input().split()))
    
    counter = 0
    if not sol:
        for j in range(1, ingreds[0]+1):
            if ingreds[j] in donts:
                counter += 1
            if counter > ingreds[0]/3:
                print(i+1)
                sol = True
                break
if not sol:
    print(-1)