//CURSO DE PIC
//PROGRAMA 30...ESSE CODIGO FOI DESENVOLVIDO PARA IMPLEMENTAR O PWM COM TIMER 2 COM O PIC16F628A
//MAIS INFORM��ES NO LINK : https://www.youtube.com/watch?v=TtYJtwj8ry8&list=PLZ8dBTV2_5HQ-LrS9r1dP30h8n9sh04gh&index=30
//GUILHERME CARVALHO PEREIRA
//INICIO

//MAPEAMENTO DE HARDWARE
#define S1 RA0_bit
#define S2 RA1_bit

/*ESSA FUN��O J� � IMPLEMENTADA NO MIKROC...ELA AJUDA O PROGRAMADOR A TRATAR DE INTERRUP��ES (VEJA O HELP)....
ESSA FUN��O � DO TIPO VOID, PORTANTO NAO POSSUI RETONO...TAMB�M N�O POSSUI NENHUM TIPO DE PARAMETRO...
*/
void interrupt(){//VARREDURA ACONTECE A CADA 20ms APROXIMADAMENTE
     if(T0IF_bit){//VERIFICA SE HOUVE ESTOURO DO TIMER 0
                  T0IF_bit = 0x00;//LIMPA A FLAG DE INTERRUP��O DO TIMER 0...***IMPORTANTE***
                  TMR0 = 0x6C;//REDEFINE O VALOR DE TIME
                  if(!S1) CCPR1L++;      //CASO S1 FOR PRECIONADO, ENT�O AUMENTA O DUTY CICLE
                  if(!S2) CCPR1L--;      //CASO S2 FOR PRECIONADO, ENT�O DECREMENTA DUTY CICLE
     }
}

//FUN��O MAIN
void main() {
     //CONFIGURANDO OS REGISTRADORES
     CMCON = 0x07;                  //DESABILITA OS COMPARADORES
     //CONFIGURANDO OS REGISTRADORES DA INTERRUP��O DO TIMER 0
     OPTION_REG = 0x86;              //DESABILITA OS RESISTORES DE PULL-UP...SETA O PRESCALER DO TIME 0 PARA 1:126
     GIE_bit = 0x01;                 //HABILITA AS INTERRUP��ES GLOBAIS
     PEIE_bit = 0x01;                //HABILITA AS INTERRUP��ES POR PERIFERICOS
     T0IE_bit = 0x01;                //HABILITA AS INTERRUP��ES POR TIMER 0
     TMR0 = 0x6C;                    //DEFINE O VALOR DE TIMER 0 PARA O ESTOURO SER APROXIMADAMENTE 20ms
     //CONFIGURA OS REGISTRADORES DO TIMER 2 PARA O PWM
     //EQ. QUE DEFINE O PERIODO DO PWM:
     //PERIODO = (PR2 +1) * CICLO DE MAQUINA * PRESCALER DO TIMER 2
     //PERIDO = (255+10 * 1us * 16 =  4,096ms
     //FREQ = 1 / PERIODO = 244,4142Hz
     T2CON = 0x06;                   //LIGA O TIMER 2...SETA O POSCALER DE 1:1 E PRESCALER DE 1:16
     TMR2 = 0xFF;                    //DEFINER O VALOR INICIAL DO REGISTRADOR DE ESTOURO TIMER 2
     CCPR1L = 0x00;                  //FAZ COM QUE O LED INICIE APAGADO... A RESOLU��O DO PWM � DE 10 BITS
                                     //ESSE 10 BITS S�O FORMADOS PELOS 8 BITS DO CCPR1L E PELOS 2 BITS MAIS SIGNIFICATIVOS
                                     //DO REGISTRADOR CCP1CON
     CCP1CON = 0x0C;                 //HABILITA O MODOLU PWM
     //CONFIGURANDO OS REGISTRADORES TRIS
     TRISA = 0x03;                   //DEFINE RA0 E RA1 COMO ENTRADAS DIGITAIS
     TRISB = 0x00;                   //DEFINE TODO O PORTB COMO SAIDA DIGITAL..PINO QUE � USADO PARA PWM � O RB3/CCP1
     PORTA = 0x03;                   //RA0 E RA1 INICIAM EM NIVEL HIGH...S�O ATIVOS EM NIVEL LOW(RESISTOR DE PULL-UP)
     PORTB = 0x00;                   //INICIA O PORTB TODO EM NIVEL LOW
     //ESSE CODIGO NAO POSSUI LOOP PRINCIPAL POIS A LOGICA ESTA IMPLEMENTADA NA INTERRUP��O
}
//FIM