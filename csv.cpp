

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>

#define FILE_NAME "file.csv"


using namespace std;

class csv {
public:
	void remove_report() {
		remove("report.csv");
	}
	
	void report(int m) {
		string month_array[12] =
		{ "January","February","March",
			"April","May","June",
			"July","August","September",
			"October","November","December" };

		

		ifstream fin;
		ofstream fout;

		fin.open(FILE_NAME);

		fout.open("report.csv", ios::app);

		

		int month = m;

		fout << "\nReport for " << month_array[month-1] << "\n";
		fout << "Name;Month;Total Hours\n\n";

		string line, word, temp;
		vector<vector<string>> row;
		int row_count = 0;
		int col_count = 0;

		//create 2d array from file.csv

		while (!fin.eof()) {
			getline(fin, line);

			stringstream sin(line);

			row.push_back(vector<string>());
			col_count = 0;
			while (getline(sin, word, ';')) {
				row[row_count].push_back(word);
				col_count++;
			}
			row_count++;
		}

		int sum = 0;
		vector <string> names;
		vector <int> rows;
		vector <int> month_filter;
		int month_number;
		int num = 0;
		const int name_index = 0;
		const int date_index = 6;
		const int hours_index = 7;

		//filter by names and month and fill array with names and names line position

		for (int i = 1; i < row_count - 1; i++)
		{
			if (find(names.begin(), names.end(), row[i][name_index]) == names.end() && row[i][date_index].substr(7, 2) == to_string(m))
			{
				names.push_back(row[i][name_index]);
				rows.push_back(i);
			}
			month_number = stoi(row[i][date_index].substr(7, 2));
			if (find(month_filter.begin(), month_filter.end(), month_number) == month_filter.end())
			{
				month_filter.push_back(month_number);
			}
		}

		int names_size = size(names);
		int n;

		//use saved names line positions to summ the hours

		for (int i = 0;i < names_size;i++)
		{
			n = rows[i];
			sum = 0;
			for (int j = 1; j < row_count - 1; j++)
			{
				if (row[n][name_index] == row[j][name_index] && row[n][date_index] == row[j][date_index]) {
					
					sum = sum + stoi(row[j][hours_index]);

				}
			}

			
			string year = row[1][date_index].substr(0, 4);

			//output the result to report.scv and to the console

			fout << names[i] << ";" << month_array[month-1] << " "<< year <<";" << sum << "\n";

			cout << names[i] << " " << month_array[month - 1] << " " << year << " " << sum << endl;
		}


		fin.close();
		fout.close();

	}

	string welcome_message() {
		string message1 = "========================================\n";
		string message2 = "||| Welcome to monthly report App!!! |||\n";
		string message3 = "========================================\n\n";
		return message1+message2+message3;
	}
	bool check_if_existed() {
		ifstream file;
		file.open(FILE_NAME);
		bool if_open = file.is_open();
		file.close();
		return if_open;
	}
	string not_existed_message() {
		string message = "File is not existed at the directory\nPlease check or create file.csv\n";
		return message;
	}
	void add_record() {
		string name, fname,email, department, position, project, task, date;
		
		int logged_hours, y, m, d;
		
		char dash;

		cout << "Enter your First and Last name: ";
		cin >> name>>fname;
		cout << endl;
		cout << "Enter your email: ";
		cin >> email;
		cout << endl;
		cout << "Enter your department: ";
		cin >> department;
		cout << endl;
		cout << "Enter your position: ";
		cin >> position;
		cout << endl;
		cout << "Enter your project: ";
		cin >> project;
		cout << endl;
		cout << "Enter your task: ";
		cin >> task;
		cout << endl;
		cout << "Enter the date following format YYYY-MM-DD for this year: ";

		cin >> y >> dash >> m >> dash >> d;

		date = date_input(y, m, d, dash);

		string validation = validate_date(y, m, d, dash);

		while (validation != "good") {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << validation;
			cin >> y >> dash >> m >> dash >> d;
			date = date_input(y, m, d, dash);
			validation = validate_date(y, m, d, dash);
		}
		cout << endl;
		cout << "Enter your worked hours: ";
		cin >> logged_hours;
		while (cin.fail()) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Entry failed, please enter again: ";
			cin >> logged_hours;
		}

		cout << endl;

		add_line_csv(name+" "+fname, email, department, position, project, task, date, logged_hours);
	}
	private:

	string date_input(int y, int m, int d, char dash) {
		string year = to_string(y);
		string month = to_string(m);
		string day = to_string(d);

		string date = year +" "+dash +" "+ month + " "+dash+ " " + day;

		return date;
	}
	string validate_date(int y, int m, int d, char dash) {
		string message = "good";
		if (to_string(y).length() < 4 || to_string(y).length() > 4) {
			message = "Input Year Error, try again: ";
		}
		else if (m < 1 || m>12) {
			message = "Input Month Error, try again: ";
		}
		else if (d < 1 || d>31) {
			message = "Input Day Error, try again: ";
		}
		else if (dash != '-') {
			message = "Input Dash Error, try again: ";
		}
		return message;
	}
	void add_line_csv(string name, string email, string department, string position, string project, string task, string date, int logged_hours) {
		ofstream csv(FILE_NAME, ios::app);
		char c = ';';
		char newline = '\n';
		csv << name << c << email << c << department << c << position << c << project << c << task << c << date << c << to_string(logged_hours)<< newline;

		csv.close();
	}
};



int main()
{
	csv myreport;

	cout<< myreport.welcome_message();

	if (myreport.check_if_existed()) {
		string answer;
		cout << endl;
		cout << "Would you like to enter a record to " << FILE_NAME << "? y/n ";
		cin >> answer;
		
		if (answer == "y") {
			while (answer == "y") {
				myreport.add_record();
				cout << endl;
				cout << "Record added successfully!" << endl;
				cout << endl;
				cout << "Would you like to enter one more record to " << FILE_NAME << "? y/n ";
				cin >> answer;
			}
		}
		else if (answer != "y" || answer != "n") 
		{
			while (answer != "n") 
			{
				if (answer != "y" || answer != "n")
				{
					cout << endl;
					cout << "I dont anderstand your answer, please try again: " << endl;
					cout << endl;
					cin >> answer;
				}
				if (answer == "y")
				{
					while (answer == "y") {
						myreport.add_record();
						cout << endl;
						cout << "Record added successfully!" << endl;
						cout << endl;
						cout << "Would you like to enter one more record to " << FILE_NAME << "? y/n ";
						cin >> answer;
					}
				}
			}
			if(answer == "n")
			{
				cout << endl;
				cout << "Entering record aborted!!!" << endl;
				cout << endl;
			}	
		}
		else 
		{
			cout << endl;
			cout << "Entering record aborted!!!" << endl;
			cout << endl;
		}
		cout << endl;
		cout << "Would you like to generate a report from " << FILE_NAME << " to report.csv? y/n ";
		cin >> answer;

		if (answer == "y") 
		{
				// not to build the records everytime the application runs remove report.csv file first
				myreport.remove_report();

				for (int i = 1; i < 13; i++)
				{
					myreport.report(i);
				}
				cout << endl;
				cout << "The report was generated successfully!!!" << endl;
				cout << endl;		
		}
		else if (answer != "y" || answer != "n") 
		{
			while (answer != "n" && answer!="y")
			{
					cout << endl;
					cout << "I dont anderstand your answer, please try again: " << endl;
					cout << endl;
					cin >> answer;
			}
			if (answer == "y") 
			{
				// not to build the records everytime the application runs remove report.csv file first
				myreport.remove_report();

				for (int i = 1; i < 13; i++)
				{
					myreport.report(i);
				}
				cout << endl;
				cout << "The report was generated successfully!!!" << endl;
				cout << endl;
			}
			else
			{
				cout << endl;
				cout << "The repord was aborted!!!" << endl;
				cout << endl;
			}
		}
		else
		{
			cout << endl;
			cout << "The repord was aborted!!!" << endl;
			cout << endl;
		
		}
	}
	else 
	{
		cout << myreport.not_existed_message();
	}
}

