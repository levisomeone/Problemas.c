/*
beecrowd | 1060
Números Positivos
Adaptado por Neilor Tonin, URI
Brasil

Timelimit: 1

Faça um programa que leia 6 valores. Estes valores serão somente negativos
ou positivos (desconsidere os valores nulos). A seguir, mostre a quantidade
de valores positivos digitados.

Entrada:
Seis valores, negativos e/ou positivos.

Saída:
Imprima uma mensagem dizendo quantos valores positivos foram lidos.
*/

7 -5 6 -3.4 4.6 12   --->   4 valores positivos
-1 -2 -3 -4 -5 -6   --->   0 valores positivos
1 2 3 4 5 6         --->   6 valores positivos

// source code || 1060 c99 ||  https://resources.beecrowd.com/repository/UOJ_1060.html

#include <stdio.h>

int main(void)
{
    float n;
    int pos = 0;

    for (int i = 0; i < 6; i++)
    {
        scanf("%f", &n);

        if (n > 0)
            pos++;
    }

    printf("%d valores positivos\n", pos);

    return 0;
}
