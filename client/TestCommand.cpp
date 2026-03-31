#include "TestCommand.h"

int TestCommand::operator()() {
    init();
    int errn = 0;
    Errcodes& handler = Errcodes::get();
    if ((errn = validate())) { handler.makeError(errn); return errn; }
    if ((errn = run())) { handler.makeError(errn); return errn; }
    return 0;
}

TestCommand::TestCommand() {
    init();
}
void TestCommand::init() { //상수 설정 (ex cmd length)

}
int TestCommand::prepare(std::vector<std::string>& args)
{
    cmds = std::move(args);
    return 0;
}
int TestCommand::run()
{
    //read file dir, find filename with given str, then do test
    FileHandler &filehandler = FileHandler::get();
    auto target_case = filehandler.getrelevant(cmds[1]);
    std::vector<std::string> orders = filehandler.get_test_cmds(target_case.first);
    std::vector<std::string> shards;
    std::string shard;
     
    std::pair<std::string, std::string> errcause = {" ", ""};
    for (auto& order: orders) {
        
        //std::cout << "taking " << order << std::endl;
        std::stringstream ss(order);
        shards.clear();
        while (std::getline(ss, shard, ' ')) {
            shards.emplace_back(shard);
        }
        TestShell& executor = TestShell::get();
        
        //if (!executor.exists_cmd(shards[0])) continue;
        int parselen = (shards.back() == "COMMAND") ? 2 : 1;
        
        std::vector<std::string> cmd = std::vector<std::string>(shards.begin(), shards.end() - parselen);

        std::string res = "";
        for (int i = shards.size() - parselen; i < shards.size(); i++) {
            res += shards[i];
            res += " ";
        }
        if (res != "") res.pop_back();

        //std::cout << "cmd : ";
        //for (auto& s : cmd) {
        //    std::cout << s << " ";
        //}
        //std::cout << std::endl;
        //std::cout << "res : " << res << std::endl;
        
        auto resultpair = executor.runCommand(cmd, true);
        //std::cout << "got > " << resultpair.first << " " << resultpair.second << std::endl;
        if (resultpair.second == res) {
            //std::cout << "succeed" << std::endl;
        }
        else {
            errcause = resultpair;
            //std::cout << "error on > " << order << std::endl;
            break;
        }
    }
    if (errcause.first != " ") {
        std::cout << "[FAIL] " << target_case.second << std::endl;
        std::cout << "caused by " << errcause.first << std::endl;
    }
    else {
        std::cout << "[SUCCESS] " << target_case.second << std::endl;
    }

    return 0;
}

int TestCommand::validate()
{
    //TestCommand
    //std::cout << "INPUT:  ";
    //for (auto& s : cmds) {
    //    std::cout << s << " " << std::endl;
    //}
    if (cmds.size() != 2) return -2;
    std::string& s = cmds[1];

    int pos = s.find('_');
    std::string substring = s.substr(0, pos);
    if (pos == std::string::npos || pos == 0) return -1;
    for (auto& c : substring) {
        if (!isdigit(c)) return -1;
    }
    //if (!std::isdigit(s[0])) return -1;
    //if (s[1] != '_') return -1;
    
    
    return 0;
}