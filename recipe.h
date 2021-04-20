#pragma once
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <algorithm>
#include <map>
#include <iomanip>
#include <string.h>
#include <stdlib.h>

using namespace std;
class recipe {
private:
	string name;
	int id;
	int min;
	int conId;
	string nutrition;
	string submitted;
	string tags;
	string steps;
	string ingredients;
	vector<string> ingreVec;
public:
	recipe() {}
	void setName(string name) { this->name = name; }
	void setId(int id) { this->id = id; }
	void setMin(int min) { this->min = min; }
	void setNutrition(string nutr) { this->nutrition = nutr; }
	void setConId(int conId) { this->conId = conId; }
	void setSubmmitted(string submitted) { this->submitted = submitted; }
	void setTags(string tags) { this->tags = tags; }
	void setIngredients(string ingredients) { this->ingredients = ingredients; }
	void setSteps(string steps) { this->steps = steps; }
	void splitIngredients()
	{
		vector<string> result;
		string temp = ingredients;
		temp = temp.substr(1, temp.size() - 2);
		//cout << temp << endl;
		string ingred;
		stringstream ss(temp);
		while (getline(ss, ingred, ' '))
		{
			ingred.erase(remove(ingred.begin(), ingred.end(), '\''), ingred.end());
			result.push_back(ingred);
			//cout << ingred << endl;
		}
		ingreVec = result;
	}
	vector<string> getIngreVec() { return ingreVec; }
	string getName() { return name; }
	string getIngredients() { return ingredients; }
};
struct Node
{
	vector<string> dish;
	string ingred;
	Node* left;
	Node* right;
	Node() { left = NULL; right = NULL; }
	Node(string ingred) { this->ingred = ingred; left = NULL; right = NULL;}
	Node(string ingred, string dishName) { this->ingred = ingred; this->dish.push_back(dishName); left = NULL; right = NULL;}
	Node(string ingred, vector<string> val, Node* l, Node* r) { this->ingred = ingred; this->dish = val; left = l; right = r; }
};
class recipeManu
{
private:
	vector<recipe> menu;
	unordered_map<string, vector<string>> ingredMap;
	map <string, vector<string>> ingredMap2;
	Node* root = NULL;
public:
	recipeManu() {}
	void buildIngredMap()
	{
		for (int i = 0; i < menu.size(); i++)
		{
			vector<string> temp = menu[i].getIngreVec();
			for (int j = 0; j < temp.size(); j++)
			{
				//cout << temp[j] << endl;
				ingredMap[temp[j]].push_back(menu[i].getName());
			}
		}
	};
	void buildRecipeManu(int size)
	{
		ifstream inFile("RAW_recipes.csv", ios::in);
		int i = 0;
		string line;
		string field;
		getline(inFile, line);
		while (getline(inFile, line) && i < size)
		{
			recipe cur;
			string name;
			string id;
			string min;
			string conId;
			string submitted;
			string tags;
			string nutrition;
			string steps;
			string ingredients;
			istringstream sin(line);
			getline(sin, name, ',');
			cur.setName(name);
			//cout << name.c_str() << endl;
			getline(sin, id, ',');
			cur.setId(stoi(id));
			//cout << id.c_str() << endl;
			getline(sin, min, ',');
			cur.setMin(stoi(min));
			//cout << min.c_str() << endl;
			getline(sin, conId, ',');
			cur.setConId(stoi(conId));
			//cout << conId.c_str() << endl;
			getline(sin, submitted, ',');
			cur.setSubmmitted(submitted);
			//cout << submitted.c_str() << endl;
			getline(sin, tags, ',');
			cur.setTags(tags);
			//cout << tags.c_str() << endl;
			getline(sin, nutrition, ',');
			cur.setNutrition(nutrition);
			//cout << nutrition.c_str() << endl;
			getline(sin, steps, ',');
			cur.setSteps(steps);
			//cout << steps.c_str() << endl;
			getline(sin, ingredients);
			int num = count(ingredients.begin(), ingredients.end(), ',');
			ingredients = ingredients.substr(0, ingredients.size() - num );
			cur.setIngredients(ingredients);
			//cout << ingredients << endl;
			i++;
			cur.splitIngredients();
			menu.push_back(cur);
		}
		inFile.close();
	}
	void buildBstIngredMap()
	{
		for (int i = 0; i < menu.size(); i++)
		{
			vector<string> temp = menu[i].getIngreVec();
			for (int j = 0; j < temp.size(); j++)
			{
				root = insert(root, temp[j], menu[i].getName());
			}
		}
	}
	//vector<string> splitIngre(string ingredients)
	//{
	//	//vector<string> result;
	//	//string temp = ingredients;
	//	//temp = temp.substr(1, temp.size() - 2);
	//	////cout << temp << endl;
	//	//string ingred;
	//	//stringstream ss(temp);
	//	//while (getline(ss, ingred, ' '))
	//	//{
	//	//	ingred.erase(remove(ingred.begin(), ingred.end(), '\''), ingred.end());
	//	//	result.push_back(ingred);
	//	//	//cout << ingred << endl;
	//	//}
	//	//return result;
	//}
	vector<recipe> getMenu() { return menu; }
	unordered_map<string, vector<string>> getIngredMap() { return ingredMap; }
	vector<string> Union(vector<string> v1, vector<string> v2) {
		vector<string> result;
		sort(v1.begin(), v1.end());
		sort(v2.begin(), v2.end());
		set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(result));
		return result;
	}
	vector<string> Intersection(vector<string> v1, vector<string> v2) {
		vector<string> result;
		sort(v1.begin(), v1.end());
		sort(v2.begin(), v2.end());
		set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(result));
		return result;
	}
	vector<string> difference(vector<string> v1, vector<string> v2) {
		vector<string> result;
		sort(v1.begin(), v1.end());
		sort(v2.begin(), v2.end());
		set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(result));
		return result;
	}
	Node* search(Node* node, string key)
	{
		//cout << node->ingred << endl;
		if (node == NULL)
		{
			cout << "does not exist" << endl;
			return node;
		}
		if (node->ingred == key)
		{
			cout << "searched result " << node->ingred << endl;
			return node;
		}
		else if (key.compare(node->ingred) > 0)
		{
			return search(node->right, key);
		}
		else if(key.compare(node->ingred) < 0)
		{
			return search(node->left, key);
		}
	}
	Node* insert(Node* node, string ingred, string dish)
	{
		if (node == NULL)
		{
			Node* temp = new Node(ingred, dish);
			return temp;
		}
		else if (node->ingred == ingred)
		{
			node->dish.push_back(dish);
		}
		else
		{
			if (ingred.compare(node->ingred) > 0)
			{
				//cout << ingred << endl;
				//cout << node->ingred <<  " should be smaller" << endl;
				node->right = insert(node->right, ingred, dish);
			}
			else if (ingred.compare(node->ingred) < 0)
			{
				node->left = insert(node->left, ingred, dish);

			}
			else
			{
				node->dish.push_back(dish);
			}
		}
		return node;
	}
	Node* getRoot() { return root; }
};
