class Solution:
    def lastStoneWeight(self, stones: List[int]) -> int:
        while (len(stones)>1):
            ma1 = max(stones)
            stones.remove(ma1)
            ma2 = max(stones)
            stones.remove(ma2)
            if(ma1==ma2):
                continue
            else:
                stones.append(abs(ma1-ma2))
        if(len(stones)==0):
            return 0
        else:
            return stones[0]
        