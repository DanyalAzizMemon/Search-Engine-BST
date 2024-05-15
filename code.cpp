#include <fstream>		//library for file handling
#include <sstream>		//library used for word by word traversal in a sentence
#include <iostream>
#include <string>		//string functions used
using namespace std;

struct Tree 
{
	Tree* left;
	Tree* right;
	string keyword;
	string URL;
	int count;
};

struct bstinfo 
{
	string keyword;
	string URL;
	int count=0;	//to allocate size for URL
};


//----------------------------------------------------------------------------functions for trees

void insert(Tree* root, bstinfo obj)
{
	if (root == NULL)
	{
		root = new Tree;
		root->URL = obj.URL;
		root->keyword = obj.URL;
		root->count = 0;
		root->right = NULL;
		root->left = NULL;
	}
	else
	{
		Tree* x, * y;
		x = y = root;
		while (y != NULL)
		{
			if (y->URL == obj.URL && y->keyword == obj.keyword)		//if equal
			{
				y->count++;
				return;
			}

			else if (obj.keyword < y->keyword)		//if less then we go to left
			{
				x = y;
				y = y->left;
			}

			else if (obj.keyword > y->keyword)		//if greater then we go to right
			{
				x = y;
				y = y->right;
			}
		}

		Tree* temp = new Tree;			//new tree added
		temp->URL = obj.URL;
		temp->keyword = obj.keyword;
		temp->count = obj.count;
		temp->right = NULL;
		temp->left = NULL;

		if (obj.keyword < x->keyword)
		{
			x->left = temp;
		}
		else if (obj.keyword > x->keyword)
		{
			x->right = temp;
		}
	}
}



void search(Tree* root, string keyword)
{
	bool found = 0;
	if (root == NULL)
	{
		cout << "\nTree does not contain any data ";
		return;
	}
	else
	{
		Tree* x, * y;
		x = y = root;
		while (y != NULL)
		{
			if (y->keyword == keyword)
			{
				cout << "Word found\n Keyword : " << y->keyword << "\n" << y->URL;
				found = 1;
				return;
			}

			else if (keyword < y->keyword)
			{
				x = y;
				y = y->left;
			}

			else if (keyword > y->keyword)
			{
				x = y;
				y = y->right;
			}
		}

		if (!found)
			cout << "Word not found in tree ";
	}
}




void remove(Tree*& node)	//used to delete the node specified by deletenode function
{
	Tree* temp;

	if (node->right == NULL)
	{
		temp = node;
		node = node->left;
		delete temp;
	}

	else if (node->left == NULL)
	{
		temp = node;
		node = node->right;
		delete temp;
	}

	else
	{
		temp = node->right;
		while (temp->left)
			temp = temp->left;
	}

	temp->left = node->left;
	temp = node;
	node = node->right;
	delete temp;
}








void inorder(Tree* root)//inorder display through reccursion order(left,root,right)
{
	if (root != NULL) 
	{
		inorder(root->left);
		cout << root->keyword << "\nNumber of times repeated : " << root->count << endl << root->URL << endl << endl;
		inorder(root->right);
	}
}

void preorder(Tree* root)//pre order (root,left,right)
{
	if (root != NULL)
	{

		cout << root->keyword << "\nNumber of times repeated : " << root->count << endl << root->URL << endl << endl;
		preorder(root->left);
		preorder(root->right);
	}
}

void postorder(Tree* root)//post order (left,right,root)
{
	if (root != NULL)
	{
		postorder(root->left);
		postorder(root->right);
		cout << root->keyword << "\nNumber of times repeated : " <<root->count << endl << root->URL << endl << endl;
	}
}


void deletenode(string s, Tree*& node)//traversing to the specific root containing the string s
{
	if (node == NULL)
		cout << s << "is not present in tree ";
	else if (s < node->keyword)
		deletenode(s, node->left);
	else if (s > node->keyword)
		deletenode(s, node->right);
	else
		remove(node);

	inorder(node);		//printing the new tree after deletion
	cout << "\n\n\nAbove is the tree after deleting : '" << s << "' using in order traversal" << endl << endl;


}


void count_words(string keywords[], int &count)			//counting the words present in all sentences
{
	string temp;
	for (int i = 0; i < 54; i++) 
	{
		istringstream a(keywords[i]);
		while (a >> temp) 
		{
			count++;
		}
	}


}



int main()
{
	string URL[55], keywords[55];
	int ID[55];
	string temp;
	ifstream file;

	int choice = 0;

	string filename;
	label123:
	cout << "\nEnter name of the file you want to open : ";
	cin >> filename;
	file.open(filename, ios::in);
	//file.open("Assignment_Data.txt", ios::in);
	if (!file)
	{
		cout << "\nFile not created";
		goto label123;
	}
	else
	{
		cout << "\nFile created ";
		for (int i = 0; !file.eof(); i++)				//reading elements of file into the arrays
		{
			file >> ID[i];
			getline(file, URL[i], '\n');
			getline(file, keywords[i], '\n');
		}
	}
	file.close();




	while (choice < 4) 
	{
		cout << "\n---------------------------------TASK 1---------------------------------\nPress 1 to read file contents\nPress 2 to find keywords\npress 3 to exit\nEnter your choice : ";
		cin >> choice;

	
		if (choice == 1) 
		{
			for (int i = 0; i < 54; i++)
				cout << ID[i] << " " << URL[i] << endl<< keywords[i] << endl <<endl;
		}

		if (choice == 2) 
		{
			string word;
			cout << "\nEnter the word you want to search for : ";
			cin >> word;
		
			bool found = 0;
			for (int i = 0; i<54; i++) 
			{
				found = keywords[i].find(word) != string::npos;
				if (found) 
					cout << URL[i] << endl;
			}
	
		}

		if (choice == 3) 
			break;
		
	}
	//-------------------------------------------------------------------------------------------------------------------------------|
	//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	//-------------------------------------------------------------------------------------------------------------------------------|
	//														TASK 2


	//reading the sentences word by word
	//the identical words will be separated later on in BST
	int count = 0;
	count_words(keywords,count);
	


	bstinfo *nodedata = new bstinfo[count];



	//copying each word into node data
	int j = 0;  //for while loop
	for (int i = 0; i < 54; i++)
	{
		istringstream a(keywords[i]);
		while (a >> temp)
		{
			//words[j] = temp;
			nodedata[j].keyword = temp;
			j++;
		}
	}

	//searching for how many times the keyword occur in each line to allocate a specific URL array size
	for (int f = 0; f < count; f++) 
	{
		string word = nodedata[f].keyword;

		bool found = 0;
		for (int i = 0; i < 54; i++)
		{
			found = keywords[i].find(word) != string::npos;
			if (found)
				nodedata[f].count++;
		}

		for (int i = 0; i < 54; i++)
		{
			found = keywords[i].find(word) != string::npos;
			if (found) 
			{
				nodedata[f].URL = URL[i];
				/*	for (int z = 0; z < count; z++)
				{
					if (nodedata[z].keyword == nodedata[f].keyword && nodedata[z].URL != nodedata[f].URL)
					{	
						cout << "Reached";
						nodedata[f].URL = URL[i];
						break;
					}

					else if (nodedata[z].keyword == nodedata[f].keyword && nodedata[z].URL == nodedata[f].URL) 
						continue;
				}
				continue;*/
			}
		}

	}


	
	//creation of tree; which would be used as root
	Tree* root = new Tree;
	root->keyword = nodedata[0].keyword;
	root->URL = nodedata[0].URL;
	root->count =nodedata[0].count;
	root->right = NULL;
	root->left = NULL;
	for (int i = 0; i < count; i++)
			insert(root, nodedata[i]);

	while (choice != 4) 
	{
		Tree* temp = root;
		cout << "\n---------------------------------TASK 2---------------------------------\nPress 1 to display tree contents\nPress 2 to search keywords\npress 3 to delete keywords\nPress 4 to exit\nEnter your choice : ";
		cin >> choice;

		if (choice == 1) //printing using inorder,preorder or postorder
		{
			int choice2;
			
			cout << "\n\nPress 1 to display tree inorder\nPress 2 to display tree preorder\nPress 3 to display tree postorder\nEnter your choice : ";
			cin >> choice2;

			switch (choice2) 
			{
			case 1:
				inorder(temp);
				break;

			case 2:
				preorder(temp);
				break;

			case 3:
				postorder(temp);
				break;

			default:
				cout << "\nInvalid Input entered ";
				break;
			}
		
		}


		if (choice == 2) //calling search 
		{
			string word;
			cout << "\nEnter the word you want to search for : ";
			cin >> word;
			search(temp,word);

		}

		if (choice == 3)	//calling deletion
		{
			string s;
			cout << "\nEnter the word you want to remove : ";
			cin >> s;
			deletenode(s, temp);			
		}

		if (choice == 4)
		{
			break;
		}

	}

}
