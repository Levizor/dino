
#include <string>
namespace sc{
#ifdef _WIN32
#include <windows.h>
#include <shlobj.h>

    std::string getAppDataPath();
#endif


    std::string getConfigPath();

    std::string getScoreFilePath();

    int readBestScore();

    bool writeBestScore(int score);
}
