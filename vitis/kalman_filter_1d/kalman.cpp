#include <hls_math.h>
#include <ap_axi_sdata.h>
#include <hls_stream.h>
#include <ap_int.h>

// Define the interface for the AXI Lite bus
void kalman_filter(int z_k, int &P_k, int &x_hat, int Q, int R, int P_k_prev, int x_hat_prev)
{
#pragma HLS INTERFACE s_axilite port = z_k
#pragma HLS INTERFACE s_axilite port = P_k
#pragma HLS INTERFACE s_axilite port = x_hat
#pragma HLS INTERFACE s_axilite port = Q
#pragma HLS INTERFACE s_axilite port = R
#pragma HLS INTERFACE s_axilite port = P_k_prev
#pragma HLS INTERFACE s_axilite port = x_hat_prev
#pragma HLS INTERFACE ap_ctrl_none port = return
	//	#pragma HLS INTERFACE s_axilite port=run bundle=CTRL_BUS

	// Computation and Parameter largely based on the Paper by Welch and Bishop: https://www.cs.unc.edu/~welch/media/pdf/kalman_intro.pdf
	// x_k = A * x_k-1 + wk (we put u=0)
	// z_k = H * x_k + v_k

	/*
	 For Time Update we assume:
	 x_hat_tilde = x_hat_-1
	 P_k_tilde = P_k-1 + Q
	 K_k = P_k_tilde(P_k_tilde + R)^-1
	 x_hat = x_hat_tilde + K(z_k - x_hat_tilde
	 P_k = (1-K_k) * P_k_tilde
	 */

	/* Inputs need to be in int  */

	// paramaeter:

	float z_k_float = static_cast<float>(z_k) / 10000;
	float Q_float = static_cast<float>(Q) / 10000;
	float R_float = static_cast<float>(R) / 10000;
	float P_k_prev_float = static_cast<float>(P_k_prev) / 10000;
	float x_hat_prev_float = static_cast<float>(x_hat_prev) / 10000;

	// time Update

	P_k_prev_float = P_k_prev_float + Q_float;
	float K_k = 0.0f;

	// Measurement Update

	K_k = P_k_prev_float / (P_k_prev_float + R_float);

	float x_hat_float = x_hat_prev_float + K_k * (z_k_float - x_hat_prev_float);

	float P_k_float = (1 - K_k) * P_k_prev_float;

	x_hat = static_cast<int>(round(x_hat_float * 10000));
	P_k = static_cast<int>(round(P_k_float * 10000));
}
