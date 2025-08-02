// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // stdlib includes malloc() and free()

// user-defined header files
#include "mypcm.h"
#include <math.h>


// function prototypes
void run(asignal * inputsignal);


int main()
{
    asignal * inputsignal = (asignal *) malloc(sizeof(asignal));
    run(inputsignal);
    
    //call any other function here

    free(inputsignal);
	return 0;
}

void run(asignal * inputsignal) 
{
    float A,omega,sigma;
    int duration,interval,encoderbits;

    scanf("%f %f %f %d %d %d",&A,&omega,&sigma,&duration,&interval,&encoderbits);
    inputsignal->A = A;
    inputsignal->omega = omega;
    inputsignal->duration = duration;
    inputsignal->sigma = sigma;

    int samplecount = (duration/interval) + 1;
    int bitstreamcount = samplecount*encoderbits;

    float *samples = malloc(samplecount*sizeof(float));
    int *pcmpulses = malloc(samplecount*sizeof(int));
    int *dsignal = malloc(bitstreamcount*sizeof(int));

    int levels = pow(2,encoderbits);

    sampler(samples,interval,*inputsignal);
    quantizer(samples,pcmpulses,levels,A);
    encoder(pcmpulses,dsignal,encoderbits);

    int n = bitstreamcount;
    for (int i=0;i<n;i++){
        printf("%d",dsignal[i]);
    }

    free(samples);
    free(pcmpulses);
    free(dsignal);
}


