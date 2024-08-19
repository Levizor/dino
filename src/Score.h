
#include <string>
namespace sc{

    std::string getDocumentsPath();

    std::string getConfigPath();

    std::string getScoreFilePath();

    int readBestScore();

    bool writeBestScore(int score);
}
