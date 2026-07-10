from bisect import bisect_right

memo = {}

def rec(voy):
    if voy == n:
        return 0

    if voy in memo:
        return memo[voy]

    i1 = bisect_right(l, l[voy] + t1)
    i2 = bisect_right(l, l[voy] + t2)

    ans = min(
        t1 + rec(i1),
        t2 + rec(i2)
    )

    memo[voy] = ans
    return ans


n, c, t1, t2 = map(int, input().split())
l = list(map(int, input().split()))

print(rec(0))
