#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// funções
int realizarDeposito(float valorDeposito, int numeroAgencia, int numeroContaCorrente, int digitoVerificador, char nomeFavorecido[50], float *somaTotal);
int validarDigitoVerificador(int numeroContaCorrente);
int somarEImprimirSoma(float *soma, float valorDeposito);
int lerInformacoes(float *valorDeposito, int *numeroAgencia, int *numeroContaCorrente, int *digitoVerificador, char nomeFavorecido[50]);

int main() {
    setlocale(LC_ALL, "portuguese");
    
    // Variável para armazenar a soma total dos depósitos
    float somaTotal = 0;

    // Variável de controle para determinar se o programa deve continuar
    int continuar = 1;

    // Loop para permitir múltiplos depósitos
    while (continuar) {
        // Variáveis individuais para armazenar as informações do cliente
        float valorDeposito;
        int numeroAgencia, numeroContaCorrente, digitoVerificador;
        char nomeFavorecido[50];

        // Leitura das informações do cliente
        lerInformacoes(&valorDeposito, &numeroAgencia, &numeroContaCorrente, &digitoVerificador, nomeFavorecido);

        // Realiza o depósito e valida o dígito verificador
        realizarDeposito(valorDeposito, numeroAgencia, numeroContaCorrente, digitoVerificador, nomeFavorecido, &somaTotal);

        // Verificação se o usuário deseja realizar outro depósito
        char resposta[2];
        printf("Deseja realizar outro depósito? (S/N): ");
        scanf("%s", resposta);

        // Atualiza a variável de controle com base na resposta
        continuar = (toupper(resposta[0]) == 'S') ? 1 : 0;
    }

    // Imprimir a soma total dos depósitos ao final
    printf("Soma total dos depósitos: %.2f\n", somaTotal);

    return 0;
}

// Função para realizar depósito e validar o dígito verificador
int realizarDeposito(float valorDeposito, int numeroAgencia, int numeroContaCorrente, int digitoVerificador, char nomeFavorecido[50], float *somaTotal) {
    // Validação do dígito verificador
    if (digitoVerificador == validarDigitoVerificador(numeroContaCorrente)) {
        // Somar e imprimir a soma dos depósitos
        somarEImprimirSoma(somaTotal, valorDeposito);
    } else {
        printf("Erro: Digito verificador incorreto. Tente novamente.\n");
    }
}

// Função para validar o dígito verificador
int validarDigitoVerificador(int numeroContaCorrente) {
    int inverso = 0;
    int soma = 0;
    int posicao = 1;

    // Calcula o inverso do número da conta
    while (numeroContaCorrente > 0) {
        inverso = inverso * 10 + numeroContaCorrente % 10;
        numeroContaCorrente /= 10;
    }

    // Soma os produtos dos dígitos pela posição
    while (inverso > 0) {
        int digito = inverso % 10;
        soma += digito * posicao;
        inverso /= 10;
        posicao++;
    }

    // Retorna o último dígito da soma
    return soma % 10;
}

// Função para somar e imprimir a soma dos depósitos
int somarEImprimirSoma(float *soma, float valorDeposito) {
    *soma += valorDeposito;
    printf("Depósito realizado com sucesso. Soma parcial: %.2f\n", *soma);
}

// Função para ler informações do cliente
int lerInformacoes(float *valorDeposito, int *numeroAgencia, int *numeroContaCorrente, int *digitoVerificador, char nomeFavorecido[50]) {
    printf("Digite o valor a ser depositado: ");
    scanf("%f", valorDeposito);

    printf("Digite o número da agência (4 dígitos): ");
    scanf("%d", numeroAgencia);

    printf("Digite o número da conta corrente (5 dígitos): ");
    scanf("%d", numeroContaCorrente);

    printf("Digite o dígito verificador da conta corrente: ");
    scanf("%d", digitoVerificador);

    printf("Digite o nome do favorecido: ");
    scanf("%s", nomeFavorecido);
}
