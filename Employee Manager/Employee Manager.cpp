#include <iostream>
#include <fstream>
#pragma warning(disable: 4996)
using namespace std;

struct EMPLOYEES
{
	char name[40];
	char surname[40];
	int age;
	float salary;
};

struct DATA
{
	int size_employees = 0;
	EMPLOYEES* employees = new EMPLOYEES[size_employees];
};

EMPLOYEES* Add_employee(DATA data)
{
	EMPLOYEES employee;
	cout << "Name: ";
	cin >> employee.name;
	cout << "Surname: ";
	cin >> employee.surname;
	cout << "Age: ";
	cin >> employee.age;
	cout << "Salary: ";
	cin >> employee.salary;
	cout << endl;

	data.size_employees++;
	EMPLOYEES* new_employees = new EMPLOYEES[data.size_employees];
	for (int i = 0; i < data.size_employees - 1; i++)
		new_employees[i] = data.employees[i];
	new_employees[data.size_employees - 1] = employee;

	return new_employees;
}

void Print_employee(DATA data)
{
	for (size_t i = 0; i < data.size_employees; i++)
	{
		cout << data.employees[i].name << endl;
		cout << data.employees[i].surname << endl;
		cout << data.employees[i].age << endl;
		cout << data.employees[i].salary << endl;
	}
	cout << endl << endl;
}

void Rewrite_employee(DATA data)
{
	EMPLOYEES employee;
	string name;
	cout << "Enter name: ";
	cin >> name;

	for (size_t i = 0; i < data.size_employees; i++)
	{
		if (name == data.employees[i].name)
		{
			cout << "Name: ";
			cin >> employee.name;
			cout << "Surname: ";
			cin >> employee.surname;
			cout << "Age: ";
			cin >> employee.age;
			cout << "Salary: ";
			cin >> employee.salary;

			for (int j = i; j < i + 1; j++)
				data.employees[j] = employee;
			break;
		}
		else
			cout << "Don't found!" << endl << endl;
	}
}

EMPLOYEES* Delete_employee(DATA data)
{
	EMPLOYEES employee;
	string surname;
	cout << "Enter surname: ";
	cin >> surname;

	for (size_t i = 0; i < data.size_employees; i++)
	{
		if (surname == data.employees[i].surname)
		{
			data.size_employees--;
			EMPLOYEES* new_employees = new EMPLOYEES[data.size_employees];

			int index = i;
			for (size_t j = 0, d = 0; j < data.size_employees + 1; j++, d++)
			{
				if (d == index)
					d++;
				new_employees[j] = data.employees[d];
			}

			cout << "Deleted!" << endl;
			return new_employees;
		}
		else
			cout << "Don't found!" << endl << endl;
	}
}

void Search_employee(DATA data)
{
	EMPLOYEES employee;
	string surname;
	cout << "Enter surname: ";
	cin >> surname;

	for (size_t i = 0; i < data.size_employees; i++)
	{
		if (surname == data.employees[i].surname)
		{
			cout << "Found!" << endl;
			cout << data.employees[i].name << endl;
			cout << data.employees[i].surname << endl;
			cout << data.employees[i].age << endl;
			cout << data.employees[i].salary << endl;
			break;
		}
		else
			cout << "Don't found!" << endl << endl;
	}
}

void File_end(DATA data)
{
	ofstream file;
	string path = "file(8).txt";
	string path_size = "file(size).txt";

	file.open(path_size);
	if (file.is_open())
		file << data.size_employees;
	else
		cout << "ERROR opening file with size!" << endl;
	file.close();

	file.open(path);
	if (file.is_open())
	{
		for (size_t i = 0; i < data.size_employees; i++)
		{
			file << data.employees[i].name << endl;
			file << data.employees[i].surname << endl;
			file << data.employees[i].age << endl;
			file << data.employees[i].salary << endl;
			cout << endl;
		}
	}
	else
		cout << "ERROR opening file with array!" << endl;
	file.close();
}

EMPLOYEES* File_start(DATA data)
{
	EMPLOYEES employee;
	ifstream file;
	string path = "file(8).txt";
	string path_size = "file(size).txt";

	file.open(path_size);
	file >> data.size_employees;
	file.close();

	EMPLOYEES* new_employees = new EMPLOYEES[data.size_employees];

	file.open(path);
	for (int i = 0; i < data.size_employees; i++)
		file.read((char*)&new_employees[i], sizeof(employee));
	file.close();

	return new_employees;
}

int main()
{
	DATA data;
	EMPLOYEES employee;
	cout << "Employees" << endl << endl;

	data.employees = File_start(data);

	int choice = 1;
	if (choice >= 0 && choice <= 5)
	{
		while (true)
		{
			if (choice > 0)
			{
				cout << "0 - Exit\n1 - Add employee\n2 - Print all employees\n3 - Rewrite employee\n4 - Delete employee by surname\n";
				cout << "5 - Search employee by surname\nEnter your choice: "; cin >> choice; cout << endl << endl;
			}
			if (choice == 0)
			{
				cout << "Exit!" << endl;
				File_end(data);
				return 0;
			}
			if (choice == 1)
			{
				data.employees = Add_employee(data);
				data.size_employees++;
			}
			if (choice == 2)
				Print_employee(data);
			if (choice == 3)
				Rewrite_employee(data);
			if (choice == 4)
			{
				data.employees = Delete_employee(data);
				data.size_employees--;
			}
			if (choice == 5)
				Search_employee(data);
		}
	}
	else
		cout << "Something going wrong... ";

	return 0;
}