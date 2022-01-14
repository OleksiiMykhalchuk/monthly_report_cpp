#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <algorithm>
#include <filesystem>

using namespace std;

#define FILE "file.csv"
#define REPORT "report.csv"

class Open_file
{
public:
	Open_file();
	Open_file(string inFile, string outFile);
	~Open_file();
	int GetInputFileSize();
	int HowManyPeopleLogged();
	int HowManyEntries();



private:
	void Logic();

	ifstream csv_file;
	ofstream csv_report;
	string inFile;
	string outFile;
	string line, word;
	vector<string> names;
	int8_t name_index = 0;
	vector<int> row_numbers;
	uint8_t hours_index = 7;
	int sum = 0;
	vector<int> hours_sum;



	string month_array[12] =
	{ "January","February","March",
		"April","May","June",
		"July","August","September",
		"October","November","December"
	};

	uint8_t month_number = 0;
	int first_line = 1;
	int date_index = 6;

protected:
	vector<vector<string>> array;
	int rows_number = 0;
	int words_number = 0;
	set<int> words;

};

Open_file::Open_file()
{

}

void Open_file::Logic()
{
	csv_file.open(inFile, ios::binary);
	if (csv_file.is_open())
	{
		while (!csv_file.eof())
		{
			getline(csv_file, line);
			stringstream str(line);
			array.push_back(vector<string>());
			words_number = 0;
			while (getline(str, word, ';'))
			{
				array[rows_number].push_back(word);
				words.emplace(words_number);
				words_number++;
			}
			rows_number++;
		}

		auto it = words.end();
		it--;
		int n = *it + 1;



		for (size_t i = 1; i < rows_number - 1; i++)
		{
			if (find(names.begin(), names.end(), array[i][name_index]) == names.end())
			{
				names.push_back(array[i][name_index]);
				row_numbers.push_back(i);
			}
		}

		for (size_t i = 0; i < size(names); i++)
		{
			int n = row_numbers[i];
			sum = 0;
			for (int j = 0; j < rows_number - 1;j++)
			{
				if (array[n][name_index] == array[j][name_index])
				{
					sum = sum + stoi(array[j][hours_index]);
				}
			}
			hours_sum.push_back(sum);
		}

		int len = outFile.length();

		const int buffer = 255;
		char arr[buffer];

		strcpy_s(arr, outFile.c_str());

		remove(arr);

		csv_report.open(outFile, ios::app);

		csv_report << "Name;Month;Total_hours\n";

		month_number = stoi(array[first_line][date_index].substr(5, 2));

		for (size_t i = 0; i < size(names); i++)
		{
			csv_report << names[i] << ';' << month_array[month_number - 1] << " " << array[first_line][date_index].substr(0, 4) << ';' << hours_sum[i] << '\n';
		}

		cout << "Report for " << month_array[month_number - 1] << " " << array[first_line][date_index].substr(0, 4) << " saved to " << REPORT << " file!" << endl;

	}
	else
	{
		cout << "File " << inFile << " is not found!!!" << endl;
	}



}

Open_file::Open_file(string inFile, string outFile)
{
	this->inFile = inFile;
	this->outFile = outFile;

	Logic();


}

Open_file::~Open_file()
{
	csv_file.close();

	csv_report.close();
}




int Open_file::HowManyPeopleLogged()
{
	return size(names);
}

int Open_file::HowManyEntries()
{
	return rows_number - 2;
}







int main()
{

	Open_file file(FILE, REPORT);

	cout << file.HowManyPeopleLogged() << " people logged their time." << endl;
	cout << file.HowManyEntries() << " entries in a source file." << endl;

	return 0;
}