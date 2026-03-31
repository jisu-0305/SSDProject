#include "FileHandler.h"


FileHandler& FileHandler::get()
{
    static FileHandler handler;
    return handler;
}
std::string FileHandler::getrelevant(std::string shard) {
    fs::path p = fs::current_path();
    try {
        for (auto& e : fs::directory_iterator(p)) {
            auto target = e.path().filename().string();
            if (target.find(shard) != std::string::npos) {
                return target;
            }
        }
    }
    catch (std::exception& e) {
        Errcodes handler = Errcodes::get();
        handler.makeError(-3);
        std::cerr << e.what() << std::endl;
    }
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
}