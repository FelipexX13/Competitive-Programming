n = int(input())
matrix = []
for i in range(n):
    matrix.append(list(map(int,input().split())))
pos = [matrix[0][0], matrix[0][n-1], matrix[n-1][n-1], matrix[n-1][0]]
me = min(pos)
print(pos.index(me))
