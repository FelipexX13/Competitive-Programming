class Solution:
    def largestAltitude(self, gain: List[int]) -> int:
        g = [0]
        for i in range(len(gain)):
            g.append(gain[i]+g[-1])
               
                
        return max(g)
        