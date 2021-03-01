#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SIG_LENGTH 501
double _501pts_20Hz_sig_rex[SIG_LENGTH];
double _501pts_20Hz_sig_imx[SIG_LENGTH];
double sig_out_freq_rex_arr[SIG_LENGTH];
double sig_out_freq_imx_arr[SIG_LENGTH];
void complex_DFT(double *sig_src_rex_arr, double *sig_src_imx_arr, double *sig_out_freq_rex_arr, double *sig_out_freq_imx_arr, int sig_length);
int main()
{
    FILE *output_mag_fptr, *output_phase_fptr;
    double Output_sig[SIG_LENGTH];
    complex_DFT((double *) &_501pts_20Hz_sig_rex, (double *) &_501pts_20Hz_sig_imx, (double *)&sig_out_freq_rex_arr, (double *)&sig_out_freq_imx_arr,  SIG_LENGTH);
    output_mag_fptr=fopen("sig_out_freq_rex.dat","w");
    output_phase_fptr=fopen("sig_out_freq_imx.dat","w");
    for (int i =0; i<SIG_LENGTH;i++)
    {
        fprintf(output_mag_fptr,"\n%f",sig_out_freq_rex_arr[i]);
        fprintf(output_phase_fptr,"\n%f",sig_out_freq_imx_arr[i]);
    }
    fclose(output_phase_fptr);
    return 0;
}


void complex_DFT(double *sig_src_rex_arr, double *sig_src_imx_arr, double *sig_out_freq_rex_arr, double *sig_out_freq_imx_arr, int sig_length)
{
    double SReal, SImag;
    for(int k=0; k<sig_length-1/*<-not sure why -1*/;k++)
    {
        for (int i =0;i<sig_length; i++)
        {
            SReal= cos((2*M_PI*k*i)/sig_length);
            SImag = -sin((2*M_PI*k*i)/sig_length);

            sig_out_freq_rex_arr[k]= sig_out_freq_rex_arr[k]+sig_src_rex_arr[i]*SReal-sig_src_imx_arr[i]*SImag;
            sig_out_freq_imx_arr[k]= sig_out_freq_imx_arr[k]+sig_src_imx_arr[i]*SImag-sig_src_imx_arr[i]*SReal;
        }
    }
}