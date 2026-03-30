#include <iostream>
#include <string>
#include <fstream>
#include <vector>
const int totalLBA = 100;
using namespace std;
string filename = "nand.txt";
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

std::vector<std::string> read() {
	std::vector<std::string> data(totalLBA, "00000000");
	std::ifstream fin(filename);

	//for (int i = 0; i < totalLBA && std::getline(fin, data[i]); i++);
	for (int i = 0; i < totalLBA; i++) {
		getline(fin, data[i]);
	}
	return data;
}


void write(const std::vector<std::string>& data) {
	std::ofstream fout(filename);
	for (auto v : data) {
		fout << v << "\n";
	}
}

int main() {

	
	ifstream readfile("nand.txt");

	//파일이 존재하는지 아닌지 확인
	if (readfile.is_open()){
		
		cout << "nand.txt 파일이 존재하는 상태입니다. 이제 명령을 수행합니다."<<endl;

		string input;
		
		//Read먼저

		

		//read 수행

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
		
			
		string LBA = "9";
		string value = "AAAAAAAA";

			int LBA_int = stoi(LBA);
			if (0 <= LBA_int && LBA_int < 100) { //LBA 검증

				if ("00000000" <= value && value <= "FFFFFFFF") {//Value 검증
					//Write 수행
					std::fstream fs(filename, std::ios::in | std::ios::out | std::ios::binary);
					if (fs.is_open()) {

						auto data = read();
						data[LBA_int] = value;
						write(data);
						
					}

				}
				else {
					cout << "[ERROR]: Value 값 오류";
				}

			}
			else {
				cout << "[ERROR]: LBA 범위 오류";
			}
		

	}
	else {

		cout << "nand.txt가 존재하지 않음 생성시작 " << endl;
		init();

	}

}