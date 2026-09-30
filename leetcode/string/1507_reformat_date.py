# <3
# Tema: LeetCode Hub / Formateo de Fecha
# NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
#
# LeetCode 1507 "Reformat Date": pasar "20th Oct 2052" a "2052-10-20".
# Tecnica: split, diccionario de mes a numero, y quitar las dos ultimas letras del dia (st, nd,
# rd, th) con d[:-2]. El if de len(d) == 1 es para el cero de relleno.

class Solution:
    def reformatDate(self, date: str) -> str:

        dic2 = {'Jan': '01',
               'Feb': '02',
               'Mar': '03',
               'Apr': '04',
               'May': '05',
               'Jun': '06',
               'Jul': '07',
               'Aug': '08',
               'Sep': '09',
               'Oct': '10',
               'Nov': '11',
               'Dec': '12'}

        d,m,a = list(date.split())
        d = str(d[:-2])
        if len(d) == 1:
            d = '0'+d
        return str(a)+'-'+dic2[m]+'-'+d