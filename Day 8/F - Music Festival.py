from bisect import bisect_left

n = int(input())

shows = []

for stage in range(n):
    data = list(map(int, input().split()))
    m = data[0]
    for i in range(m):
        s = data[1 + 3 * i]
        e = data[2 + 3 * i]
        p = data[3 + 3 * i]
        shows.append((s, e, stage, p))

shows.sort()

m = len(shows)

starts = [x[0] for x in shows]

next_show = [0] * m
for i in range(m):
    next_show[i] = bisect_left(starts, shows[i][1])

FULL = (1 << n) - 1
NEG = -10**18

dp = [[NEG] * (1 << n) for _ in range(m + 1)]
dp[m][FULL] = 0

for i in range(m - 1, -1, -1):
    for mask in range(1 << n):
        dp[i][mask] = dp[i + 1][mask]

    _, _, stage, songs = shows[i]
    bit = 1 << stage

    for mask in range(1 << n):
        if dp[next_show[i]][mask | bit] != NEG:
            dp[i][mask] = max(
                dp[i][mask],
                songs + dp[next_show[i]][mask | bit]
            )

ans = dp[0][0]

print(ans if ans != NEG else -1)