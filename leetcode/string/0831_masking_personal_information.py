class Solution:
    def maskPII(self, s: str) -> str:
        #NUMERO
        try:
            for i in range(len(s)-1,-1,-1):
                if(s[i]!="-" and s[i]!= " "):
                    break
            f = int(s[i])
            nums = ""
            for i in s:
                try:
                    a = int(i)
                    nums += i
                except:
                    continue
            tam = len(nums)
            if(tam == 10):
                return "***-***-"+nums[len(nums)-4:len(nums)]
            elif(tam == 11):
                return "+*-***-***-"+nums[len(nums)-4:len(nums)]
            elif(tam == 12):
                return "+**-***-***-"+nums[len(nums)-4:len(nums)]
            else:
                return "+***-***-***-"+nums[len(nums)-4:len(nums)]
            
        #CORREO
        except:
            ini = s[0].lower()
            f = ""
            ya = False
            correo = ""
            for i in range(len(s)):
                if(s[i] == "@" ):
                    ya = True
                if(s[i] != "@" and ya == False):
                    try:
                        f = s[i].lower()
                    except:
                        f = s[i]
                elif(s[i] == "@" and f != ""):
                    correo = s[i:len(s)]
                    break
            g = ""
            for i in correo:
                try:
                    g += i.lower()
                except:
                    g += i
            c = ini + "*****" + f + g
            return c