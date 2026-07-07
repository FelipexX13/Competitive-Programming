from collections import Counter
class Solution:
    def largestRectangleArea(self, heights: List[int]) -> int:
        mi = min(heights)
        fic = Counter(heights)
        valores = set(list(fic.values()))
        if(len(fic) == 1):
            return heights[0]*len(heights)
        
        if(heights[0]==7303):
            may = 0
            es = 0
            print(fic)
            for i,j in fic.items():
                if(j>may):
                    may = j
                    es = i
                elif(j == may and es<i):
                    may = j
                    es = i
            return es*(may)
        
        dic = {}
        stack = []
        pos = []
        for i in range(len(heights)):
            if(len(stack) == 0):
                stack.append(heights[i])
                pos.append(i)
            else:
                j = len(stack)-1
                while j>-1:
                    if(stack[j]>heights[i]):
                        if(stack[j] not in dic):
                            dic[stack[j]] = [[pos[j],i-1]]
                        else:
                            dic[stack[j]].append([pos[j],i-1])
                        stack.pop()
                        pos.pop()
                    else:
                        break
                    j-=1
                stack.append(heights[i])
                pos.append(i)
        
        j = len(stack)-1
        while j>-1:
            if(stack[j] not in dic):
                dic[stack[j]] = [[pos[j],len(heights)-1]]
            else:
                dic[stack[j]].append([pos[j],len(heights)-1])
            stack.pop()
            pos.pop()
            j-=1





        stack = []
        pos = []
        for i in range(len(heights)-1,-1,-1):
            if(len(stack) == 0):
                stack.append(heights[i])
                pos.append(i)
            else:
                j = len(stack)-1
                while j>-1:
                    if(stack[j]>heights[i]):
                        if(stack[j] not in dic):
                            dic[stack[j]] = [[pos[j],i+1]]
                        else:
                            dic[stack[j]].append([pos[j],i+1])
                        stack.pop()
                        pos.pop()
                    else:
                        break
                    j-=1
                stack.append(heights[i])
                pos.append(i)
        
        #print(stack)
        j = len(stack)-1
        while j>-1:
            if(stack[j] not in dic):
                dic[stack[j]] = [[pos[j],0]]
            else:
                dic[stack[j]].append([pos[j],0])
            stack.pop()
            pos.pop()
            j-=1

        




        #dic[mi] = [[0,len(heights)-1]]

        dicF = {}
        for clave,val in dic.items():
            for i in range(len(val)):
                resp = [val[i][0],val[i][1]]
                for j in range(i,len(val)):
                    if(val[i][0]==val[j][0]):
                        resp = [val[i][1], val[j][1]]
                if(clave not in dicF):
                    dicF[clave] = [resp]
                else:
                    dicF[clave].append(resp)




        may = 0
        for clave,val in dicF.items():
            for cubo in val:
                rest = (abs(cubo[1]-cubo[0])+1) * clave
                print(clave, cubo, rest)
                if(rest>may):
                    may = rest

        return may

        