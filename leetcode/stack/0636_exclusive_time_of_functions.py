class Solution:
    def exclusiveTime(self, n: int, logs: List[str]) -> List[int]:
        dic = {}
        val = 0
        stack = []
        for i in range(len(logs)):
            partes = logs[i].split(":")
            if(partes[1]== "start"):
                if(partes[0] not in dic):
                    dic[partes[0]]=0
                if(int(partes[2])!=val):
                    dic[stack[-1]] += int(partes[2])-val
                stack.append(partes[0])
                val = int(partes[2])
            else:
                time = int(partes[2]) - val + 1
                dic[stack[-1]] += time
                stack.pop()
                val = int(partes[2])+1
                
        f = []
        for clave,val in dic.items():
            f.append(val)

        return f


                
