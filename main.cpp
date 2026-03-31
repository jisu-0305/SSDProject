#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
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
		if (((48 <= c && c <= 57)) || ((65 <= c) && (c <= 70))) {
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

				ifstream readfile("nand.txt");
				if (readfile.is_open()) {

					cout << "Executing command: " << command << " for LBA " << LBAInt << endl;

					if (command == "read") {
						string line = read(LBAInt, readfile);
						boost::asio::write(socket, boost::asio::buffer(line + "\n"));
					}
					else if (command == "write") {
						string value;
						ss >> value;
						if (!isValidValue(value)) {
							boost::asio::write(socket, boost::asio::buffer("ERROR: Invalid Value\n"));
							continue;
						}

						auto data = fullRead();
						data[LBAInt] = value;
						write(data);

						boost::asio::write(socket, boost::asio::buffer("SUCCESS\n"));
					}
				}
				else {
					init();
				}
			}


			std::cout << "Client disconnected\n";
		}
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
}
