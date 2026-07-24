class Solution:
    def detectCapitalUse(self, word: str) -> bool:
        gr = word.upper()
        pe = word.lower()
        if(word == gr):
            return True
        elif(word == pe):
            return True
        else:
            if(word[0] == word[0].upper()):
                c = 0
                for i in range(1,len(word)):
                    if(word[i] == word[i].upper()):
                        c+=1
                if(c == 0):
                    return True
            return False
            
        