#include <stdio.h> 
#include <ctype.h>  

int main() {
    printf("Bem-vindo, Marcus Tomazelli!\n");  

    char prato;  
    char tamanho;  
    int quantidade = 1;  

    
    printf("Escolha o prato (Bife Acebolado = B, File de Frango = F): ");
    scanf(" %c", &prato);  
    prato = toupper(prato); 

    printf("Escolha o tamanho (P, M, G): ");  
    scanf(" %c", &tamanho);  
    tamanho = toupper(tamanho);  

    printf("Informe a quantidade de marmitas: ");  
    scanf("%d", &quantidade);  

    double preco = 0.0; 


    if (prato == 'B') {  
        if (tamanho == 'P') {
            preco = 16.0;  
        } else if (tamanho == 'M') {
            preco = 18.0;  
        } else if (tamanho == 'G') {
            preco = 22.0;  
        }
    } else if (prato == 'F') {  
        if (tamanho == 'P') {
            preco = 15.0;  
        } else if (tamanho == 'M') {
            preco = 17.0;  
        } else if (tamanho == 'G') {
            preco = 21.0;  
        }
    }

    
    if (preco == 0.0 || quantidade <= 0) {
        printf("Opcao invalida. Reinicie e escolha prato/tamanho validos.\n");
        return 1;  
    }

    double total = preco * quantidade;  

    
    printf("\nResumo do pedido:\n");
    printf("Prato: %s\n", prato == 'B' ? "Bife Acebolado" : "File de Frango");
    printf("Tamanho: %c\n", tamanho);
    printf("Quantidade: %d\n", quantidade);
    printf("Preco unitario: R$ %.2f\n", preco);
    printf("Total a pagar: R$ %.2f\n", total);

    return 0;  
}
