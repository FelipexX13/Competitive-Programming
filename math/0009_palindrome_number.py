class Solution:
    def isPalindrome(self, x: int) -> bool:
        b = str(x)
        i = 0
        while i < len(b)/2:
            if(b[i]==b[len(b)-1-i]):
                i+=1
                continue
            else:
                return False
        return True