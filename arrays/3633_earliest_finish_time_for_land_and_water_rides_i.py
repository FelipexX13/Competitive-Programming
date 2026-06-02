class Solution:
    def earliestFinishTime(self, landStartTime: List[int], landDuration: List[int], waterStartTime: List[int], waterDuration: List[int]) -> int:
        menor = 9999999999999999999999999999999
        c1 = menor
        c2 = menor
        for i in range(len(landStartTime)):
            for j in range(len(waterStartTime)):
                if(landStartTime[i]+landDuration[i]>waterStartTime[j]):
                    c1 = landStartTime[i]+landDuration[i]+waterDuration[j]
                else:
                    c1 = waterStartTime[j]+waterDuration[j]
                
                if(c1<menor):
                    menor = c1

        for i in range(len(waterStartTime)):
            for j in range(len(landStartTime)):
                if(waterStartTime[i]+waterDuration[i]>landStartTime[j]):
                    c2 = waterStartTime[i]+waterDuration[i]+landDuration[j]
                else:
                    c2 = landStartTime[j]+landDuration[j]
                if(c2<menor):
                    menor = c2


        return menor

        