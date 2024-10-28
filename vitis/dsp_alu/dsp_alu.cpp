#include <ap_int.h>
#include <hls_stream.h>

// Define the bit-widths of input and output data
typedef ap_int<16> data_t;
typedef ap_int<32> result_t;

void dsp_alu(
    volatile data_t *A,   // AXI4 Full Interface for input A
    volatile data_t *B,   // AXI4 Full Interface for input B
    volatile result_t *Y, // AXI4 Full Interface for output Y
    ap_uint<2> Sel,       // AXI4-Lite Interface for operation selection
    int size              // Size of the input arrays
)
{
#pragma HLS INTERFACE m_axi port = A offset = slave bundle = gmem0
#pragma HLS INTERFACE m_axi port = B offset = slave bundle = gmem1
#pragma HLS INTERFACE m_axi port = Y offset = slave bundle = gmem2

#pragma HLS INTERFACE s_axilite port = Sel
#pragma HLS INTERFACE s_axilite port = size
#pragma HLS INTERFACE s_axilite port = return

    result_t mac_acc = 0;

    // Iterate through all input elements
    for (int i = 0; i < size; i++)
    {
#pragma HLS PIPELINE II = 1

        data_t a_val = A[i];
        data_t b_val = B[i];

        // Perform the operation based on the selection signal
        switch (Sel)
        {
        case 0: // Addition
            Y[i] = a_val + b_val;
            break;
        case 1: // Subtraction
            Y[i] = a_val - b_val;
            break;
        case 2: // Multiplication
            Y[i] = a_val * b_val;
            break;
        case 3: // Multiply-Accumulate (MAC)
            mac_acc += a_val * b_val;
            Y[i] = mac_acc;
            break;
        default:
            Y[i] = 0; // Default to zero if an unknown operation is selected
            break;
        }
    }
}
