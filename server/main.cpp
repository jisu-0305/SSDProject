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

string read(int LBA, ifstream& txtFile) 
{
	cout << "index: " << LBA << std::endl;
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
}

void write(const std::vector<std::string>& data) {
	std::ofstream fout(filename);

	for (auto v : data) {
		fout << v << "\n";
	}
}

std::vector<std::string> fullRead() {
	std::vector<std::string> data(totalLBA, "00000000");
	std::ifstream fin(filename);

	for (int i = 0; i < totalLBA; i++) {
		getline(fin, data[i]);
	}
	return data;
}

// 숫자 검증 변환 메서드 필요(03 -> 03)

// 0~99 범위 + 4byte 값인지 검증하는 메서드 필요

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
	ifstream readfile("nand.txt");
	
	//파일이 존재하는지 아닌지 확인
	if (readfile.is_open()) {
		cout << "nand.txt 파일이 존재하는 상태입니다. 이제 명령을 수행합니다." << endl;

		int LBA_int = stoi(LBA);

		if (0 <= LBA_int && LBA_int < 100) { //LBA 검증
		}
		else {
			cout << "[ERROR]: LBA 범위 오류";
		}

		if (command == "read") {
			string line = read(LBA_int, readfile);
			cout << "read로 찾은 value값: " << line << endl;
		}
		else if (command == "write") {
			string value; //16진수 값는 변수값(취향 따라서 이름 변경) 
			ss >> value;

			if ("00000000" <= value && value <= "FFFFFFFF") {//Value 검증
				//Write 수행
				std::fstream fs(filename, std::ios::in | std::ios::out | std::ios::binary);
				if (fs.is_open()) {
					
					auto data = fullRead();
					data[LBA_int] = value;
					write(data);
					string line = read(LBA_int, readfile);
					cout << "read로 찾은 value값: " << line << endl;
				}
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
		//	int LBA_int = stoi(LBA);
		//	if (0 <= LBA_int && LBA_int < 100) { //LBA 검증

		//		if ("00000000" <= value && value <= "FFFFFFFF") {//Value 검증
		//			//Write 수행
		//			std::fstream fs(filename, std::ios::in | std::ios::out | std::ios::binary);
		//			if (fs.is_open()) {
		//			
		//				fs.seekp(LBA_int, std::ios::beg);
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


