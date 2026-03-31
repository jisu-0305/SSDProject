#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace std;

const string FILE_NAME = "nand.txt";
const int TOTAL_LBA = 100;

void init() 
{
	ofstream newwrite;
	newwrite.open(FILE_NAME);

	for (int i = 0; i < 100; i++) {
		string temp = "00000000"; //이거 수정해야함
		if (i != 99) {
			temp += "\n";
		}

		newwrite.write(temp.c_str(), temp.size());


	}
	cout << "FILE_NAME 생성 완료" << "\n";
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

//void write(const vector<std::string>& data) {
//	std::ofstream fout(FILE_NAME);
//
//	for (auto v : data) {
//		fout << v << "\n";
//	}
//}

vector<string> fullRead() {
	vector<string> data(TOTAL_LBA, "00000000");
	ifstream fin(FILE_NAME);

	for (int i = 0; i < TOTAL_LBA; i++) {
		getline(fin, data[i]);
	}
	return data;
}

void write(const string& value, const int LBAInt, fstream& txtFile) {
	auto data = fullRead();
	string dataValue = value.substr(2, 8);
	data[LBAInt] = dataValue;
	ofstream fout(FILE_NAME);

	for (auto v : data) {
		fout << v << "\n";
	}
	cout << "write 값 변환 완료 ";
}

// LBA변환 (0 -> 3)
int transformInt(string& s) {
	if (s.size() > 2) return -1;
	try {
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
		if (((48 <= c && c <= 57)) || ((65 <= c) && (c <= 70))) {
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
	try {
		boost::asio::io_context io;

		tcp::acceptor acceptor(io, tcp::endpoint(tcp::v4(), 12345));

		std::cout << "Server started on port 12345\n";

		while (true) {
			tcp::socket socket(io);
			acceptor.accept(socket);

			std::cout << "Client connected\n";

			while (true) {
				char input_data[1024];
				boost::system::error_code ec;

				size_t length = socket.read_some(boost::asio::buffer(input_data), ec);

				if (ec == boost::asio::error::eof) break;
				else if (ec) throw boost::system::system_error(ec);


				string cmd_str(input_data, length);
				stringstream ss(cmd_str);

				string command, LBA;
				if (!(ss >> command >> LBA)) continue;

				int LBAInt = transformInt(LBA);
				if (LBAInt == -1) {
					boost::asio::write(socket, boost::asio::buffer("ERROR: Invalid LBA\n"));
					continue; 
				}

				ifstream findfile(FILE_NAME);

				if (findfile.is_open()) cout << "nand.txt 파일이 존재하는 상태입니다. 이제 명령을 수행합니다." << endl;
				else {
					cout << "nand.txt가 존재하지 않음 생성시작 " << endl;
					init();
				}

				cout << "Executing command: " << command << " for LBA " << LBAInt << endl;

				if (command == "read") {
					ifstream readfile(FILE_NAME);
					string line = read(LBAInt, readfile);
					boost::asio::write(socket, boost::asio::buffer(line));
				}
				else if (command == "write") {
					string value;
					ss >> value;
					if (!isValidValue(value)) {
						cout << "Invalid Value";
						boost::asio::write(socket, boost::asio::buffer("ERROR: Invalid Value\n"));
						continue;
					}

					fstream fs(FILE_NAME, ios::in | ios::out | ios::binary);
					write(value, LBAInt, fs);
					
					boost::asio::write(socket, boost::asio::buffer("SUCCESS\n"));
				}
			
			}

			std::cout << "Client disconnected\n";
		}
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
}
