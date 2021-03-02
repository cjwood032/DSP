#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SIG_LENGTH 320
#define KERN_LENGTH 29
extern double InputSignal_f32_1kHz_15kHz[SIG_LENGTH];
double sig_output_arr[SIG_LENGTH-KERN_LENGTH];
double output_filter_arr[KERN_LENGTH];
double lower_cutoff_buff_arr[KERN_LENGTH];
double upper_cutoff_buff_arr[KERN_LENGTH];

void band_pass_windowed_sinc_ftr(double * lower_cutoff_state_buff, double * upper_cutoff_state_buff, double * fltr_kern_dest_arr, double lower_cutoff_freq,
double upper_cutoff_freq, int filter_length, double *sig_src_arry, double *sig_dest_arr, int input_sig_length);
int main()
{
    const double lower_cut =0.002;//normalized 10kHZ cutoff (10/24)*0.5
    const double upper_cut = .11;//normalized 
    band_pass_windowed_sinc_ftr((double *) lower_cutoff_buff_arr, (double *) upper_cutoff_buff_arr, (double *) output_filter_arr, lower_cut, upper_cut, KERN_LENGTH, (double *) InputSignal_f32_1kHz_15kHz, (double *) sig_output_arr,SIG_LENGTH);
    
    FILE *filter_fptr, *output_fptr, *input_fptr, *upper_fptr, *lower_fptr;
    filter_fptr=fopen("filter_signal.dat","w");
    output_fptr=fopen("output_signal.dat","w");
    
    input_fptr=fopen("input_signal.dat","w");
    upper_fptr=fopen("upper_buffer.dat","w");
    lower_fptr=fopen("lower_buffer.dat","w");
    for (int i =0;i<SIG_LENGTH;i++)
    {
        if (i>=KERN_LENGTH)
        {
            fprintf(output_fptr,"\n%f",sig_output_arr[i]);
            
        }
        else
        {
            fprintf(upper_fptr,"\n%f",upper_cutoff_buff_arr[i]);
            fprintf(filter_fptr,"\n%f",output_filter_arr[i]);
            fprintf(lower_fptr,"\n%f",lower_cutoff_buff_arr[i]);
        }
        fprintf(input_fptr,"\n%f",InputSignal_f32_1kHz_15kHz[i]);
    }
    fclose(filter_fptr);
    fclose(output_fptr);
    fclose(input_fptr);
    fclose(upper_fptr);
    fclose(lower_fptr);
    return 0;
}

void band_pass_windowed_sinc_ftr(
    double * lower_cutoff_state_buff, double * upper_cutoff_state_buff, double * fltr_kern_dest_arr,
     double lower_cutoff_freq, double upper_cutoff_freq,int filter_length, double *sig_src_arry, double *sig_dest_arr, int input_sig_length)
{
    for(int i =0; i<filter_length; i++)
    {
        if(i-filter_length/2==0)
        {
            lower_cutoff_state_buff[i]=2*M_PI*lower_cutoff_freq;
        }
        if(i-filter_length/2!=0)
        {
            lower_cutoff_state_buff[i]=sin(2*M_PI*lower_cutoff_freq*(i-filter_length/2)/(i-filter_length/2));
            lower_cutoff_state_buff[i] = lower_cutoff_state_buff[i] * (0.42-.5*cos(2*M_PI*i/filter_length)+0.08*cos(4*M_PI*i/filter_length));
        }
    }
   for(int i =0; i<filter_length; i++)
   {
       if(i-filter_length/2==0)
       {
           upper_cutoff_state_buff[i]=2*M_PI*upper_cutoff_freq;
       }
       if(i-filter_length/2!=0)
       {
           upper_cutoff_state_buff[i]=sin(2*M_PI*upper_cutoff_freq*(i-filter_length/2)/(i-filter_length/2));
           upper_cutoff_state_buff[i]=upper_cutoff_state_buff[i] * (0.42-.5*cos(2*M_PI*i/filter_length)+0.08*cos(4*M_PI*i/filter_length));
       }
   }
   //spectral inversion to change it from low pass to high pass
   for(int i=0; i<filter_length; i++)
   {
       upper_cutoff_state_buff[i]=-upper_cutoff_state_buff[i];
   }
   upper_cutoff_state_buff[filter_length/2]=upper_cutoff_state_buff[filter_length/2]+1;
   //add the low and high pass kernals to form a band-reject filter kernal
   for(int i =0; i<filter_length; i++)
   {
       fltr_kern_dest_arr[i]=lower_cutoff_state_buff[i]+upper_cutoff_state_buff[i];
   }
   for (int i =0; i<filter_length; i++)
   {
       fltr_kern_dest_arr[i]=-fltr_kern_dest_arr[i];//another spectral inversion
   }
   fltr_kern_dest_arr[filter_length/2]=fltr_kern_dest_arr[filter_length/2]+1;//the band pass filter
    for(int j=filter_length; j<input_sig_length;j++)
    {
        sig_dest_arr[j]=0;
        for(int i =0; i<filter_length; i++)
        {
            sig_dest_arr[j] = sig_dest_arr[j]+sig_src_arry[j-i]*fltr_kern_dest_arr[i];
        }
    }

}
