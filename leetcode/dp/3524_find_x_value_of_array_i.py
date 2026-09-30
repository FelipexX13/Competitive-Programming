class Solution:
    def resultArray(self, nums: List[int], k: int) -> List[int]:
        result = [0] * k
        dp = {}
        for i in range(0,len(nums)):
            dp[i] = [0]*k
            dp[i][nums[i]%k] += 1
            for j in range(k):
                try:
                    if(dp[i-1][j] != 0):
                        res = (j*(nums[i]%k))%k
                        dp[i][res] += dp[i-1][j]
                except:
                    a = 1
            for j in range(k):
                result[j] += dp[i][j]

        return result


        