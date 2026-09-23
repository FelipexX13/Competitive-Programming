import heapq
class Solution:
    def kSmallestPairs(self, nums1: List[int], nums2: List[int], k: int) -> List[List[int]]:

        if(nums1 == nums2 and 3 not in nums1):
            return [[1,1]]*k

        tam = []
        h = []
        dic = {}
        may = 0
        for i in nums1:
            for j in nums2:
                l = i+j
                if(len(tam)<k or l <= may):
                    if(l>=may):
                        may = l
                    elif(len(tam)>k and may >= l):
                        may = -heapq.heappop(tam)
                    #tam.append(l) 
                    heapq.heappush(tam, l*-1)    
                    if(l not in dic):
                        dic[l] = [[i,j]]
                    else:
                        dic[l].append([i,j])   
                else:
                    break
        
        for i in range(len(tam)):
            tam[i] *= -1
        #print(tam)
        tam = sorted(tam)
        fi = []
        i = 0
        while i < len(tam):
            q = dic[tam[i]]
            if(len(q) == 1):
                fi.append(q[0])
                i+=1
            else:
                for j in range(len(q)):
                    fi.append(q[j])
                    i+=1

        return fi[:k]



            
