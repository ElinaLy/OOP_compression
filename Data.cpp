#include "Header.h"
using namespace std;

Data::Data()
{
	this->data = "";
	this->code_data = { 0 };
}

Data::Data(const string& filename)
{
	ifstream file_(filename);
	string str;
	if (file_.is_open())
	{
		while (!file_.eof())
		{
			getline(file_, str);
			this->data += str + '\n';
		}
		this->code_data = { 0 };
		file_.close();
	}
}

ofstream Data::write_to_file()
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


void Data::print_code_data()
{
	stringstream ss;
	for (auto i = 0; i < this->code_data.size(); i++)
	{	
		//cout << this->code_data[i]<<endl;
		auto a = this->code_data[i];
		ss << a;
	}
	string compressed = ss.str(); //строка из цифр
	cout << compressed;
	cout << endl;
}

void Data::print_data() 
{
	cout << this->data;
}


void Data::compress(ArchInterface& interface)
{
	interface.compress(this->data, this->code_data);
}

void Data::decompress(ArchInterface& interface)
{
	interface.decompress(this->code_data);
}

