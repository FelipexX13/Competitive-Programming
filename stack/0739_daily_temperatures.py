class Solution:
    
    def calculo(self, temperatures, i):
        j = i+1
        c = 0
        f = False
        while j < len(temperatures):
            if(temperatures[i]>= temperatures[j]):
                c+=1
            else:
                c+=1
                f = True
                break
            j+=1
        if(f):
            return c
        else:
            return 0


    def dailyTemperatures(self, temperatures: List[int]) -> List[int]:

        ma = max(temperatures)
        fin  = []
        dic = {}
        i = 0
        while i < len(temperatures)-1:
            if(temperatures[i]== ma):
                fin.append(0)
            elif(temperatures[i] not in dic):
                dic[temperatures[i]] = [i]
                val = self.calculo(temperatures, i)
                fin.append(val)
                dic[temperatures[i]].append(val)
            else:
                rest = (dic[temperatures[i]][1])-(i-dic[temperatures[i]][0])
                if(rest>-1):
                    dic[temperatures[i]] = [i,rest]
                    fin.append(rest)
                else:
                    val = self.calculo(temperatures, i)
                    fin.append(val)
                    dic[temperatures[i]].append(val)
            i+=1

        fin.append(0)
        return fin
        