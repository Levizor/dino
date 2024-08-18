#include "Score.h"
#include <filesystem>
#include "fmt/core.h"
#include <fstream>
#include <string>

namespace fs = std::filesystem;

#ifdef _WIN32
#include <iostream>
#include <windows.h>
#include <shlobj.h>  // For SHGetKnownFolderPath
#include <combaseapi.h>  // For CoTaskMemFree
                         //
std::string GetDocumentsPath() {
    PWSTR path = nullptr;
    std::string documentsPath;

    // Get the path to the Documents folder
    if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_Documents, 0, NULL, &path))) {
        // Convert the wide character string (PWSTR) to a standard string
        char charPath[MAX_PATH];
        wcstombs(charPath, path, MAX_PATH);
        documentsPath = charPath;
    }

    // Free the memory allocated by SHGetKnownFolderPath
    if (path) {
        CoTaskMemFree(path);
    }

    return documentsPath;
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
