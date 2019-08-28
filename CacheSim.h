#include <string>

class CacheSim{

public:

	struct values{
		int tag;
		int valid;
		int LRUbit;
	};

	CacheSim();
	void memSim(std::string instruction, long long int address, int lcount, char* ofile);
	void DirectMapped4(std::string instruction,long long int address);
	void DirectMapped8(std::string instruction,long long int address);
	void DirectMapped16(std::string instruction,long long int address);
	void DirectMapped32(std::string instruction,long long int address);
	void DirectMapped64(std::string instruction,long long int address);
	void FullyAssocLRU(std::string instruction,long long int address);
	void FullyAssocRand(std::string instruction,long long int address);

	//bd
	
	void updateLRUstate(int index, int x, int ways);
	void updateLRUstateEC(int index,int x,int ways);
	void updateLRUstate1k(int index,int x,int ways);
	int roundNum(float precision);

	void twoWayAsct(std::string instruction, long long int address, int lcount);
	void fourWayAsct(std::string instruction, long long int address, int lcount);
	void eightWayAsct(std::string instruction, long long int address, int lcount);
	void sixteenWayAsct(std::string instruction, long long int address, int lcount);

	void twoWayD(std::string instruction, long long int address, int lcount);
	void fourWayD(std::string instruction, long long int address, int lcount);
	void eightWayD(std::string instruction, long long int address, int lcount);
	void sixteenWayD(std::string instruction, long long int address, int lcount);
	void CacheView();

	//1kb test
	void TwoWay1k(std::string instruction, long long int address, int lcount);
	void FourWay1k(std::string instruction, long long int address, int lcount);
	void EightWay1k(std::string instruction, long long int address, int lcount);
	void SixteenWay1k(std::string instruction, long long int address, int lcount);

	//EC
	void TwoWayEC(std::string instruction, long long int address, int lcount);
	void FourWayEC(std::string instruction, long long int address, int lcount);
	void EightWayEC(std::string instruction, long long int address, int lcount);
	void SixteenWayEC(std::string instruction, long long int address, int lcount);


	//ac
	int DM4 [64][2];
	int DM8 [128][2];
	int DM16 [256][2];
	int DM32 [512][2];
	int DM64 [1024][2];
	long long int FAL [1024][3];
	long long int FAR [1024][3];
//	int LoadCount;
//	int DM4C;
//	int LoadCount;

private:
	int DM4C;
	int DM8C;
	int DM16C;
	int DM32C;
	int DM64C;
	int FALC;
	int FARC;

	//bd
	int twowayC;
	int fourwayC;
	int eightwayC;
	int sixteenwayC;

	values twoway[512][2];
	values fourway[256][4];
	values eightway[128][8];
	values sixteenway[64][16];

//1kbtest
	int twoway1kC;
	int fourway1kC;
	int eightway1kC;
	int sixteenway1kC;

	values twoway1k[8][2];
	values fourway1k[4][4];
	values eightway1k[2][8];
	values sixteenway1k[16];



//EC
	int twowayECC;
	int fourwayECC;
	int eightwayECC;
	int sixteenwayECC;

	values twowayEC[8][2];
	values fourwayEC[4][4];
	values eightwayEC[2][8];
	values sixteenwayEC[16];




	values twowayD[512][2];
	values fourwayD[256][4];
	values eightwayD[128][8];
	values sixteenwayD[64][16];	


};
