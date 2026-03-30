#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

void init()
{
	ofstream newwrite;
	newwrite.open("nand.txt");

	for (int i = 0; i < 100; i++) {
		string temp = "0x00000000";
		if (i != 99) {
			temp += "\n";
		}

		newwrite.write(temp.c_str(), temp.size());


	}
	cout << "nand.txt 생성 완료" << "\n";
}

string read(int index, ifstream& txtFile) 
{
	cout << "index: " << index << std::endl;
	string line;
	int currentLine = 0;

	if (txtFile.is_open()) {
		while (getline(txtFile, line)) {
			if (currentLine == index) {
				txtFile.close();
				return line;
			}
			currentLine++;
		}
	} 
}

// 숫자 검증 변환 메서드 필요(03 -> 03)

// 0~99 범위 + 4byte 값인지 검증하는 메서드 필요

int main() {
	//예시 더미 데이터
	string exampleInput = "read 3"; 
	//string exampleInput = "read 03";
	//string exampleInput = "read 04";
	//string exampleInput = "write 3 0xFFFFFFFF"; 

	// client 입력 받기
	stringstream ss(exampleInput);
	string command;
	int index;
	ss >> command >> index;
	ifstream readfile("nand.txt");
	
	//파일이 존재하는지 아닌지 확인
	if (readfile.is_open()) {
		cout << "nand.txt 파일이 존재하는 상태입니다. 이제 명령을 수행합니다." << endl;
		
		if (command == "read") {
			string line = read(index, readfile);
			cout << "read로 찾은 value값: " << line << endl;
		}
		else if (command == "write") {
			string text16; //16진수 값는 변수값(취향 따라서 이름 변경) 
			ss >> text16; 
			//write 메서드 추가 필요
		}
		else {
			//에러값 반환 필요
		}
	}
	else {

		cout << "nand.txt가 존재하지 않음 생성시작 " << endl;
		init();
	}
}


