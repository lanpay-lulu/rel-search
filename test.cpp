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

double gettime(struct timeval & t1, struct timeval & t2) {
	return (t2.tv_sec - t1.tv_sec)*1000 + (t2.tv_usec - t1.tv_usec)/1000.0;
}

long* createData(short size) {
	long* data = new long[size];
	for(int i=0; i<size; i++){
		data[i] = i;
	}
	return data;
}

Rdata* createData1(short size) {
	Rdata* data = new Rdata[size];
	for(int i=0; i<size; i++){
		data[i].type = 'a' + randInt(26);
	}
	return data;
}

void genDat(string fname, int n) {
	struct timeval t1;
    struct timeval t2;

    // --- begin
    gettimeofday(&t1,NULL);

	ofstream fout(fname, std::ios::binary);
	fout.write((char*) &n, sizeof(n));
	int rsize = 0;
	long id;
	for(int i=0; i<n; i++){
		if(i%1000000==0){
			printf("process %d00w\n", i);
		}
		id = i;
		Tdata nd;
		nd.size = randInt(50) + 1;
		rsize += nd.size;
		nd.data = createData1(nd.size);
		if(i<5){
			printf("write data %ld, len=%d\n",id,nd.size);
		}
		fout.write((char*) &id, sizeof(id));
		fout.write((char*) &(nd.size), sizeof(nd.size));
		fout.write((char*)nd.data, nd.size*sizeof(Rdata));
	}
	fout.close();
	// --- end
    gettimeofday(&t2,NULL);
    printf("genDat! time use = %f ms\n", gettime(t1,t2));
    printf("write data to %s\n", fname.c_str());
    printf("total relation num = %d\n", rsize);
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


int main() {
	string fname = "data/hello.dat";
	const int n = 10000000; // 1kw
	genDat(fname, n);
	//readDat(fname);

	return 0;
}



