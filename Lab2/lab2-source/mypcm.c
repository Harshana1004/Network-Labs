// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // includes malloc(),free()
//Add any necessary headers here
#include <math.h>

// user-defined header files
#include "mypcm.h" // do not modify this file

// put your function prototypes for additional helper functions below:


// implementation
float analog_signal_generator(asignal signal, int t)
{
	//TODO
	if (t<0 || t > signal.duration) return 0.0;


	float x = signal.A*sin(signal.omega*t + signal.sigma);
	return x;
}
void sampler(float *samples, int interval, asignal signal)
{
	//TODO
	int idx = 0;
	for (int t=0;t<=signal.duration;t += interval){
		samples[idx] = analog_signal_generator(signal,t);
		idx++;
	}
	samples[idx] = -99999.0f;
}
void quantizer1(float *samples, int *pcmpulses, int levels)
{
	//TODO


}
void quantizer(float *samples, int *pcmpulses, int levels, float A)
{
	//TODO
	
	float Amax = A;
	float Amin = -A;

	int i = 0;
	
	while (samples[i] != -99999.0f){
	    float q = ((samples[i]-Amin)/(Amax-Amin));

		int level = (int) floorf(q*levels);
		if (level >= levels){
			level = levels - 1;
		}

		pcmpulses[i] = level;
		i++;
	}
	pcmpulses[i] = -1;
}


void encoder(int *pcmpulses, int *dsignal, int encoderbits)
{
	//TODO
    int j = 0;
	int n = encoderbits;
	int idx = 0;
	while (pcmpulses[j] != -1){
		int val = pcmpulses[j];
		for (int i=n-1;i>=0;i--){
			dsignal[idx+i] = val%2;
			val /= 2;	
		}
		j++;
		idx +=encoderbits;
	}
}