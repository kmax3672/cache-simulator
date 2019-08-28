#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "stdlib.h"
#include "predictors.h"

using namespace std;

int main(int argc, char* argv[])
{
	if(argc != 3)
	{
		cout << "Usage: exe <input_file> <output_file>" << endl;
		return -1;
	}
	

	long long int address = 0;
	int i=0;
	string instruction = "";
	int lcount = 1;
	cacheSim line =  cacheSim();
	ifstream in(argv[1]);
	while(!in.eof() || in.peek() != EOF)
	{	
	
			if(in.eof() || in.peek() == EOF){
				break;	
			}
			in >> instruction;
				
	
			if(in.eof() || in.peek() == EOF){
				break;	
			}
			in >> hex >> address;


	line.memSim(instruction, address, lcount, argv[2]);
	
	lcount++;


	}
	in.close();


	


	//write array to file
	/*FILE* fp = fopen(argv[2], "w");
	fclose(fp);*/
	//cleanup
	//delete [] data;

	return 0;
}

