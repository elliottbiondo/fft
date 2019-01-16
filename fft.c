#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>
#include <string.h>


#define PI 3.14159265358979323846

void odd_even(complex double* samples, int num_samples)
{
    complex double* temp
        = (complex double*) malloc(num_samples/2*sizeof(complex double));
    
    // copy all odd elements into temp;
    for (size_t i = 0; i<num_samples/2; i++)
    {
        temp[i] = samples[i*2+1];
    }

    // copy all even elements into the lower have of <samples>
    for (size_t i = 0; i<num_samples/2; i++)
    {
        samples[i] = samples[i*2];
    }

    // copy odd elements to the upper half of <samples>
    memcpy(samples + num_samples/2, temp, num_samples/2*sizeof(complex double));

    free(temp);
}

void fft(complex double* samples, int num_samples)
{
    if (num_samples > 2)
    {
        odd_even(samples, num_samples);
        fft(samples, num_samples/2);
        fft(&samples[num_samples/2], num_samples/2);

        for(size_t i=0; i<num_samples/2; i++)
        {
            complex double even = samples[i];
            complex double odd = samples[i + num_samples/2];
            complex double w = cexp(-2*PI*i/num_samples*I);
            samples[i] = even + w*odd;
            samples[i + num_samples/2] = even - w*odd;
        }
    }    
}

void print_samples(complex double* samples, int num_samples)
{
    FILE *f = fopen("samples.txt", "w");
    for(size_t i = 0; i < num_samples; i++)
    {
        fprintf(f, "%f\n", creal(samples[i]));
    }
    fclose(f);
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("Supply the number of samples as a cmd line arg \n");
        exit(1);
    }

    int num_samples = atoi(argv[1]);

    complex double* samples
        = (complex double*) malloc(num_samples*sizeof(complex double));

    const int  n_freqs = 3;
    double freqs[3] = {8, 32, 64};

    for (size_t i = 0; i < num_samples; i++)
    {
        for (size_t j = 0; j < n_freqs; j++)
        {
            samples[i] += sin(2*PI*freqs[j]*i/num_samples);
        }
    }

    print_samples(samples, num_samples);
    fft(samples, num_samples);
    print_samples(samples, num_samples);

    free(samples);
}
