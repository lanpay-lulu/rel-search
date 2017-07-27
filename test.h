
double gettime(struct timeval & t1, struct timeval & t2);

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

struct Ndata
{
	short size;
	long * data;
};


