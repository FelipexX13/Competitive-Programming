class Solution:
    def numberOfSpecialChars(self, word: str) -> int:
        l = set()
        u = set()
        c = 0
        esta = set()
        ya = set()
        for i in word:
            if(i.islower() and i not in l):
                l.add(i)
            elif(i in esta and i not in ya):
                c-=1
                ya.add(i)
            elif(i.isupper() and i.lower() in l and i not in u):
                c+=1
                esta.add(i.lower())
            if(i.isupper()):
                u.add(i)
        return c