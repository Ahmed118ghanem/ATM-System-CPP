#pragma warning(disable : 4996)
#include <ctime>
#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <cctype>
#include <fstream>
using namespace std;

const string clientfile = "bankfile.txt";

void login();
void atm_mainmenu_screen();
void quick_withdraw_screen();
void normal_withdraw_screen();

struct stclient
{
	string accountnumber;
	string pincode;
	string clientname;
	string phone;
	double accountbalance;
};

enum enatmmainmenu { Qwithdraw = 1, Nwithdraw = 2, Deposit = 3, checkbalance = 4, logout = 5 };

stclient currentclient;

void goback_to_atmMainmenu()
{
	cout << "\n\nPress any key to go back to Main Menu...";
	system("pause>0");
	atm_mainmenu_screen();
}


// Functions specific to manage system.

vector <string> splitline(string line)
{
	vector <string> vclient;
	string  word, belim = "#//#";
	int pos = 0;
	while ((pos = line.find(belim)) != string::npos)
	{
		word = line.substr(0, pos);
		if (word != "")
		{
			vclient.push_back(word);
			line.erase(0, pos + belim.length());
		}
	}
	if (line != "")
	{
		vclient.push_back(line);
	}
	return vclient;
}

stclient convertline_to_record(string line)
{
	vector <string> vclientaftersplit = splitline(line);
	stclient client;
	client.accountnumber = vclientaftersplit[0];
	client.pincode = vclientaftersplit[1];
	client.clientname = vclientaftersplit[2];
	client.phone = vclientaftersplit[3];
	client.accountbalance = stod(vclientaftersplit[4]);
	return client;
}

vector <stclient> load_datafromfile(string filename)
{
	vector <stclient> vclient;
	fstream myfile;
	myfile.open(filename, ios::in);
	if (myfile.is_open())
	{
		string line;
		stclient client;
		while (getline(myfile, line))
		{
			client = convertline_to_record(line);
			vclient.push_back(client);
		}
	}
	myfile.close();
	return vclient;
}

string convertrecord_to_line(stclient client)
{
	string line, belim = "#//#";

	line += client.accountnumber + belim;
	line += client.pincode + belim;
	line += client.clientname + belim;
	line += client.phone + belim;
	line += to_string(client.accountbalance);
	return line;
}

bool findclient_by_accountnumberandpincode(string accountnumber, string pincode, stclient& client)
{
	vector <stclient> vclient = load_datafromfile(clientfile);
	for (stclient& c : vclient)
	{
		if (c.accountnumber == accountnumber && c.pincode == pincode)
		{
			client = c;
			return true;
		}
	}
	return false;
}
// Functions specific to quick withdraw

short read_quick_withdraw()
{
	short choose;
	cout << "Choose what do you want to do? [1 to 9]? ";
	cin >> choose;
	while (choose < 1 || choose>9)
	{
		cout << "\nWrong Value!\n";
		cout << "Choose what do you want to do? [1 to 5]? ";
		cin >> choose;
	}
	return choose;
}

vector <stclient> savedata_of_client(string filename, stclient client)
{
	vector <stclient> vclient = load_datafromfile(filename);
	fstream myfile;
	myfile.open(filename, ios::out);
	if (myfile.is_open())
	{
		for (stclient& c : vclient)
		{
			if (c.accountnumber == client.accountnumber)
			{
				c = client;
			}
			string line = convertrecord_to_line(c);
			myfile << line << endl;
		}
	}
	myfile.close();
	return vclient;
}

stclient quick_withdraw(stclient& client, int withdrawammount)
{
	client.accountbalance -= withdrawammount;
	return client;
}

bool perform_quick_withdraw(short number)
{
	int arr[] = { 20,50,100,200,400,600,800,1000 };

	if (number == 9)
	{
		atm_mainmenu_screen();
		return true;
	}

	if (currentclient.accountbalance < arr[number - 1])
	{
		cout << "\nThe amount exceeds your balance , make another choose.\n";
		cout << "Press any key to continue...";
		system("pause>0");
		quick_withdraw_screen();
	}

	string do_transaction;
	cout << "\nAre you sure you want perform this transaction? [Yes OR No]? ";
	cin >> do_transaction;
	if (do_transaction == "yes" || do_transaction == "YES")
	{
		quick_withdraw(currentclient, arr[number - 1]);
		savedata_of_client(clientfile, currentclient);
		cout << "\nDone Successfully. New Balance is : " << currentclient.accountbalance << endl;
		return true;
	}
	else
	{
		cout << "\nThe Operation Was Cancelled.\n";
		return false;
	}
	
}

void quick_withdraw_screen()
{
	system("cls");
	cout << "================================================\n";
	cout << "\t     Quick Withdraw Screen\n";
	cout << "================================================\n";
	cout << "\t[1] 20          [2] 50\n";
	cout << "\t[3] 100         [4] 200\n";
	cout << "\t[5] 400         [6] 600\n";
	cout << "\t[7] 800         [8] 1000\n";
	cout << "\t[9] Exit " << endl;
	cout << "================================================\n";
	cout << "Your Balance is " << currentclient.accountbalance << endl;
	perform_quick_withdraw(read_quick_withdraw());
}


// Functions Specific to Normal withdraw

bool normal_withdraw(int amount)
{
	if (currentclient.accountbalance < amount)
	{
		cout << "\nThe amount exceeds your balance , make another amount.\n";
		cout << "Press any key to continue...";
		system("pause>0");
		normal_withdraw_screen();
	}
	string do_transaction;
	cout << "\nAre you sure you want perform this transaction? [Yes OR No]? ";
	cin >> do_transaction;
	if (do_transaction == "yes" || do_transaction == "YES")
	{
		currentclient.accountbalance -= amount;
		savedata_of_client(clientfile, currentclient);
		cout << "\nDone Successfully. New Balance is : " << currentclient.accountbalance << endl;
		return true;
	}
	else
	{
		cout << "\nThe Operation Was Cancelled.\n";
		return false;
	}
}

void normal_withdraw_screen()
{
	system("cls");
	cout << "================================================\n";
	cout << "\t     Normal Withdraw Screen\n";
	cout << "================================================\n";
	cout << "Your Balance is " << currentclient.accountbalance << endl;
	int amount;
	do
	{
		cout << "\nEnter an amount multiply of 5's? ";
		cin >> amount;
	} while (amount % 5 != 0);
	normal_withdraw(amount);
}

// Functions specific to deposit

bool deposit(int amount)
{
	string do_transaction;
	cout << "\nAre you sure you want perform this transaction? [Yes OR No]? ";
	cin >> do_transaction;
	if (do_transaction == "yes" || do_transaction == "YES")
	{
		currentclient.accountbalance += amount;
		savedata_of_client(clientfile, currentclient);
		cout << "\nDone Successfully. New Balance is : " << currentclient.accountbalance << endl;
		return true;
	}
	else
	{
		cout << "\nThe Operation Was Cancelled.\n";
		return false;
	}
}

void Deposit_screen()
{
	system("cls");
	cout << "==========================================\n";
	cout << "\t     Deposit Screen\n";
	cout << "==========================================\n";
	cout << "Your Balance is " << currentclient.accountbalance << endl;
	int amount;
	do
	{
		cout << "\nEnter a Positive Deposit Amount? ";
		cin >> amount;
	} while (amount < 1);
	deposit(amount);
}

// Check balance screen

void check_balance_screen()
{
	system("cls");
	cout << "=========================================\n";
	cout << "\t   Check Balance Screen\n";
	cout << "=========================================\n";
	cout << "Your Balance is " << currentclient.accountbalance << endl;

}

short read_client_choose()
{
	short choose;

	cout << "Choose what do you want to do? [1 to 5]? ";
	cin >> choose;
	while (choose < 1 || choose>5)
	{
		cout << "\nWrong Value!\n";
		cout << "Choose what do you want to do? [1 to 5]? ";
		cin >> choose;
	}
	return choose;
}

void perform_mainmenuscreen(enatmmainmenu mainmenu)
{
	switch (mainmenu)
	{
	case enatmmainmenu::Qwithdraw:
		quick_withdraw_screen();
		goback_to_atmMainmenu();
		break;
	case enatmmainmenu::Nwithdraw:
		normal_withdraw_screen();
		goback_to_atmMainmenu();
		break;
	case enatmmainmenu::Deposit:
		Deposit_screen();
		goback_to_atmMainmenu();
		break;
	case enatmmainmenu::checkbalance:
		check_balance_screen();
		goback_to_atmMainmenu();
		break;
	case enatmmainmenu::logout:
		login();
		break;
	}
}

void atm_mainmenu_screen()
{
	system("cls");
	cout << "===============================================\n";
	cout << "\t     ATM Main Menu Screen\n";
	cout << "===============================================\n";
	cout << "     [1] Quick Withdraw.\n";
	cout << "     [2] Normal Withdraw.\n";
	cout << "     [3] Deposit.\n";
	cout << "     [4] Check Balance.\n";
	cout << "     [5] Logout.\n";
	cout << "===============================================" << endl;
	perform_mainmenuscreen((enatmmainmenu)read_client_choose());
}

bool loaddataclientbyaccountnumberorpincode(string accountnumber, string pincode)
{
	return (findclient_by_accountnumberandpincode(accountnumber, pincode, currentclient));

}

void login()
{

	string accountnumber, pincode;
	bool logfaild = false;

	do
	{
		system("cls");
		cout << "------------------------------------\n";
		cout << "\t   Login Screen\n";
		cout << "------------------------------------\n";
		if (logfaild)
		{
			cout << "Invaild Account Number/Pin Code!\n";
		}
		cout << "Enter Account Number? ";
		getline(cin >> ws, accountnumber);
		cout << "Enter Pin Code? ";
		getline(cin >> ws, pincode);
		logfaild = !loaddataclientbyaccountnumberorpincode(accountnumber, pincode);
	} while (logfaild);
	atm_mainmenu_screen();
}

int main()
{
	login();
}