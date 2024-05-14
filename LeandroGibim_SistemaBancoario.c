#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// fun��es
int realizarDeposito(float valorDeposito, int numeroAgencia, int numeroContaCorrente, int digitoVerificador, char nomeFavorecido[50], float *somaTotal);
int validarDigitoVerificador(int numeroContaCorrente);
int somarEImprimirSoma(float *soma, float valorDeposito);
int lerInformacoes(float *valorDeposito, int *numeroAgencia, int *numeroContaCorrente, int *digitoVerificador, char nomeFavorecido[50]);

int main() {
    setlocale(LC_ALL, "portuguese");
    
    // Vari�vel para armazenar a soma total dos dep�sitos
    float somaTotal = 0;

    // Vari�vel de controle para determinar se o programa deve continuar
    int continuar = 1;

    // Loop para permitir m�ltiplos dep�sitos
    while (continuar) {
        // Vari�veis individuais para armazenar as informa��es do cliente
        float valorDeposito;
        int numeroAgencia, numeroContaCorrente, digitoVerificador;
        char nomeFavorecido[50];

        // Leitura das informa��es do cliente
        lerInformacoes(&valorDeposito, &numeroAgencia, &numeroContaCorrente, &digitoVerificador, nomeFavorecido);

        // Realiza o dep�sito e valida o d�gito verificador
        realizarDeposito(valorDeposito, numeroAgencia, numeroContaCorrente, digitoVerificador, nomeFavorecido, &somaTotal);

        // Verifica��o se o usu�rio deseja realizar outro dep�sito
        char resposta[2];
        printf("Deseja realizar outro dep�sito? (S/N): ");
        scanf("%s", resposta);

        // Atualiza a vari�vel de controle com base na resposta
        continuar = (toupper(resposta[0]) == 'S') ? 1 : 0;
    }

    // Imprimir a soma total dos dep�sitos ao final
    printf("Soma total dos dep�sitos: %.2f\n", somaTotal);

    return 0;
}

// Fun��o para realizar dep�sito e validar o d�gito verificador
int realizarDeposito(float valorDeposito, int numeroAgencia, int numeroContaCorrente, int digitoVerificador, char nomeFavorecido[50], float *somaTotal) {
    // Valida��o do d�gito verificador
    if (digitoVerificador == validarDigitoVerificador(numeroContaCorrente)) {
        // Somar e imprimir a soma dos dep�sitos
        somarEImprimirSoma(somaTotal, valorDeposito);
    } else {
        printf("Erro: Digito verificador incorreto. Tente novamente.\n");
    }
}

// Fun��o para validar o d�gito verificador
int validarDigitoVerificador(int numeroContaCorrente) {
    int inverso = 0;
    int soma = 0;
    int posicao = 1;

    // Calcula o inverso do n�mero da conta
    while (numeroContaCorrente > 0) {
        inverso = inverso * 10 + numeroContaCorrente % 10;
        numeroContaCorrente /= 10;
    }

    // Soma os produtos dos d�gitos pela posi��o
    while (inverso > 0) {
        int digito = inverso % 10;
        soma += digito * posicao;
        inverso /= 10;
        posicao++;
    }

    // Retorna o �ltimo d�gito da soma
    return soma % 10;
}

// Fun��o para somar e imprimir a soma dos dep�sitos
int somarEImprimirSoma(float *soma, float valorDeposito) {
    *soma += valorDeposito;
    printf("Dep�sito realizado com sucesso. Soma parcial: %.2f\n", *soma);
}

// Fun��o para ler informa��es do cliente
int lerInformacoes(float *valorDeposito, int *numeroAgencia, int *numeroContaCorrente, int *digitoVerificador, char nomeFavorecido[50]) {
    printf("Digite o valor a ser depositado: ");
    scanf("%f", valorDeposito);

    printf("Digite o n�mero da ag�ncia (4 d�gitos): ");
    scanf("%d", numeroAgencia);

    printf("Digite o n�mero da conta corrente (5 d�gitos): ");
    scanf("%d", numeroContaCorrente);

    printf("Digite o d�gito verificador da conta corrente: ");
    scanf("%d", digitoVerificador);

    printf("Digite o nome do favorecido: ");
    scanf("%s", nomeFavorecido);
}
