class Solution:
    def earliestFinishTime(self, landStartTime: List[int], landDuration: List[int], waterStartTime: List[int], waterDuration: List[int]) -> int:
        res1 = [x + y for x, y in zip(landStartTime, landDuration)]
        res2 = [x + y for x, y in zip(waterStartTime, waterDuration)]

        men1 = min(res1)
        men2 = min(res2)

        f1 = 999999999999999999999
        f2 = 999999999999999999999
        for i in range(len(res2)):
            if(men1<waterStartTime[i]):
                val = men1+(waterStartTime[i]-men1)+waterDuration[i]
            else:
                val = men1+waterDuration[i]
            print(val)
            if(val<f1):
                f1 = val

        for i in range(len(res1)):
            if(men2<landStartTime[i]):
                val = men2+(landStartTime[i]-men2)+landDuration[i]
            else:
                val = men2+landDuration[i]
            if(val<f2):
                f2 = val

        if(f1<f2):
            return f1
        else:
            return f2