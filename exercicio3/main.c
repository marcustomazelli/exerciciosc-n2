#include <stdio.h>   
#include <string.h>  
#include <ctype.h>   


int main() {
    printf("Bem-vindo, Marcus Tomazelli!\n"); 

    char modelo[4]; 
    int quantidade = 0;  
    int freteOpcao = 0;  

    
    printf("Modelos disponiveis:\n");
    printf("MCS - Manga Curta Simples (R$ 1.80)\n");
    printf("MLS - Manga Longa Simples (R$ 2.10)\n");
    printf("MCE - Manga Curta Estampa (R$ 2.90)\n");
    printf("MLE - Manga Longa Estampa (R$ 3.20)\n");

    printf("Informe o codigo do modelo: ");  
    scanf("%3s", modelo);  
    

    printf("Informe a quantidade de camisetas: ");  
    scanf("%d", &quantidade);  

    
    if (quantidade > 20000) {
        printf("Pedido nao aceito para quantidade acima de 20000 camisetas.\n");
        return 1;  
    }

    
    double unitario = 0.0;  
    if (strcmp(modelo, "MCS") == 0) {
        unitario = 1.80;  
    } else if (strcmp(modelo, "MLS") == 0) {
        unitario = 2.10;  
    } else if (strcmp(modelo, "MCE") == 0) {
        unitario = 2.90;  
    } else if (strcmp(modelo, "MLE") == 0) {
        unitario = 3.20;  
    }

    
    if (unitario == 0.0 || quantidade <= 0) {
        printf("Modelo ou quantidade invalidos.\n");
        return 1;  
    }

    
    double desconto = 0.0;  
    if (quantidade >= 20 && quantidade < 200) {
        desconto = 0.05; 
    } else if (quantidade >= 200 && quantidade < 2000) {
        desconto = 0.07;  
    } else if (quantidade >= 2000) {
        desconto = 0.12;  
    }

    printf("Frete (0 = retirar na fabrica, 1 = transportadora, 2 = sedex): ");  
    scanf("%d", &freteOpcao);  

    double frete = 0.0;  
    if (freteOpcao == 1) {
        frete = 100.0;  
    } else if (freteOpcao == 2) {
        frete = 200.0;  
    } else if (freteOpcao == 0) {
        frete = 0.0;  
    } else {
        printf("Opcao de frete invalida.\n");
        return 1;  
    }

    double subtotal = unitario * quantidade; 
    double totalComDesconto = subtotal * (1.0 - desconto);  
    double total = totalComDesconto + frete;  

    
    printf("\nResumo do pedido:\n");
    printf("Modelo: %s\n", modelo);
    printf("Quantidade: %d\n", quantidade);
    printf("Preco unitario: R$ %.2f\n", unitario);
    printf("Subtotal: R$ %.2f\n", subtotal);
    printf("Desconto aplicado: %.0f%%\n", desconto * 100.0);
    printf("Frete: R$ %.2f\n", frete);
    printf("Total a pagar: R$ %.2f\n", total);

    return 0; 
}
