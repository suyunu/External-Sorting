#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

// Maximum number of numbers in files.
const int MAX_SIZE = 1024;
// Total quantity of numbers
int N;
// File counter for heap. Initially equals fileNumber and decreases when all number in a file used. 
int fileCtr = 0;
// Number of files
int fileNumber;
// Heap for sorting numbers from main file part by part.
double *dmHeap;

/*
 * Struct to be used in main heap.
 * Moves like a cursor on a specific file.
 */
struct numbFiles{
	// Current number in its file.
	double x;
	// Remaining number in its file.
	int counter;
	// Index for its file in filesH[]
	int No;
};

// Ordering rule for the heap while merging
struct greater1{
	bool operator()(const numbFiles& a, numbFiles& b) const{
		return a.x > b.x;
	}
};

// Ordering rule for the heap while separating
struct greater2{
	bool operator()(const double& a, double& b) const{
		return a > b;
	}
};

double heap_pop(int& array_size){
	array_size--;
	double value = dmHeap[array_size];
	dmHeap[array_size] = 0;
	return value;
}

/*
 * Reads the numbers to dmHeap[] from the given file part by part.
 * Each file has MAX_SIZE numbers (last file has <= MAX_SIZE).
 * Writes the sorted version of the heap to a specific file.
 * File name is "/tmp/F_"+fileCtr+".txt".
 * For example, 3. part will be written in "F_3.txt".
 */
void readnSeparate(string fname){
	ifstream finn (fname);
	int i, j;
	dmHeap = new double[MAX_SIZE];
	
	finn >> N;
	
	while(!finn.eof()){
		fileCtr++;
		double x;
		
		for(i = 0 ; i < MAX_SIZE ; i++){
			finn >> x;
			if(finn.eof()){
				if(x != dmHeap[i-1]){
					dmHeap[i] = x;
					i++;
				}
				break;
			}
			dmHeap[i] = x;
		}
		
		
		make_heap(&dmHeap[0],&dmHeap[i],greater2());
		
		string fpath = "";
		fpath += "/tmp/F_";
		fpath += to_string(fileCtr);
		fpath += ".txt";
		ofstream fout(fpath);
		fout << fixed;
		fout.precision(6);
		while(i){
			pop_heap (&dmHeap[0],&dmHeap[i],greater2());
			double x = heap_pop(i);
			fout << x <<endl;
		}
	}
	
	delete[] dmHeap;
}

// Deletes the created files in /tmp directory.
void deleteFiles(){
	int i, j;
	for(i = 1 ; i <= fileNumber ; i++){
		string fpath = "";
		fpath += "/tmp/F_";
		fpath += to_string(i);
		fpath += ".txt";
		char f_name[fpath.length()];
		for(j = 0 ; j < fpath.length() ; j++)
			f_name[j] = fpath[j];
		const char* file_name = f_name;
		remove(file_name);
	}
}

int main(int argc, char *argv[]){
	int i, j;
	
	readnSeparate(argv[1]);
	
	fileNumber = fileCtr;
	
	
	numbFiles heapX[fileCtr];
	
	// Cursor for each file. Starts from index 1.
	// filesH[i] shows "/tmp/F_"+i+".txt".
	ifstream filesH[fileCtr+1];
	
	// Initialization of heapX[]
	for(i = 0 ; i < fileCtr ; i++){
		heapX[i].No = i+1;
		string fpath = "";
		fpath += "/tmp/F_";
		fpath += to_string(i+1);
		fpath += ".txt";
		filesH[i+1].open(fpath);
		filesH[i+1] >> heapX[i].x;
		heapX[i].counter = MAX_SIZE;
	}
	
	heapX[fileCtr-1].counter =  N - (fileCtr-1)*MAX_SIZE;
	
	make_heap(&heapX[0],&heapX[fileCtr],greater1());
	
	ofstream fout(argv[2]);
	fout << fixed;
	fout.precision(6);
	/*
	 * Like in our final exam question there are fileNumber files with MAX_SIZE number of double numbers in them.
	 * The code puts every file's first number into the heap.
	 * Then pop the min number and write it on the output file.
	 * If there is still numbers in the poped number's file, then the new number pushed into the heap.
	 * If there is no number remains in the poped number's file, then the heap's size decreases
	 * and this procedure continues until there is only one file remains.
	 * When one file remains, the code attach the remaining numbers on this file to the output file.
	 * 
	 */
	for(i = 0 ; i < N ; i++){
		if(fileCtr == 1){
			fout << heapX[0].x <<endl;
			filesH[ heapX[0].No ] >> heapX[0].x;
		}
		else{
			pop_heap (&heapX[0],&heapX[fileCtr],greater1());
			fout << heapX[fileCtr-1].x<<endl;
			heapX[fileCtr-1].counter--;
			if(heapX[fileCtr-1].counter > 0){
				filesH[ heapX[fileCtr-1].No ] >> heapX[fileCtr-1].x;
				push_heap(&heapX[0],&heapX[fileCtr],greater1());
			}
			else
				fileCtr--;
		}
	}
	fileCtr--;
	
	deleteFiles();
	
	return (0-0);
}

