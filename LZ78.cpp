#include "Header.h"
using namespace std;

struct Node1 {
	int index;
	string data;
	Node1* next;
};

void st_Node(Node1* head, int index, string data)
{
	head->index = index;
	head->data = data;
	head->next = NULL;
}

void insert_Node(Node1* head, int index, string data) {
	Node1* new_Node = new Node1;
	new_Node->index = index;
	new_Node->data = data;
	new_Node->next = NULL;

	Node1* curr = head;
	while (curr != NULL)
	{
		if (curr->next == NULL)
		{
			curr->next = new_Node;
			return;
		}
		curr = curr->next;
	}
}

Node1* search_Node(Node1* head, string data)
{
	Node1* curr = head;
	while (curr != NULL)
	{
		if (data.compare(curr->data) == 0)
			return curr;
		else
			curr = curr->next;
	}
	return NULL;
}

Node1* search_Node(Node1* head, int index)
{
	Node1* curr = head;
	while (curr != NULL)
	{
		if (index == curr->index)
			return curr;
		else
			curr = curr->next;
	}
	return NULL;
}

bool delete_Node(Node1* head, Node1* to_delete) {
	if (to_delete == NULL)
		return false;
	else if (to_delete == head)
	{
		head = to_delete->next;
		delete to_delete;
		return true;
	}
	else {
		Node1* curr = head;
		while (curr)
		{
			if (curr->next == to_delete)
			{
				curr->next = to_delete->next;
				delete to_delete;
				return true;
			}
			curr = curr->next;
		}
		return false;
	}
}

vector <string> split(string str, char delimiter) {
	vector<string> internal;
	stringstream ss(str); // Turn the string into a stream.
	string tok;

	while (getline(ss, tok, delimiter)) {
		internal.push_back(tok);
	}

	return internal;
}

void LZ78::compress(string s1, vector<int>& output_code)
{
	string op = s1;
	Node1* dictionary = new Node1;
	string word, result;
	int length, last_seen, index = 1;

	length = (int)op.length();
	word = op[0];
	st_Node(dictionary, 1, word);
	result += "0," + word;

	for (int i = 1; i < length; i++)
	{
		string data;
		data = op[i];

	re_check:
		Node1* search = search_Node(dictionary, data);

		if (search)
		{
			i++;
			data += op[i];
			last_seen = search->index;
			goto re_check;
		}
		else
		{
			char zero;
			if (op[i] == ' ')
				zero = '^';
			else
				zero = op[i];

			if ((int)data.length() < 2)
				result += " " + to_string(0) + "," + zero;
			else
				result += " " + to_string(last_seen) + "," + zero;

			index++;
			if (i != length)
				insert_Node(dictionary, index, data);
		}
	}
	vector<int> res(result.begin(), result.end());
	output_code = res;
	
}

void LZ78::decompress(vector<int>& output_code)
{
	string input(output_code.begin(), output_code.end());
	Node1* dictionary = new Node1;
	string result;

	vector <string> s_input = split(input, ' ');
	int zz = 2;
	for (int i = 0; i < s_input.size(); i++)
	{
		vector <string> ss_input = split(s_input[i], ',');

		if (i == 0)
		{
			st_Node(dictionary, 1, ss_input[1]);
			result += ss_input[1];
		}
		else
		{
			Node1* serched;
			string get_search = ss_input[1];
			serched = search_Node(dictionary, stoi(ss_input[0]));
			if (serched)
			{
				result += serched->data + get_search;
				get_search = serched->data + split(s_input[i], ',')[1];
				insert_Node(dictionary, zz, get_search);
			}
			else
			{
				if (stoi(ss_input[0]) == 0)
					insert_Node(dictionary, zz, get_search);
				else
					insert_Node(dictionary, zz, get_search);

				result += get_search;
			}
			zz++;
		}
	}

	if (result[(int)result.length() - 1] == '0')
		result = result.substr(0, result.size() - 1);
	vector<int> res(result.begin(), result.end());
	output_code = res;
}




	