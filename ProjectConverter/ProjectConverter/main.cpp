#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<filesystem::directory_entry> files = vector<filesystem::directory_entry>();
const char* seperator = "//";

void convert(string pPath, string tPath);

void createPackage(string target);
void copyDirectory(string target);
void getFilesFromDirectory(string target);
void format(string* str);

int main() {
	string pPath, tPath;

	cout << "NetBeans Project Path: ";
	cin >> pPath;

	cout << "Target Path: ";
	cin >> tPath;

	convert(pPath, tPath);

	return 0;
}

void convert(string pPath, string tPath) {
	format(&pPath);
	format(&tPath);
	pPath += "//src//main//java//";
	tPath += "//";
	createPackage(tPath);
	getFilesFromDirectory(pPath);
	copyDirectory(tPath);

}

void createPackage(string target) {
	fstream pgk(target+"package.bluej", ios::out);
	pgk << flush;
	pgk.close();
	cout << "->created package\n";

}

void copyDirectory(string target) {
	for (filesystem::directory_entry file : files) {
		string filename = file.path().filename().string();
		if (filename.find(".java") != string::npos) {
			string newPath = target.c_str() + file.path().filename().string();
			filesystem::copy(file.path(), newPath);
			cout << "Copied file: " << filename << "\nPath: " << file.path().string() << "\n";

		}
		else {
			cout << "->Skipped non-'.java' file\n";

		}

	}

}

void getFilesFromDirectory(string target) {
	for (const auto & file : filesystem::recursive_directory_iterator(target)) {
		files.push_back(file);

	}

}

void format(string* str) {
	string str_n = *str;

	for (int i = 0; i < str_n.length(); i++) {
		if (str_n.at(i) == 34) {
			str_n.erase(i, i+1);

		}
		else if (str_n.at(i) == 92) {
			str_n.replace(i, 1, "//");

		}

	}

	*str = str_n;

}