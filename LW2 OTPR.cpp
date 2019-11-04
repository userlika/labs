// LW2 OTPR.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <ctime>
#include <locale.h>
#include <cstdlib>
using namespace std;
//================================ Prototypes ==================================
void fillUpRandom(int** matrix, int task, int proc, int t1, int t2);
int* sumofRows(int** matrix, int task, int proc);
int maxSum(int* matrix, int task);
int maxSumInd(int* matrix, int task);
int minSumInd(int* matrix, int task);
int minSum(int* matrix, int task);
int** sortbySumRowsDown(int** matrix, int task, int proc);
int** sortbySumRowsUp(int** matrix, int task, int proc);
int Zmax(int* matrix, int proc);
int ZmaxInd(int* matrix, int proc);
void printMatrix(int** matrix, int task, int proc);
void printMatrix(int* matrix2, int proc);
void bestPlaces(int* matrix1, int* matrix2, int* matrix3, int task);
int* CPUs(int **matrix, int task, int proc);
void TmaxPlace(int tmr, int tmu, int tmd, int tmrp, int tmup, int tmdp);
int* bestPlaces2(int tmr, int tmu, int tmd, int tmrsum, int tmusum, int tmdsum); 
int main()
{
	// ========================== Variables ====================================
	int task, t1, t2;
	int z; //���������� ��������
	int zrandmax = 0, zupmax = 0, zdownmax = 0;
	double zrandav = 0, zupav = 0, zdownav = 0;
	int zrandind = 0, zupind = 0, zdownind = 0;
	int tmaxrand = 0, tmaxup = 0, tmaxdown = 0;
	//int tmr = 0, tmu = 0, tmd = 0;
	int tmrp = 0, tmup = 0, tmdp = 0;
	int tmrsum = 0, tmusum = 0, tmdsum = 0;
	double zrandindav = 0, zupindav = 0, zdownindav = 0;
	int *tmsum;
	int *tmsumcopy;
	int proc = 0;
	//int **matrix; //�������� ������
	int **matrix;
	int *cpumatrix{};
	int *sumrowsind; //������ �������� �����
	int **matrixdown; // ������, ��������������� �� ��������
	int **matrixup; // ������, ��������������� �� �����������
	int *matrixupproc; // ������ � ������������ ��� �������, ���������������� �� �����������
	int *matrixdownproc; // ������ � ������������ ��� �������, ���������������� �� ��������

    // ==========================Program code===================================
	setlocale(LC_ALL, "rus");
	srand(time(0));
	cout << "-----------------------------------------------------------" << endl;
	cout << "|        ��������� ��������� ��������� �������������       |" << endl;
	cout << "|        ��� ������� ������������ ����������� ������       |" << endl;
	cout << "|            ���������� ������������ ��������              |" << endl;
	cout << "------------------------------------------------------------" << endl;
	cout << "������� ���������� ��������: " << endl;
	cin >> z;
	cout << "������� ���������� �������: " << endl;
	cin >> task;
	cout << "������� ���������� �����������: " << endl;
	cin >> proc;
	cout << "������� t1: " << endl;
	cin >> t1;
	cout << "������� t2: " << endl;
	cin >> t2;

	cout << endl;

	tmsumcopy = new int[3];
	for (int i = 0; i < 3; i++)
		tmsumcopy[i] = 0;
	for (int i = 0; i < z; i++) {
		cout << "======================================================================" << endl;
		cout << "Z = " << i + 1 << ": " << endl;
		// ������������ �������� ���������� �������
		matrix = new int*[task]; // ����� � �������
		for (int i = 0; i < task; i++)
			matrix[i] = new int[proc]; // ��������
		matrixup = new int*[task]; 
		for (int i = 0; i < task; i++)
			matrix[i] = new int[proc];
		matrixdown = new int*[task]; 
		for (int i = 0; i < task; i++)
			matrix[i] = new int[proc];
		tmsum = new int[3];
		for (int i = 0; i < 3; i++)
			tmsum[i] = 0;
		//������������ �������� ����������� ������� � ��������� �����
		sumrowsind = new int[task];
		for (int i = 0; i < task; i++) {
			sumrowsind[i] = 0;
		}
		// ������������� �������� � ����������
		cpumatrix = new int[proc];
		for (int i = 0; i < proc; i++) {
			cpumatrix[i] = 0;
		}
		matrixupproc = new int[proc];
		for (int i = 0; i < proc; i++) {
			matrixupproc[i] = 0;
		}
		matrixdownproc = new int[proc];
		for (int i = 0; i < proc; i++) {
			matrixdownproc[i] = 0;
		}
		//�������� �������
		cout << "������ � ��������� �������: " << endl;
		fillUpRandom(matrix, task, proc, t1, t2);
		printMatrix(matrix, task, proc);
		cout << "����� ����� ������������������ �������:" << endl;
		printMatrix(sumofRows(matrix, task, proc), task);
		cout << endl;
		cout << "������������� �������� �� ���������� (��������� �������): ";
		cpumatrix = CPUs(matrix, task, proc);
		printMatrix(cpumatrix, proc);
		zrandmax = zrandmax + Zmax(cpumatrix, proc);
		zrandind = zrandind + ZmaxInd(cpumatrix, proc);
		tmaxrand = Zmax(cpumatrix, proc);
		cout << "Tmax = " << tmaxrand << ";" << endl;
		cout << "zrandind =" << zrandind;
		cout << endl;

		cout << "......................................................" << endl;
		cout << "��������������� ������ �� �����������: " << endl;
		matrixup = sortbySumRowsUp(matrix, task, proc);
		printMatrix(matrixup, task, proc);
		cout << "����� ����� ���������������� �������:" << endl;
		printMatrix(sumofRows(matrixup, task, proc), task);
		cout << endl;
		cout << "������������� �������� �� ����������(������ �� �����������): ";
		matrixupproc = CPUs(matrixup, task, proc);
		printMatrix(matrixupproc, proc);
		zupmax = zupmax + Zmax(matrixupproc, proc);
		zupind = zupind + ZmaxInd(matrixupproc, proc);
		tmaxup = Zmax(matrixupproc, proc);
		cout << "Tmax = " << tmaxup << ";" << endl;
		cout << "zupind=" << zupind;
		cout << endl;

		cout << "......................................................" << endl;
		cout << "��������������� ������ �� ��������: " << endl;
		matrixdown = sortbySumRowsDown(matrix, task, proc);
		printMatrix(matrixdown, task, proc);
		cout << "����� ����� ���������������� �������:" << endl;
		printMatrix(sumofRows(matrixdown, task, proc), task);
		cout << endl;
		cout << "������������� �������� �� ����������(������ �� ��������): ";
		matrixdownproc = CPUs(matrixdown, task, proc);
		printMatrix(matrixdownproc, proc);
		zdownmax = zdownmax + Zmax(matrixdownproc, proc);
		zdownind = zdownind + ZmaxInd(matrixdownproc, proc);
		tmaxdown = Zmax(matrixdownproc, proc);
		cout << "Tmax = " << tmaxdown << ";" << endl;
		//cout <<"zdownind=" << zdownind;
		cout << endl;
		//bestPlaces(cpumatrix, matrixupproc, matrixdownproc, task);
		//TmaxPlace(tmaxrand, tmaxup, tmaxdown, tmrp, tmup, tmdp);
		tmsum = bestPlaces2(tmaxrand, tmaxup, tmaxdown,tmrsum,tmusum,tmdsum);
		for (int i = 0; i < 3; i++) {
			tmsumcopy[i] = tmsumcopy[i] + tmsum[i];
		}
		delete[] matrix;

	}
	cout << "----------------------***---***---***------------------------------" << endl;
	cout << "��������� �����������: " << endl;
	cout << "Zrandmax: " << zrandmax << endl;
	cout << "Zupmax: " << zupmax << endl;
	cout << "Zdownmax: " << zdownmax << endl;
	cout << endl;
	zrandav = double(zrandmax) / double(z);
	zupav = double(zupmax) / double(z);
	zdownav = double(zdownmax) / double(z);
	cout << "������� Zrandmax: " << zrandav << endl;
	cout << "������� Zupmax: " << zupav << endl;
	cout << "������� Zdownmax: " << zdownav << endl;
	cout << endl;
	/*zrandindav = double(zrandind) / double(z);
	cout << "Zrandmax average index: " << zrandindav << endl;
	zupindav = double(zupind) / double(z);
	cout << "Zupmax average index: " << zupindav << endl;
	zdownindav = double(zdownind) / double(z);
	cout << "Zdownmax average index: " << zdownindav << endl;*/
	
	cout << "������� �� ����� Zrandmax: " << double(tmsumcopy[0]) / double(z) << endl;
	cout << "������� �� ����� Zupmax: " << double(tmsumcopy[1]) / double(z) << endl;
	cout << "������� �� ����� Zdownmax: " << double(tmsumcopy[2]) / double(z) << endl;

	system("pause");
	return 0;
}

//============================= Functions =====================================

//*** ���������� ���������� ������� ����������� ������� ***
void fillUpRandom(int** matrix, int task, int proc, int t1, int t2) {
	int temp;
	for (int i = 0; i < task; i++) {
		for (int j = 0; j < proc; j++) {
			temp = rand() % (t2 - t1 + 1) + t1;
			matrix[i][j] = temp;
		}
	}
}
//*** ����� ����� ���������� ������� ***
int* sumofRows(int** matrix, int task, int proc) {
	int *sumrowsind = new int[task];
	for (int i = 0; i < task; i++) {
		sumrowsind[i] = 0;
	}

	int sum = 0;
	for (int i = 0; i < task; i++) {
		for (int j = 0; j < proc; j++) {
			sum = sum + matrix[i][j];
		}
		sumrowsind[i] = sum;
		sum = 0;
	}

	return sumrowsind;
}
//*** ������������ ������� ������� ***
int Zmax(int* matrix, int proc) {
	int max = 0;
	for (int i = 0; i < proc; ++i) {
		if (matrix[i] > max) {
			max = matrix[i];
		}
	}
	return max;
}
int ZmaxInd(int* matrix, int proc) {
	int max = 0;
	int indmax = 0;
	for (int i = 0; i < proc; ++i) {
		if (matrix[i] > max) {
			max = matrix[i];
			indmax = i;
		}
	}
	return indmax + 1;
}
//*** ������������ ������� ��� ���������� ***
int maxSum(int* matrix, int task) {
	int max = 0;
	for (int i = 0; i < task; ++i) {
		if (matrix[i] > max) {
			max = matrix[i];
		}
	}
	return max;
}
int maxSumInd(int* matrix, int task) {
	int max = 0;
	int ind = 0;
	for (int i = 0; i < task; ++i) {
		if (matrix[i] > max) {
			max = matrix[i];
			ind = i;
		}
	}
	return ind;
}

// ������ �����
void bestPlaces(int* matrix1, int* matrix2, int* matrix3, int task) {
	int Zavpl = 0, Zuppl = 0, Zdownpl = 0;
	int bestplace = 0;
	int min = 0;
	int bestPlaceMatrix[3];
	
	Zavpl = Zmax(matrix1, task);
	Zuppl = Zmax(matrix2, task);
	Zdownpl = Zmax(matrix3, task);
	cout << Zavpl << ";"<< Zuppl << ";"<<Zdownpl << ";" << endl;
	bestPlaceMatrix[0] = Zavpl;
	bestPlaceMatrix[1] = Zuppl;
	bestPlaceMatrix[2] = Zdownpl;
	min = bestPlaceMatrix[0];
	for (int i = 0; i < 3; i++) {		
		if (bestPlaceMatrix[i] < min) {
			min = bestPlaceMatrix[i];
			bestplace = i + 1;
		}		
	}
	cout << "������ �������� Tmax:" << endl;
	for (int i = 0; i < 3; i++) {
		cout << bestPlaceMatrix << endl;
	}
	if (bestplace == 1) cout << "������ ����� � ���������� �������. ��� �������� = " << min << endl;
	else if (bestplace == 2) cout << "������ ����� � ���������� �������. ��� �������� = " << min << endl;
	else  cout << "������ ����� � ���������� �������. ��� �������� = " << min << endl;


}
int* bestPlaces2(int tmr, int tmu, int tmd, int tmrsum, int tmusum, int tmdsum) {
	int Zavpl = 0, Zuppl = 0, Zdownpl = 0;
	int bestplace = 0, bestplace2 = 0;
	int min = 0, max = 0;
	int bestPlaceMatrix[3];
	int usedInd1 = 100, usedInd2 = 100, usedInd3 = 100;
	int maxkol = 0, minkol = 0;
	int* tmaxsum = new int[3];
	Zavpl = tmr;
	Zuppl = tmu;
	Zdownpl = tmd;
	cout << Zavpl << ";" << Zuppl << ";" << Zdownpl << ";" << endl;
	bestPlaceMatrix[0] = Zavpl;
	bestPlaceMatrix[1] = Zuppl;
	bestPlaceMatrix[2] = Zdownpl;
	min = bestPlaceMatrix[0];
	max = bestPlaceMatrix[0];
	for (int i = 0; i < 3; i++) {
		if (bestPlaceMatrix[i] < min) {
			min = bestPlaceMatrix[i];
			bestplace = i;
		}
		if (bestPlaceMatrix[i] > max) {
			max = bestPlaceMatrix[i];
			bestplace2 = i;			
		}
	}
	for (int i = 0; i < 3; i++) {
		if (bestPlaceMatrix[i] == max)
			maxkol++;
	 }
	for (int i = 0; i < 3; i++) {
		if (bestPlaceMatrix[i] == min)
			minkol++;
	}

	if ((maxkol != 2)&& (minkol!=2)) {
		for (int i = 0; i < 3; i++) {
			if (bestPlaceMatrix[i] == min) {
				cout << "������ ����� � " << i + 1 << " �������. ��� �������� = " << bestPlaceMatrix[i] << endl;
				if (i == 0) {
					tmrsum = tmrsum + 1; 
					usedInd1 = i;
				}
				else if (i == 1) {
					tmusum += 1;
					usedInd2 = i;
				}
				else if (i == 2) {
					tmdsum += 1;
					usedInd3 = i;
				}
			}
		}
		for (int i = 0; i < 3; i++) {
			if ((usedInd1 == i) || (usedInd2 == i) || (usedInd3 == i)) continue;
			if ((bestPlaceMatrix[i] > min) && (bestPlaceMatrix[i] < max)) {
				cout << "������ ����� � " << i + 1 << " �������. ��� �������� = " << bestPlaceMatrix[i] << endl;
				if (i == 0) {
					tmrsum += 2;
					usedInd1 = i;
				}
				else if (i == 1) {
					tmusum += 2;
					usedInd2 = i;
				}
				else if (i == 2) {
					tmdsum += 2;
					usedInd3 = i;
				}
			}
		}

		for (int i = 0; i < 3; i++) {
			if ((usedInd1 == i) || (usedInd2 == i) || (usedInd3 == i)) continue;
			if (bestPlaceMatrix[i] = max) {
				cout << "������ ����� � " << i + 1 << " �������. ��� �������� = " << bestPlaceMatrix[i] << endl;
				if (i == 0) {
					tmrsum += 3;
					usedInd1 = i;
				}
				else if (i == 1) {
					tmusum += 3;
					usedInd2 = i;
				}
				else if (i == 2) {
					tmdsum += 3;
					usedInd3 = i;
				}
			}
		}
	}
	
	else if ((maxkol == 2)||(minkol ==2 )) {
		for (int i = 0; i < 3; i++) {
			if (bestPlaceMatrix[i] == min) {
				cout << "������ ����� � " << i + 1 << " �������. ��� �������� = " << bestPlaceMatrix[i] << endl;
				if (i == 0) {
					tmrsum += 1;
					usedInd1 = i;
				}
				else if (i == 1) {
					tmusum += 1;
					usedInd2 = i;
				}
				else if (i == 2) {
					tmdsum += 1;
					usedInd3 = i;
				}
			}
		}

		for (int i = 0; i < 3; i++) {
			if ((usedInd1 == i) || (usedInd2 == i) || (usedInd3 == i)) continue;
			cout << "������ ����� � " << i + 1 << " �������. ��� �������� = " << bestPlaceMatrix[i] << endl;
			if (i == 0) {
				tmrsum += 2;
				usedInd1 = i;
			}
			else if (i == 1) {
				tmusum += 2;
				usedInd2 = i;
			}
			else if (i == 2) {
				tmdsum += 2;
				usedInd3 = i;
			}
		}		
	}
	tmaxsum[0] = tmrsum;
	tmaxsum[1] = tmusum;
	tmaxsum[2] = tmdsum;
	return tmaxsum;
}



void TmaxPlace(int tmr, int tmu, int tmd, int tmrp, int tmup, int tmdp) {
	int min = tmr;
	if (tmu < min) {
		min = tmu; tmup = 1;
		cout << "������ ����� Tmax �� �����������: " << tmu << endl;
	}
	else if (tmd < min) {
		min = tmd; tmdp = 1;
		cout << "������ ����� Tmax �� ��������: " << tmd << endl;
	}
	else {
		tmrp = 1;
		cout << "������ ����� Tmax � ��������� �������: " << tmr << endl;
	}

	if (min == tmr) {
		if (tmu < tmd) {
			tmup = 2; tmdp = 3;
			cout << "������ ����� Tmax �� �����������: " << tmu << endl;
			cout << "������ ����� Tmax �� ��������: " << tmd << endl;
		}
		else if (tmu == tmd) {
			tmup = 2; tmdp = 2;
			cout << "������ ����� Tmax �� �����������: " << tmu << endl;
			cout << "������ ����� Tmax �� ��������: " << tmd << endl;
		}
		else {
			tmup = 3; tmdp = 2;
			cout << "������ ����� Tmax �� ��������: " << tmd << endl;
			cout << "������ ����� Tmax �� �����������: " << tmu << endl;
		}
	}
	if (min == tmu) {
		if (tmr < tmd) {
			tmrp = 2; tmdp = 3;
			cout << "������ ����� Tmax � ��������� �������: " << tmr << endl;
			cout << "������ ����� Tmax �� ��������: " << tmd << endl;
		}
		else if (tmr == tmd) {
			tmrp = 2; tmdp = 2;
			cout << "������ ����� Tmax � ��������� �������: " << tmr << endl;
			cout << "������ ����� Tmax �� �����������: " << tmd << endl;
		}
		else {
			tmrp = 3; tmdp = 2;
			cout << "������ ����� Tmax �� ��������: " << tmd << endl;
			cout << "������ ����� Tmax � ��������� �������: " << tmr << endl;
		}
	}
	if (min == tmd) {
		if (tmu < tmr) {
			tmup = 2; tmrp = 3;
			cout << "������ ����� Tmax �� �����������: " << tmu << endl;
			cout << "������ ����� Tmax � ��������� ������� : " << tmr << endl;
		}
		else if (tmu == tmr) {
			tmup = 2; tmrp = 2;
			cout << "������ ����� Tmax �� ��������: " << tmr << endl;
			cout << "������ ����� Tmax �� �����������: " << tmu << endl;
		}
		else {
			tmup = 3; tmrp = 2;
			cout << "������ ����� Tmax � ��������� �������: " << tmr << endl;
			cout << "������ ����� Tmax �� �����������: " << tmu << endl;
		}
	}
}
//*** ����������� ������� ��� ���������� ***
int minSum(int* matrix, int task) {
	int min = matrix[0];
	for (int i = 0; i < task; ++i) {
		if (matrix[i] < min) {
			min = matrix[i];
		}
	}
	return min;
}
int minSumInd(int* matrix, int task) {
	int min = matrix[0];
	int ind = 0;
	for (int i = 0; i < task; ++i) {
		if (matrix[i] < min) {
			min = matrix[i];
			ind = i;
		}
	}
	return ind;
}
// *** ������� ���������� �� �������� � ����������� ***
int** sortbySumRowsDown(int** matrix, int task, int proc) {
	int sum = 0, maxEl = 0, maxInd = 0;
	int* sumrow = new int [task];
	for (int i = 0; i < task; i++) {
		sumrow[i] = 0;
	}

	int** sortedmatrixdown = new int*[task];
	for (int i = 0; i < task; i++) {
		sortedmatrixdown[i] = new int[proc];
	}

	for (int i = 0; i < task; i++) {
		for (int j = 0; j < proc; j++) {
			sum = sum + matrix[i][j];
		}
		sumrow[i] = sum;
		sum = 0;
	}
	for (int i = 0; i < task; i++) {
		maxEl = maxSum(sumrow, task);
		maxInd = maxSumInd(sumrow, task);
		for (int j = 0; j < proc; j++) {
			sortedmatrixdown[i][j] = matrix[maxInd][j];
		}
		sumrow[maxInd] = 0;
	}
	return sortedmatrixdown;
}
int** sortbySumRowsUp(int** matrix, int task, int proc) {
	int sum = 0, minEl = 0, minInd = 0;
	int* sumrow = new int[task];
	for (int i = 0; i < task; i++) {
		sumrow[i] = 0;
	}

	int** sortedmatrixup = new int*[task];
	for (int i = 0; i < task; i++) {
		sortedmatrixup[i] = new int[proc];
	}

	for (int i = 0; i < task; i++) {
		for (int j = 0; j < proc; j++) {
			sum = sum + matrix[i][j];
		}
		sumrow[i] = sum;
		sum = 0;
	}
	for (int i = 0; i < task; i++) {
		minEl = minSum(sumrow, task);
		minInd = minSumInd(sumrow, task);
		for (int j = 0; j < proc; j++) {
			sortedmatrixup[i][j] = matrix[minInd][j];
		}
		sumrow[minInd] = 1000;
	}
	return sortedmatrixup;
}

//*** ������ ������� �� �����***
void printMatrix(int** matrix, int task, int proc) {
	for (int i = 0; i < task; i++) {
		for (int j = 0; j < proc; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

void printMatrix(int* matrix2, int proc) {
	for (int i = 0; i < proc; i++) {
		cout << matrix2[i] << " ";
	}
	cout << endl;
}
//*** ������������� �� ���������� ***
int* CPUs(int **matrix, int task, int proc) {

	int *cpumatrix = new int[proc];
	for (int i = 0; i < proc; i++) {
		cpumatrix[i] = 0;
	}
	int* tempmatrix = new int[proc];
	for (int i = 0; i < proc; i++) {
		tempmatrix[i] = 0;
	}

	for (int i = 0; i < task; i++) {
		for (int j = 0; j < proc; j++) {
			tempmatrix[j] = matrix[i][j] + cpumatrix[j];
		}
		cpumatrix[minSumInd(tempmatrix, proc)] = minSum(tempmatrix, proc);
		for (int k = 0; k < proc; k++) {
			tempmatrix[k] = 0;
		}
	}
	return cpumatrix;
}
