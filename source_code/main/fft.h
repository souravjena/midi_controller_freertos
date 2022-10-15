/**
 * @file      fft.h
 * @author    Sourav Jena, Yi Chen
 * @brief     Header file for FFT
 * @version   1.0
 * @date      2022-05-28
 * 
 */

#ifndef FFT_H
#define FFT_H

#include "main.h"
#include "arduinoFFT.h"

#define CHANNEL A0
#define NUM_SAMPLES 128

extern arduinoFFT FFT;                       ///<   FFT Object 

extern const uint16_t samples;               // This value MUST ALWAYS be a power of 2
extern const double samplingFrequency;       // Hz, must be less than 10000 due to ADC

extern unsigned int sampling_period_us;
extern unsigned long microseconds;

extern double vReal[NUM_SAMPLES];
extern double vImag[NUM_SAMPLES];

/**
 * @brief Generates random 128 samples and uses these to populate a buffer.
 * 
 */
void fft_generate_samples();

/**
 * @brief FFT initializations
 * 
 */
void fft_init(void);

/**
 * @brief Uses ADC to generate samples.
 * 
 */
void fft_generate_sample(void);

/**
 * @brief Returns computed FFT
 * 
 * @param vReal Address of the buffer containing real values of the smaples.
 * @param vImag Address of the buffer containing imaginary values of the samples
 * @param samples Number of samples
 * @return double Computed FFT
 */
double fft_get(double *vReal, double *vImag, uint16_t samples);

#endif