#include <stdio.h>  // Biblioteca padrão para entrada e saída
#include <stdlib.h> // Biblioteca padrão para funções utilitárias, como malloc e free
#include <string.h> // Biblioteca padrão para manipulação de strings

// Função para converter uma lista de binários em texto
char* BinarioParaTexto(char** ListaBinarios, int size) {
    char* result = (char*)malloc(size + 1); // Aloca memória para a string de resultado
    for (int i = 0; i < size; i++) {
        // Converte a string binária para um caractere usando strtol e armazena no resultado
        result[i] = (char)strtol(ListaBinarios[i], NULL, 2);
    }
    result[size] = '\0'; // Adiciona o caractere nulo ao final da string
    return result; // Retorna a string resultante
}

// Função para decodificar a mensagem criptografada em binário
void ChaveDeDecodificacao(const char* mensagem, char** arrayLetrasBinariasDecodificado, int* size) {
    char* token; // Ponteiro para armazenar cada token da mensagem
    char* mensagemCopy = strdup(mensagem); // Cria uma cópia da mensagem para tokenização
    token = strtok(mensagemCopy, " "); // Separa a mensagem por espaços
    *size = 0; // Inicializa o tamanho do array de letras binárias decodificadas

    while (token != NULL) {
        int len = strlen(token); // Obtém o comprimento do token
        // Aloca memória para as duas partes do token
        char* parte1 = (char*)malloc(len / 2 + 1);
        char* parte2 = (char*)malloc(len / 2 + 1);
        // Copia a primeira metade do token para parte1
        strncpy(parte1, token, len / 2);
        parte1[len / 2] = '\0'; // Adiciona o caractere nulo ao final de parte1
        // Copia a segunda metade do token para parte2
        strncpy(parte2, token + len / 2, len / 2);
        parte2[len / 2] = '\0'; // Adiciona o caractere nulo ao final de parte2

        // Inverte os últimos dois bits de parte2
        parte2[len / 2 - 2] = (parte2[len / 2 - 2] == '1') ? '0' : '1';
        parte2[len / 2 - 1] = (parte2[len / 2 - 1] == '1') ? '0' : '1';

        // Aloca memória para o novo item combinando parte2 e parte1
        char* novoItemTrocandoPartesDeLugar = (char*)malloc(len + 1);
        sprintf(novoItemTrocandoPartesDeLugar, "%s%s", parte2, parte1); // Combina parte2 e parte1
        arrayLetrasBinariasDecodificado[(*size)++] = novoItemTrocandoPartesDeLugar; // Armazena no array

        // Libera a memória alocada para parte1 e parte2
        free(parte1);
        free(parte2);
        // Obtém o próximo token
        token = strtok(NULL, " ");
    }
    // Libera a memória alocada para a cópia da mensagem
    free(mensagemCopy);
}

// Função para exibir na tela as mensagens criptografada, decodificada e o texto
void ExibeNaTela(const char* mensagemCriptografada, char** arrayBinarioDecodificado, int size, const char* texto) {
    printf("Mensagem Criptografada: %s\n", mensagemCriptografada); // Imprime a mensagem criptografada
    printf("Mensagem Descriptograda: ");
    for (int i = 0; i < size; i++) {
        // Imprime cada elemento do array de binários decodificados
        printf("%s ", arrayBinarioDecodificado[i]);
    }
    printf("\nMensagem: %s\n", texto); // Imprime a mensagem decodificada em texto
    printf("Resultado Disponível Também no console!!\n");
}

int main() {
    // Mensagem criptografada em binário
    const char* mensagemCriptografada = "10010110 11110111 01010110 00000001 00010111 00100110 01010111 00000001 00010111 01110110 01010111 00110110 11110111 11010111 01010111 00000011";
    char* arrayBinarioDecodificado[16]; // Array para armazenar os binários decodificados
    int size = 0; // Variável para armazenar o tamanho do array

    // Decodifica a mensagem criptografada
    ChaveDeDecodificacao(mensagemCriptografada, arrayBinarioDecodificado, &size);
    // Converte os binários decodificados em texto
    char* texto = BinarioParaTexto(arrayBinarioDecodificado, size);

    // Exibe as mensagens na tela
    ExibeNaTela(mensagemCriptografada, arrayBinarioDecodificado, size, texto);

    // Libera a memória alocada para cada string binária decodificada
    for (int i = 0; i < size; i++) {
        free(arrayBinarioDecodificado[i]);
    }
    // Libera a memória alocada para o texto
    free(texto);

    return 0; // Indica que o programa terminou com sucesso
}
