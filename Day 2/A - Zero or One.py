# <3
# Tema: Implementation / Ad Hoc
# Resuelve "Zero or One" (Maratona de Programacao da SBC 2013, problem A): Alice, Beto y Clara
# juegan "cero o uno" mostrando cada uno la mano con un valor 0 o 1; gana quien elige un valor
# distinto al de los otros dos, y si nadie queda en esa situacion (todos iguales, o empate 2-1
# sin un unico distinto) no hay ganador.
# Usa la suma A+B+C para detectarlo sin comparar par por par: si la suma es 1, el unico que
# voto 1 es el ganador; si la suma es 2, el unico que voto 0 es el ganador; en cualquier otro
# caso (suma 0 o 3) no hay ganador y se imprime '*'.

a, b, z = list(map(int, input().split()))

if 0<(a+b+z)< 3:
    if (a+b+z == 2 and a == 0) or (a+b+z == 1 and a == 1):
        print("A")
    if (a+b+z == 2 and b == 0) or (a+b+z == 1 and b == 1):
        print("B")
    if (a+b+z == 2 and z == 0) or (a+b+z == 1 and z == 1):
        print("C")
else:
    print('*')
