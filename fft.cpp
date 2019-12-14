#include <complex>
#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

template<typename T>
void ftpswap( T& a, T& b) {
	T temp;
	temp = a;
	a = b;
	b = temp;
}

int Ptwo(int n) {
	int count = 1;
	if (n < 2) {
		return 0;
	}
	n /= 2;

	while (!(n % 2)) {
		count++;
		n /= 2;
	}
	if (n == 1) { 
		return count;
	}
	return 0;
}


template<typename T>
void Transpose(T* mat, int width, int height) {
	for (int m = 0; m < height - 1; ++m) {
		for (int n = m + 1; n < width; ++n) { 
			T buf = mat[m * width + n];
			mat[m * width + n] = mat[n * width + m];
			mat[n * width + m] = buf;
		}
	}
}


template<typename T>
void fft1( std::complex<T> d[], int sz, int isign) {
	int m, j;
	int nL, nLh, iSize, nChunks;
   
	double theta;
	complex<T> W, Wk, temp;

	m = Ptwo(sz);
	if (m == 0) {
		cout << "\n Error in fft1 : incorrect data size" << std::endl;
		exit(0);
	}

	j = 0;
	for (int i = 0; i < sz; i++) {
		if (j > i) {
			ftpswap(d[j], d[i]);     // swap if appropriate
		}

		m = sz >> 1;      // n = N/2, shifts one bit to the right
		while(m >= 1 && j >= m) {
			j -= m;
			m >>= 1;
		}
		j += m;
	}


	// -----------------------------------------------------
	// Now we have the Danielson-Lanczos part of the routine
	// -----------------------------------------------------

	for(nL = 2; nL <= sz; nL *= 2) {
		nLh = nL/2;
		nChunks = sz/nL;
		
		theta = 6.28318530717959/(isign*nL);
		complex<T> c(cos(theta), sin(theta));
		W = c;
		iSize = 0;

		for(int n = 0; n < nChunks; n++) {
			Wk = 1.0;
			for(int k = iSize; k < (nLh + iSize); k++) {
				temp = Wk * d[k + nLh];
				d[k + nLh] = d[k] - temp;
				d[k] += temp;
				Wk *= W;
			}
			iSize +=nL;
		}
	} 
}

template<typename T>
void fft2( std::complex<T> *d, int szx, int szy, int isign) {
	for(int m = 0; m < szy; ++m) {
		fft1(&d[m * szx], szx, isign);
	}
	Transpose(d, szx, szy);

	for(int m = 0; m < szx; ++m) {
		fft1(&d[m * szy], szy, isign);
	}
	Transpose(d, szy, szx);
}

template<typename T>
void fft2h( std::complex<T> *d, int szx, int szy, int isign) {
	for(int m = 0; m < szy; ++m) {
		fft1(&d[m * szx], szx, isign);
	}
	Transpose(d, szx, szy);
}


