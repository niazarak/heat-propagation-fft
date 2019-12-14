#include <complex>
#include <math.h>

#include "fft.cpp"
#include "utils.cpp"

using namespace std;

const double PI = 3.1415926535;
const int N = 8;
const int M = 8;


void Damp(complex<float>* FF, int MM, int NN, float t) {
	for(int k1=0; k1<MM; ++k1) {
		for(int k2=0; k2<NN; ++k2) {
			float C = pow(sin(PI * k1 / MM), 2) + pow(sin(PI * k2 / N), 2);
			FF[k1 * NN + k2] *= exp(-4 * C * t);     // damp Fourier components
		}
	}
}

int main(int argn, char** argv) {
	// init
	float D[M * N] = {};
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			int x = j - M / 2;
			int y = i - M / 2;

			D[i * M + j] = exp(-x*x-y*y);
		}
	}
	printMat(D, N, M);

	float delta = 0.0;

	complex<float> F1[N * M]{};
	
	for (int t = 0; t < 50; t+= 1) {
		for (int i = 0; i < N * M; i++) {
			F1[i] = {D[i], 0.0};
		}
		// forward FFT
		fft2<float>(F1, N, M, 1);

		// damping coefficitnes
		Damp(F1, N, M, t);

		// inverse transform
		fft2(F1, N, M, -1);
		for(int k=0; k< N * M; ++k) {
			F1[k] /= (N*M);
		}

		printMatC(F1, N, M);
		writeMat(F1, N, M, t);
	}
	// fin
	return 0;
}
