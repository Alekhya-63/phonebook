#include<iostream>
#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
#define int long long
#define double long double
#define inf (int)1e9
#define f first
#define s second
void start();
int manu();

class Trie {
public:
	// for signifying the end of contact.
	bool isEnd;
	// for storing the given property at the end.
	string store;
	// using hashMap for space optimisation.
	unordered_map<char, Trie*> branch;

	Trie() {
		this->isEnd = false;
	}
};

class PhoneBook {
private:
	// one trie would contain all numbers and other all names.
	Trie *TrieForNames;
	Trie *TrieForNumbers;

	// for storing all ASCII chars into a list
	vector<char> charSet;

public:
	PhoneBook() {
		// initialized NULL for each instance.
		this->TrieForNames = NULL;
		this->TrieForNumbers = NULL;

		// adding all possible representable ASCII characters
		// into a list for search operation.
		for(int i = 32 ; i < 127 ; ++i) {
			charSet.push_back((char)i);
		}
	}

	// to insert name and number into trie.
	void insert(const string &name, const string &number) {
		// base condition for name and number not NULL.
		if(name.empty() || number.empty()) {
			return;
		}

		insertByAttribute(TrieForNames, name, number);
		insertByAttribute(TrieForNumbers, number, name);
	}

	// to insert attribute in the given Trie and update it's property.
	void insertByAttribute(Trie *&root, const string &str, const string &prop) {
		if(!root) {
			root = new Trie();
		}

		// initialized to root.
		Trie *currNode = root;
		for(char c : str) {
			// if branch not found, create one.
			if(currNode->branch.count(c) == 0) {
				currNode->branch[c] = new Trie();
			}
			// Now, next branch is available so move to next branch.
			currNode = currNode->branch[c];
		}
		// indicate that a word is completed here and store it's property.
		currNode->isEnd = true;
		currNode->store = prop;
	}

	// for searching any number/name in phonebook
	void search(const string &str) {
		// if the given query string in NULL.
		if(str.empty()) return;

		vector<pair<string, string>> byName, byNumber;
		// search for prefix by name and number seperately.
		searchByAttribute(TrieForNames, str, byName);
	 	searchByAttribute(TrieForNumbers, str, byNumber);

	 	// display results.
 		cout << "Contacts Found by Name: " << byName.size() << '\n';
 		for(pair<string, string> p : byName) {
 			cout << p.first << " : " << p.second << '\n';
 		}
 		cout << "Contacts Found by Number: " << byNumber.size() << '\n';
 		for(pair<string, string> p : byNumber) {
 			cout << p.first << " : " << p.second << '\n';
 		}
	}

	// checks if a given prefix exist
	void searchByAttribute(Trie *root, const string &str, vector<pair<string, string>> &List) {
		// checks if the given Trie is empty or not
		if(!root) return;

		// for storing found prefix of the given string.
		string buffer;
		Trie *currNode = root;
		for(char c : str) {
			// if branch not found, means given prefix not found.
			if(currNode->branch.count(c) == 0) {
				break;
			}
			buffer += c;
			currNode = currNode->branch[c];
		}
		// some prefix of the given string found, now search for complete details.
		if(!buffer.empty()) {
			depthFirstSearch(currNode, List, buffer);
		}
	}

	// search for complete details for the prefix found.
	void depthFirstSearch(Trie *root, vector<pair<string, string>> &List, string curr) {
		// one such contact is found and store it.
		if(root->isEnd) {
			List.push_back({curr, root->store});
		}

		// iterate over all character set to check all possible combination
		// that can be done on the given prefix.
		for(char c : charSet) {
			// if branch exist, go and check this branch.
			if(root->branch.count(c)) {
				depthFirstSearch(root->branch[c], List, curr + c);
			}
		}
	}

	// delete contact from phonebook.
	void remove(const string &str) {
		// if the given query string is empty.
		if(str.empty()) return;

		removeByAttribute(TrieForNames, str);
		removeByAttribute(TrieForNumbers, str);
	}

	// delete contact from given trie if found.
	void removeByAttribute(Trie *&root, const string &str) {
		// if Trie is empty, no contact can be deleted;
		if(!root) return;

		// start from the root node.
		Trie *currNode = root;
		for(char c : str) {
			// if branch not found, contact with given details doesn't exist, return.
			if(currNode->branch.count(c) == 0) return;
			// Now, next branch is available so move to next branch.
			currNode = currNode->branch[c];
		}
		// mark no such word exist.
		currNode->isEnd = false;
	}
};

int32_t main()
{
	PhoneBook p;
	start();
	//ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	// Test for insetion and basic search.
	
   int check=0;
	int Total_contacts=0;
   check=manu();
    do{
	
    	if(check==1)
    	{
    		
    		cout<<"\t\t\t\t\t\t Name :";
    		string s,t;
    		cin>>s;
    		cout<<"\t\t\t\t\t\t Phone no :";
    		cin>>t;
    		p.insert(s, t);
    		Total_contacts++;
		}
		else if(check==2)
		{
			
			cout<<"\t\t\t\t\tNumber : ";
			string s;
			cin>>s;
			p.search(s);
		}
		else if(check==3)
		{
			
			cout<<"\t\t\t\t\tName : ";
			string temp;
			cin>>temp;
			p.search(temp);
		}
		else if(check==4)
		{
			
			cout<<"\t\t\t\t\tFor Delete Enter Name : ";
			string t;
			cin>>t;
			Total_contacts--;
			p.remove(t);
		}
		else if(check==5)
		{
			cout<<"\t\t\t\t\tTotal Number of contact list are : "<<Total_contacts<<endl;
		}
	
		check=manu();
	}while(check!=6);

    
	//return 0;
}

int manu()
{
	cout<<"\n";
	cout<<"\t\t\t\t\t--------------------------------------------\n";
	cout<<"\t\t\t\t\t--------------------------------------------\n";
	cout<<"\t\t\t\t\t|          PHONE BOOK APPLICATION          |\n";
	cout<<"\t\t\t\t\t--------------------------------------------\n";
	cout<<"\t\t\t\t\t|                                          |\n";
	cout<<"\t\t\t\t\t|       [1]  Add Contacts                  |\n";
	cout<<"\t\t\t\t\t|       [2]  Search by Number              |\n";
	cout<<"\t\t\t\t\t|       [3]  Search by Name                |\n";
	cout<<"\t\t\t\t\t|       [4]  delete                        |\n";
	cout<<"\t\t\t\t\t|       [5]  Number of contacts            |\n";
	cout<<"\t\t\t\t\t|                                          |\n";
	cout<<"\t\t\t\t\t--------------------------------------------\n";
	cout<<"\t\t\t\t\t|            [6]    Exite                  |\n";
	cout<<"\t\t\t\t\t--------------------------------------------\n";
	int a;
	cin>>a;
	system("cls");
	return a;
}

void start()
{
	system("Color 0B");
	cout<<"\n\n\n\n\n\n\n\n\n";
	cout<<"\t\t\t\t\t\t----------------------------\n";
	cout<<"\t\t\t\t\t\t----------------------------\n";
	cout<<"\t\t\t\t\t\tPHONE BOOK APPLICATION\n";
	cout<<"\t\t\t\t\t\t----------------------------\n\n";
	cout<<"\t\t\t\t\tLoading ";
	char x = 219;
	for(int i=0; i<35; i++)
	{
		cout<<x;
		if(i<10)
		Sleep(300);
		if(i>=10 && i<20)
		Sleep(150);
		if(i>=10)
		Sleep(25);
	}
	system("cls");
	
}



