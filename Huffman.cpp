
#include "Header.h"


using namespace std;

struct Node
{
	char ch;
	int freq;
	Node* left, * right;
};

Node* getNode(char ch, int freq, Node* left, Node* right)
{
	Node* node = new Node();

	node->ch = ch;
	node->freq = freq;
	node->left = left;
	node->right = right;

	return node;
}

struct comp
{
	bool operator()(Node* l, Node* r)
	{
		// highest priority item has lowest frequency
		return l->freq > r->freq;
	}
};


void encode(Node* root, string str,
	unordered_map<char, string>& huffmanCode)
{
	if (root == nullptr)
		return;

	// found a leaf node
	if (!root->left && !root->right) {
		huffmanCode[root->ch] = str;
	}

	encode(root->left, str + "0", huffmanCode);
	encode(root->right, str + "1", huffmanCode);
}

void decode(Node* root, int& index, string str)
{
	if (root == nullptr) {
		return;
	}

	// found a leaf node
	if (!root->left && !root->right)
	{
		cout << root->ch;
		return;
	}

	index++;

	if (str[index] == '0')
		decode(root->left, index, str);
	else
		decode(root->right, index, str);
}

string buildHuffmanTree_encoding(string text)
{
	unordered_map<char, int> freq;
	for (char ch : text) {
		freq[ch]++;
	}

	priority_queue<Node*, vector<Node*>, comp> pq;

	for (auto pair : freq) {
		pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
	}

	while (pq.size() != 1)
	{
		Node* left = pq.top(); pq.pop();
		Node* right = pq.top();	pq.pop();

		int sum = left->freq + right->freq;
		pq.push(getNode('\0', sum, left, right));
	}

	Node* root = pq.top();

	unordered_map<char, string> huffmanCode;
	encode(root, "", huffmanCode);

	//cout << "Huffman Codes are :\n" << '\n';
	/*for (auto pair : huffmanCode) {
		cout << pair.first << " " << pair.second << '\n';
	}*/

	//cout << "\nOriginal string was :\n" << text << '\n';

	// print encoded string
	string str = "";
	for (char ch : text) {
		str += huffmanCode[ch];
	}

	//cout << "\nEncoded string is :\n" << str << '\n';

	int index = -1;
	
	return str;
}


string buildHuffmanTree_decoding(string text)
{
	unordered_map<char, int> freq;
	for (char ch : text) {
		freq[ch]++;
	}

	priority_queue<Node*, vector<Node*>, comp> pq;

	for (auto pair : freq) {
		pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
	}

	while (pq.size() != 1)
	{
		Node* left = pq.top(); pq.pop();
		Node* right = pq.top();	pq.pop();

		int sum = left->freq + right->freq;
		pq.push(getNode('\0', sum, left, right));
	}

	Node* root = pq.top();

	unordered_map<char, string> huffmanCode;
	encode(root, "", huffmanCode);

	//cout << "Huffman Codes are :\n" << '\n';
	/*for (auto pair : huffmanCode) {
		cout << pair.first << " " << pair.second << '\n';
	}*/

	//cout << "\nOriginal string was :\n" << text << '\n';

	// print encoded string
	string str = "";
	for (char ch : text) {
		str += huffmanCode[ch];
	}

	//cout << "\nEncoded string is :\n" << str << '\n';

	int index = -1;
	//cout << "\nDecoded string is: \n";
	while (index < (int)str.size() - 2) {
		decode(root, index, str);
	}

	return str;
}


void Huffman::compress(string s1, vector<int>& output_code) 
{
	string result = buildHuffmanTree_encoding(s1);
	vector<int> res(result.begin(), result.end());
	output_code = res;

	
}

void Huffman::decompress(vector<int>& output_code) 
{
	
	string s1(output_code.begin(), output_code.end());
	string res = buildHuffmanTree_decoding(s1);
	vector<int> temp(res.begin(), res.end());
	output_code = temp;

}
