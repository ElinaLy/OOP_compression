# OOP_compression
Проект архивации, реализованный с помощью принципов ООП

Стрим
Стрим реализован через 2 класса: Data(работа с файлами) и Accumulator(работа с потоками).
У обоих классов есть методы:
  ofstream write_to_file(); //запись в файл кодированной информации

	void print_code_data(); //печать кодированной информации

	void print_data(); //пичеть исходной информации
	
	void compress(ArchInterface& interface); // сжатие
	
	void decompress(ArchInterface& interface); //деархивация
	
У класса Accumulator есть также методы 
  void addData(unsigned int uIntNumber, float floatNumber, unsigned short UShortNumber); // добавление информации

	string getAccumulatedData(); //получение исходных данных

	void AccumulateForSeconds(float seconds); // ввод данных за определенное время


Интерфейс :
class ArchInterface {
public:
	void virtual compress(string s1, vector<int> &output_code) = 0;
	
	void virtual decompress( vector<int> &output_code) = 0;
};

Архивация реализована тремя алгоритмами: LZW, LZ78, Huffman. В class_compression рассмотрены примеры применения этих способов архивации.
