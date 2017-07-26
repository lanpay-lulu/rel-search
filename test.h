

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


