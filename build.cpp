#include <stdio.h>
#include <unordered_map>
#include <sys/time.h>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>       // std::chrono::system_clock


using namespace std;


#pragma pack(2)
struct Rdata
{
	char type;
	long id;
};

struct Tdata
{
	short size;
	Rdata * data;
};
#pragma pack()

typedef unordered_map<long, Tdata*> tmap;
const int NN = 40000000; // 1kw
tmap map(NN);


int randInt(int n) {
	return rand() % n;
}

double gettime(struct timeval & t1, struct timeval & t2) {
	return (t2.tv_sec - t1.tv_sec)*1000 + (t2.tv_usec - t1.tv_usec)/1000.0;
}

Tdata* createData(short size) {
	Tdata* td = new Tdata();
	td->size = size;
	td->data = new Rdata[size];
	for(int i=0; i<size; i++){
		td->data[i].type = 'a' + randInt(26);
	}
	return td;
}

void genDat(int n) {
	struct timeval t1;
    struct timeval t2;

    // --- begin
    gettimeofday(&t1,NULL);

	int rsize = 0;
	long id;
	for(int i=0; i<n; i++){
		if(i%1000000==0){
			printf("process %d\n", i);
		}
		id = i;
		Tdata * td = createData(randInt(50) + 1);
		rsize += td->size;
		map[i] = td;
	}

	// --- end
    gettimeofday(&t2,NULL);
    printf("genDat! time use = %f ms\n", gettime(t1,t2));
    printf("total relation num = %d\n", rsize);
}

void readDat(int n) {
	long id;
	long rid;

	struct timeval t1;
    struct timeval t2;

    vector<int> vec(n);
    for(int i=0; i<n; i++){
    	vec.push_back(i);
    }
  	//unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine e(0);
    std::shuffle(vec.begin(), vec.end(), e); 

    // --- begin
    gettimeofday(&t1,NULL);

	printf("data size = %d\n", n);
	Tdata * td;
	for(int i=0; i<n; i++){
		id = vec[i];
		td = map[id];
		for(int j=0; j<td->size; j++){
			rid = (td->data)[j].id;
		}
	}
	// --- end
    gettimeofday(&t2,NULL);
    double time = gettime(t1, t2);
    double qps = n/time*1000;
    printf("readDat! time use = %f ms， qps=%f\n", time, qps);
}


int main() {
		
	genDat(NN);
	int n = 10000*4000;
	readDat(NN);
	//readDat(fname);

	return 0;
}



