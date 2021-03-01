#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SIG_LENGTH 320
extern double _320_pts_ecg_REX[SIG_LENGTH];
extern double _320_pts_ecg_IMX[SIG_LENGTH];
double output_mag[SIG_LENGTH];
double output_phase[SIG_LENGTH];
void rect2polar(double *sig_src_rex_arr, double *sig_src_imx_arr, double *sig_out_mag_arr, double *sig_out_phase_arr, int sig_length);
int main()
{
    rect2polar((double*) &_320_pts_ecg_REX, (double *) &_320_pts_ecg_IMX, (double *) &output_mag, (double *)&output_phase, SIG_LENGTH);
    FILE *output_mag_fptr, *output_phase_fptr;
    double Output_sig[SIG_LENGTH];
    
    output_mag_fptr=fopen("output_magnitude.dat","w");
    output_phase_fptr=fopen("output_signal.dat","w");
    for (int i =0; i<SIG_LENGTH;i++)
    {
        fprintf(output_mag_fptr,"\n%f",output_mag[i]);
        fprintf(output_phase_fptr,"\n%f",output_phase[i]);
    }
    fclose(output_phase_fptr);
    return 0;
}


void rect2polar(double *sig_src_rex_arr, double *sig_src_imx_arr, double *sig_out_mag_arr, double *sig_out_phase_arr, int sig_length)
{
    int k;
    for (k=0;k<sig_length;k++)
    {
        //magnitude mag[k]= square root of ReX[k]^2 + ImX[k]^2
        sig_out_mag_arr[k] =sqrt(powf(sig_src_rex_arr[k],2) +powf(sig_src_imx_arr[k],2));
        if(sig_src_rex_arr[k]==0)
        {
            sig_src_rex_arr[k] = pow(10,-20); //this is a known value
            //PhaseX[k[ arctan(ImX[k]/ReX[k])
            sig_out_phase_arr[k] = atan(sig_src_imx_arr[k]/sig_src_rex_arr[k]);
        }
        if(sig_src_rex_arr[k]<0 && sig_src_imx_arr[k]<0)
        {
            sig_out_phase_arr[k] = sig_out_phase_arr[k]-M_PI;
        }
        if(sig_src_rex_arr[k]<0&&sig_src_imx_arr[k]>=0)
        {
            sig_out_phase_arr[k]=sig_out_phase_arr[k]+M_PI;
        }
    }
}