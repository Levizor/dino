#include "Score.h"
#include <filesystem>
#include "fmt/core.h"
#include <fstream>
#include <string>

namespace fs = std::filesystem;

#ifdef _WIN32
#include <windows.h>
#include <shlobj.h>

    std::string sc::getAppDataPath() {
        std::string path;
        if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, path))) {
            return std::string(path) + "\\Dino\\score.txt";
        }
        return "";
    }
#endif


    std::string sc::getConfigPath() {
        const char* homeDir = getenv("HOME");
        return std::string(homeDir) + "/.config/Dino/score.txt";
    }

    std::string sc::getScoreFilePath() {
#ifdef _WIN32
        return getAppDataPath();
#else
        return getConfigPath();
#endif
    }


    int sc::readBestScore(){
        std::string path = getScoreFilePath();
        std::ifstream ifs = std::ifstream(path);
        if(!ifs.is_open()){
            fs::path p(path);
            if(!fs::exists(p)){
                fs::path pd = p.parent_path();   
                fs::create_directory(pd);
            } 
            return 0;
        }
        int score=0;
        ifs.read(reinterpret_cast<char*>(&score), 4);
        
        return score;
    }

    bool sc::writeBestScore(int score){
        std::ofstream ofs(getScoreFilePath());

        if(!ofs.is_open()){
            return false;
        }
        ofs.write(reinterpret_cast<const char*>(&score), 4);
        ofs.close();
        return true;
    }
