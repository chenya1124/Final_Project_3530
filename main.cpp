#include "recipe.h"
#include <ctime>
#include <chrono>
using namespace std;
class userInterface
{
private:
	recipeManu menu;
	int choice;
public:
	userInterface()
	{
		cout << "-----------------------------------------------------" << endl;
		cout << "Welcome to the final project of Group 62 for COP3530!" << endl;
		cout << "     The databse includes over 2,000,000 recipes!    " << endl;
		cout << "Please select data structure for implementation: " << endl;
		cout << "1. Binary Search Tree" << endl;
		cout << "2. Sets made by hash table" << endl;
		cin >> this->choice;
		if (!userSelect(choice))
		{
			userInterface();
		};
	}
	bool userSelect(int choice)
	{
		if (choice == 1)
		{
			cout << "Please input the size of database you want to check" << endl;
			int size;
			cin >> size;
			menu.buildRecipeManu(size);
			clock_t start = clock();
			menu.buildBstIngredMap();
			clock_t end = clock();
			cout << "The time consume for insertion BST database is " << (double)(end - start) / CLOCKS_PER_SEC << " seconds" << endl;
			searchMenu(menu);
			return true;
		}
		else if (choice == 2)
		{
			cout << "Please input the size of database you want to check" << endl;
			int size;
			cin >> size;
			menu.buildRecipeManu(size);
			clock_t start = clock();
			menu.buildIngredMap();
			clock_t end = clock();
			cout << "The time consume for insertion hash table set database is " << (double)(end - start) / CLOCKS_PER_SEC << " seconds" << endl;
			searchMenu(menu);
			return true;
		}
		else if (choice == 0)
		{
			return true;
		}
		else
		{
			cout << "Invalid input, please retype 1 or 2" << endl;
			return false;
		}
	}
	void searchMenu(recipeManu inserted)
	{
		cout << "Please list the name of ingredients you want to search: " << endl;
		string input;
		cin >> input;
		if (this->choice == 1)
		{
			auto start = std::chrono::high_resolution_clock::now();
			Node* temp = menu.search(menu.getRoot(), input);
			auto elapsed = std::chrono::high_resolution_clock::now() - start;
			long long microseconds = chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
			cout << "The time consume for searching " << input << " in BST database is " << microseconds << " microseconds" << endl;
			
			if (temp != NULL)
			{
				vector<string> curVec = temp->dish;
				cout << "There are " << curVec.size() << " items found, do you want to see the result? 1.Yes 2. No" << endl;
				int c;
				cin >> c;
				if (c == 1) 
				{
				cout << "There are " << curVec.size() << " that can made by " << input << endl;
				for (int i = 0; i < curVec.size(); i++)
				{
					cout << curVec[i] << ", ";
				}
				cout << endl;
				}
			}
		}
		if (this->choice == 2)
		{
			unordered_map<string, vector<string>> cur = menu.getIngredMap();
			auto start = std::chrono::high_resolution_clock::now();
			auto itr = cur.find(input);
			auto elapsed = std::chrono::high_resolution_clock::now() - start;
			long long microseconds = chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
			if (itr == cur.end())
			{
				cout << "Does not exist" << endl;
			}
			cout << "The time consume for searching " << input << " in hash map database is " << microseconds << " microseconds" << endl;
			if (itr != cur.end())
			{
				vector<string> curVec = itr->second;
				cout << "There are " << curVec.size() << " items found, do you want to see the result? 1.Yes 2. No" << endl;
				int c;
				cin >> c;
				if (c == 1)
				{
					for (int i = 0; i < curVec.size(); i++)
					{
						cout << curVec[i] << ", ";
					}
					cout << endl;
				}
			}
		}
		cout << "1. Create a new database" << endl;
		cout << "2. Searching a new item" << endl;
		cout << "0. Exist" << endl;
		int newChoice;
		cin >> newChoice;
		if (newChoice == 1)
		{
			userInterface();
		}
		else if (newChoice == 2)
		{
			searchMenu(menu);
		}
		else if (newChoice == 0)
		{
			return;
		}
	}
};
void main()
{
	userInterface();
}