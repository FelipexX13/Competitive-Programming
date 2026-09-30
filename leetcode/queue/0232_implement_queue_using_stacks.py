# <3
# Tema: LeetCode Hub / Cola
# NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
#
# LeetCode 232 "Implement Queue using Stacks": cola con push, pop, peek y empty.
# Tecnica del codigo: una sola lista con append al final y pop(0) al inicio.
# OJO: el problema pide hacerlo con DOS PILAS y aca usa una lista, o sea se salta el ejercicio.
# pop(0) en Python es O(n). Lo que se buscaba: una pila de entrada y una de salida, y cuando
# la de salida esta vacia se voltea la de entrada encima; eso da O(1) amortizado.

class MyQueue:
    
    def __init__(self):
        self.stack = []
        
    def push(self, x: int) -> None:
        self.stack.append(x)
        
    def pop(self) -> int:
        k = self.stack[0]
        self.stack.pop(0)
        return k

    def peek(self) -> int:
        return self.stack[0]

    def empty(self) -> bool:
        return len(self.stack)==0
                


# Your MyQueue object will be instantiated and called as such:
# obj = MyQueue()
# obj.push(x)
# param_2 = obj.pop()
# param_3 = obj.peek()
# param_4 = obj.empty()