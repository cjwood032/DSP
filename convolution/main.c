#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SIG_LENGTH 320
#define IMP_RSP_LENGTH 29
extern double InputSignal_f32_1kHz_15kHz[SIG_LENGTH];
extern double  Impulse_response[IMP_RSP_LENGTH];
void convolution( double *sig_src_arr, double *sig_dest_arr, double *imp_resp_arr, int sig_src_length, int imp_resp_length );
int main()
{
    FILE *input_sig_fptr, *imp_rsp_fptr, *out_sig_fptr;
    double Output_sig[IMP_RSP_LENGTH+SIG_LENGTH];
    convolution((double*) &InputSignal_f32_1kHz_15kHz, (double*)&Output_sig, (double*)&Impulse_response, SIG_LENGTH , IMP_RSP_LENGTH );
    input_sig_fptr=fopen("input_signal.dat","w");
    for (int i =0; i<SIG_LENGTH;i++)
    {
        fprintf(input_sig_fptr,"\n%f",InputSignal_f32_1kHz_15kHz[i]);
    }
    fclose(input_sig_fptr);
    imp_rsp_fptr=fopen("impulse_response_.dat","w");
    for (int i =0; i<IMP_RSP_LENGTH;i++)
    {
        fprintf(imp_rsp_fptr,"\n%f",Impulse_response[i]);
    }
    fclose(imp_rsp_fptr);
    out_sig_fptr=fopen("output_signal.dat","w");
    for (int i =0; i<IMP_RSP_LENGTH+SIG_LENGTH;i++)
    {
        fprintf(out_sig_fptr,"\n%f",Output_sig[i]);
    }
    fclose(out_sig_fptr);
    return 0;
}
void convolution( double *sig_src_arr, double *sig_dest_arr, double *imp_resp_arr, int sig_src_length, int imp_resp_length )
{
    int i,j;
    for (i=0;i<sig_src_length+imp_resp_length;i++)
    {
        sig_dest_arr[i]=0;
    }
    for(i=0;i<sig_src_length; i++)
    {
        for(j=0;j<imp_resp_length;j++)
        {
            sig_dest_arr[i+j]=sig_dest_arr[i+j] + sig_src_arr[i]*imp_resp_arr[j];//convolution sum
        }
    }
}
