

#include <iostream>
#include "Header.h"

using namespace std;

int main()
{
	Data newfile("f1.txt");
	//Accumulator acc; 
	//acc.AccumulateForSeconds(5);
	LZW lzw;
	LZ78 lz78;
	Huffman hf;
	
	int q;
	cout << "Choose the method:" << "\t\n 1 - Huffman \n 2 - LZW \n 3 - LZ78\n";
	cin >> q;
	switch (q) 
	{
		case 1:
			newfile.compress(hf);
			//acc.compress(hf);
			break;
		case 2:
			newfile.compress(lzw); 
			//acc.compress(lzw);
			break;
		case 3:
			//acc.compress(lz78);
			newfile.compress(lz78);
			break;
		default:
			cout << "Method is not found. Compression doesn't exist";
			break;
		
	}
	
	newfile.write_to_file();
	return 0;
}

