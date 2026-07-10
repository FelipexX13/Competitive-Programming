n, m = list(map(int,input().split()))
k = set(list(map(int,input().split())))
if(n == m):
    print("*")
fin = ""
for i in range(1,n+1):
    if(i not in k):
        fin+=(str(i)+" ")
print(fin)
