

#pragma once
#include <unordered_map>
#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <random>
#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <bitset>
#include <iterator>
#include <ctime> 
#include <chrono> 

using namespace std;

class ArchInterface {
public:
	void virtual compress(string s1, vector<int> &output_code) = 0;
	
	void virtual decompress( vector<int> &output_code) = 0;
};

class LZW : public ArchInterface {


public:
	void compress(string s1, vector<int> &output_code) override;

	void decompress(vector<int> &output_code) override;
	
};

class LZ78 : public ArchInterface {
public:
	void compress(string s1, vector<int> &output_code) override;
		
	void decompress(vector<int> &output_code) override;
	
};

class Huffman : public ArchInterface {
public:
	void compress(string s1, vector<int> &output_code) override;

	void decompress(vector<int> &output_code) override;
};

class Data
{
private:
	string data;
	vector<int> code_data;
	

	vector<uint8_t> compressByteArray(const string& compressed)
	{
		vector<uint8_t> byte_array;
		for (size_t i = 0; i < compressed.size(); i += 8)
		{
			string byte_str = compressed.substr(i, 8);
			uint8_t byte = bitset<1>(byte_str).to_ulong();
			byte_array.push_back(byte);
		}
		return byte_array;
	}

	
public:
	Data();
	
	Data(const string& filename);
	
	ofstream write_to_file();

	void print_code_data();

	void print_data();
	
	void compress(ArchInterface& interface) ;
	
	void decompress(ArchInterface& interface) ;
	
	
};

class Accumulator  {
private:
	fstream st;
	vector<int> code_data;
	string data;
	vector<uint8_t> compressByteArray(const string& compressed)
	{
		vector<uint8_t> byte_array;
		for (size_t i = 0; i < compressed.size(); i += 8)
		{
			string byte_str = compressed.substr(i, 8);
			uint8_t byte = bitset<1>(byte_str).to_ulong();
			byte_array.push_back(byte);
		}
		return byte_array;
	}


public:
	Accumulator();

	void addData(unsigned int uIntNumber, float floatNumber, unsigned short UShortNumber);

	string getAccumulatedData();

	void AccumulateForSeconds(float seconds);

	void compress(ArchInterface& interface) ;
	
	void decompress(ArchInterface& interface) ;
	
	void print_code_data();

	void print_data();

	ofstream write_to_file();

};


