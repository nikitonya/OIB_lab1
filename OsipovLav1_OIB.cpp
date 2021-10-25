#include <iostream>
#include "math.h"

using namespace std;

void test_1(int* arr, int N) {
	int result = 0; // для промежуточных вычислений
	double S = 0; // по формуле
	double P = 0; // P-значение – 
	// вероятность того, что генератор производит значения, сравнимые с эталоном. Если P-значение стремится к 1, то говорят, 
	// что генератор стремиться к идеальному. Если P-значение стремиться к 0 – генератор полностью предсказуем.

	// TEST 1
	cout << endl << "TEST 1" << endl << endl;

	for (size_t i = 0; i < N; ++i) { // считаем по формуле
		if (arr[i] == 1) {
			result++;
		}
		else
			result--;
	}
	cout << "result = " << result << endl;

	S = result / sqrt(N);

	P = erfc(S / sqrt(2));
	cout << "P = " << P << endl;

}

void test_2(int* arr, int N) {
	double tetta = 0;
	double V = 0;
	double a = 0;
	double b = 0;
	double P = 0;
	double count_of_1 = 0;  // количество единиц в последовательности

	// TEST 2
	cout << endl << "TEST 2" << endl << endl;
	// далее куча вычислений
	for (size_t i = 0; i < N; ++i) {
		if (arr[i] == 1) {
			count_of_1++;
		}
	}
	cout << "count of 1 = " << count_of_1 << endl;
	tetta = count_of_1 / N;
	cout << "tetta = " << tetta << endl;

	if (fabs(tetta - 0.5) >= (2.0 / sqrt(N))) {
		P = 0;
	}
	cout << "P = " << P << endl;

	for (size_t i = 0; i < 127; ++i) {
		if (arr[i] != arr[i + 1]) {
			V++;
		}
	}
	cout << "V = " << V << endl;
	a = fabs(V - 256.0 * tetta * (1.0 - tetta));
	b = (32 * tetta * (1.0 - tetta));
	P = erfc(a / b);
	cout << "P = " << P << endl;

}

void test_3(int* arr, int N) {
	cout << endl << "TEST 3" << endl << endl;

	int v1 = 0; // 𝑣1 = { кол-во блоков с макс. длиной ≤ 1 }
	int v2 = 0; // 𝑣2 = { кол-во блоков с макс. длиной = 2 }
	int v3 = 0; // 𝑣3 = { кол-во блоков с макс. длиной = 3 }
 	int v4 = 0; // 𝑣4 = { кол-во блоков с макс. длиной ≥ 4 }

	int maxlen = 0; // переменная для записи максимального значения в одном блоке
	int nowlen = 0; // текущий счётчик

	for (size_t i = 0; i < 128; ++i) {
		if (arr[i] == 1) {
			nowlen++;
		}
		if (arr[i] == 0) {
			if (nowlen > maxlen)
				maxlen = nowlen;
			nowlen = 0;
		}
		if ((i + 1) % 8 == 0) {
			if (nowlen > maxlen) {
				maxlen = nowlen;
			}
			if (maxlen <= 1) {
				v1++;
			}
			if (maxlen == 2) {
				v2++;
			}
			if (maxlen == 3) {
				v3++;
			}
			if (maxlen >= 4) {
				v4++;
			}
			nowlen = 0;
			maxlen = 0;
		}
	}

	cout << "v1 = " << v1 << endl;
	cout << "v2 = " << v2 << endl;
	cout << "v3 = " << v3 << endl;
	cout << "v4 = " << v4 << endl;

	double hi2 = ((pow(v1 - 16.0 * 0.2148, 2)) / 16.0 * 0.2148) + ((pow(v2 - 16.0 * 0.3672, 2)) / 16.0 * 0.3672) + ((pow(v3 - 16.0 * 0.2305, 2)) / 16.0 * 0.2305) + ((pow(v4 - 16.0 * 0.1875, 2)) / 16.0 * 0.1875);

	cout << "hi2: " << hi2 << endl;
	cout << "hi2/2: " << hi2 / 2 << endl; // для рассчета hi2
	cout << "P = 0.99633589" << endl; // рассчитано с помощью онлайн калькулятора 
}

int main()
{
	// Создание, заполнение и вывод массива:
	const int N = 128; // определение размера массива
	int* arr = new int[N];  // создание динамического массива
	for (size_t i = 0; i < N; ++i) { // заполнение массива бинарными значениями
		arr[i] = rand() % 2;
	}
	
	cout << "Sequence a c++: " << endl << endl;
	for (size_t i = 0; i < 16; i++) { // вывод массива блоками в консоль
		for (size_t j = 0; j < 8; j++) {
			cout << arr[8 * i + j]; 
		}
		cout << endl ;
	}
	cout << endl << "A test with a c++ sequence" << endl;
	test_1(arr, N);
	test_2(arr, N);
	test_3(arr, N);


	delete[] arr;
	return 0;
}
// 



