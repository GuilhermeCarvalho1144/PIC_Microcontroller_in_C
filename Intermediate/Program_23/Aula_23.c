//CURSO DE PIC
//PROGRAMA 23.....ESSE PROGRAMA TESTA A INTERRUP��O UTILIZANDO OUVERFLOW TIMMER0 COM O PIC16F628A
//MAIS INFORMA��ES NO LINK: https://www.youtube.com/watch?v=K81eMwKZYYw&index=23&list=PLZ8dBTV2_5HQ-LrS9r1dP30h8n9sh04gh
//GUILHERME CARVALHO

//MAPEAMENTO DE HARDWARE
#define output RB4_bit

//VARIAVEIS
int count = 0;

/*ESSA FUN��O J� � IMPLEMENTADA NO MIKROC...ELA AJUDA O PROGRAMADOR A TRATAR DE INTERRUP��ES (VEJA O HELP)....
ESSA FUN��O � DO TIPO VOID, PORTANTO NAO POSSUI RETONO...TAMB�M N�O POSSUI NENHUM TIPO DE PARAMETRO...
*/
 void interrupt(){
      if(T0IF_bit){             //QUANDO T0IF_BIT � 1 HOUVE INTERRUP��O
               count++;         //INCREMENTO DE COUNT
               TMR0 = 0x06;     //INICIALIZANDO TIMMER0
               T0IF_bit = 0x00; //******BIT QUE DETERMINA SE HOUVE A INTERRUP��O DEVE SER ZERADO VIA SOFTWARE******
      }
 }

//FUN��O MAIN
void main() {
     //CONFIGURANDO A INTERUP��O
     OPTION_REG = 0x81;         //DESABILITA OS RESISTORES DE PULL-UP (BIT MAIS SIGNIFICATIVO...ATIVA EM LOW RBPU)..
                                //...DEFINE O PRESCALE DA CONTAGEM 1:4...A CADA 4 INTRU��ES TIMER0 � INCREMENTADO
     GIE_bit = 0x01;            //HABILITA AS INTERRUP��ES GLOBAIS(BIT MAIS SIGNIFIFATIVO GIE)...
     PEIE_bit = 0x01;           //...HABILITA AS INTERRUP��ES PELOS PERRIFERICOS(SEGUNDO BIT MAIS SIGNIFICATIVO PEIE)...
     T0IE_bit = 0x01;           //...HABILITA AS INTERRUP��ES POR MEIO DO TIMMER0(TERCEIRO BIT MAIS SIGNIFICATIVO T0IE)

     TMR0 = 0x06;               //INICIALIZA O TIMMER0

     //CONFIGURANDO OS REGISTRADORES
     //CMCON = 0x07;            //DESABILITA OS COMPARADORES
     TRISB.RB4 = 0x00;          //DEFINE O PINO RB4 COMO SAIDA DIGITAL
     PORTB = 0x00;              //INICIALIZA TODO O PORTB...O VALOR DEVE SER 0x06 PARA QUE O DELAY SEJA DE 500ms

     //LOOP PRINCIPAL
     while(1){
     		if(count == 500){    //***CONTA*** -> [1/(CLOCK/4)] * 4 * 250 = 500ms......***CLOCK = 4MHz**
                       output = ~output;
                       count = 0;
              }
     }
}