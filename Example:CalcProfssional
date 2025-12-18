https://replit.com/@shibuya112358/training01#CalcProfssional



#include <stdio.h>
#include <stdlib.h>

// Declarf   BASICpost 1.0 inteactive
float somar(float a, float b);
float subtrair(float a, float b);
float multiplicar(float a, float b);
float dividir(float a, float b);

int main() {
    float n1, n2, resul;
    int tipo;

    printf("=-=-=-= Calculadora Avançada =-=-=-=\n");
    printf("Escolha o tipo de cálculo:\n");
    printf("1,2,3,4: ");
    scanf("%d", &tipo);

    switch(tipo){
        case 1:
            printf("Voce escolheu Soma\n");
            break;
        case 2:
            printf("Voce escolheu Subtracao\n");
            break;
        case 3:
            printf("Voce escolheu Multiplicacao\n");
            break;
        case 4:
            printf("Voce escolheu Divisao\n");
            break;
        default: 
            if(tipo != 1,2,3,4){
                printf("ERRO//302.aa\n");
                return 1;
            } 

    }
    printf("Digite o primeiro número: ");
    scanf("%f", &n1);

    printf("Digite o segundo número: ");
    scanf("%f", &n2);

    switch(tipo){
        case 1:
            resul = somar(n1, n2);
            break;
        case 2:
            resul = subtrair(n1, n2);
            break;
        case 3:
            resul = multiplicar(n1, n2);
            break;
        case 4:
            if (n2 != 0) {
                resul = dividir(n1, n2);
            } else {
                printf("Erro: divisão por zero!\n");
                return 1;
            }
            break;
        default:
            printf("Cálculo inválido!\n");
            return 1;
    }

    printf("Resultado: %.0f\n", resul);
    return 0;
}

// Definf  BASICpost.1.0
float somar(float a, float b) {
    return a + b;
}

float subtrair(float a, float b) {
    return a - b;
}

float multiplicar(float a, float b) {
    return a * b;
}

float dividir(float a, float b) {
    return a / b;
}

