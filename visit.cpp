#include <stdio.h>
#include <unordered_map>
#include <sys/time.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include "test.h"

using namespace std;


typedef unordered_map<long, Ndata> hashmap;
typedef unordered_map<long, Tdata> tmap;


int randInt(int n) {
	return rand() % n;
}


void readDat(string fname, tmap & map) {
	std::ifstream fin(fname, std::ios::binary);
	int n;
	long id;
	fin.read((char*)&n, sizeof(int));
	printf("data size = %d\n", n);
	Tdata nd;
	for(int i=0; i<n; i++){
		fin.read((char*)&id, sizeof(id));
		fin.read((char*)&(nd.size), sizeof(nd.size));
		if(i<5){
			printf("read data %ld, len=%d\n",id,nd.size);
		}
		nd.data = new Rdata[nd.size];
		fin.read((char*)(nd.data), nd.size*sizeof(Rdata));
		map[id] = nd;
	}
	fin.close();
}

double gettime(struct timeval & t1, struct timeval & t2) {
	return (t2.tv_sec - t1.tv_sec)*1000 + (t2.tv_usec - t1.tv_usec)/1000.0;
}

void test() {
	printf("hello world!\n");
	const static int N = 1000;
	//short kt = 10;
	//printf("sizeof n = %d\n", sizeof(kt));
	struct timeval t1;
    struct timeval t2;
    struct timeval t3;
    double time;
    int num = 0;

    // --- begin
    gettimeofday(&t1,NULL);

	hashmap map(N*2);	
	
	gettimeofday(&t2,NULL);
	time = gettime(t1, t2);
	printf("build map! time use = %f ms\n", time);

	long v;
	for(int i=0; i<N; i++){
		long id = ((i<<3)+11) % N;
		for(int j=0; j<map[id].size; j++){
			v = map[id].data[j];
		}
		num += map[id].size;
	}
	printf("visit rel num = %d\n", num);

	gettimeofday(&t3,NULL);
	time = gettime(t2, t3);
	printf("visit map! time use = %f ms\n", time);
	// --- end
}



int main() {
	string fname = "data/hello.dat";
	//const int n = 100;
	//genDat(fname, n);
	tmap map;
	readDat(fname, map);
	long id = 3;
	printf("id=%ld, size=%d\n", id, map[id].size);

	return 0;
}



