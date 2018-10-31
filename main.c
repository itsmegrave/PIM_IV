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

struct horario_peca{
    int hora;
    int minuto;
};


void CompreIngresso();
void MenuPrincipal();
struct tm* PegarData();

int Sair() {
    printf("Sistema finalizado");
    return 0;
}

struct tm* DATA;
struct horario_peca HORARIO_PECA;
float PRECO_BASE = 50.0;

int main() {
    DATA = PegarData();
    HORARIO_PECA.hora=21;
    HORARIO_PECA.minuto=30;
    MenuPrincipal();
}

struct tm* PegarData() {
    time_t now;
    time (&now);

    return localtime(&now);
}


int ConferirEstudante() {
    int valido = 0;
    char opcao;
    do{
        printf("É estudante?\nUse S ou N");
        scanf("%s", &opcao);
        switch(opcao) {
            case 'S':
            case 's':
                return 1;
            case 'N':
            case 'n':
                return 0;
            default:
                break;
        }

    }while(valido!=1);

    return 0;
}

int ConferirProfessor() {
    int valido = 0;
    char opcao;
    do{
        printf("É professor rede publica?\nUse S ou N");
        scanf("%s", &opcao);
        switch(opcao) {
            case 'S':
            case 's':
                return 1;
                break;
            case 'N':
            case 'n':
                return 0;
                break;
            default:
                break;
        }

    }while(valido!=1);

    return 0;
}

int ConferirMenorDeIdade(int idade) {
    if(idade >=2 && idade<=12) {
        return 1;
    }
    return 0;
}

int ConferirIdoso(int idade){
    if(idade >=60) {
        return 1;
    }
    return 0;
}

int ConferirIdadeDiaDaSemana(int idade) {
    int diaDaSemana = DATA->tm_wday;

    char opcao;
    do{
        printf("É estudante carente?\nUse S ou N");
        scanf("%s", &opcao);
        switch(opcao) {
            case 'S':
            case 's':
                if(diaDaSemana==2) {
                    return 1;
                }
                return 0;
            case 'N':
            case 'n':
                return 0;
            default:
                break;
        }
    }while(1);
}

void CompreIngresso() {
    int idade=0;

    printf("Informe sua idade:");
    scanf("%d", &idade);

    int menor = ConferirMenorDeIdade(idade);
    int idoso = ConferirIdoso(idade);
    int estudante=ConferirEstudante();
    int professor = ConferirProfessor();
    int criancaTercaFeira =  ConferirIdadeDiaDaSemana(idade);
     // MenuPrincipal();
}

void MenuPrincipal() {
    int sair = 0;
    int opcao = 0;

    printf("\n\n\n\n");
    printf("\t\t===============================================\n");
    printf("\t\t*      I N G R E S S O * T E A T R O          *\n");
    printf("\t\t===============================================");
    printf("\n\t\t||         Data da peça: %d/%d/%d %d:%d     ||         ", DATA->tm_mday, DATA->tm_mon, (DATA->tm_year+1900), HORARIO_PECA.hora, HORARIO_PECA.minuto);
    printf("\n\t\t||            M A I N  *  M E N U            ||");
    printf("\n\t\t===============================================");
    printf("\n\t\t||                                           ||");
    printf("\n\t\t||        1. COMPRAR INGRESSO                ||");
    printf("\n\t\t||        2. FECHAMENTO                      ||");
    printf("\n\t\t||        3. SAIR                            ||");
    printf("\n\t\t||                                           ||");
    printf("\n\t\t===============================================\n\n\n");

        printf("\n\t\t Selecione opção:");

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
