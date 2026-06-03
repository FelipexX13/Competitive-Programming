class Solution:
    def buildArray(self, target: List[int], n: int) -> List[str]:
        g = set(target)
        print(g)
        res = []
        num = []
        for i in range(1,n+1):
            if(target == num):
                return res
            res.append("Push")
            num.append(i)
            if(i not in g):
                res.append("Pop")
                num = num[0:len(num)-1]
        return res