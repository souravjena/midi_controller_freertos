/**
 * @file      fft.cpp
 * @author    Sourav Jena, Yi Chen
 * @brief     Source code of FFT
 * @version   1.0
 * @date      2022-05-28
 * 
 */

#include "fft.h"
#include "arduinoFFT.h"

arduinoFFT FFT = arduinoFFT(vReal, vImag, samples, samplingFrequency); /* Create FFT object */

const uint16_t samples = 64; 
const double samplingFrequency = 1000; 

double vReal[NUM_SAMPLES];
double vImag[NUM_SAMPLES];

unsigned int sampling_period_us;
unsigned long microseconds;


void fft_generate_samples(){

  randomSeed(analogRead(A7));

  for(int i = 0; i < NUM_SAMPLES; i++){
    vReal[i] = random(100, 999)/1000.0;
    vImag[i] = random(100, 999)/1000.0;
  }

}

void fft_init(){
  sampling_period_us = round(1000000*(1.0/samplingFrequency));
  // fft_generate_sample();
}


void fft_generate_sample(){
  microseconds = micros();
  for(int i=0; i<samples; i++){
      vReal[i] = analogRead(CHANNEL);
      vImag[i] = 0;
      while(micros() - microseconds < sampling_period_us){
        //empty loop
      }
      microseconds += sampling_period_us;
  }
}



double fft_get(double *vReal, double *vImag, uint16_t samples){

  // fft_generate_sample();

  FFT.Windowing(vReal, samples, FFT_WIN_TYP_HAMMING, FFT_FORWARD);	/* Weigh data */
  FFT.Compute(vReal, vImag, samples, FFT_FORWARD); /* Compute FFT */
  FFT.ComplexToMagnitude(vReal, vImag, samples); /* Compute magnitudes */
  double ans = FFT.MajorPeak(vReal, samples, samplingFrequency);
  // Serial.println(ans, 6); //Print out what frequency is the most dominant.

  return ans;
}
