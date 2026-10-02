# <3
# Tema: LeetCode Hub / Simulacion de Cola
# Resumen: Los que no comen porque el sandwich de arriba no les gusta y se van al final de la fila
# O: (n^2) simulando con pop(0); contando los dos tipos seria (n)
# Detalle: LeetCode 1700 "Number of Students Unable to Eat Lunch": los que no comen porque el
# sandwich de arriba no les gusta y se van al final de la fila. Tecnica: simular la fila con
# pop(0) y append. El contador c cuenta rechazos seguidos, y cuando llega al tamano de la fila
# significa que ya nadie mas puede comer. Tambien sale contando cuantos quieren cada tipo, sin
# simular.

class Solution:
    def countStudents(self, students: List[int], sandwiches: List[int]) -> int:
        c = -1
        while c != len(students):
            if(students[0]==sandwiches[0]):
                students.pop(0)
                sandwiches.pop(0)
                c = 0
            else:
                student = students[0]
                students.pop(0)
                students.append(student)
                c += 1
        return c
                

        