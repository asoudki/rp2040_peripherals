#ifndef EDF_H
#define EDF_H

#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>

#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/irq.h"
#include "pico/time.h"

#define EDF_MAX_TASKS               10
#define EDF_SCHEDULER_PRIORITY      (configMAX_PRIORITIES - 1)
#define EDF_SELECTED_PRIORITY       (configMAX_PRIORITIES - 2)
#define EDF_UNSELECTED_PRIORITY     (configMAX_PRIORITIES - 3)
#define EDF_SCHEDULER_STACK_SIZE    2048

typedef enum {
    EDF_TASK_READY = 0,
    EDF_TASK_RUNNING = 1,
    EDF_TASK_SUSPENDED = 2
} edf_task_state_t;

typedef struct {
    TaskHandle_t task_handle;
    TickType_t task_deadline;
    TickType_t task_period;
    edf_task_state_t task_state;
} edf_task_t;

SemaphoreHandle_t scheduler_semaphore;
repeating_timer_t scheduler_timer;

void edf_init(void);
bool edf_add_task(TaskHandle_t task_handle, TickType_t task_deadline, TickType_t task_period, edf_task_state_t task_state);
bool edf_start_task(TaskHandle_t task_handle);
bool edf_pause_task(TaskHandle_t task_handle);
bool edf_remove_task(TaskHandle_t task_handle);
bool edf_task_completed(TaskHandle_t task_handle);
void edf_start(uint32_t timer_period_us);

#endif // EDF_H