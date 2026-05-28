class Solution:
    def numberOfSpecialChars(self, word: str) -> int:

        w = set(word)
        c = 0
        for i in w:
            if(i.islower() and i.upper() in w ):
                c+=1
        return c
        
        