
double gettime(struct timeval & t1, struct timeval & t2);

#pragma pack(1)
struct Rdata
{
	char type;
	long id;
};

#pragma pack(2)
struct Tdata
{
	short size;
	Rdata * data;
};

#pragma pack(2)
struct Ndata
{
	short size;
	long * data;
};
#pragma pack()


