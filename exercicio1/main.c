#include <stdio.h>  
int main() {
    printf("Bem-vindo, Marcus Tomazelli!\n");  

    double valorPedido = 0.0;  
    int quantidadeParcelas = 0;  

    printf("Informe o valor do pedido: ");  
    
    scanf("%lf", &valorPedido);  

    printf("Informe a quantidade de parcelas: ");  
    scanf("%d", &quantidadeParcelas);  

    double juros = 0.0;  

    
    if (quantidadeParcelas < 4) {
        juros = 0.0;  
    } else if (quantidadeParcelas >= 4 && quantidadeParcelas < 6) {
        juros = 0.04;  
    } else if (quantidadeParcelas >= 6 && quantidadeParcelas < 9) {
        juros = 0.08;  
    } else if (quantidadeParcelas >= 9 && quantidadeParcelas < 13) {
        juros = 0.16;  
    } else {
        juros = 0.32;  
    }

    
    double valorDaParcela = (valorPedido * (1.0 + juros)) / quantidadeParcelas;
    
    double valorTotalParcelado = valorDaParcela * quantidadeParcelas;

    
    printf("\nResumo do pedido:\n");
    printf("Valor original: R$ %.2f\n", valorPedido);
    printf("Quantidade de parcelas: %d\n", quantidadeParcelas);
    printf("Juros aplicado: %.0f%%\n", juros * 100.0);
    printf("Valor de cada parcela: R$ %.2f\n", valorDaParcela);
    printf("Valor total parcelado: R$ %.2f\n", valorTotalParcelado);

    return 0;  
}
