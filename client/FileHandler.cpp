#include "FileHandler.h"


FileHandler& FileHandler::get()
{
    static FileHandler handler;
    return handler;
}
std::vector<std::string> FileHandler::getalltest() {
    std::vector<std::string> res;
    fs::path p = fs::current_path() / "tests";

    //std::cout << "path : " << p.root_path().string();
    try {
        for (auto& e : fs::directory_iterator(p)) {
            auto target = e.path().filename().string();
            res.emplace_back(target);
        }
    }
    catch (std::exception& e) {
        Errcodes handler = Errcodes::get();
        handler.makeError(-3);
        std::cerr << e.what() << std::endl;
    }
    return res;
}
std::pair<std::string, std::string> FileHandler::getrelevant(std::string shard) {
    fs::path p = fs::current_path() / "tests";
    try {
        for (auto& e : fs::directory_iterator(p)) {
            auto target = e.path().filename().string();
            if (target.find(shard) != std::string::npos) {
                return { e.path().string(), e.path().filename().string() };
            }
        }
    }
    catch (std::exception& e) {
        Errcodes handler = Errcodes::get();
        handler.makeError(-3);
        std::cerr << e.what() << std::endl;
    }
    return {};
}
std::vector<std::string> FileHandler::get_test_cmds(std::string path)
{
    std::ifstream fin(path);
    if (!fin) {
        return std::vector<std::string>();
    }
    std::string line;
    std::vector<std::string> res;
    while (std::getline(fin, line)) {
        res.emplace_back(line);
    }
    fin.close();
    return res;
}
int FileHandler::writelog(std::string log) {
    ofs << log;
    return 0;
}