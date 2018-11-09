//
// Created by grave on 23/10/18.
//Este PIM é composto de duas partes: uma teórica e outra prática.
//Para a parte prática, cada aluno ou grupo de PIM deverá desenvolver, em linguagem C,
//um sistema para venda de ingressos de teatro.
//O sistema de venda de ingressos de teatro deverá levar em consideração uma tabela de
//valores para os ingressos, a qual deverá contemplar meia-entrada (50% de desconto) para
//estudantes,  crianças  de  02  a  12  anos,  adultos  a  partir  de  60  anos  e  professores  da  rede
//pública de ensino.
//A  tabela  também  deverá  contemplar  ingresso  com  100%  de  desconto  para  crianças
//carentes da rede pública de ensino às terças-feiras.
//Ao concretizar a compra do ingresso, o sistema deverá emitir (mostrar na tela) um ticket
//com a data, a hora, o nome da peça teatral e o número da poltrona. Nenhum espectador
//pode ter um ingresso com o mesmo número da poltrona de outro espectador da mesma
//        peça teatral de um determinado horário.
//O   sistema   deverá   informar   quando   não   existir   mais   lugares   disponíveis   e,
//consequentemente,  não  permitir  mais  a  venda  de  ingressos  para  a  peça  em  questão.
//Deverá também fazer a gestão do caixa, isto é, informar no fechamento do caixa todas as
//        movimentações do dia e o saldo do fechamento.
//

#include <stdio.h>
#include <time.h>
#include <locale.h>
#include <stdlib.h>
#include "clearscr.h"


struct horario_peca {
    int hora;
    int minuto;
};


void CompreIngresso();

void MenuPrincipal();

void InicializarSala();

int SelecionarPoltrona();

int VerificarSalaCheia();

float CalcularValor(int ehMenor, int ehIdoso, int ehEstudante, int ehCriancaETercaFeira, int ehProfessor);

void GravarPoltrona(int cadeiraSelecionada, float valor);

void GerarTicket(int cadeiraSelecionada, float valor);

struct tm *PegarData();

int Sair() {
    printf("\t\t[Sistema finalizado]");
    return 0;
}

struct tm *DATA;
struct horario_peca HORARIO_PECA;
float PRECO_BASE = 50.0;
float POLTRONAS[50];

int main() {
    setlocale(LC_ALL, "Portuguese");

    DATA = PegarData();
    HORARIO_PECA.hora = 21;
    HORARIO_PECA.minuto = 30;

    InicializarSala();
    MenuPrincipal();
}

struct tm *PegarData() {
    time_t now;
    time(&now);

    return localtime(&now);
}

void InicializarSala() {
    for (int i = 0; i < sizeof(POLTRONAS) / sizeof(float); ++i) {
        POLTRONAS[i] = -1;
    }
}

int ConferirEstudante() {
    char opcao;
    do {
        printf("\t\tÉ estudante? (S/N) ");
        scanf("%s", &opcao);
        switch (opcao) {
            case 'S':
            case 's':
                return 1;
            case 'N':
            case 'n':
                return 0;
            default:
                break;
        }

    } while (1);
}

int ConferirProfessor() {
    char opcao;
    do {
        printf("\t\t� professor da rede publica? (S/N) ");
        scanf("%s", &opcao);
        switch (opcao) {
            case 'S':
            case 's':
                return 1;
            case 'N':
            case 'n':
                return 0;
            default:
                break;
        }

    } while (1);
}

int ConferirMenorDeIdade(int idade) {
    if (idade >= 2 && idade <= 12) {
        return 1;
    }
    return 0;
}

int ConferirIdoso(int idade) {
    if (idade >= 60) {
        return 1;
    }
    return 0;
}

int ConferirCriancaCarenteDiaDaSemana() {
    int diaDaSemana = DATA->tm_wday;

    char opcao;
    do {
        printf("\t\tÉ estudante rede pública? (S/N) ");
        scanf("%s", &opcao);
        switch (opcao) {
            case 'S':
            case 's':
                if (diaDaSemana == 2) {
                    return 1;
                }
                return 0;
            case 'N':
            case 'n':
                return 0;
            default:
                break;
        }
    } while (1);
}

int VerificarSalaCheia() {
    for (int i = 0; i < sizeof(POLTRONAS) / sizeof(float); ++i) {
        if (POLTRONAS[i] == -1) {
            return 0;
        }
    }
    return 1;
}

void CompreIngresso() {
    if (VerificarSalaCheia() == 1) {
        printf("\t\t[Sala Lotada!]");

        MenuPrincipal();
    }
    int idade = 0;
    int ehMenor = 0;
    int ehIdoso = 0;
    int ehEstudante = 0;
    int ehEstudanteCriancaETercaFeira = 0;
    int ehProfessor = 0;
    int cadeiraSelecionada = 0;
    float valor;

    printf("\t\tInforme sua idade: ");
    scanf("%d", &idade);

    ehMenor = ConferirMenorDeIdade(idade);
    ehIdoso = ConferirIdoso(idade);
    ehEstudante = ConferirEstudante();

    if (ehEstudante == 1) {
        ehEstudanteCriancaETercaFeira = ConferirCriancaCarenteDiaDaSemana();
    } else {
        ehProfessor = ConferirProfessor();
    }
    cadeiraSelecionada = SelecionarPoltrona();

    valor = CalcularValor(ehMenor, ehIdoso, ehEstudante, ehEstudanteCriancaETercaFeira, ehProfessor);

    GravarPoltrona(cadeiraSelecionada, valor);
    GerarTicket(cadeiraSelecionada, valor);

    system("read -p '\t\tPressione ENTER para continuar...' var");

    clearscr();

    MenuPrincipal();
}

float CalcularValor(int ehMenor, int ehIdoso, int ehEstudante, int ehCriancaETercaFeira, int ehProfessor) {
    float valorIngresso = PRECO_BASE;
    if (ehMenor == 1 || ehIdoso == 1 || ehEstudante == 1 || ehProfessor == 1) {
        valorIngresso = valorIngresso / 2;
    } else if (ehCriancaETercaFeira) {
        valorIngresso = 0;
    }

    return valorIngresso;
}

void GravarPoltrona(int cadeiraSelecionada, float valor) {
    POLTRONAS[cadeiraSelecionada - 1] = valor;
}

void GerarTicket(int cadeiraSelecionada, float valor) {
    printf("\t\t====================================\n");
    printf("\t\t*            T I C K E T           *\n");
    printf("\t\t====================================\n");

}

int SelecionarPoltrona() {
    int selecao;
    do {
        printf("\n\n");
        printf("\t\t=================================================\n");
        printf("\t\t*               P O L T R O N A S               *\n");
        printf("\t\t=================================================\n");

        for (int i = 1; i <= 50; i++) {
            if (i == 1 || i == 11 || i == 21 || i == 31 || i == 41) {
                printf("\n\t\t");
            }
            if (POLTRONAS[i - 1] == -1) {
                printf("[%2.d] ", i);
            } else {
                printf("[--] ");
            }
        }

        printf("\n\n\t\tSelecione sua Poltrona: ");
        scanf("%d", &selecao);
        selecao = selecao;
        if (POLTRONAS[selecao - 1] == -1) {
            return selecao;
        } else {
            printf("\n\t\t[O Lugar já foi reservado!] \n");
        }
    } while (1);
}

void MenuPrincipal() {
    int opcao = 0;

    printf("\n\n\n\n");
    printf("\t\t===============================================\n");
    printf("\t\t*      I N G R E S S O * T E A T R O          *\n");
    printf("\t\t===============================================");
    printf("\n\t\t||         Data da peça: %d/%d/%d %d:%d     ||", DATA->tm_mday, DATA->tm_mon, (DATA->tm_year + 1900),
           HORARIO_PECA.hora, HORARIO_PECA.minuto);
    printf("\n\t\t||            M A I N  *  M E N U            ||");
    printf("\n\t\t===============================================");
    printf("\n\t\t||                                           ||");
    printf("\n\t\t||        1. COMPRAR INGRESSO                ||");
    printf("\n\t\t||        2. FECHAMENTO                      ||");
    printf("\n\t\t||        3. SAIR                            ||");
    printf("\n\t\t||                                           ||");
    printf("\n\t\t===============================================\n\n\n");

    printf("\n\t\tSelecione opção: ");

    scanf("%d", &opcao);
    switch (opcao) {
        case 1:
            CompreIngresso();
            break;
        case 2:
            printf("Fechamento");
            break;
        case 3:
            Sair();
            break;
        default:
            printf("Selecione uma opção válida");
            MenuPrincipal();
            break;
    }
    opcao = 0;
}
