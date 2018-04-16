#pragma config FOSC = INTOSCCLK // Oscillator Selection bits (INTOSC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = ON        // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is digital input, MCLR internally tied to VDD)
#pragma config BOREN = ON       // Brown-out Detect Enable bit (BOD disabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (RB4/PGM pin has digital I/O function, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Data memory code protection off)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>

bit currentState;

void OpenShutter() {

    PORTB = 0b01000010;
    _delaywdt(1500000);
    PORTB = 0b01000100;
    
}

void CloseShutter() {
    
    PORTB = 0b00101000;        
    _delaywdt(800000);
    PORTB = 0b00000000;
}

void interrupt isr(void) { }


int main(void) {
        
    TRISB = 0b00000001;
    OPTION_REG = 0b10001111;
    currentState = 0;
    
    PORTB = 0b00000000;
    _delaywdt(250000);
    PORTB = 0b01000000;
    _delaywdt(250000);
    PORTB = 0b00100000;
    _delaywdt(250000);
    PORTB = 0b00001000;
    _delaywdt(250000);
    PORTB = 0b00000100;
    _delaywdt(250000);
    PORTB = 0b00000010;
    _delaywdt(250000);
    PORTB = 0b00000000;

    while(1) {
        
        if (currentState == 0 && RB0 == 1) {
            currentState = RB0;
            OpenShutter();
            
        } else if (currentState == 1 && RB0 == 0) {
            currentState = RB0;
            CloseShutter();
            
        }
                       
        _delaywdt(1000);
        CLRWDT();
    }
    
    return 0;
}



