//
// Created by grave on 23/10/18.
//Este PIM � composto de duas partes: uma te�rica e outra pr?tica.
//Para a parte pr?tica, cada aluno ou grupo de PIM dever? desenvolver, em linguagem C,
//um sistema para venda de ingressos de teatro.
//O sistema de venda de ingressos de teatro dever? levar em considera??o uma tabela de
//valores para os ingressos, a qual dever? contemplar meia-entrada (50% de desconto) para
//estudantes,  crian?as  de  02  a  12  anos,  adultos  a  partir  de  60  anos  e  professores  da  rede
//p?blica de ensino.
//A  tabela  tamb?m  dever?  contemplar  ingresso  com  100%  de  desconto  para  crian?as
//carentes da rede p?blica de ensino ?s ter?as-feiras.
//Ao concretizar a compra do ingresso, o sistema dever? emitir (mostrar na tela) um ticket
//com a data, a hora, o nome da pe?a teatral e o n?mero da poltrona. Nenhum espectador
//pode ter um ingresso com o mesmo n?mero da poltrona de outro espectador da mesma
//        pe?a teatral de um determinado hor?rio.
//O   sistema   dever?   informar   quando   n?o   existir   mais   lugares   dispon?veis   e,
//consequentemente,  n?o  permitir  mais  a  venda  de  ingressos  para  a  pe?a  em  quest?o.
//Dever? tamb?m fazer a gest?o do caixa, isto ?, informar no fechamento do caixa todas as
//        movimenta??es do dia e o saldo do fechamento.
//

#include <stdio.h>
#include <time.h>
#include <locale.h>
#include <stdlib.h>
#include "clearscr.h"
#include "pausecmd.h"


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
        printf("\t\t� estudante? (S/N) ");
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
        printf("\t\t� estudante rede p?blica? (S/N) ");
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

    pausecmd();

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
            printf("\n\t\t[O Lugar j� foi reservado!] \n");
        }
    } while (1);
}

void MenuPrincipal() {
    int opcao = 0;

    printf("\n\n\n\n");
    printf("\t\t===============================================\n");
    printf("\t\t*      I N G R E S S O * T E A T R O          *\n");
    printf("\t\t===============================================");
    printf("\n\t\t||         Data da pe�a: %d/%d/%d %d:%d     ||", DATA->tm_mday, DATA->tm_mon, (DATA->tm_year + 1900),
           HORARIO_PECA.hora, HORARIO_PECA.minuto);
    printf("\n\t\t||            M A I N  *  M E N U            ||");
    printf("\n\t\t===============================================");
    printf("\n\t\t||                                           ||");
    printf("\n\t\t||        1. COMPRAR INGRESSO                ||");
    printf("\n\t\t||        2. FECHAMENTO                      ||");
    printf("\n\t\t||        3. SAIR                            ||");
    printf("\n\t\t||                                           ||");
    printf("\n\t\t===============================================\n\n\n");

    printf("\n\t\tSelecione op��o: ");

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
            printf("Selecione uma op��o v�lida");
            MenuPrincipal();
            break;
    }
    opcao = 0;
}
