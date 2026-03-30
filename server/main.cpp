#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

string filename = "nand.txt";
const int totalLBA = 100;

void init()
{
	ofstream newwrite;
	newwrite.open("nand.txt");

	for (int i = 0; i < 100; i++) {
		string temp = "00000000"; //이거 수정해야함
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
				return line;
			}
			currentLine++;
		}
	} 
	return "ERROR"; 
}

void write(const vector<std::string>& data) {
	std::ofstream fout(filename);
	
	for (auto v : data) {
		fout << v << "\n";
	}
}

vector<string> fullRead() {
	vector<string> data(totalLBA, "00000000");
	ifstream fin(filename);

	for (int i = 0; i < totalLBA; i++) {
		getline(fin, data[i]);
	}
	return data;
} 

// LBA변환 (0 -> 3)
int transformInt(string& s) {
	int LBAInt = stoi(s); // try~catch 여부 궁금

	if (0 <= LBAInt && LBAInt < 100) { 
		return LBAInt;
	}
	else {
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
			cout << c << "일때 문제 없음" << endl;
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
	//string exampleInput = "read 04";
	string exampleInput = "write 3 0xFFFFFFFF"; 
	
	// client 입력 받기
	stringstream ss(exampleInput);
	string command;
	string LBA; 
	ss >> command >> LBA; 

	//LBA 검증
	int LBAInt = transformInt(LBA);
	if (LBAInt == -1) return -1; 

	ifstream readfile("nand.txt");
	
	//파일이 존재하는지 아닌지 확인
	if (readfile.is_open()) {
		cout << "nand.txt 파일이 존재하는 상태입니다. 이제 명령을 수행합니다." << endl;

		if (command == "read") {
			string line = read(LBAInt, readfile);
			cout << "read로 찾은 value값: " << line << endl;
		}
		else if (command == "write") {
			string value; 
			ss >> value;
			if(!isValidValue(value)) return -1;
			
			fstream fs(filename, ios::in | ios::out | ios::binary);
			if (fs.is_open()) {
				auto data = fullRead();
				data[LBAInt] = value;
				write(data);
				string line = read(LBAInt, readfile);
				cout << "write로 찾은 value값: " << line << endl;
			}
		
			else {
				cout << "[ERROR]: Value 값 오류";
			}
		}
		else {
			//에러값 반환 필요
		}

		//if (input[0] == "write") {
		//	string LBA = input[1];
		//	string value = input[2];
		//	
		//	int LBAInt = stoi(LBA);
		//	if (0 <= LBAInt && LBAInt < 100) { //LBA 검증

		//		if ("00000000" <= value && value <= "FFFFFFFF") {//Value 검증
		//			//Write 수행
		//			fstream fs(filename, ios::in | ios::out | ios::binary);
		//			if (fs.is_open()) {
		//			
		//				fs.seekp(LBAInt, ios::beg);
		//				fs.write(value.c_str(),value.size()); 
		//				fs.close();
		//			}
		//			
		//		}
		//		else {
		//			cout << "[ERROR]: Value 값 오류";
		//		}

		//	}
		//	else {
		//		cout << "[ERROR]: LBA 범위 오류";
		//	}
		//}
	}
	else {
		cout << "nand.txt가 존재하지 않음 생성시작 " << endl;
		init();
	}
}


