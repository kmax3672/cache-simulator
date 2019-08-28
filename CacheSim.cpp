#include <iostream>
#include <fstream>
#include "CacheSim.h"
#include "math.h"
#include <stdlib.h>
using namespace std;

struct values{
	int tag;
	int valid;
	int LRUbit;

};

CacheSim::CacheSim(){

	//part a
	DM4 [64][2];
	DM8 [128][2];
	DM16 [256][2];
	DM32 [512][2];
	DM64 [1024][2];
	DM4C=0;
	DM8C=0;
	DM16C=0;
	DM32C=0;
	DM64C=0;
	for(DM4C;DM4C<64;DM4C++){
		DM4[DM4C][0]=0;
		DM4[DM4C][1]=0;
	}
	for(DM4C=0;DM4C<128;DM4C++){
		DM8[DM4C][0]=0;
		DM8[DM4C][1]=0;
	}
	for(DM4C=0;DM4C<256;DM4C++){
		DM16[DM4C][0]=0;
		DM16[DM4C][1]=0;
	}
	for(DM4C=0;DM4C<512;DM4C++){
		DM32[DM4C][0]=0;
		DM32[DM4C][1]=0;
	}
	for(DM4C=0;DM4C<1024;DM4C++){
		DM64[DM4C][0]=0;
		DM64[DM4C][1]=0;
	}

	DM4C=0;
	
	//part c
	FAL [1024][3];
	FALC=0;
	for(FALC;FALC<1024;FALC++){
		FAL[FALC][0]=0;
		FAL[FALC][1]=0;
		FAL[FALC][2]=0;
	}
	FALC=0;
	
	FAR [1024][3];
	FARC=0;
	for(FARC;FARC<1024;FARC++){
		FAR[FARC][0]=0;
		FAR[FARC][1]=0;
		FAR[FARC][2]=0;
		
	}
	FARC=0;

	//part b and d
	twowayC=0;
	fourwayC=0;
	eightwayC=0;
	sixteenwayC=0;
	

	twoway[512][2];
	fourway[256][4];
	eightway[128][8];
	sixteenway[64][16];


	twowayD[512][2];
	fourwayD[256][4];
	eightwayD[128][8];
	sixteenwayD[64][16];
	
	int x=0;
	int y=0;

	for(x=0; x<512; x++){
		for(y=0; y<2; y++){
			twoway[x][y].tag = 0;
			twoway[x][y].valid = 0;
			twoway[x][y].LRUbit = 0;
		}			
	}

	for(x=0; x<256; x++){
		for(y=0; y<4; y++){
			fourway[x][y].tag = 0;
			fourway[x][y].valid = 0;
			fourway[x][y].LRUbit = 0;
		}			
	}
	for(x=0; x<128; x++){
		for(int y=0; y<8; y++){
			eightway[x][y].tag = 0;
			eightway[x][y].valid = 0;
			eightway[x][y].LRUbit = 0;
		}			
	}	

	for(x=0; x<64; x++){
		for(y=0; y<16; y++){
			sixteenway[x][y].tag = 0;
			sixteenway[x][y].valid = 0;
			sixteenway[x][y].LRUbit = 0;
		}			
	}
	//1kb
	twoway1kC=0;
	fourway1kC=0;
	eightway1kC=0;
	sixteenway1kC=0;
	

	twoway1k[8][2];
	fourway1k[4][4];
	eightway1k[2][8];
	sixteenway1k[16];
	for(x=0; x<8; x++){
		for(y=0; y<2; y++){
			twoway1k[x][y].tag = 0;
			twoway1k[x][y].valid = 0;
			twoway1k[x][y].LRUbit = 0;
		}			
	}

	for(x=0; x<4; x++){
		for(y=0; y<4; y++){
			fourway1k[x][y].tag = 0;
			fourway1k[x][y].valid = 0;
			fourway1k[x][y].LRUbit = 0;
		}			
	}
	for(x=0; x<2; x++){
		for(y=0; y<8; y++){
			eightway1k[x][y].tag = 0;
			eightway1k[x][y].valid = 0;
			eightway1k[x][y].LRUbit = 0;
		}			
	}	

		for(y=0; y<16; y++){
			sixteenway1k[y].tag = 0;
			sixteenway1k[y].valid = 0;
			sixteenway1k[y].LRUbit = 0;
		}			




	//Extra Credit
	twowayECC=0;
	fourwayECC=0;
	eightwayECC=0;
	sixteenwayECC=0;
	

	twowayEC[8][2];
	fourwayEC[4][4];
	eightwayEC[2][8];
	sixteenwayEC[16];
	for(x=0; x<8; x++){
		for(y=0; y<2; y++){
			twowayEC[x][y].tag = 0;
			twowayEC[x][y].valid = 0;
			twowayEC[x][y].LRUbit = 0;
		}			
	}

	for(x=0; x<4; x++){
		for(y=0; y<4; y++){
			fourwayEC[x][y].tag = 0;
			fourwayEC[x][y].valid = 0;
			fourwayEC[x][y].LRUbit = 0;
		}			
	}
	for(x=0; x<2; x++){
		for(y=0; y<8; y++){
			eightwayEC[x][y].tag = 0;
			eightwayEC[x][y].valid = 0;
			eightwayEC[x][y].LRUbit = 0;
		}			
	}	

		for(y=0; y<16; y++){
			sixteenwayEC[y].tag = 0;
			sixteenwayEC[y].valid = 0;
			sixteenwayEC[y].LRUbit = 0;
		}			


}

void CacheSim::memSim(string instruction, long long int address, int lcount, char* ofile){

		int prectwoWay=0;
		int precfourWay=0;
		int preceightWay=0;
		int precsixteenWay=0;			


		DirectMapped4(instruction,address);
		DirectMapped8(instruction,address);
		DirectMapped16(instruction,address);
		DirectMapped32(instruction,address);
		DirectMapped64(instruction,address);
		FullyAssocLRU(instruction,address);
		FullyAssocRand(instruction,address);

		//bd
		twoWayAsct(instruction, address, lcount);
		fourWayAsct(instruction,address, lcount);
		eightWayAsct(instruction,address, lcount);
		sixteenWayAsct(instruction,address, lcount);	

		//EC
		TwoWay1k(instruction, address, lcount);
		FourWay1k(instruction,address, lcount);
		EightWay1k(instruction,address, lcount);
		SixteenWay1k(instruction,address, lcount);	

		TwoWayEC(instruction, address, lcount);
		FourWayEC(instruction,address, lcount);
		EightWayEC(instruction,address, lcount);
		SixteenWayEC(instruction,address, lcount);			


		if(lcount==2000000){

			prectwoWay = roundNum(100 * (float)twowayC/lcount);
			precfourWay = roundNum(100 * (float)fourwayC/lcount);
			preceightWay= roundNum(100 * (float)eightwayC/lcount);
			precsixteenWay= roundNum(100 * (float)sixteenwayC/lcount);	

		/*	cout << DM4C/(lcount/100) << " ";
			cout << DM8C/(lcount/100)<< " ";		
			cout << DM16C/(lcount/100) << " ";
			cout << DM32C/(lcount/100) << " ";
			cout << DM64C/(lcount/100) << endl;*/
			cout << DM4C << " ";
			cout << DM8C<< " ";		
			cout << DM16C << " ";
			cout << DM32C << " ";
			cout << DM64C << endl;

			//bd
			cout << twowayC << " ";
			cout << fourwayC << " ";
			cout << eightwayC << " ";
			cout << sixteenwayC << endl;	

			//c
			cout << FALC << endl;
			cout << FARC << endl;
			//1kb
			cout << twoway1kC << " ";
			cout << fourway1kC << " ";
			cout << eightway1kC << " ";
			cout << sixteenway1kC << endl;	


			//EC
			cout << twowayECC << " ";
			cout << fourwayECC << " ";
			cout << eightwayECC << " ";
			cout << sixteenwayECC << endl;	

		CacheView();
		}
		


}

void CacheSim::DirectMapped4(string instruction, long long int address){

	int offSet=address % 64;
	address=address/64;
	int index=address % 64;
	address=address/64;

	long int tag = DM4[index][1];
	if(instruction=="S"){
		if(tag==address){
			DM4C++;
		}
		else{
		DM4[index][0]=2;
		DM4[index][1]=address;
		}
	}
	else if(instruction=="L"){
		if(DM4[index][0]!=2){
			DM4[index][0]=2;
			DM4[index][1]=address;
		}
		else if(tag==address){
			DM4C++;
		}
		else if(tag!=address){
			DM4[index][1]=address;
		}
	}
}
void CacheSim::DirectMapped8(string instruction, long long int address){

	int offSet=address % 64;
	address=address/64;
	int index=address % 128;
	address=address/128;

	long int tag = DM8[index][1];
	if(instruction=="S"){
		if(tag==address){
			DM8C++;
		}
		else{
			DM8[index][0]=2;
			DM8[index][1]=address;
		}
	}
	else if(instruction=="L"){
		if(DM8[index][0]!=2){
			DM8[index][0]=2;
			DM8[index][1]=address;
		}
		else if(tag==address){
			DM8C++;
		}
		else if(tag!=address){
			DM8[index][1]=address;
		}
	}
}

void CacheSim::DirectMapped16(string instruction, long long int address){

	int offSet=address % 64;
	address=address/64;
	int index=address % 256;
	address=address/256;

	long int tag = DM16[index][1];
	if(instruction=="S"){
		if(tag==address){
			DM16C++;
		}
		else{
			DM16[index][0]=2;
			DM16[index][1]=address;
		}
	}
	else if(instruction=="L"){
		if(DM16[index][0]!=2){
			DM16[index][0]=2;
			DM16[index][1]=address;
		}
		else if(tag==address){
			DM16C++;
		}
		else if(tag!=address){
			DM16[index][1]=address;
		}
	}
}

void CacheSim::DirectMapped32(string instruction, long long int address){

	int offSet=address % 64;
	address=address/64;
	int index=address % 512;
	address=address/512;

	long int tag = DM32[index][1];
	if(instruction=="S"){
		if(tag==address){
			DM32C++;
		}
		else{
			DM32[index][0]=2;
			DM32[index][1]=address;
		}
	}
	else if(instruction=="L"){
		if(DM32[index][0]!=2){
			DM32[index][0]=2;
			DM32[index][1]=address;
		}
		else if(tag==address){
			DM32C++;
		}
		else if(tag!=address){
			DM32[index][1]=address;
		}
	}
}

void CacheSim::DirectMapped64(string instruction, long long int address){

	int offSet=address % 64;
	address=address/64;
	int index=address % 1024;
	address=address/1024;

	long int tag = DM64[index][1];
	if(instruction=="S"){
		if(tag==address){
			DM64C++;
		}
		else{
			DM64[index][0]=2;
			DM64[index][1]=address;
		}
	}
	else if(instruction=="L"){
		if(DM64[index][0]!=2){
			DM64[index][0]=2;
			DM64[index][1]=address;
		}
		else if(tag==address){
			DM64C++;
		}
		else if(tag!=address){
			DM64[index][1]=address;
		}
	}
}

//Part C

void CacheSim::FullyAssocLRU(string instruction,long long int address){   //does long long int truncate to int to give faulty equals?
	address=address/64;
	int m=0;
	bool hit=false;
	int tag=0;
	for(m;m<1024;m++){
	//	cout << m << endl;
	//	cout <<FAL[m][1] << endl;
	//	cout << address << "\n" << endl;
		if((FAL[m][1]==address)&&(FAL[m][0]==1)){
			hit=true;
			tag=m;
		//	cout << "here" << endl;
		}
	}
//	cout << "blah" << endl;
	if(hit){
	//	cout << "hit" << endl;
		FALC++;
		//FAL[tag][2]=0;
	}else{
	//	cout << "else" << endl; 
		int max=FAL[0][2];
		for(m=0;m<1024;m++){
			if(FAL[m][2]>max){
				max=FAL[m][2];
				tag=m;
			}
		}
	//	cout << "here" << endl;
		FAL[tag][1]=address;
	//	cout << FAL[tag][1] << endl;
		FAL[tag][0]=1;
	}

	for(m=0;m<1024;m++){
		FAL[m][2]++;
	}
	FAL[tag][2]=0;


}


//random Fully Assoc
void CacheSim::FullyAssocRand(string instruction,long long int address){   //does long long int truncate to int to give faulty equals?
	address=address/64;
	int m=0;
	bool hit=false;
	int tag=0;
	for(m;m<1024;m++){
	//	cout << m << endl;
	//	cout <<FAL[m][1] << endl;
	//	cout << address << "\n" << endl;
		if((FAR[m][1]==address)&&(FAR[m][0]==1)){
			hit=true;
			tag=m;
		//	cout << "here" << endl;
		}
	}
//	cout << "blah" << endl;
	if(hit){
	//	cout << "hit" << endl;
		FARC++;
		//FAL[tag][2]=0;
	}else{
		tag= rand() %1024;
		FAR[tag][1]=address;
	//	cout << FAL[tag][1] << endl;
		FAR[tag][0]=1;
	}

	for(m=0;m<1024;m++){
		FAR[m][2]++;
	}
	FAR[tag][2]=0;


}


//b&d--------------------------------------------------
int CacheSim::roundNum(float precision){
	int rounded;
	rounded = (int)floor(precision + 0.5);
	return rounded;

}



void CacheSim::updateLRUstate(int index, int x, int ways){
	
	for(int i=0; i<ways; i++){
		if(ways == 2){
			twoway[index][i].LRUbit++;
		}
		if(ways == 4){
			fourway[index][i].LRUbit++;
		}
		if(ways == 8){
			eightway[index][i].LRUbit++;
		}
		if(ways == 16){
			sixteenway[index][i].LRUbit++;
		}
	}
	
		if(ways == 2){twoway[index][x].LRUbit = 0;}
		if(ways == 4){fourway[index][x].LRUbit = 0;}
		if(ways == 8){eightway[index][x].LRUbit = 0;}
		if(ways == 16){sixteenway[index][x].LRUbit =0;}

	return;

}
//1kb LRU
void CacheSim::updateLRUstate1k(int index, int x, int ways){
	
	for(int i=0; i<ways; i++){
		if(ways == 2){
			twoway1k[index][i].LRUbit++;
		}
		if(ways == 4){
			fourway1k[index][i].LRUbit++;
		}
		if(ways == 8){
			eightway1k[index][i].LRUbit++;
		}
		if(ways == 16){
			sixteenway1k[i].LRUbit++;
		}
	}
	
		if(ways == 2){twoway1k[index][x].LRUbit = 0;}
		if(ways == 4){fourway1k[index][x].LRUbit = 0;}
		if(ways == 8){eightway1k[index][x].LRUbit = 0;}
		if(ways == 16){sixteenway1k[x].LRUbit =0;}

	return;

}


//Extra Credit LRU  (LRU shared by both 1kb gave good results!
void CacheSim::updateLRUstateEC(int index, int x, int ways){
	
	for(int i=0; i<ways; i++){
		if(ways == 2){
			twowayEC[index][i].LRUbit++;
		}
		if(ways == 4){
			fourwayEC[index][i].LRUbit++;
		}
		if(ways == 8){
			eightwayEC[index][i].LRUbit++;
		}
		if(ways == 16){
			sixteenwayEC[i].LRUbit++;
		}
	}
	
		if(ways == 2){twowayEC[index][x].LRUbit = 0;}
		if(ways == 4){fourwayEC[index][x].LRUbit = 0;}
		if(ways == 8){eightwayEC[index][x].LRUbit = 0;}
		if(ways == 16){sixteenwayEC[x].LRUbit =0;}

	return;

}




void CacheSim::twoWayAsct(string instruction, long long int address, int lcount){

	int maxLRU=0;
	int maxIndex=0;
	address = address/64;
	int index=address % 512;

	address=address/512;

	if(instruction=="S"){
		int n=0;
		int x=0;
		for(x=0; x<2; x++){
			if(twoway[index][x].tag==address){
				twowayC++;
				updateLRUstate(index, x, 2);
				break;
			}
			else
				n++;	
		}
		if(n==2){
			for(x=0; x<2; x++){
				if(twoway[index][x].LRUbit > maxLRU){
					maxLRU = twoway[index][x].LRUbit;
					maxIndex = x;
				}
			}
			updateLRUstate(index, maxIndex, 2);
			twoway[index][maxIndex].tag=address;
			twoway[index][maxIndex].valid=1;
		}
		
	}
	else if(instruction=="L"){
		int m=0;
		int y=0;
		for(y=0; y<2; y++){
			if(twoway[index][y].tag==address){
				twowayC++;
				updateLRUstate(index, y, 2);
				break;
			}
			else
				m++;	
		}
		if(m==2){
			for(y=0; y<2; y++){
				if(twoway[index][y].LRUbit > maxLRU){
					maxLRU = twoway[index][y].LRUbit;
					maxIndex = y;
				}
			}
			updateLRUstate(index, maxIndex, 2);
			twoway[index][maxIndex].tag=address;
			twoway[index][maxIndex].valid=1;
		}
	}


}


void CacheSim::fourWayAsct(std::string instruction, long long int address, int lcount){

	int maxLRU=0;
	int maxIndex=0;
	int offset = address % 64;
	address = address/64;
	int index=address % 256;
	address=address/256;

	int tag = address;


	if(instruction=="S"){
		int n=0;
		int x=0;
		for(x=0; x<4; x++){
			if(fourway[index][x].tag==address){
				updateLRUstate(index, x, 4);
				fourwayC++;
				break;
			}
			else
				n++;	
		}
		if(n==4){
			for(x=0; x<4; x++){
				if(fourway[index][x].LRUbit > maxLRU){
					maxLRU = fourway[index][x].LRUbit;
					maxIndex = x;
				}
			}	
			updateLRUstate(index, maxIndex, 4);
			fourway[index][maxIndex].tag=address;
			fourway[index][maxIndex].valid=1;
		}


	}

	else if(instruction=="L"){
		int m=0;
		for(int y=0; y<4; y++){
			if(fourway[index][y].tag==address){
				updateLRUstate(index, y, 4);
				fourwayC++;
				break;
			}
			else
				m++;	                            //if it goes through all nodes without a hit it replaces the LRU
		}
		if(m==4){
			for(int y=0; y<4; y++){
				if(fourway[index][y].LRUbit > maxLRU){
					maxLRU = fourway[index][y].LRUbit;
					maxIndex = y;
				}
			}
			updateLRUstate(index, maxIndex, 4);
			fourway[index][maxIndex].tag=address;
			fourway[index][maxIndex].valid=1;
		}
	}


}


void CacheSim::eightWayAsct(std::string instruction, long long int address, int lcount){
	int maxLRU=0;
	int maxIndex=0;
	address = address/64;
	int index=address % 128;
	address=address/128;


	if(instruction=="S"){
		int n=0;
		for(int x=0; x<8; x++){
			if(eightway[index][x].tag==address){
				updateLRUstate(index, x, 8);
				eightwayC++;
				break;
			}
			else
				n++;	
		}
		if(n==8){
			for(int x=0; x<8; x++){
				if(eightway[index][x].LRUbit > maxLRU){
					maxLRU = eightway[index][x].LRUbit;
					maxIndex = x;
				}
			}	
			updateLRUstate(index, maxIndex, 8);
			eightway[index][maxIndex].tag=address;
			eightway[index][maxIndex].valid=1;
		}


	}

	else if(instruction=="L"){
		int m=0;
		for(int y=0; y<8; y++){
			if(eightway[index][y].tag==address){
				updateLRUstate(index, y, 8);
				eightwayC++;
				break;
			}
			else
				m++;	
		}
		if(m==8){
			for(int y=0; y<8; y++){
				if(eightway[index][y].LRUbit > maxLRU){
					maxLRU = eightway[index][y].LRUbit;
					maxIndex = y;
				}
			}
			updateLRUstate(index, maxIndex, 8);
			eightway[index][maxIndex].tag=address;
			eightway[index][maxIndex].valid=1;
		}
	}

}

void CacheSim::sixteenWayAsct(std::string instruction, long long int address, int lcount){
	int maxLRU=0;
	int maxIndex=0;
	address = address/64;
	int index=address % 64;
	address=address/64;



	if(instruction=="S"){
		int n=0;
		for(int x=0; x<16; x++){
			if(sixteenway[index][x].tag==address){
				updateLRUstate(index, x, 16);
				sixteenwayC++;
				break;
			}
			else
				n++;	
		}
		if(n==16){
			for(int x=0; x<16; x++){
				if(sixteenway[index][x].LRUbit > maxLRU){
					maxLRU = sixteenway[index][x].LRUbit;
					maxIndex = x;
				}
			}	
			updateLRUstate(index, maxIndex, 16);
			sixteenway[index][maxIndex].tag=address;
			sixteenway[index][maxIndex].valid=1;
		}


	}

	else if(instruction=="L"){
		int m=0;
		for(int y=0; y<16; y++){
			if(sixteenway[index][y].tag==address){
				updateLRUstate(index, y, 16);
				sixteenwayC++;
				break;
			}
			else
				m++;	
		}
		if(m==16){
			for(int y=0; y<16; y++){
				if(sixteenway[index][y].LRUbit > maxLRU){
					maxLRU = sixteenway[index][y].LRUbit;
					maxIndex = y;
				}
			}
			updateLRUstate(index, maxIndex, 16);
			sixteenway[index][maxIndex].tag=address;
			sixteenway[index][maxIndex].valid=1;
		}
	}

}

void CacheSim::CacheView(){
	cout << "Two Way" << endl;
	cout << "W1: " << twoway[14][0].tag << "\t\tW2: " << twoway[14][1].tag << endl;
	int c=0;
	cout << "\n\nSixteen Way-----------" << endl;
	for(c=0;c<16;c++){
	cout << c << ")    " << sixteenway[14][c].tag << endl;
	}


}
//1kb test
void CacheSim::TwoWay1k(string instruction, long long int address, int lcount){

	int maxLRU=0;
	int maxIndex=0;
	address = address/64;
	int index=address % 8;

	address=address/8;

	if(instruction=="S"){
		int n=0;
		int x=0;
		for(x=0; x<2; x++){
			if(twoway1k[index][x].tag==address){
				twoway1kC++;
				updateLRUstate1k(index, x, 2);
				break;
			}
			else
				n++;	
		}
		if(n==2){
			for(x=0; x<2; x++){
				if(twoway1k[index][x].LRUbit > maxLRU){
					maxLRU = twoway1k[index][x].LRUbit;
					maxIndex = x;
				}
			}
			updateLRUstate1k(index, maxIndex, 2);
			twoway1k[index][maxIndex].tag=address;
			twoway1k[index][maxIndex].valid=1;
		}
		
	}
	else if(instruction=="L"){
		int m=0;
		int y=0;
		for(y=0; y<2; y++){
			if(twoway1k[index][y].tag==address){
				twoway1kC++;
				updateLRUstate1k(index, y, 2);
				break;
			}
			else
				m++;	
		}
		if(m==2){
			for(y=0; y<2; y++){
				if(twoway1k[index][y].LRUbit > maxLRU){
					maxLRU = twoway1k[index][y].LRUbit;
					maxIndex = y;
				}
			}
			updateLRUstate1k(index, maxIndex, 2);
			twoway1k[index][maxIndex].tag=address;
			twoway1k[index][maxIndex].valid=1;
		}
	}


}


void CacheSim::FourWay1k(std::string instruction, long long int address, int lcount){

	int maxLRU=0;
	int maxIndex=0;
	int offset = address % 64;
	address = address/64;
	int index=address % 4;
	address=address/4;

	int tag = address;


	if(instruction=="S"){
		int n=0;
		int x=0;
		for(x=0; x<4; x++){
			if(fourway1k[index][x].tag==address){
				updateLRUstate1k(index, x, 4);
				fourway1kC++;
				break;
			}
			else
				n++;	
		}
		if(n==4){
			for(x=0; x<4; x++){
				if(fourway1k[index][x].LRUbit > maxLRU){
					maxLRU = fourway1k[index][x].LRUbit;
					maxIndex = x;
				}
			}	
			updateLRUstate1k(index, maxIndex, 4);
			fourway1k[index][maxIndex].tag=address;
			fourway1k[index][maxIndex].valid=1;
		}


	}

	else if(instruction=="L"){
		int m=0;
		for(int y=0; y<4; y++){
			if(fourway1k[index][y].tag==address){
				updateLRUstate1k(index, y, 4);
				fourway1kC++;
				break;
			}
			else
				m++;	                            //if it goes through all nodes without a hit it replaces the LRU
		}
		if(m==4){
			for(int y=0; y<4; y++){
				if(fourway1k[index][y].LRUbit > maxLRU){
					maxLRU = fourway1k[index][y].LRUbit;
					maxIndex = y;
				}
			}
			updateLRUstate1k(index, maxIndex, 4);
			fourway1k[index][maxIndex].tag=address;
			fourway1k[index][maxIndex].valid=1;
		}
	}


}


void CacheSim::EightWay1k(std::string instruction, long long int address, int lcount){
	int maxLRU=0;
	int maxIndex=0;
	address = address/64;
	int index=address % 2;
	address=address/2;


	if(instruction=="S"){
		int n=0;
		for(int x=0; x<8; x++){
			if(eightway1k[index][x].tag==address){
				updateLRUstate1k(index, x, 8);
				eightway1kC++;
				break;
			}
			else
				n++;	
		}
		if(n==8){
			for(int x=0; x<8; x++){
				if(eightway1k[index][x].LRUbit > maxLRU){
					maxLRU = eightway1k[index][x].LRUbit;
					maxIndex = x;
				}
			}	
			updateLRUstate1k(index, maxIndex, 8);
			eightway1k[index][maxIndex].tag=address;
			eightway1k[index][maxIndex].valid=1;
		}


	}

	else if(instruction=="L"){
		int m=0;
		for(int y=0; y<8; y++){
			if(eightway1k[index][y].tag==address){
				updateLRUstate1k(index, y, 8);
				eightway1kC++;
				break;
			}
			else
				m++;	
		}
		if(m==8){
			for(int y=0; y<8; y++){
				if(eightway1k[index][y].LRUbit > maxLRU){
					maxLRU = eightway1k[index][y].LRUbit;
					maxIndex = y;
				}
			}
			updateLRUstate1k(index, maxIndex, 8);
			eightway1k[index][maxIndex].tag=address;
			eightway1k[index][maxIndex].valid=1;
		}
	}

}

void CacheSim::SixteenWay1k(std::string instruction, long long int address, int lcount){
	int maxLRU=0;
	int maxIndex=0;
	address = address/64;



	if(instruction=="S"){
		int n=0;
		for(int x=0; x<16; x++){
			if(sixteenway1k[x].tag==address){
				updateLRUstate1k(-1, x, 16);
				sixteenway1kC++;
				break;
			}
			else
				n++;	
		}
		if(n==16){
			for(int x=0; x<16; x++){
				if(sixteenway1k[x].LRUbit > maxLRU){
					maxLRU = sixteenway1k[x].LRUbit;
					maxIndex = x;
				}
			}	
			updateLRUstate1k(-1, maxIndex, 16);
			sixteenway1k[maxIndex].tag=address;
			sixteenway1k[maxIndex].valid=1;
		}


	}

	else if(instruction=="L"){
		int m=0;
		for(int y=0; y<16; y++){
			if(sixteenway1k[y].tag==address){
				updateLRUstate1k(-1, y, 16);
				sixteenway1kC++;
				break;
			}
			else
				m++;	
		}
		if(m==16){
			for(int y=0; y<16; y++){
				if(sixteenway1k[y].LRUbit > maxLRU){
					maxLRU = sixteenway1k[y].LRUbit;
					maxIndex = y;
				}
			}
			updateLRUstate1k(-1, maxIndex, 16);
			sixteenway1k[maxIndex].tag=address;
			sixteenway1k[maxIndex].valid=1;
		}
	}

}



//EXTRA CREDIT--------------

void CacheSim::TwoWayEC(string instruction, long long int address, int lcount){

	int maxLRU=0;
	int maxIndex=0;
	address = address/64;
	int index=address % 8;

	address=address/8;

	if(instruction=="S"){
		int n=0;
		int x=0;
		for(x=0; x<2; x++){
			if(twowayEC[index][x].tag==address){
				twowayECC++;
				updateLRUstateEC(index, x, 2);
				break;
			}
			else
				n++;	
		}
		if(n==2){
			for(x=0; x<2; x++){
				if(twowayEC[index][x].LRUbit > maxLRU){
					maxLRU = twowayEC[index][x].LRUbit;
					maxIndex = x;
				}
			}
			updateLRUstateEC(index, maxIndex, 2);
			twowayEC[index][maxIndex].tag=address;
			twowayEC[index][maxIndex].valid=1;
		}
		
	}
	else if(instruction=="L"){
		int m=0;
		int y=0;
		for(y=0; y<2; y++){
			if(twowayEC[index][y].tag==address){
				twowayECC++;
				updateLRUstateEC(index, y, 2);
				break;
			}
			else
				m++;	
		}
		if(m==2){
			for(y=0; y<2; y++){
				if(twowayEC[index][y].LRUbit > maxLRU){
					maxLRU = twowayEC[index][y].LRUbit;
					maxIndex = y;
				}
			}
			updateLRUstateEC(index, maxIndex, 2);
			twowayEC[index][maxIndex].tag=address;
			twowayEC[index][maxIndex].valid=1;
		}
	}


}


void CacheSim::FourWayEC(std::string instruction, long long int address, int lcount){

	int maxLRU=0;
	int maxIndex=0;
	int offset = address % 64;
	address = address/64;
	int index=address % 4;
	address=address/4;

	int tag = address;


	if(instruction=="S"){
		int n=0;
		int x=0;
		for(x=0; x<4; x++){
			if(fourwayEC[index][x].tag==address){
				updateLRUstateEC(index, x, 4);
				fourwayECC++;
				break;
			}
			else
				n++;	
		}
		if(n==4){
			for(x=0; x<4; x++){
				if(fourwayEC[index][x].LRUbit > maxLRU){
					maxLRU = fourwayEC[index][x].LRUbit;
					maxIndex = x;
				}
			}	
			updateLRUstateEC(index, maxIndex, 4);
			fourwayEC[index][maxIndex].tag=address;
			fourwayEC[index][maxIndex].valid=1;
		}


	}

	else if(instruction=="L"){
		int m=0;
		for(int y=0; y<4; y++){
			if(fourwayEC[index][y].tag==address){
				updateLRUstateEC(index, y, 4);
				fourwayECC++;
				break;
			}
			else
				m++;	                            //if it goes through all nodes without a hit it replaces the LRU
		}
		if(m==4){
			for(int y=0; y<4; y++){
				if(fourwayEC[index][y].LRUbit > maxLRU){
					maxLRU = fourwayEC[index][y].LRUbit;
					maxIndex = y;
				}
			}
			updateLRUstateEC(index, maxIndex, 4);
			fourwayEC[index][maxIndex].tag=address;
			fourwayEC[index][maxIndex].valid=1;
		}
	}


}


void CacheSim::EightWayEC(std::string instruction, long long int address, int lcount){
	int maxLRU=0;
	int maxIndex=0;
	address = address/64;
	int index=address % 2;
	address=address/2;


	if(instruction=="S"){
		int n=0;
		for(int x=0; x<8; x++){
			if(eightwayEC[index][x].tag==address){
				updateLRUstateEC(index, x, 8);
				eightwayECC++;
				break;
			}
			else
				n++;	
		}
		if(n==8){
			for(int x=0; x<8; x++){
				if(eightwayEC[index][x].LRUbit > maxLRU){
					maxLRU = eightwayEC[index][x].LRUbit;
					maxIndex = x;
				}
			}	
			updateLRUstateEC(index, maxIndex, 8);
			eightwayEC[index][maxIndex].tag=address;
			eightwayEC[index][maxIndex].valid=1;
		}


	}

	else if(instruction=="L"){
		int m=0;
		for(int y=0; y<8; y++){
			if(eightwayEC[index][y].tag==address){
				updateLRUstateEC(index, y, 8);
				eightwayECC++;
				break;
			}
			else
				m++;	
		}
		if(m==8){
			for(int y=0; y<8; y++){
				if(eightwayEC[index][y].LRUbit > maxLRU){
					maxLRU = eightwayEC[index][y].LRUbit;
					maxIndex = y;
				}
			}
			updateLRUstateEC(index, maxIndex, 8);
			eightwayEC[index][maxIndex].tag=address;
			eightwayEC[index][maxIndex].valid=1;
		}
	}

}

void CacheSim::SixteenWayEC(std::string instruction, long long int address, int lcount){
	int maxLRU=0;
	int maxIndex=0;
	address = address/64;



	if(instruction=="S"){
		int n=0;
		for(int x=0; x<16; x++){
			if(sixteenwayEC[x].tag==address){
				updateLRUstateEC(-1, x, 16);
				sixteenwayECC++;
				break;
			}
			else
				n++;	
		}
		if(n==16){
			for(int x=0; x<16; x++){
				if(sixteenwayEC[x].LRUbit > maxLRU){
					maxLRU = sixteenwayEC[x].LRUbit;
					maxIndex = x;
				}
			}	
			updateLRUstateEC(-1, maxIndex, 16);
			sixteenwayEC[maxIndex].tag=address;
			sixteenwayEC[maxIndex].valid=1;
		}


	}

	else if(instruction=="L"){
		int m=0;
		for(int y=0; y<16; y++){
			if(sixteenwayEC[y].tag==address){
				updateLRUstateEC(-1, y, 16);
				sixteenwayECC++;
				break;
			}
			else
				m++;	
		}
		if(m==16){
			for(int y=0; y<16; y++){
				if(sixteenwayEC[y].LRUbit > maxLRU){
					maxLRU = sixteenwayEC[y].LRUbit;
					maxIndex = y;
				}
			}
			updateLRUstateEC(-1, maxIndex, 16);
			sixteenwayEC[maxIndex].tag=address;
			sixteenwayEC[maxIndex].valid=1;
		}
	}

}
















































































