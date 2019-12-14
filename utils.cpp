#include <iostream>
#include <fstream>
#include <complex>

using namespace std;

void printMat(float* arr, int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << arr[i * m + j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

template<typename T>
void printMatC(complex<T>* arr, int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << arr[i * m + j].real() << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

void writeMat(complex<float>* F, int m, int n, float t) {
	ofstream f;
	f.open("out/" + to_string(t) + ".txt");
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			f << F[i * m + j].real() << ' ';
		}
		f << endl;
	}
	f << endl;
	f.close();

}

