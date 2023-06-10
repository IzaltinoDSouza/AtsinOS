#pragma once

#include <timer.h>

//High precision event timer

#define HPET_GENERAL_CAPABILITIES 0xFED00000
#define HPET_GENERAL_CONFIG       0xFED00010
#define HPET_MAIN_COUNTER         0xFED000F0

u64 hpet_read(u64 reg)
{
    volatile u64 * hpet = (u64*)reg;
    return *hpet;
}

void hpet_write(u64 reg, u64 value)
{
    volatile u64 * hpet = (u64*)reg;
    *hpet = value;
}

void timer_init()
{
    hpet_write(HPET_GENERAL_CONFIG, 1);
    hpet_write(HPET_MAIN_COUNTER, 0);
}

u64 get_time_ms()
{
    u64 main_counter = hpet_read(HPET_MAIN_COUNTER);
    u64 frequency    = hpet_read(HPET_GENERAL_CAPABILITIES) >> 32;
    return (main_counter * 1000) / frequency;
}

void delay_ms(u64 ms)
{
    u64 start = get_time_ms();
    while((get_time_ms() - start) < (ms)) { }
}
