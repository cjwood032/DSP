#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SIG_LENGTH 320
#define KERN_LENGTH 29
extern double InputSignal_f32_1kHz_15kHz[SIG_LENGTH];
double sig_output_arr[SIG_LENGTH-KERN_LENGTH];
double output_filter_arr[KERN_LENGTH];

void low_pass_windowed_sinc_ftr(double * sig_src_arr, double * sig_dest_arr, double * fltr_kern_dest_arr, double cutoff_freq, int filter_len, int input_sig_length);
int main()
{
    const double cutoff_freq = 0.2; 
    low_pass_windowed_sinc_ftr((double *) InputSignal_f32_1kHz_15kHz, (double *) sig_output_arr, (double *) output_filter_arr, cutoff_freq, KERN_LENGTH, SIG_LENGTH);
    FILE *filter_fptr, *output_fptr, *input_fptr;
    filter_fptr=fopen("filter_signal.dat","w");
    output_fptr=fopen("output_signal.dat","w");
    input_fptr=fopen("input_signal.dat","w");
    for (int i =0;i<SIG_LENGTH;i++)
    {
        if (i>=KERN_LENGTH)
        {
            fprintf(output_fptr,"\n%f",sig_output_arr[i]);
        }
        else
        {
            fprintf(filter_fptr,"\n%f",output_filter_arr[i]);
        }
        fprintf(input_fptr,"\n%f",InputSignal_f32_1kHz_15kHz[i]);
    }
    fclose(filter_fptr);
    fclose(output_fptr);
    fclose(input_fptr);
    return 0;
}

void low_pass_windowed_sinc_ftr(double * sig_src_arr, double * sig_dest_arr, double * fltr_kern_dest_arr, double cutoff_freq, int filter_len, int input_sig_length)
{
    //calc low pass filter kernal
    for(int i =0; i<filter_len;i++)
    {
        if(i-filter_len/2==0)
        {
            fltr_kern_dest_arr[i]= 2*M_PI * cutoff_freq;
        }
        if(i-filter_len/2!=0)
        {
            fltr_kern_dest_arr[i]= sin(2*M_PI * cutoff_freq*(i-filter_len/2))/(i-filter_len/2);
            fltr_kern_dest_arr[i]=fltr_kern_dest_arr[i] * (0.54-0.46*cos(2*M_PI*i/filter_len));
        }
    }
    for(int j=filter_len; j<input_sig_length; j++)
    {
        sig_dest_arr[j]=0;
        for (int i = 0;i<filter_len;i++)
        {
            sig_dest_arr[j] = sig_dest_arr[j] + sig_src_arr[j-i] * fltr_kern_dest_arr[i];
        }
    }
}
