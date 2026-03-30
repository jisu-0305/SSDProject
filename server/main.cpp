#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

const string FILE_NAME = "nand.txt";
const int TOTAL_LBA = 100;

void init()
{
	ofstream newwrite;
	newwrite.open(FILE_NAME);

	for (int i = 0; i < 100; i++) {
		string temp = "00000000"; 
		if (i != 99) {
			temp += "\n";
		}

		newwrite.write(temp.c_str(), temp.size());
	}
	cout << "nand.txt 생성 완료" << "\n";
}

string read(const int LBA, ifstream& txtFile) 
{
	string line;
	int currentLine = 0;

	if (txtFile.is_open()) {
		while (getline(txtFile, line)) {
			if (currentLine == LBA) {
				txtFile.close();
				string hexValue = "0x" + line; 
				return hexValue; 
			}
			currentLine++;
		}
	} 
	return "-1"; 
}

vector<string> fullRead() {
	vector<string> data(TOTAL_LBA, "00000000");
	ifstream fin(FILE_NAME);

	for (int i = 0; i < TOTAL_LBA; i++) {
		getline(fin, data[i]);
	}
	return data; 
} 

int write(const string& value, const int LBAInt, fstream& txtFile) {
	if (txtFile.is_open()) { 
		auto data = fullRead();
		string dataValue = value.substr(2, 8);
		data[LBAInt] = dataValue;
		ofstream fout(FILE_NAME);
		
		for (auto v : data) {
			fout << v << "\n";
		}
		cout << "write 값 변환 완료";
		return 1;
	}
	else {
		return -1; // txt파일 없는 경우 - 빼도 될듯한 내용
	}
 }

// LBA변환 (0 -> 3)
int transformInt(string& s) {
	if (s.size() > 2) return -1; 
	try{
		int LBAInt = stoi(s); 
		if (0 <= LBAInt && LBAInt < 100) {
			return LBAInt;
		}
		else {
			return -1;
		}
	}
	catch (const std::invalid_argument& e) {
		cout << "정수값이 아닌 값 발견" << endl;
		return -1;
	} 
} 

// 0~F까지 범위 + 4byte 값인지 검증하는 메서드 필요
bool isValidValue(const string& s) { 
	if (s.size() != 10) return false; 
	if (s.substr(0, 2) != "0x") return false; 
	for (int i = 2; i < 10; i++) { 
		char c = s[i]; 
		//0~9와 F까지의 문자만 가능(48~57 또는 65~70만 가능) 
		if (((48 <= c && c <= 57)) || ((65 <= c)&&(c <= 70))) {  
			continue; 
		}
		else { 
			cout << "value값 오류!" << endl; 
			return false;
		}
	} 
	return true; 
}

int main() {
	//예시 더미 데이터
	//string exampleInput = "read 3";
	//string exampleInput = "read 03";
	//string exampleInput = "read 03a"; 
	string exampleInput = "write 3 0xFFFFFFFF"; 
	
	// client 입력 받기
	stringstream ss(exampleInput);
	string command;
	string LBA; 
	ss >> command >> LBA; 
	
	//LBA 검증
	int LBAInt = transformInt(LBA);
	if (LBAInt == -1) return -1; 

	ifstream findfile(FILE_NAME);
	
	if (findfile.is_open()) cout << "nand.txt 파일이 존재하는 상태입니다. 이제 명령을 수행합니다." << endl;
	else {
		cout << "nand.txt가 존재하지 않음 생성시작 " << endl;
		init();
	}

	if (command == "read") {
		ifstream readfile(FILE_NAME);
		string line = read(LBAInt, readfile);
		cout << "read로 찾은 value값: " << line << endl;
		if (line == "- 1") return false;  
	}
	else if (command == "write") {
		string value; 
		ss >> value;
		if(!isValidValue(value)) return -1;

		fstream fs(FILE_NAME, ios::in | ios::out | ios::binary); 
		return write(value, LBAInt, fs);
	}
	else { 
		return -1; 
	}
}
