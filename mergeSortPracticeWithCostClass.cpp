//17-06-2022
#include <iostream>
#include <fstream>
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
using namespace std;
#ifndef _DEBUG
#define new new(_CLIENT_BLOCK,__FILE__,__LINE)
#endif


//for qsort library //data type is double
int compare(const void* a, const void* b) 
{
	double* aa = (double*)(a);
	double* bb = (double*)(b);
	if (*aa > *bb) { return -1; }
	else if (*aa < *bb) { return 1; }
	return 0;
}
//using template
template<class T>
void merge(T* arr, int start,int mid, int end)
{
	int i = start;
	int j = mid+1;
	int size = end - start + 1;
	int sb = 0;
	T* temp = new T[size];
	while ((i <= mid) && (j <= end))
	{
		if (arr[i] > arr[j])
		{
			temp[sb] = arr[j++];
		}
		else// if (arr[i] <= arr[j]) //This is problem //why just else is not okay?
		{
			temp[sb] = arr[i++];
		}
		sb++;
	}
	if (j > end)
	{
		for (; i <= mid;)
		{
			temp[sb] = arr[i++];sb++;
		}
		
	}
	if (i > mid)
	{
		for (;j <= end;)
		{
			temp[sb] = arr[j++]; sb++;
		}
		
	}
	i = 0;
	
	for (int ix = start; ix <= end; ix++)
	{
		arr[ix] = temp[i++];
	}
	delete[] temp;
}
template<class T>
void mergeSort(T* arr, int start, int end)
{
	if (start < end)
	{
		int mid = (start + end) / 2;
		mergeSort(arr, start, mid);
		mergeSort(arr, mid+1, end);
		merge(arr, start, mid, end);
	}
}
int main()
{
	_CrtDumpMemoryLeaks();
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	ifstream scores("sort1.txt"); //execution score
	double d;
	int studentNumber = 37;
	double* dd = new double[studentNumber];
	double* dd2 = new double[studentNumber];
	
	int i = 0;
	while (scores >> dd[i++]); //save execution score
	scores.close();
	scores.open("sort2.txt");  //additional score
	i = 0;
	while (scores >> d) //add additional score
	{
		dd[i++] += d;
	}
	scores.close();
	double mean=0;
	cout << "Unsorted students' execution score\n";
	for (int ix = 0; ix < studentNumber; ix++) 
	{
		cout<<ix+1<<": " << dd[ix] << '\n';
		mean += dd[ix];
		dd2[ix] = dd[ix];
	}
	mean /= 37;
	cout << "MEAN : " << mean << "\n";

	//qsort library decreasing order
	qsort(dd, 37, sizeof(double), compare);
	cout << "\n\n\n\nUsing qsort() STL\n";
	for (int ix = 0; ix < studentNumber; ix++)
	{
		cout << ix + 1 << ": " << dd[ix] << '\n';
	}
	cout << "Median : ";
	if (studentNumber % 2 == 0) //even number
	{
		double k = (dd[(studentNumber / 2)] + dd[(studentNumber / 2)-1])/2.0;
		cout << k << "\n";
	}
	else
	{
		cout << dd[studentNumber / 2]; //automatically floor (odd number)
	}
	
	
	//why size 8? //cause pointer != array ?
	//int endNum = (sizeof(dd2) / sizeof(double)) - 1;
	//cout << sizeof(dd2) << endl;
	//cout << "endNum=" << endNum<<"\n";
	cout << "\n\nMergeSort increasing order\n";
	mergeSort(dd2, 0, studentNumber-1);
	for (int ix = 0; ix < studentNumber; ix++) {
		cout << ix + 1 << ": " << dd2[ix] << '\n';
	}
	cout << "\n\n\n";
	delete[] dd, dd2;

	int array[7] = {3,3,1,2,4,9,1};
	cout << "\n\nBefore sorting integers' array\n";
	for (int ix = 0; ix < 7; ix++)
	{
		cout << ix + 1 << ": " << array[ix] << '\n';
	}
	mergeSort(array, 0, 6);
	cout << "\n\nSorted integers' array\n";
	for (int ix = 0; ix < 7; ix++)
	{
		cout << ix + 1 << ": " << array[ix] << '\n';
	}

	char str[10] = "kfcdeighe";
	cout << "\n\nBefore sorting string\n";
	cout << str<<'\n';
	mergeSort(str, 0, 8);
	cout << "\n\nSorted string\n";
	cout << str<<'\n';

	return 0;
}