#include <stdio.h>
#include "kalman.h"


int main(){

	int P_k = 1;
	int x_hat =0;
	int Q = 1;
	int R = 1000;
	int z_k = 3900;
	int P_k_prev = 10000;
	int x_hat_prev = 0;

	kalman_filter(z_k, P_k,x_hat,Q,R,P_k_prev,x_hat_prev);

	printf("Estimated value is at: %d", x_hat);

	P_k_prev = P_k;
	x_hat_prev = x_hat;
	z_k = 5000;

	kalman_filter(z_k, P_k,x_hat,Q,R,P_k_prev,x_hat_prev);

	printf("Estimated value is at: %d", x_hat);

	return 0;
}
