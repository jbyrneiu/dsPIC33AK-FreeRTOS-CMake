/*
 * FreeRTOSConfig.h - minimal configuration for a single blink task on
 * dsPIC33AK128MC.
 *
 * This is a trimmed-down version of the configuration used by Microchip's
 * official dsPIC33A FreeRTOS demo (pic24-dspic33-freertos-demo repo).
 * Co-routines, trace facility, and other demo-only options were removed
 * to keep this project as simple as possible.
 */

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#ifndef __ASSEMBLER__
#include "xc.h"
#endif

/*-----------------------------------------------------------
 * IMPORTANT: configCPU_CLOCK_HZ MUST match the actual Fosc your clock
 * init code configures (see vClockInitialise() in main.c). If you change
 * the clock setup (e.g. via MCC's Clock Configurator), update this too -
 * the FreeRTOS tick timer (Timer1, set up automatically in port.c) is
 * derived directly from this value.
 *----------------------------------------------------------*/
#define configCPU_CLOCK_HZ ((unsigned long)50000000)
#define configTICK_RATE_HZ ((TickType_t)1000)

#define configUSE_PREEMPTION 1
#define configUSE_IDLE_HOOK 1
#define configUSE_TICK_HOOK 0
#define configMAX_PRIORITIES (4)
#define configMINIMAL_STACK_SIZE (200)
#define configTOTAL_HEAP_SIZE ((size_t)10000)
#define configMAX_TASK_NAME_LEN (10)
#define configUSE_TRACE_FACILITY 0
#define configUSE_16_BIT_TICKS 0
#define configIDLE_SHOULD_YIELD 1
#define configUSE_CO_ROUTINES 0
#define configUSE_TIMERS 1
#define configUSE_MUTEXES 1
#define configSUPPORT_STATIC_ALLOCATION 1
#define configSUPPORT_DYNAMIC_ALLOCATION 1

#define configTIMER_TASK_STACK_DEPTH configMINIMAL_STACK_SIZE
#define configTIMER_TASK_PRIORITY (configMAX_PRIORITIES - 1)
#define configTIMER_QUEUE_LENGTH 10

/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */
#define INCLUDE_vTaskPrioritySet 1
#define INCLUDE_uxTaskPriorityGet 0
#define INCLUDE_vTaskDelete 0
#define INCLUDE_vTaskCleanUpResources 0
#define INCLUDE_vTaskSuspend 1
#define INCLUDE_vTaskDelayUntil 1
#define INCLUDE_vTaskDelay 1

#define portHAS_STACK_OVERFLOW_CHECKING 1
#define taskYIELD() portYIELD_WITHIN_API()
#define portPOINTER_SIZE_TYPE int

/* Kernel (tick) interrupt priority - Timer1 is configured at this IPL by
the weak vApplicationSetupTickTimerInterrupt() in port.c. */
#define configKERNEL_INTERRUPT_PRIORITY 0x01

#define pdMS_TO_TICKS(xTimeInMs)                                               \
  ((TickType_t)(((TickType_t)(xTimeInMs)) * ((TickType_t)configTICK_RATE_HZ) / \
                (TickType_t)1000))

#endif /* FREERTOS_CONFIG_H */
