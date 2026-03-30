#include <iostream>
#include <string>
#include <fstream>
#include <vector>

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


int main() {


	ifstream readfile("nand.txt");

	//파일이 존재하는지 아닌지 확인
	if (readfile.is_open()) {

		cout << "nand.txt 파일이 존재하는 상태입니다. 이제 명령을 수행합니다." << endl;

		//Read먼저

		string input;



	}
	else {

		cout << "nand.txt가 존재하지 않음 생성시작 " << endl;
		init();

	}

}