#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

typedef struct Timer {
    uint32_t end_time;
} Timer;

void TimerInit(Timer* timer);
void TimerCountdownMS(Timer* timer, unsigned int timeout_ms);
void TimerCountdown(Timer* timer, unsigned int timeout_s);
char TimerIsExpired(Timer* timer);
int  TimerLeftMS(Timer* timer);

#endif
