m, n, s = list(map(int, input().split()))
sensors = []

for i in range(s):
    sensors.append(list(map(int, input().split())))
ans = "S"
visited = set()
def rec(x,y,r, start):
    global ans, m, n
    
    if ans == "N":
        return
    for xi,yi,ri in sensors:
        if (xi, yi, ri) in visited:
            continue
        dist = ((x-xi)**2+(y-yi)**2)**(1/2)
        if dist <= (r+ri):
            if (start == "l" and (xi+ri >= m or yi-ri <= 0)) or (start == "d" and (xi-ri <= 0 or yi+ri >= n)) or (start == "u" and (xi-ri >= m or yi-ri <= 0)) or (start == "r" and (yi+ri >= n or x-ri <= 0)):
                ans = "N"
                break
            visited.add((xi,yi,ri))
            rec(xi,yi, ri, start)
  
        
for i, sensor in enumerate(sensors):
    r = sensor[2]
    x = sensor[0]
    y = sensor[1]
    if (x + r >= m and x - r <= 0) or (y + r >= n and y - r <= 0) or (x - r <= 0 and y - r <= 0) or (x + r >= m and y + r >= n):
        ans = "N"
        break
    if x-r<=0 or y-r<=0 or y+r>=n or x+r>=m:
        dir = ""
        if x-r<=0:
            dir = "l"
        elif y-r<=0:
            dir = "d"
        elif y+r>=n:
            dir = "u"
        elif x+r>=m:
            dir = "r"
        if dir != "":
            visited = set()
            rec(x,y,r, dir)
print(ans)
