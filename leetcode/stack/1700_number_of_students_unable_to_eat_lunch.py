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
                

        