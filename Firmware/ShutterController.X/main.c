#pragma config FOSC = INTOSCCLK // Oscillator Selection bits (INTOSC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = ON        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = OFF      // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is digital input, MCLR internally tied to VDD)
#pragma config BOREN = ON       // Brown-out Detect Enable bit (BOD enabled)
#pragma config LVP = ON         // Low-Voltage Programming Enable bit (RB4/PGM pin has PGM function, low-voltage programming enabled)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Data memory code protection off)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>

bit currentState;
void CloseShutter();

void OpenShutter() {

    PORTB = 0;
    RB1 = 1;
    _delaywdt(2000000);
    RB1 = 0;
    RB2 = 1;    

}

void CloseShutter() {
    
    PORTB = 0;
        
    RB3 = 1;
    _delaywdt(800000);
    RB3 = 0;
}

void interrupt isr(void) {
    
    
    
}


int main(void) {
    
    TRISA = 0b00100000;
    TRISB = 0b00000000;
    OPTION_REG = 0b10001111;

    while(1) {
        
        if (currentState == 0 && RA5 == 1) {
            currentState = RA5;
            OpenShutter();
            
        } else if (currentState == 1 && RA5 == 0) {
            currentState = RA5;
            CloseShutter();
            
        }
                       
        _delay(100);
        CLRWDT();
    }
    
    return 0;
}



