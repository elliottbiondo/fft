#include "stdio.h"
#include "stdlib.h"
#include "complex.h"
#include "math.h"

#define pi 3.14159265358979323846

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("Supply the number of samples as a cmd line arg \n");
        exit(1);
    }

    int num_samples = atoi(argv[1]);

    printf("Hello World %i", num_samples);

    complex double* samples = malloc(num_samples*sizeof(complex double));

    const int  n_freqs = 3;
    double freqs[3] = {2, 10, 100};

    for (size_t i = 0; i < num_samples; i++)
    {
        for (size_t j = 0; j < n_freqs; j++)
            samples[i] += sin(2*pi*freqs[j]*i/num_samples);
    }

    FILE *f = fopen("samples.txt", "w");
    for(unsigned int i = 0; i < num_samples; i++)
    {
        fprintf(f, "%f\n", samples[i]);
    }
    fclose(f);

    free(samples);
}
