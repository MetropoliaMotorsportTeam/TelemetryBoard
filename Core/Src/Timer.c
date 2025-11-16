#include "Timer.h"
#include "main.h"

void TimerInit(Timer* timer)
{
    timer->end_time = 0;
}

void TimerCountdownMS(Timer* timer, unsigned int timeout_ms)
{
    timer->end_time = HAL_GetTick() + timeout_ms;
}

void TimerCountdown(Timer* timer, unsigned int timeout_s)
{
    timer->end_time = HAL_GetTick() + (timeout_s * 1000);
}

char TimerIsExpired(Timer* timer)
{
    return (HAL_GetTick() >= timer->end_time);
}

int TimerLeftMS(Timer* timer)
{
    int32_t diff = (int32_t)timer->end_time - (int32_t)HAL_GetTick();
    return (diff > 0) ? diff : 0;
}
