
#include "Header.h"
using namespace std;


Accumulator::Accumulator()
{
	this->data = " ";
	this->code_data = { 0 };

}

void Accumulator::addData(unsigned int uIntNumber, float floatNumber, unsigned short UShortNumber)
{
	std::ostringstream oss;
	oss << uIntNumber << " " << floatNumber << " " << UShortNumber;
	this->data = oss.str(); 
}

string Accumulator::getAccumulatedData()
{
	return this->data;
}

void Accumulator::AccumulateForSeconds(float seconds)
{
	auto startTime = std::chrono::high_resolution_clock::now();
	unsigned int uIntNumber;
	float floatNumber;
	unsigned short UShortNumber;

	while (true)
	{
		auto currentTime = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsedSeconds = currentTime - startTime;

		if (elapsedSeconds.count() >= seconds)
		{
			cout << "Time is out" << endl;
			break;
		}

		cin >> uIntNumber;
		cin >> floatNumber;
		cin >> UShortNumber;

		addData(uIntNumber, floatNumber, UShortNumber);
	}

}



ofstream Accumulator::write_to_file()
{
	stringstream ss;
	ofstream newfile;
	newfile.open("newfile.bin", ios::binary);
	int t = 0;
	if (newfile.is_open())
	{

		for (auto i = 0; i < this->code_data.size(); i++)
		{
			auto a = bitset<1>(this->code_data[i]);
			ss << a;
		}

		string compressed = ss.str();

		vector<uint8_t> byte_array = compressByteArray(compressed);
		for (uint8_t i : byte_array)
		{
			newfile << i;
		}
		newfile.close();
	}
	return newfile;
}


void Accumulator::print_()
{
	stringstream ss;
	for (auto i = 0; i < this->code_data.size(); i++)
	{
		
		auto a = bitset<1>(this->code_data[i]);
		ss << a;
	}
	string compressed = ss.str(); //строка из цифр
	cout << compressed;
	cout << endl;
}

void Accumulator::compress(ArchInterface& interface)
{
	interface.compress(this->data, this->code_data);
}

void Accumulator::decompress(ArchInterface& interface)
{
	interface.decompress(this->code_data);
}