// Source(s) of logic assistance:  
// Gaddis, T. (2018). Starting out with C++:
// From control structures through objects. Pearson. 
// https://www.geeksforgeeks.org/cpp-program-for-double-to-string-conversion/

#include <iostream> // To use cin/cout
#include <iomanip>  // To access setw, setprecision for output width
#include <string>   // To implement to_string, getline functions
#include <fstream>  // To utilize ifstream, ofstream, fstream
#include <sstream>  // To use ostringstream to convert double to string
#include <ctime>    // To access random number generator
#include <vector>   // To use vector (dynamically sized form of array)
using namespace std;

// Global Constant Initialization
const string TITLE = "Inventory Vector Builder Program";
const string AUTHOR_LINE = "By Forrest Moulin";

// Declare struct for item object
struct Item
{	// Item structure variables
	string partNumber;
	char partType;
	int quantity;
	double unitCost;
};

// Function prototypes to notify compiler
string itemToStr(Item invItem);
int displayMenu();
bool readFile(vector<Item>& inventory, ifstream& fin, string inputFilePath);
double getTotalInvCost(const vector <Item> inventory);
void showQtyByPartType(const vector <Item> inventory,
	vector <int> partTypeCounts);
void displayCounts(const vector <int>& partTypeCounts);
double getCostOfPartType(char partType, const vector <Item>& inventory);
string getHighestCost(const vector <Item>& inventory, double& highCost);
string getLowestCost(const vector <Item>& inventory, double& lowCost);

int main()
{	
	cout << fixed << setprecision(2) << TITLE << endl
		<< AUTHOR_LINE << endl << endl;

	// Dynamic Variable Initialization
	int displaySelection;
  // File directory
	string inputFilePath = "C:\\Users\\UserName\\Path\\To\\Directory";
	// File name appended
  inputFilePath += "InventoryParts.txt";
	bool keepLooping = true;

	// Create input file stream object
	ifstream fin;
	// Inventory object is vector of multiple item structs
	vector<Item> inventory;
	// Vector size initialized as 6 (A, B, C, D, E, F)
	vector<int> partTypeCounts(6);
	bool fileRead;
	double totalInvCost = 0, costOfPartType = 0, 
		lowCost = 0, highCost = 0;
	char partType = ' ';

	// Open file using file path string
	fin.open(inputFilePath);

	// Read the file with custom function
	fileRead = readFile(inventory, fin, inputFilePath);
	// Keep looping until bool changed to false
	while (keepLooping)
	{	// Display selection is read from displayMenu() function
		displaySelection = displayMenu();
		switch (displaySelection) 
		{
		case 1:
			// Calculate total inventory cost
			totalInvCost = getTotalInvCost(inventory);
			break;
		case 2:
			// Show quantity of each part type/category
			showQtyByPartType(inventory, partTypeCounts);
			break;
		case 3:
			// Show the cost of a specific part type/category
			costOfPartType = getCostOfPartType(partType, inventory);
			break;
		case 4:
			// Display highest valued inventory part and its cost
			cout << "You selected 4: Part with highest inventory cost" << endl
				<< endl << left << setw(25) << "Highest total item cost:"
				<< endl << getHighestCost(inventory, highCost)
				<< ", $" << highCost << endl << endl;
			break;
		case 5:
			// Display lowest valued inventory part and its cost
			cout << "You selected 5: Part with lowest inventory cost" << endl
				<< endl << left << setw(25) << "Lowest total item cost:"
				<< endl << getLowestCost(inventory, lowCost)
				<< ", $" << lowCost << endl << endl;
			break;
		case 6:
			// Exit the program
			cout << "You selected 6: Exit program" <<
				endl << "Exiting the program. Until next time!: )" << endl;
			keepLooping = false;
			fin.close();
			return 0;
			break;
		default:
			// Error message in case wrong selection entered
			cout << "Invalid menu selection. Please run the program and try again." 
				<< endl;
			fin.close();
			return 0;
		}
	}
}
bool readFile(vector<Item>& inventory, ifstream& fin,
	string inputFilePath)
{
	bool fileRead = true;
	string partNumberRead;
	char partTypeRead;
	int quantityRead;
	double unitCostRead;
	Item structureRead;
	// End program in event of file read failure
	if (fin.fail())
	{
		cout << "File open failure:" << endl
			<< inputFilePath << endl;
		fin.close();
		fileRead = false;
	}
	cout << "InventoryParts.txt read successfully!" << endl << endl;

	// While input file still contains inventory data on each line
	while (fin >> partNumberRead >> partTypeRead >> quantityRead >> unitCostRead)
	{	// Build the item struct with read data
		structureRead.partNumber = partNumberRead;
		structureRead.partType = partTypeRead;
		structureRead.quantity = quantityRead;
		structureRead.unitCost = unitCostRead;
		inventory.push_back(structureRead);
	}
	// Close the file once reading completed
	fin.close();

	for (int i = 0; i < inventory.size(); i++)
	{
		cout << itemToStr(inventory[i]) << endl;
	}
	cout << endl;
	// Return boolean value (true if read successfully)
	return fileRead;
}
string itemToStr(Item invItem)
{
	// Read the double to string using ostringstream
	// for formatting/building the string
	ostringstream strStream;

	strStream << invItem.partNumber << "  ";
	strStream << invItem.partType << " ";
	strStream << right << setw(3)
		<< invItem.quantity << "  ";
	strStream <<  right << setw(6) << invItem.unitCost;
	strStream.clear();
	// Return the string from string stream
	return strStream.str();
}
int displayMenu()
{
	int menuSelection = 0;
	cout << "FORREST'S GREEN INVENTORY MENU"
		<< endl << "Please enter the number of your menu selection below:"
		<< endl << "1. Total inventory cost"
		<< endl << "2. Quantity by part type"
		<< endl << "3. Total cost of part type"
		<< endl << "4. Part with higest inventory cost"
		<< endl << "5. Part with lowest inventory cost"
		<< endl << "6. Exit program" << endl << endl;
	cin >> menuSelection;
	return menuSelection;	
}
double getTotalInvCost(const vector <Item> inventory)
{
	double totalInvCost = 0;
	for (int i = 0; i < inventory.size(); i++)
	{	// Add cost of each item to total
		totalInvCost +=
			inventory[i].unitCost * inventory[i].quantity;
	}
	cout << "You selected 1:" << endl 
		<< "The total cost of inventory is $" << totalInvCost
		<< endl << endl;
	return totalInvCost;
}
void showQtyByPartType(const vector <Item> inventory,
	vector <int> partTypeCounts)
{
	for (int i = 0; i < inventory.size(); i++)
	{
		if (inventory[i].partType == 'A')
		{
			partTypeCounts[0]++;
		}
		else if (inventory[i].partType == 'B')
		{
			partTypeCounts[1]++;
		}
		else if (inventory[i].partType == 'C')
		{
			partTypeCounts[2]++;
		}
		else if (inventory[i].partType == 'D')
		{
			partTypeCounts[3]++;
		}
		else if (inventory[i].partType == 'E')
		{
			partTypeCounts[4]++;
		}
		else if (inventory[i].partType == 'F')
		{
			partTypeCounts[5]++;
		}
	}
	cout << "You selected 2: Quantity by part type" << endl;
	displayCounts(partTypeCounts);
}
double getCostOfPartType(char partType, const vector <Item>& inventory)
{
	cout << "You selected 3: Total cost of part type"
		<< endl << "Please enter the character for the part type"
		<< endl << "(Choice of character A-F)" << endl;
	cin >> partType;
	double costOfPartType = 0;
	for (int i = 0; i < inventory.size(); i++)
	{	// If vector item part type matches val entered by user
		if (inventory[i].partType == partType
			|| inventory[i].partType == toupper(partType))
		{	// Calculate the cost of the matching part type
			costOfPartType +=
				inventory[i].quantity * inventory[i].unitCost;
		}
	}
	cout << endl << "Part type " << partType
		<< " inventory cost: " << "$" << costOfPartType 
		<< endl << endl;
	return costOfPartType;
}
string getHighestCost(const vector <Item>& inventory, double& highCost)
{
	string highStr = "";
	for (int i = 0; i < inventory.size(); i++)
	{	// Set first value as highest cost
		if (i == 0)
		{	
			highCost =
				inventory[0].quantity * inventory[0].unitCost;
		}
		// Then compare values on each iteration to find highest
		else if ((inventory[i].quantity * inventory[i].unitCost) 
		> highCost) {
			// Keep track of high cost/string values
			highCost = inventory[i].quantity * inventory[i].unitCost;
			highStr = inventory[i].partNumber;
		}
	}
	return "Part " + highStr;
}
string getLowestCost(const vector <Item>& inventory, double & lowCost)
{
	string lowStr = "";
	for (int i = 0; i < inventory.size(); i++)
	{	// Set first value as lowest cost
		if (i == 0)
		{
			lowCost =
				inventory[0].quantity * inventory[0].unitCost;
		}
		// Then compare values on each iteration to find lowest
		else if ((inventory[i].quantity * inventory[i].unitCost)
	< lowCost) {
			// Keep track of low cost/string values
			lowCost = inventory[i].quantity * inventory[i].unitCost;
			lowStr = inventory[i].partNumber;
		}
	}
	return "Part " + lowStr;
}
void displayCounts(const vector <int>& partTypeCounts)
{
	cout << endl << left << setw(6) << "A"
		<< partTypeCounts[0] << endl
		<< left << setw(6) << "B"
		<< partTypeCounts[1] << endl
		<< left << setw(6) << "C"
		<< partTypeCounts[2] << endl
		<< left << setw(6) << "D"
		<< partTypeCounts[3] << endl
		<< left << setw(6) << "E"
		<< partTypeCounts[4] << endl
		<< left << setw(6) << "F"
		<< partTypeCounts[5] << endl << endl;
}
/*
* CONSOLE OUTPUT
* Inventory Vector Builder Program
* By Forrest Moulin
*
* InventoryParts.txt read successfully!
*
* P-39457  A  16  102.14
* P-11702  B  21   24.74
* P-11754  B  27   15.23
* P-12009  D   3    12.8
* P-12131  A  48   24.17
* P-12385  B  41   27.33
* P-12652  E  18   28.33
* P-12677  D  15   26.59
* ...
*
* FORREST'S GREEN INVENTORY MENU
* Please enter the number of your menu selection below:
* 1. Total inventory cost
* 2. Quantity by part type
* 3. Total cost of part type
* 4. Part with higest inventory cost
* 5. Part with lowest inventory cost
* 6. Exit program
* 
* 1
* You selected 1:
* The total cost of inventory is $342965.70
*
* FORREST'S GREEN INVENTORY MENU
* Please enter the number of your menu selection below:
* 1. Total inventory cost
* 2. Quantity by part type
* 3. Total cost of part type
* 4. Part with higest inventory cost
* 5. Part with lowest inventory cost
* 6. Exit program
*
* 2
* You selected 2: Quantity by part type
*
* A     85
* B     69
* C     77
* D     60
* E     5
* F     8
*
* FORREST'S GREEN INVENTORY MENU
* Please enter the number of your menu selection below:
* 1. Total inventory cost
* 2. Quantity by part type
* 3. Total cost of part type
* 4. Part with higest inventory cost
* 5. Part with lowest inventory cost
* 6. Exit program
*
* 3
* You selected 3: Total cost of part type
* Please enter the character for the part type
* (Choice of character A-F)
* C
*
* Part type C inventory cost: $50322.30
*
* FORREST'S GREEN INVENTORY MENU
* Please enter the number of your menu selection below:
* 1. Total inventory cost
* 2. Quantity by part type
* 3. Total cost of part type
* 4. Part with higest inventory cost
* 5. Part with lowest inventory cost
* 6. Exit program
*
* 4
* You selected 4: Part with highest inventory cost
*
* Highest total item cost:
* Part P-27850, $8329.22
*
* FORREST'S GREEN INVENTORY MENU
* Please enter the number of your menu selection below:
* 1. Total inventory cost
* 2. Quantity by part type
* 3. Total cost of part type
* 4. Part with higest inventory cost
* 5. Part with lowest inventory cost
* 6. Exit program
*
* 5
* You selected 5: Part with lowest inventory cost
*
* Lowest total item cost:
* Part P-30538, $2.86
*
* FORREST'S GREEN INVENTORY MENU
* Please enter the number of your menu selection below:
* 1. Total inventory cost
* 2. Quantity by part type
* 3. Total cost of part type
* 4. Part with higest inventory cost
* 5. Part with lowest inventory cost
* 6. Exit program
*
* 6
* You selected 6: Exit program
* Exiting the program. Until next time!: )
*/
