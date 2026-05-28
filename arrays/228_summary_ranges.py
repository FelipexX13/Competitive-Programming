class Solution:
    def summaryRanges(self, nums: List[int]) -> List[str]:
        


        resultado = []

        if len(nums) == 0:
            
            return ([])
            
        else:
            
            a = nums[0]

            try:

                for i in range(len(nums)):
                    
                    b = nums[i + 1]

                    if b == nums[i] + 1:
                        
                        continue
                    
                    else:
                        
                        if a == nums[i]:
                            
                            resultado.append(str(a))
                            
                        else:
                            
                            resultado.append(f"{a}->{nums[i]}")
                            
                        a = b
                        
            except:
                
                if a == nums[-1]:
                        
                    resultado.append(str(a))
                    
                else:
                    
                    resultado.append(f"{a}->{nums[-1]}")
                    
                
                return (resultado)
