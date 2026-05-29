class Solution:
    def isPalindrome(self, s: str) -> bool:
        s = s.lower()
        lt = ["a","b","c","d","e","f","g","h","i","j",
                "k","l","m","n","o","p","q","r","s","t",
                "u","v","w","x","y","z"
            ]

        n = ["0","1","2","3","4","5","6","7","8","9"]

        guar = ""
        for i in range(0,len(s)):
            if ((s[i] in lt) or (s[i] in n)):        
                guar += s[i]

        print(guar)

        total = len(guar)

        for i in range(0,total):
            if guar[i] != guar[total-1]:
                return False
            total = total - 1

        return True

                