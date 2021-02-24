#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SIG_LENGTH 320
extern double InputSignal_f32_1kHz_15kHz[SIG_LENGTH];
double calc_signal_mean(double *sig_src_arr, int sig_length);
double calc_signal_variance(double *sig_src_arr, double sig_mean, int sig_length);
double MEAN;
double VARIANCE;
int main()
{
    MEAN = calc_signal_mean(&InputSignal_f32_1kHz_15kHz[0],SIG_LENGTH);
    printf("the mean is: %f\n",MEAN);
    VARIANCE = calc_signal_variance(&InputSignal_f32_1kHz_15kHz[0],MEAN,SIG_LENGTH);
    printf("the variance is: %f\n",VARIANCE);
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
double calc_signal_variance(double *sig_src_arr, double sig_mean, int sig_length)
{
    double _variance = 0.0;
    for(int i =0; i<SIG_LENGTH; i++)
    {
        _variance += (double)pow((sig_src_arr[i]-sig_mean),2);
    }
    _variance=_variance/(sig_length-1);
    return _variance;
}