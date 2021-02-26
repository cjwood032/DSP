#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SIG_LENGTH 320
extern double InputSignal_f32_1kHz_15kHz[SIG_LENGTH];
void calc_sig_dft(double *sig_src_arr, double * sig_dest_arr,double * sig_dest_imx_arr, int sig_leng);
int main()
{
    FILE *input_sig_fptr, *out_rex_fptr, *out_imx_fptr;
    double output_rex[SIG_LENGTH/2];
    double output_imx[SIG_LENGTH/2];
    calc_sig_dft((double *)InputSignal_f32_1kHz_15kHz, (double *) output_rex,(double *) output_imx, SIG_LENGTH);
    input_sig_fptr=fopen("input_signal.dat","w");
    for (int i =0; i<SIG_LENGTH;i++)
    {
        fprintf(input_sig_fptr,"\n%f",InputSignal_f32_1kHz_15kHz[i]);
    }
    fclose(input_sig_fptr);
    out_rex_fptr=fopen("output_rex.dat","w");
    for (int i =0; i<(SIG_LENGTH/2);i++)
    {
        fprintf(out_rex_fptr,"\n%f",output_rex[i]);
    }
    fclose(out_rex_fptr);
    out_imx_fptr=fopen("output_imx.dat","w");
    for (int i =0; i<(SIG_LENGTH/2);i++)
    {
        fprintf(out_imx_fptr,"\n%f",output_imx[i]);
    }
    fclose(out_imx_fptr);
    return 0;
}

void calc_sig_dft(double *sig_src_arr, double * sig_dest_rex_arr,double * sig_dest_imx_arr, int sig_leng)
{
    int i,j,k;
    for(j=0;j<(sig_leng/2);j++)
    {
        sig_dest_rex_arr[j]=0;
        sig_dest_imx_arr[j]=0;
    }
    for (k=0;k<(sig_leng/2);k++)
    {
        for(i=0;i<sig_leng;i++)
        {
            sig_dest_rex_arr[k] = sig_dest_rex_arr[k] + sig_src_arr[i]*cos(2*M_PI*k*i/sig_leng);
            sig_dest_imx_arr[k] = sig_dest_imx_arr[k] - sig_src_arr[i]*sin(2*M_PI*k*i/sig_leng);
        }
    }
}