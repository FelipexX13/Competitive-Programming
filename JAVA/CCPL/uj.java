// <3
// Tema: Math / Big Exponentiation
// Calcula N^D usando BigInteger para manejar resultados con exponentes muy grandes.

import java.util.*;
import java.math.*;

class Main {
    public static void main (String[] args) throws Exception {
        Scanner sc = new Scanner(System.in);
        
        while (sc.hasNext()) {
            int N = sc.nextInt();
            int D = sc.nextInt();
            
            if (N == 0 && D == 0) break;
            
            System.out.println(BigInteger.valueOf(N).pow(D));
        }
    }
}