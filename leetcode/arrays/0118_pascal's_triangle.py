class Solution:
    def generate(self, numRows: int) -> List[List[int]]:
        numFilas = numRows       

        matriz = []

        fila = [1]

        cont = 0                

        while cont < numFilas:
            
            matriz.append(fila)  

            nueva = [1]
            
            for i in range(len(fila) - 1):
                
                nueva.append(fila[i] + fila[i + 1])
                
            nueva.append(1)

            fila = nueva
            cont+=1
            
            

        return(matriz)



        