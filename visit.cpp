#include <stdio.h>
#include <unordered_map>
#include <sys/time.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <thread>  

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
	struct timeval t1;
    struct timeval t2;
    // --- begin
    gettimeofday(&t1,NULL);

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

	// --- end
    gettimeofday(&t2,NULL);
    printf("readDat! time use = %f ms\n", gettime(t1,t2));
}

double gettime(struct timeval & t1, struct timeval & t2) {
	return (t2.tv_sec - t1.tv_sec)*1000 + (t2.tv_usec - t1.tv_usec)/1000.0;
}

long visit(tmap & map, long id) {
	Tdata nd = map[id];
	long rid;
	for(int i=0; i<nd.size; i++){
		rid = nd.data[i].id;
	}
	return rid;
}

/**
 * test map n times
*/
void test(tmap & map, int n) {
	struct timeval t1;
    struct timeval t2;
    double time;

    // --- begin
    gettimeofday(&t1,NULL);

    if(n >= map.size()) {
    	n = map.size();
    }
    for(long i=0; i<n; i++) {
    	visit(map, i);
    }
	

	gettimeofday(&t2,NULL);
	time = gettime(t1, t2);
	double qps = n/time*1000;
	printf("visit map! n=%d, time use=%f ms, qps=%f\n", n, time, qps);
	// --- end
}

void visitRange(tmap & map, long fromId, long toId) {
	for(long i=fromId; i<toId; i++){
		visit(map, i);
	}
}

/**
 * test map n times using threadNum threads
*/
/*void testM(tmap & map, int n, int threadNum) {
	struct timeval t1;
    struct timeval t2;
    double time;

    // --- begin
    gettimeofday(&t1,NULL);

    if(n >= map.size()) {
    	n = map.size();
    }
    if(threadNum > 4){
    	threadNum = 4;
    }

    int pack = n / threadNum;

    for(int k=0; k<threadNum; k++){
    	long fromId = k*pack;
    	long toId = fromId+pack;
    	thread t(visitRange, map, fromId, toId);
    }
	

	gettimeofday(&t2,NULL);
	time = gettime(t1, t2);
	printf("visit map! n=%d, time use=%f ms\n", n, time);
	// --- end
}*/




int main() {
	string fname = "data/hello.dat";
	//const int n = 100;
	//genDat(fname, n);
	tmap map;
	readDat(fname, map);
	test(map, 5000000);
	test(map, 10000000);
	test(map, 20000000);

	//long id = 3;
	//printf("id=%ld, size=%d\n", id, map[id].size);

	return 0;
}



