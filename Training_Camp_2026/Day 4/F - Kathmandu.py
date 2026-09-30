# <3
# Tema: Greedy / Simulation
# Resuelve "Kathmandu" (Training Camp 2026, Day 4 problema F): durante un vuelo de duracion D hay
# M comidas servidas en instantes y_i (hay que estar despierto para comer), y hay que decidir si
# se puede dormir T minutos seguidos sin interrupcion sin perderse ninguna comida.
# Arma la lista c de instantes relevantes (0, cada y_i, y D) y busca si existe un hueco entre dos
# instantes consecutivos de largo mayor o igual a T (abs(c[i]-c[i+1]) >= t), ya que ese hueco es
# la unica ventana disponible para dormir sin faltar a ninguna comida.

t, v, n = list(map(int,input().split()))
c = [0]
for i in range(n):
    c.append(int(input()))
c.append(v)

f = False
for i in range(len(c)-1):
    if(t <= abs(c[i]-c[i+1])):
        f = True
        break
if(f):
    print("Y")
else:
    print("N")

    