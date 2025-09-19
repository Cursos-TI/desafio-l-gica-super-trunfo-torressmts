#include <stdio.h>

// Função para exibir o menu de atributos, evitando repetir o já escolhido
void exibirMenu(int atributoExcluido) {
    printf("\n=== Menu de Atributos ===\n");
    if(atributoExcluido != 1) printf("1 - Populacao\n");
    if(atributoExcluido != 2) printf("2 - Area\n");
    if(atributoExcluido != 3) printf("3 - PIB\n");
    if(atributoExcluido != 4) printf("4 - Pontos Turisticos\n");
    if(atributoExcluido != 5) printf("5 - Densidade Demografica\n");
    if(atributoExcluido != 6) printf("6 - PIB per Capita\n");
}

// Função para retornar o valor do atributo selecionado de uma carta
float valorAtributo(int opcao, unsigned long int populacao, float area, float pib, int pontosTuristicos, float densidade, float pibPerCapita) {
    switch(opcao) {
        case 1: return (float)populacao;
        case 2: return area;
        case 3: return pib;
        case 4: return (float)pontosTuristicos;
        case 5: return densidade;
        case 6: return pibPerCapita;
        default: return 0;
    }
}

// Função para retornar o nome do atributo
char* nomeAtributo(int opcao) {
    switch(opcao) {
        case 1: return "Populacao";
        case 2: return "Area";
        case 3: return "PIB";
        case 4: return "Pontos Turisticos";
        case 5: return "Densidade Demografica";
        case 6: return "PIB per Capita";
        default: return "Desconhecido";
    }
}

int main() {
    // --- Cartas pré-cadastradas (exemplo) ---
    char nomeCidade1[50] = "Cidade A";
    char nomeCidade2[50] = "Cidade B";

    unsigned long int populacao1 = 12000000;
    unsigned long int populacao2 = 8000000;

    float area1 = 1500.0f;
    float area2 = 1800.0f;

    float pib1 = 400.0f; // em bilhões
    float pib2 = 350.0f;

    int pontosTuristicos1 = 25;
    int pontosTuristicos2 = 30;

    float densidade1 = (float)populacao1 / area1;
    float densidade2 = (float)populacao2 / area2;

    float pibPerCapita1 = (pib1 * 1000000000.0f) / populacao1;
    float pibPerCapita2 = (pib2 * 1000000000.0f) / populacao2;

    int atributo1, atributo2;

    // --- Escolha do primeiro atributo ---
    do {
        exibirMenu(0);
        printf("Escolha o primeiro atributo (1-6): ");
        scanf("%d", &atributo1);
        if(atributo1 < 1 || atributo1 > 6) printf("Opcao invalida! Tente novamente.\n");
    } while(atributo1 < 1 || atributo1 > 6);

    // --- Escolha do segundo atributo ---
    do {
        exibirMenu(atributo1);
        printf("Escolha o segundo atributo (1-6): ");
        scanf("%d", &atributo2);
        if(atributo2 < 1 || atributo2 > 6 || atributo2 == atributo1) 
            printf("Opcao invalida! Tente novamente.\n");
    } while(atributo2 < 1 || atributo2 > 6 || atributo2 == atributo1);

    // --- Valores dos atributos ---
    float val1A1 = valorAtributo(atributo1, populacao1, area1, pib1, pontosTuristicos1, densidade1, pibPerCapita1);
    float val2A1 = valorAtributo(atributo1, populacao2, area2, pib2, pontosTuristicos2, densidade2, pibPerCapita2);

    float val1A2 = valorAtributo(atributo2, populacao1, area1, pib1, pontosTuristicos1, densidade1, pibPerCapita1);
    float val2A2 = valorAtributo(atributo2, populacao2, area2, pib2, pontosTuristicos2, densidade2, pibPerCapita2);

    // --- Comparação individual dos atributos ---
    int pontosCarta1 = 0, pontosCarta2 = 0;

    // Regra especial: Densidade Demográfica -> menor vence
    if(atributo1 == 5) {
        pontosCarta1 += (val1A1 < val2A1) ? 1 : 0;
        pontosCarta2 += (val2A1 < val1A1) ? 1 : 0;
    } else {
        pontosCarta1 += (val1A1 > val2A1) ? 1 : 0;
        pontosCarta2 += (val2A1 > val1A1) ? 1 : 0;
    }

    if(atributo2 == 5) {
        pontosCarta1 += (val1A2 < val2A2) ? 1 : 0;
        pontosCarta2 += (val2A2 < val1A2) ? 1 : 0;
    } else {
        pontosCarta1 += (val1A2 > val2A2) ? 1 : 0;
        pontosCarta2 += (val2A2 > val1A2) ? 1 : 0;
    }

    // --- Soma dos valores para desempate ---
    float somaCarta1 = val1A1 + val1A2;
    float somaCarta2 = val2A1 + val2A2;

    // --- Exibição dos resultados ---
    printf("\n=== Resultado da Comparacao ===\n");
    printf("Carta 1 - %s\n", nomeCidade1);
    printf("  %s: %.2f\n", nomeAtributo(atributo1), val1A1);
    printf("  %s: %.2f\n", nomeAtributo(atributo2), val1A2);
    printf("  Soma dos atributos: %.2f\n", somaCarta1);

    printf("\nCarta 2 - %s\n", nomeCidade2);
    printf("  %s: %.2f\n", nomeAtributo(atributo1), val2A1);
    printf("  %s: %.2f\n", nomeAtributo(atributo2), val2A2);
    printf("  Soma dos atributos: %.2f\n", somaCarta2);

    // --- Determinar o vencedor ---
    if(somaCarta1 > somaCarta2)
        printf("\nResultado Final: Carta 1 (%s) venceu!\n", nomeCidade1);
    else if(somaCarta2 > somaCarta1)
        printf("\nResultado Final: Carta 2 (%s) venceu!\n", nomeCidade2);
    else
        printf("\nResultado Final: Empate!\n");

    return 0;
}
