#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SIG_LENGTH 320
#define IMP_RSP_LENGTH 29
extern double InputSignal_f32_1kHz_15kHz[SIG_LENGTH];
void calc_running_sum(double *sig_src_arr, double * sig_dest_arr, int sig_len);

int main()
{
    FILE *input_sig_fptr, *out_sig_fptr;
    double Output_sig[SIG_LENGTH];
    calc_running_sum((double*) &InputSignal_f32_1kHz_15kHz, (double *) Output_sig, SIG_LENGTH);
    input_sig_fptr=fopen("input_signal.dat","w");
    for (int i =0; i<SIG_LENGTH;i++)
    {
        fprintf(input_sig_fptr,"\n%f",InputSignal_f32_1kHz_15kHz[i]);
    }
    fclose(input_sig_fptr);
   
    out_sig_fptr=fopen("output_signal.dat","w");
    for (int i =0; i<IMP_RSP_LENGTH+SIG_LENGTH;i++)
    {
        fprintf(out_sig_fptr,"\n%f",Output_sig[i]);
    }
    fclose(out_sig_fptr);
    return 0;
}

void calc_running_sum(double *sig_src_arr, double * sig_dest_arr, int sig_len)
{
    for (int i =0; i<sig_len;i++)
    {
        sig_dest_arr[i] = sig_dest_arr[i-1] + sig_src_arr[i];
    }
}