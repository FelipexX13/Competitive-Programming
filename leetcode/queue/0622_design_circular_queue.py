# <3
# Tema: LeetCode Hub / Cola Circular con Arreglo Fijo
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# O: (1) todas las operaciones
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 622 "Design Circular Queue": cola de capacidad fija con enQueue, deQueue, Front y
# Rear. Tecnica: arreglo de tamano k con dos indices, ini y rea, que dan la vuelta al llegar a
# k. El tamano se guarda aparte, y eso es lo que permite distinguir vacia de llena sin
# desperdiciar una casilla. Rear() usa rea-1 porque rea apunta a la siguiente libre.

class MyCircularQueue:
    
    def __init__(self, k: int):
        self.lista = [0]*k
        self.tam = 0
        self.k = k
        self.ini = 0
        self.rea = 0
        
    def enQueue(self, value: int) -> bool:
        if(self.tam < self.k):
            self.lista[self.rea] = value
            self.tam += 1
            self.rea += 1
            if(self.rea == self.k):
                self.rea = 0
            return True
        else:
            return False

    def deQueue(self) -> bool:
        if(self.tam > 0):
            self.tam -= 1
            self.ini += 1
            if(self.ini == self.k):
                self.ini = 0
            return True
        else:
            return False

    def Front(self) -> int:
        if(self.tam > 0):
            return self.lista[self.ini]
        else:
            return -1

    def Rear(self) -> int:
        if(self.tam > 0):
            return self.lista[self.rea-1]
        else:
            return -1
        
    def isEmpty(self) -> bool:
        if(self.tam > 0):
            return False
        else:
            return True
        
    def isFull(self) -> bool:
        if(self.tam == self.k):
            return True
        else:
            return False
        


# Your MyCircularQueue object will be instantiated and called as such:
# obj = MyCircularQueue(k)
# param_1 = obj.enQueue(value)
# param_2 = obj.deQueue()
# param_3 = obj.Front()
# param_4 = obj.Rear()
# param_5 = obj.isEmpty()
# param_6 = obj.isFull()