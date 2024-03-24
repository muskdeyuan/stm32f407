#ifndef __BITBAND_H__
#define __BITBAND_H__

#define BITBAND(addr,bitnum)       0x42000000+ (addr & 0xFFFFF)*32 + bitnum *4
#define MEM_ADDR(addr)             *((volatile uint32_t*)(addr))
#define BIT_ADDR(addr,bitnum)      MEM_ADDR(BITBAND(addr,bitnum))

#define GPIOA_IDR_ADDR             (GPIOA_BASE + 0x10)
#define GPIOA_ODR_ADDR             (GPIOA_BASE + 0x14)

#define GPIOB_IDR_ADDR             (GPIOB_BASE + 0x10)
#define GPIOB_ODR_ADDR             (GPIOB_BASE + 0x14)

#define GPIOC_IDR_ADDR             (GPIOC_BASE + 0x10)
#define GPIOC_ODR_ADDR             (GPIOC_BASE + 0x14)

#define GPIOD_IDR_ADDR             (GPIOD_BASE + 0x10)
#define GPIOD_ODR_ADDR             (GPIOD_BASE + 0x14)

#define GPIOE_IDR_ADDR             (GPIOE_BASE + 0x10)
#define GPIOE_ODR_ADDR             (GPIOE_BASE + 0x14)

#define GPIOF_IDR_ADDR             (GPIOF_BASE + 0x10)
#define GPIOF_ODR_ADDR             (GPIOF_BASE + 0x14)

#define GPIOG_IDR_ADDR             (GPIOG_BASE + 0x10)
#define GPIOG_ODR_ADDR             (GPIOG_BASE + 0x14)

#define GPIOH_IDR_ADDR             (GPIOH_BASE + 0x10)
#define GPIOH_ODR_ADDR             (GPIOH_BASE + 0x14)

#define GPIOI_IDR_ADDR             (GPIOI_BASE + 0x10)
#define GPIOI_ODR_ADDR             (GPIOI_BASE + 0x14)


#define PAout(n)       BIT_ADDR(GPIOA_ODR_ADDR,n)  
#define PAin(n)        BIT_ADDR(GPIOA_IDR_ADDR,n) 

#define PBout(n)       BIT_ADDR(GPIOB_ODR_ADDR,n)  
#define PBin(n)        BIT_ADDR(GPIOB_IDR_ADDR,n)

#define PCout(n)       BIT_ADDR(GPIOC_ODR_ADDR,n)  
#define PCin(n)        BIT_ADDR(GPIOC_IDR_ADDR,n)

#define PDout(n)       BIT_ADDR(GPIOD_ODR_ADDR,n)  
#define PDin(n)        BIT_ADDR(GPIOD_IDR_ADDR,n)

#define PEout(n)       BIT_ADDR(GPIOE_ODR_ADDR,n)  
#define PEin(n)        BIT_ADDR(GPIOE_IDR_ADDR,n)

#define PFout(n)       BIT_ADDR(GPIOF_ODR_ADDR,n)  
#define PFin(n)        BIT_ADDR(GPIOF_IDR_ADDR,n)

#define PGout(n)       BIT_ADDR(GPIOG_ODR_ADDR,n)  
#define PGin(n)        BIT_ADDR(GPIOG_IDR_ADDR,n)

#define PHout(n)       BIT_ADDR(GPIOH_ODR_ADDR,n)  
#define PHin(n)        BIT_ADDR(GPIOH_IDR_ADDR,n)

#define PIout(n)       BIT_ADDR(GPIOI_ODR_ADDR,n)  
#define PIin(n)        BIT_ADDR(GPIOI_IDR_ADDR,n)

#endif
