#include <iostream>

using namespace std;

void print(int *variable)
{
	cout << "\n----------------------------\n";
	cout << "You have entered " << *variable << " in variable" << endl;
	cout << "The variable is located at address " << variable << " in memory" << endl;
}

int main()
{
	int variable;
	int choic = 0;
	cout << "Please input variable\t";
	cin >> variable;
	print(&variable);

	do
	{
		cout << "for change variable please press\t 1" << endl;
		cout << "to complete the program please press\t 2\n\n" << endl;
		cout << "for print variable please press\t press any key\n\n" << endl;
		cin >> choic;
		if(choic == 2)
			break;
		else if (choic == 1)
			cin >> variable;
		print(&variable);
	} while(choic != 2);

	// system("pause");
	return 0;
}