# <3
# Tema: Ad Hoc / Conjuntos
# Resuelve "Joao Joao" (Maratona SBC de Programacao 2025, Problem J): ya se crearon 10 tareas
# para un examen, cada una con un nivel de dificultad entre 1 y 4, y se necesita saber cuantas
# tareas nuevas hacen falta para poder armar un examen con exactamente 4 tareas, una de cada
# nivel de dificultad distinto. El codigo mete las 10 dificultades en un set "n" (que colapsa los
# duplicados y deja solo los niveles distintos ya cubiertos) e imprime 4 menos el tamano de ese
# set, es decir, cuantos niveles de dificultad todavia faltan por cubrir.

n = set(map(int,input().split()))
print(4-len(n))
