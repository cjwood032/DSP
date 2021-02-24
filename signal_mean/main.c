#include <stdio.h>
#include <stdlib.h>
#define SIG_LENGTH 320
extern double InputSignal_f32_1kHz_15kHz[SIG_LENGTH];
double calc_signal_mean(double *sig_src_arr, int sig_length);
double MEAN;
int main()
{
    MEAN = calc_signal_mean(&InputSignal_f32_1kHz_15kHz[0],SIG_LENGTH);
    printf("the mean is: %f\n",MEAN);
    return 0;
}

double calc_signal_mean(double *sig_src_arr, int sig_length)
{
    double _mean=0.0;
    for(int i =0; i<SIG_LENGTH; i++)
    {
        _mean += sig_src_arr[i];
    }
    _mean = _mean/(double)sig_length;
    return _mean;
}