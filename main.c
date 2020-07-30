#include <stdint.h>

#define RCC_BASE    0x40021000
#define GPIOC_BASE  0x40011000

#define RCC_APB2ENR *(volatile uint32_t *)(RCC_BASE   + 0x18u)
#define GPIOC_CRH   *(volatile uint32_t *)(GPIOC_BASE + 0x04u)
#define GPIOC_ODR   *(volatile uint32_t *)(GPIOC_BASE + 0x0Cu)

#define RCC_IOPCEN  (1u<<4u)
#define GPIOC13     (1ul<<13u)

int main() {
    RCC_APB2ENR |= RCC_IOPCEN;
    GPIOC_CRH   &= 0xFF0FFFFFu;
    GPIOC_CRH   |= 0x00200000u;

    while(1){
        GPIOC_ODR |= GPIOC13;
        for (int i = 0; i < 500000; i++)
                __asm__("nop");
        GPIOC_ODR &= ~GPIOC13;
        for (int i = 0; i < 500000; i++)
                __asm__("nop");
    }
}