/**
 * @file      main.h
 * @author    Sourav Jena, Yi Chen
 * @brief     Header file for the main.ino
 * @version   1.0
 * @date      2022-05-28
 * 
 */

#ifndef MAIN_H
#define MAIN_H

#include <Arduino_FreeRTOS.h>
#include <stdint.h>
#include <queue.h>
#include <task.h>

#include "fft.h"
#include "rt1.h"
#include "rt2.h"
#include "rt3.h"
#include "rt4.h"
#include "midi.h"

extern TaskHandle_t task_rt1_handle;
extern TaskHandle_t task_rt2_handle;

extern TaskHandle_t task_rt3_handle;
extern TaskHandle_t task_rt3p0_handle;
extern TaskHandle_t task_rt3p1_handle;

extern TaskHandle_t task_rt4_handle;

extern QueueHandle_t q_handle_buffer;
extern QueueHandle_t q_handle_signal;

struct fft_buffer {
  double *arr_real;
  double *arr_img;
};
typedef struct fft_buffer fft_buffer_t;


struct my_time {
  TickType_t rtos_ticks;
  uint32_t time_ms;
};
typedef struct my_time time_t;

#endif