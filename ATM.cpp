#include<iostream>
#include<string.h>
#include<cmath >
#include<limits>

using namespace std;

const int size_name = 101;		// size of name of each ATM account
const int n_accounts = 100;		// numbers of accounts in ATM
const int n_card_ch = 20;		// size of card number entered in form of array of char
int n_active_accounts = 0;		// number of active accounts in ATM
char choice;					// A variable represents the ATM operation chosen by the user
const int n_double_ch = 100;    // size of the array of char used to read amount
char double_ch[n_double_ch];    // array of char used to read amount

class ATM
{
private:
	char name[size_name];				// name of each ATM account
	char card_number[n_card_ch];		// card number of each ATM account
	double amount;						// amount of money in each ATM account
public:
	void set_name();					// A function to read the name of each ATM account
	void set_card_number();				// A function to read card number of each ATM account
	void create_new_acc();				// A function to set up new ATM account
	void deposit();						// A function to add money to a specific ATM account
	void withdrawal();					// A function to get money from a specific ATM account
	void transfer(ATM& acc);			// A function to transfer money from a specific ATM account to another
	void print_acc_data();				// A function to print name,card number and amount of each ATM account
	int similar_acc(char number[]);      // A function to compare between two accounts
	bool check_amount();                // A function that verifies that there is money in the accounts
	ATM();
}account[n_accounts];					// creating objects of ATM class

void choose_statements();				// A function to show the main operations of ATM and ask the user to choose one operation only
char choose();							// A function that gets the user's choice and makes sure that the user entered a number in the range 1 to 5
void check_active_accounts();			// A function that verifies that there are enough active accounts to perform various financial operations
void get_card_ch(char arr[]);				// A function to read card number of Each ATM account
bool same_number(char arr[]);           // A function that verifies that the component numbers of card number is not a recursive number
bool check_card_number(char arr[]);		// A function that checks whether the card number entered is valid or not
void chToInt(char ch, int& num);         // A function that converts numbers from characters to integers
int find_acc(ATM acc[], char number[], int num);	//A function to find a specific ATM account which entered before
int choose_acc(ATM account[]);			// A function that choose the account to apply operations on it
bool check_name(char arr[]);			//A function that checks whether the name entered is valid or not
void get_double_ch(char arr[]);         // A function to allow read the amount as array of character
double chToDouble(char arr[]);          // A function that converts array of char to double variable
bool check_double_ch(char arr[]);       //  A function that verifies that the input amount is valid
int Search(char arr[], char ch);        // A function to find the index of a specific charcter in an array of char
void clear_buffer(char arr[], int length);  // A function to make sure that the user doesn't exceeded the maximum number of inputs

int main()
{
	int index[2];
	while (true)
	{
		choose_statements();
		choice = choose();
		check_active_accounts();
		if (choice == '1')
		{
			account[n_active_accounts].create_new_acc();
			account[n_active_accounts].print_acc_data();
			n_active_accounts++;
		}
		else if (choice == '2')
		{
			index[0] = choose_acc(account);
			account[index[0]].deposit();
			account[index[0]].print_acc_data();
		}
		else if (choice == '3')
		{
			cout << "For the sender::";
			index[0] = choose_acc(account);
			if (account[index[0]].check_amount())
				continue;
			cout << "For the receiver::";
			index[1] = choose_acc(account);
			while (index[0] == index[1])
			{
				cout << "The sender and receiver are the same account. Please Re-enter for the receiver::\n";
				index[1] = choose_acc(account);
			}
			account[index[0]].transfer(account[index[1]]);
			cout << "Sending account::\n";
			account[index[0]].print_acc_data();
			cout << "Receiving account::\n";
			account[index[1]].print_acc_data();
		}
		else if (choice == '4')
		{
			index[0] = choose_acc(account);
			if (account[index[0]].check_amount())
				continue;
			account[index[0]].withdrawal();
			account[index[0]].print_acc_data();
		}
		else
		{

			return 0;
		}
	}
}

ATM::ATM()
{
    strcpy(name, "not reserved");
	strcpy(card_number, "0 0 0 0 0 0 0 0 0 0");
	amount = 0;
}

void ATM::set_name()
{
	cout << "Please enter the account name: ";
	cin.getline(name, size_name);
	clear_buffer(name, size_name);
	while (check_name(name) || strlen(name) == 0 || name[0] == ' ')
	{
		if (strlen(name) == 0)
			cout << "You entered nothing. Please Re-enter your name: ";
        else if(name[0] == ' ')
            cout << "The name must start with a character. Please Re-enter your name: ";
        else
			cout << "Please Re-enter the account name (English Alphabet and Space only): ";
		cin.getline(name, size_name);
		clear_buffer(name, size_name);

}}

void ATM::set_card_number()
{
	cout << "Please enter the card number(10 number each separated by space): ";
	get_card_ch(card_number);
	while ((find_acc(account, card_number, n_active_accounts) != -1) || same_number(card_number))
	{
		if (same_number(card_number))
			cout << "Easy to guess. Please Re-enter the card number with different 10 number in range[0, 9]: ";
		else
			cout << "This account already exists. Please Re-enter the card number:";
		get_card_ch(card_number);
	}
}

void ATM::create_new_acc()
{
	amount = 0;
	set_name();
	set_card_number();
}

void ATM::deposit()
{
	double deposit;
	cout << "Please enter the amount to be deposited: ";
	get_double_ch(double_ch);
	deposit = chToDouble(double_ch);
	amount += 1.01 * deposit;
}

void ATM::withdrawal()
{
	double drawn;
	cout << "Please enter the amount to be withdrawn: ";
	get_double_ch(double_ch);
	drawn = chToDouble(double_ch);
	drawn *= 1.03;
	while (amount < drawn)
	{
		cout << "There is no enough money. The maximum amount to be withdrawn = " << amount / 1.03;
		cout << "\nPlease Re-enter the amount to be withdrawn: ";
		get_double_ch(double_ch);
		drawn = chToDouble(double_ch);
		drawn *= 1.03;
	}
	amount -= drawn;
}

void ATM::transfer(ATM& acc)
{
	double transfer;
	cout << "Please enter the amount to be transferred: ";
	get_double_ch(double_ch);
	transfer = chToDouble(double_ch);
	transfer *= 1.015;
	while (amount < transfer)
	{
		cout << "There is no enough money. The maximum amount to be transferred = " << amount / 1.015;
		cout << "\nPlease enter the amount to be transferred: ";
		get_double_ch(double_ch);
		transfer = chToDouble(double_ch);
		transfer *= 1.015;
	}
	amount -= transfer;
	acc.amount += (0.985 / 1.015) * transfer;
}

void ATM::print_acc_data()
{
	cout << "Name: " << name;
	cout << "\nCard Number: ";
	for (int i = 0; i < n_card_ch; i++)
	{
		if(i % 2 == 0)
			cout << card_number[i];
	}
	cout << "\nAmount: " << amount;
	cout << endl;
}

int ATM::similar_acc(char number[])
{
	int found = 1;
	for (int j = 0; j < n_card_ch; j++)
	{
		if (number[j] != card_number[j])
		{
			found = 0;
			break;
		}
	}
	return found;
}

bool ATM::check_amount()
{
	if (amount == 0)
	{
		cout << "There is no money in this account. Please deposit into your account by choosing 2 then try again.\n";
		return true;
	}
	return false;
}


void choose_statements()
{
	cout << "1----Create new account";
	cout << "\n2----Deposit";
	cout << "\n3----Transfer to another account";
	cout << "\n4----Withdrawal";
	cout << "\n5----Exit";
	cout << "\nPlease enter the number of operation: ";
}

char choose()
{
	char choice[2];
	cin.getline(choice, 2);
	clear_buffer(choice, 2);
	while ((!((choice[0] >= '1') && (choice[0] <= '5'))))
	{
	    if (strlen(choice) == 0)
            cout << "You entered nothing. ";
		cout << "Please Re-enter your choice in range[1,5]: ";
		cin.getline(choice, 2);
		clear_buffer(choice, 2);
	}
	return choice[0];
}

void check_active_accounts()
{
	while ((n_active_accounts < 2) && ((choice > '1') && (choice < '5')))
	{
		if (((choice == '2') || (choice == '4')) && (n_active_accounts == 1))
			break;
		if ((choice == '2') || (choice == '4'))
		{
			cout << "There are no active accounts. Please create accounts by choosing 1 or Exit by choosing 5: ";
			choice = choose();
			while ((choice != '1') && (choice != '5'))
			{
				cout << "There are no active accounts. Please create accounts by choosing 1 or Exit by choosing 5: ";
				choice = choose();
			}
			break;
		}
		else if ((choice == '3') && (n_active_accounts == 1))
		{
			while (choice == '3')
			{
				cout << "There only 1 active account." << "\nPlease create accounts by choosing 1, deposit by choosing 2, withdraw by choosing 4 or Exit by choosing 5: ";
				choice = choose();
			}
			break;
		}
		else if (choice == '3')
		{
			while ((choice != '1') && (choice != '5'))
			{
				cout << "There are less than 2 active accounts. Please create accounts by choosing 1 or Exit by choosing 5: ";
				choice = choose();
			}
			break;
		}
	}
	while ((n_active_accounts == 100) && (choice == '1'))
	{
		cout << "There are the maximum number of active accounts(100)." << "\nPlease deposit by choosing 2,transfer by choosing 3, withdraw by choosing 4 or Exit by choosing 5: ";
		choice = choose();
	}
}

bool check_name(char arr[])
{
	for (int i = 0; arr[i] != '\0'; i++)
	{
		if (!((arr[i] >= 'a' && arr[i] <= 'z') || (arr[i] >= 'A' && arr[i] <= 'Z') || arr[i] == ' '))

			return true;

	}
	return false;
}

void get_double_ch(char arr[])
{
	cin.getline(arr, n_double_ch);
	clear_buffer(arr, n_double_ch);
	while (check_double_ch(arr) || (strlen(arr) == 0))
	{
		if ((arr[0] == '-') && (strlen(arr) > 1))
			cout << "Not valid. Please enter positive amount: ";
        else if(strlen(arr) == 0)
            cout << "You entered nothing. Please enter a valid double number: ";
		else
			cout << "Please enter a valid double number: ";
		cin.getline(arr, n_double_ch);
		clear_buffer(arr, n_double_ch);
	}
}

double chToDouble(char arr[])
{
	int dot_index, num;
	double value = 0;
	int length = strlen(arr);
	dot_index = Search(arr, '.');
	if ((dot_index) == -1)
	{
		for (int i = 0; i < length; i++)
		{
			chToInt(arr[i], num);
			value += num * pow(10, (length - i - 1));
		}
	}
	else
	{
		for (int i = 0; i < dot_index; i++)
		{
			chToInt(arr[i], num);
			value += num * pow(10, (dot_index - i - 1));
		}
		for (int i = length - 1; i > dot_index; i--)
		{
			chToInt(arr[i], num);
			value += num / pow(10, (i - dot_index));
		}
	}
	return value;
}

bool check_double_ch(char arr[])
{
	int n_dot = 0;
	int length = strlen(arr);
	for (int i = 0; i < length; i++)
	{
		if (arr[i] == '.')
			n_dot++;
		if (!(((arr[i] <= '9') && (arr[i] >= '0')) || (arr[i] == '.')) || (n_dot > 1) || (arr[0] == '-'))
		{
			return true;
			break;
		}
	}
	return false;
}

int Search(char arr[], char ch)
{
    int length = strlen(arr);
	for (int j = 0; j < length; j++)
	{
		if (arr[j] == ch)
			return j;
	}
	return -1;
}

void clear_buffer(char arr[], int length)
{
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "You have entered more inputs than allowed. Please try again: ";
		cin.getline(arr, length);
	}
}

void get_card_ch(char arr[])
{
	cin.getline(arr, n_card_ch);
	clear_buffer(arr, n_card_ch);
	while (check_card_number(arr))
	{
	    if(strlen(arr) < (n_card_ch - 1))
        {


           bool check=true;
            for (int i=0;(i<strlen(arr)&&strlen(arr)==10);i++)
            {
                if (arr[i]==' ')
                {
                    check=false;
                    break;

                }
                check=true;
            }
               if (strlen(arr) ==10 && check)
            {
                cout <<"the numbers are not be seperated by spaces.Please Re-enter the card number(10 number each separated by space):";}
        else
            cout << "You did not enter enough inputs. Please Re-enter the card number: ";
            }
		else
            cout << "Please enter the card number again(10 number each in range [0,9] and separated by space): ";
		cin.getline(arr, n_card_ch);
		clear_buffer(arr, n_card_ch);
	}
}

bool same_number(char arr[])
{
	int j;
	for (int i = 0; i < 9; i++)
	{
		j = 2 * i;
		if (arr[j] != arr[j + 2])
			return false;
	}
	return true;
}

bool check_card_number(char arr[])
{
	for (int i = 0; i < (n_card_ch - 1); i++)
	{
		if (!((arr[i] <= '9' && arr[i] >= '0') || arr[i] == ' ') || (strlen(arr) < n_card_ch - 1))
			return true;
		if ((i % 2 == 0) && (arr[i] == ' '))
			return true;
		if ((i % 2 == 1) && (arr[i] != ' '))
			return true;
	}
	return false;
}

void chToInt(char ch, int& num)
{
	switch (ch)
	{
	case '0':
		num = 0; break;
	case '1':
		num = 1; break;
	case '2':
		num = 2; break;
	case '3':
		num = 3; break;
	case '4':
		num = 4; break;
	case '5':
		num = 5; break;
	case '6':
		num = 6; break;
	case '7':
		num = 7; break;
	case '8':
		num = 8; break;
	default:
		num = 9; break;
	}
}

int find_acc(ATM acc[], char number[], int num)
{
	int i;
	for (i = 0; i < num; i++)
	{
		if (acc[i].similar_acc(number) == 1)
			return i;
	}
	return -1;
}

int choose_acc(ATM account[])
{
	char arr_ch[n_card_ch];
	int index;
	cout << "Please enter the card number(10 number each separated by space): ";
	get_card_ch(arr_ch);
	index = find_acc(account, arr_ch, n_active_accounts);
	while (index == -1)
	{
		cout << "There is no account with the card number entered.";
		cout << "\nPlease Re-enter the card number(10 number each separated by space): ";
		get_card_ch(arr_ch);
		index = find_acc(account, arr_ch, n_active_accounts);
	}
	return index;
}
