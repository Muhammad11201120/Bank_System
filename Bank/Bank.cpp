#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>

using namespace std;
enum enOptions
{
	showList = 1, addList = 2, deletList = 3, updateList = 4, findList = 5, transactions = 6, Exit = 7
};
struct stAccountData {
	string accountNumber;
	string pinCode;
	string name;
	string phone;
	string accountBalance;
	bool deleteFlag = false;
};
enum enTransactions
{
	deposit = 1, withdrow = 2, totalBalance = 3, MainMenue = 4
};
bool checkIfClientAccountNumberIsAlreadyTaken(string accountNumber, string flieName);
void pages(enOptions choice);
stAccountData readRecord()
{
	stAccountData record;
	cout << "Enter Account Number: ";
	getline(cin >> ws, record.accountNumber);
	while (checkIfClientAccountNumberIsAlreadyTaken(record.accountNumber, "clinet_Data_File.txt"))
	{
		cout << "\nClient With [ " << record.accountNumber << " ] is Already Exist, Enter Another Account Number." << endl;
		getline(cin >> ws, record.accountNumber);
	}
	cout << "Enter Pin Code: ";
	getline(cin >> ws, record.pinCode);
	cout << "Enter Name: ";
	getline(cin >> ws, record.name);
	cout << "Enter Phone: ";
	getline(cin >> ws, record.phone);
	cout << "Enter Account Balance: ";
	getline(cin >> ws, record.accountBalance);
	return record;
}
stAccountData readToUpdateRecord()
{
	stAccountData record;
	cout << "Enter Pin Code: ";
	getline(cin >> ws, record.pinCode);
	cout << "Enter Name: ";
	getline(cin >> ws, record.name);
	cout << "Enter Phone: ";
	getline(cin >> ws, record.phone);
	cout << "Enter Account Balance: ";
	getline(cin >> ws, record.accountBalance);
	return record;
}
void drowHeader()
{
	cout << "\n\t\t\t\t\t Client List" << endl;
	cout << "\n__________________________________________________________________________________________________\n"
		<< endl;
	cout << "|" << left << setw(15) << "Account Number ";
	cout << "|" << left << setw(10) << "Pin Code ";
	cout << "|" << left << setw(40) << "Name ";
	cout << "|" << left << setw(12) << "Phone ";
	cout << "|" << left << setw(12) << "Account Balance";
	cout << "\n__________________________________________________________________________________________________\n"
		<< endl;
}void drowBalancesScreenHeader()
{
	cout << "\n\t\t\t\t\t Client List" << endl;
	cout << "\n__________________________________________________________________________________________________\n"
		<< endl;
	cout << "|" << left << setw(15) << "Account Number ";
	cout << "|" << left << setw(40) << "Name ";
	cout << "|" << left << setw(12) << "Account Balance";
	cout << "\n__________________________________________________________________________________________________\n"
		<< endl;
}
void drowFooter()
{
	cout << "\n__________________________________________________________________________________________________\n"
		<< endl;
}

void performTransaction(enTransactions options);
short showTransactionsOptions();
short mainMenue() {
	system("cls"); // system("clear");
	short choice = 0;
	cout << "\n-------------------------------------------------------\n";
	cout << "\t\t\t MAIN MENUE\n";
	cout << "-------------------------------------------------------\n";
	cout << "\t[1]=> Show Clients" << endl;
	cout << "\t[2]=> Add New Client" << endl;
	cout << "\t[3]=> Delete Client" << endl;
	cout << "\t[4]=> Update Client" << endl;
	cout << "\t[5]=> Find Client" << endl;
	cout << "\t[6]=> Transactions" << endl;
	cout << "\t[7]=> Exit";
	cout << "\n-------------------------------------------------------\n";
	cout << "Choose What You Want To Do From [1 - 7] ?: ";
	cin >> choice;
	return choice;

}
void backToMainMenue() {
	cout << "To Back To Main menue Press Any Key.." << endl;
	system("pause");
	pages((enOptions)mainMenue());
}void backToTransactionsMenue() {
	cout << "To Back To Transactions menue Press Any Key.." << endl;
	system("pause");
	performTransaction((enTransactions)showTransactionsOptions());
}

vector<string> seperateString(string& text, string seperator = " ")
{
	int position = 0;
	string word;
	vector<string> words;
	position = text.find(seperator);

	while (position != string::npos)
	{
		word = text.substr(0, position);
		if (word != "")
		{
			words.push_back(word);
		}
		text.erase(0, position + seperator.length());
		position = text.find(seperator);
	}

	if (text != "")
	{
		words.push_back(text);
	}
	return words;
}
stAccountData convertLineToRecord(string line, string seperator = "#//#")
{
	stAccountData client;
	vector<string> vClientData;

	vClientData = seperateString(line, seperator);

	client.accountNumber = vClientData[0];
	client.pinCode = vClientData[1];
	client.name = vClientData[2];
	client.phone = vClientData[3];
	client.accountBalance = vClientData[4];

	return client;
}
vector<stAccountData> ReadFileToVector(string fileName)
{
	vector<stAccountData> vRecord;
	fstream file;
	file.open(fileName, ios::in);

	if (file.is_open())
	{
		string line;
		stAccountData clinet;
		while (getline(file, line))
		{
			clinet = convertLineToRecord(line, "#//#");
			vRecord.push_back(clinet);
		}
		file.close();
	}
	return vRecord;
}
string convertDataToLineOfData(stAccountData& record, string seperator = " ")
{
	string stRescord = "";

	stRescord = record.accountNumber + seperator;
	stRescord += record.pinCode + seperator;
	stRescord += record.name + seperator;
	stRescord += record.phone + seperator;
	stRescord += record.accountBalance;

	return stRescord;
}
void WriteRecordToFile(string fileName, stAccountData& record)
{
	fstream file;
	file.open(fileName, ios::out | ios::app);
	if (file.is_open())
	{

		file << convertDataToLineOfData(record, "#//#") << endl;

		file.close();
	}
}
vector<stAccountData> refreshFileAfterDeleteAccount(string fileName, stAccountData& clinet)
{
	vector<stAccountData> vRecord;
	fstream file;
	file.open(fileName, ios::in);

	if (file.is_open())
	{
		string line;
		while (getline(file, line))
		{
			if (clinet.deleteFlag == false)
			{
				clinet = convertLineToRecord(line, "#//#");
				vRecord.push_back(clinet);
			}
		}
		file.close();
	}
	return vRecord;
}

void printClientData(stAccountData& client)
{
	cout << "|" << left << setw(15) << client.accountNumber;
	cout << "|" << left << setw(10) << client.pinCode;
	cout << "|" << left << setw(40) << client.name;
	cout << "|" << left << setw(12) << client.phone;
	cout << "|" << left << setw(12) << client.accountBalance;
	cout << endl;
}void printBalancesData(stAccountData& client)
{
	cout << "|" << left << setw(15) << client.accountNumber;
	cout << "|" << left << setw(40) << client.name;
	cout << "|" << left << setw(12) << client.accountBalance;
	cout << endl;
}
void showClientsData(vector<stAccountData> vClients)
{

	for (stAccountData& cl : vClients)
	{
		printClientData(cl);
	}
}void showBalancessData(vector<stAccountData> vClients)
{

	for (stAccountData& cl : vClients)
	{
		printBalancesData(cl);
	}
}
bool findClientByAccountNumber(vector<stAccountData>& vClients, stAccountData& client, string accountNumberToFind)
{
	for (stAccountData& cl : vClients)
	{
		if (cl.accountNumber == accountNumberToFind)
		{
			client = cl; // if we find the account number we fill the client struct and return
			return true;
		}
	}
	return false;
}
bool checkIfClientAccountNumberIsAlreadyTaken(string accountNumber, string flieName) {
	vector <stAccountData> vClients;
	fstream file;
	file.open(flieName, ios::in); // open file in read mode

	if (file.is_open())
	{
		string line;
		stAccountData client;

		while (getline(file, line))
		{
			client = convertLineToRecord(line);
			if (client.accountNumber == accountNumber)
			{
				file.close();
				return true;
			}
			vClients.push_back(client);
		}
		file.close();
	}
	return false;
}
vector<stAccountData> saveClientsDataToFileAfterDelete(string fileName, vector<stAccountData>& vClients)
{
	fstream file;
	file.open(fileName, ios::out); // overwrite
	string line;
	if (file.is_open())
	{
		for (stAccountData& cl : vClients)
		{
			if (cl.deleteFlag == false)
			{
				WriteRecordToFile("clinet_Data_File.txt", cl);
			}
		}
		file.close();
	}
	return vClients;
}
vector<stAccountData> saveClientsDataToFileAfterUpdate(string fileName, vector<stAccountData>& vClients)
{
	fstream file;
	file.open(fileName, ios::out); // overwrite
	string line;
	if (file.is_open())
	{
		for (stAccountData& cl : vClients)
		{
			WriteRecordToFile("clinet_Data_File.txt", cl);
		}
		file.close();
	}
	return vClients;
}
void readRecordToFile(stAccountData& stRecord)
{

	stRecord = readRecord();
	WriteRecordToFile("clinet_Data_File.txt", stRecord);
}
void deleteClient(vector<stAccountData>& vClients, stAccountData& client, string accuontNumberToDelete)
{

	for (stAccountData& cl : vClients)
	{
		if (cl.accountNumber == accuontNumberToDelete)
		{
			cl.deleteFlag = true;
			saveClientsDataToFileAfterDelete("clinet_Data_File.txt", vClients);
			break;
		}
	}
	// refresh the clients
	vClients = refreshFileAfterDeleteAccount("clinet_Data_File.txt", client);
}
void updateClient(vector<stAccountData>& vClients, stAccountData& client, string accountNumber)
{
	stAccountData updatedClient = readToUpdateRecord();

	for (stAccountData& cl : vClients)
	{
		if (cl.accountNumber == accountNumber)
		{
			cl.pinCode = updatedClient.pinCode;
			cl.name = updatedClient.name;
			cl.phone = updatedClient.phone;
			cl.accountBalance = updatedClient.accountBalance;
			saveClientsDataToFileAfterUpdate("clinet_Data_File.txt", vClients);
			break;
		}
	}
}
void showClients() {
	vector<stAccountData> vClients = ReadFileToVector("clinet_Data_File.txt");
	drowHeader();
	showClientsData(vClients);
	drowFooter();
}

void addClient() {
	stAccountData stRecord;
	char more = 'y';

	// Insert Clients Data
	do
	{
		system("cls");
		cout << "Enter Client Data: \n";

		readRecordToFile(stRecord);

		cout << "Do You Want To Add Other Rcords? : y => yes | n => no : ";
		cin >> more;
	} while (more == 'y' || more == 'Y');
}


void findClient() {
	showClients();
	vector<stAccountData> vClients = ReadFileToVector("clinet_Data_File.txt");
	stAccountData client;
	string accountToFind = "";
	cout << "Do You Want To Search For Client? ";
	getline(cin >> ws, accountToFind);
	if (findClientByAccountNumber(vClients, client, accountToFind))
	{

		drowHeader();
		printClientData(client);
		drowFooter();
	}
	else
	{
		cout << "No Account With That Number.." << endl;
	}

}


void deleteClient() {
	showClients();
	vector <stAccountData> vClients = ReadFileToVector("clinet_Data_File.txt");
	string accountToFind = "";
	string accountNumberToDelete;
	stAccountData client;
	cout << "Enter An Account Number To Delete: ";
	getline(cin >> ws, accountNumberToDelete);
	if (findClientByAccountNumber(vClients, client, accountNumberToDelete))
	{
		system("cls");
		drowHeader();
		printClientData(client);
		drowFooter();
		char del;
		cout << "Are You Sure You Want to delete " << client.name << " ?";
		cin >> del;
		if (del == 'y' || del == 'Y')
		{
			deleteClient(vClients, client, accountNumberToDelete);
			cout << "The Account Deleted Succsessfuly.." << endl;
		}
	}
	else
	{
		cout << "No Account With This " << accountNumberToDelete << "Number.." << endl;
	}
}


void updateClient() {
	showClients();
	vector<stAccountData> vClients = ReadFileToVector("clinet_Data_File.txt");
	stAccountData client;
	string accountToFind = "";
	cout << "Do You Want To Search For Client? ";
	getline(cin >> ws, accountToFind);
	if (findClientByAccountNumber(vClients, client, accountToFind))
	{
		system("cls");
		drowHeader();
		printClientData(client);
		drowFooter();
		// update Client
		char updateOrNot;
		cout << "Do you Want To Update Client (" << client.name << ") ?";
		cin >> updateOrNot;
		if (updateOrNot == 'Y' || updateOrNot == 'y')
		{
			updateClient(vClients, client, accountToFind);
		}
	}
	else
	{
		cout << "No Account With That Number.." << endl;
	}
}
short showTransactionsOptions() {
	system("cls"); // system("clear");
	short choice = 0;
	cout << "\n-------------------------------------------------------\n";
	cout << "\t\t Transactions Screen\n";
	cout << "-------------------------------------------------------\n";
	cout << "\t[1]=> Deposit" << endl;
	cout << "\t[2]=> Withdrow" << endl;
	cout << "\t[3]=> TotalBalance" << endl;
	cout << "\t[4]=> Main Menue";
	cout << "\n-------------------------------------------------------\n";
	cout << "Choose What You Want To Do From [1 - 4] ?: ";
	cin >> choice;
	return choice;
}
void Deposit() {
	showClients();
	vector<stAccountData> vClients = ReadFileToVector("clinet_Data_File.txt");
	stAccountData client;
	string accountToFind = "";
	double depositAmount = 0;
	cout << "Enter Account Number? ";
	getline(cin >> ws, accountToFind);
	while (!findClientByAccountNumber(vClients, client, accountToFind))
	{
		cout << "No Account With Number " << accountToFind << endl;

		cout << "Enter Account Number? ";
		getline(cin >> ws, accountToFind);
	}
	system("cls");
	drowHeader();
	printClientData(client);
	drowFooter();
	cout << "How Much Do You Want To Deposit? ";
	cin >> depositAmount;
	for (stAccountData& cl : vClients)
	{
		if (cl.accountNumber == accountToFind)
		{
			cl.accountBalance = to_string(stod(cl.accountBalance) + depositAmount);
			saveClientsDataToFileAfterUpdate("clinet_Data_File.txt", vClients);
			break;
		}
	}
}
void WithDrow() {
	showClients();
	vector<stAccountData> vClients = ReadFileToVector("clinet_Data_File.txt");
	stAccountData client;
	string accountToFind = "";
	double depositAmount = 0;
	cout << "Enter Account Number? ";
	getline(cin >> ws, accountToFind);
	while (!findClientByAccountNumber(vClients, client, accountToFind))
	{
		cout << "No Account With Number " << accountToFind << endl;
		cout << "Enter Account Number? ";
		getline(cin >> ws, accountToFind);
	}
	system("cls");
	drowHeader();
	printClientData(client);
	drowFooter();
	cout << "How Much Do You Want To Withdrow? (make Sure To Enter A correct Amount..) ";
	cin >> depositAmount;

	for (stAccountData& cl : vClients)
	{
		if (cl.accountNumber == accountToFind)
		{
			while (depositAmount > stod(cl.accountBalance))
			{
				cout << "The Amount That you have entered is more than the account balance.." << endl;
				cout << "How Much Do You Want To Withdrow? (make Sure To Enter A correct Amount..) ";
				cin >> depositAmount;
			}
			cl.accountBalance = to_string(stod(cl.accountBalance) - depositAmount);
			saveClientsDataToFileAfterUpdate("clinet_Data_File.txt", vClients);
			break;
		}
	}
	
}
void TotalBalance() {
	vector<stAccountData> vClients = ReadFileToVector("clinet_Data_File.txt");
	drowBalancesScreenHeader();
	showBalancessData(vClients);
	drowFooter();
}

void performTransaction(enTransactions options) {
	switch (options)
	{
	case enTransactions::deposit:
		Deposit();
		backToTransactionsMenue();
		break;
	case enTransactions::withdrow:
		WithDrow();
		backToTransactionsMenue();
		break;
	case enTransactions::totalBalance:
		TotalBalance();
		backToTransactionsMenue();
		break;
	case enTransactions::MainMenue:
		mainMenue();
		backToMainMenue();
		break;
	}
}
void pages(enOptions choice) {
	switch (choice)
	{
	case enOptions::showList:
		system("cls");
		showClients();
		backToMainMenue();
		//cout << "ShowPage";
		break;
	case enOptions::addList:
		system("cls");
		addClient();
		backToMainMenue();
		//cout << "AddPage";
		break;
	case enOptions::deletList:
		system("cls");
		deleteClient();
		backToMainMenue();
		//cout << "deleetePage";
		break;
	case enOptions::updateList:
		system("cls");
		updateClient();
		backToMainMenue();
		//cout << "updatePage";
		break;
	case enOptions::findList:
		system("cls");
		findClient();
		backToMainMenue();
		//cout << "findPage";
		break;
	case enOptions::transactions:
		system("cls");
		performTransaction((enTransactions)showTransactionsOptions());
	case enOptions::Exit:
		system("cls");
		exit;
	}
}
int main()
{
	pages((enOptions)mainMenue());
	return 0;
}