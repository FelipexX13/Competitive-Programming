// <3
// Tema: Formulario / Tabla ASCII
// Resumen: Tabla ASCII de los caracteres imprimibles (32 a 126) en cuatro columnas
// Detalle: Tabla ASCII de los caracteres imprimibles (32 a 126) en cuatro columnas, mas los
// valores y trucos que se usan de verdad: c - '0' para el digito, c - 'a' para el indice de la
// letra, y que 'a' - 'A' = 32 permite cambiar de caso con un xor. Incluye la nota del '\r' de
// Windows, que rompe comparaciones al leer con getline.

// =============== TABLA ASCII (imprimibles 32-126) ===============
//
//     dec chr   dec chr   dec chr   dec chr
//      32 SP     56 8      80 P     104 h
//      33 !      57 9      81 Q     105 i
//      34 "      58 :      82 R     106 j
//      35 #      59 ;      83 S     107 k
//      36 $      60 <      84 T     108 l
//      37 %      61 =      85 U     109 m
//      38 &      62 >      86 V     110 n
//      39 '      63 ?      87 W     111 o
//      40 (      64 @      88 X     112 p
//      41 )      65 A      89 Y     113 q
//      42 *      66 B      90 Z     114 r
//      43 +      67 C      91 [     115 s
//      44 ,      68 D      92 \     116 t
//      45 -      69 E      93 ]     117 u
//      46 .      70 F      94 ^     118 v
//      47 /      71 G      95 _     119 w
//      48 0      72 H      96 `     120 x
//      49 1      73 I      97 a     121 y
//      50 2      74 J      98 b     122 z
//      51 3      75 K      99 c     123 {
//      52 4      76 L     100 d     124 |
//      53 5      77 M     101 e     125 }
//      54 6      78 N     102 f     126 ~
//      55 7      79 O     103 g
//
// Lo que de verdad se usa
//     '0' = 48     '9' = 57     digito: c - '0'
//     'A' = 65     'Z' = 90
//     'a' = 97     'z' = 122    indice: c - 'a'  (0..25)
//     'a' - 'A' = 32  ->  minuscula: c | 32, mayuscula: c & ~32
//     ' ' = 32     '\n' = 10    '\0' = 0    '\t' = 9
//     Cambiar de caso con xor: c ^ 32
//
// Chequeos de <cctype>
//     isalpha isdigit isalnum isupper islower isspace ispunct
//     toupper tolower
//     Rapido sin libreria: (c>='0' && c<='9')
//
// Control mas comunes (no imprimibles)
//     0  NUL    9  TAB    10 LF (\n)   13 CR (\r)   27 ESC
//     Archivos de Windows traen CR+LF: si lees con getline puede
//     quedar un '\r' al final de la linea. Quitarlo antes de comparar.
