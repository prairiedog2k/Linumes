#include "HighScoreTable.h"

#include "HighScoreTypes.h"
#include <cstdlib>
#include <cstdio>


namespace Hunchback::Linumes {


HighScoreTable::HighScoreTable() : _maxSize(10), _tableName("default")
{
}

HighScoreTable::HighScoreTable(std::string tableName, int maxSize)
    : _maxSize(maxSize), _tableName(tableName) {
}

HighScoreTable::~HighScoreTable()
{
}

void HighScoreTable::fillYaml(YAML::Node& gameModes) {
    YAML::Node gm;
    gm[HI_ATTR_NAME] = _tableName;
    gm[HI_ATTR_MAX_LISTING] = (int)_maxSize;
    YAML::Node scores;
    for (const auto& entry : _scoreTable) {
        YAML::Node score;
        score[HI_ATTR_NAME]  = entry.second;
        score[HI_ATTR_SCORE] = entry.first;
        scores.push_back(score);
    }
    gm[HI_SCORE_LISTING] = scores;
    gameModes.push_back(gm);
}

void HighScoreTable::fillTable(const YAML::Node& node) {
    if (!node || !node[HI_SCORE_LISTING]) return;
    unsigned int count = 0;
    for (const auto& entry : node[HI_SCORE_LISTING]) {
        if (count >= _maxSize) break;
        std::string name = entry[HI_ATTR_NAME] ? entry[HI_ATTR_NAME].as<std::string>() : " ";
        int val = entry[HI_ATTR_SCORE] ? entry[HI_ATTR_SCORE].as<int>() : 0;
        _scoreTable.insert(std::make_pair(val, name));
        count++;
    }
}

bool HighScoreTable::addScore(int score, std::string name) {
    bool bRetVal = false;
    std::pair<int, std::string> currPair = std::make_pair(score, name);
    if (_scoreTable.insert(currPair).second) {
        if (_scoreTable.size() > _maxSize) {
            ScoreTable::iterator iter = _scoreTable.end();
            iter--;
            _scoreTable.erase(iter);
        }
        bRetVal = true;
    }
    return bRetVal;
}

int HighScoreTable::getHighestScore() {
    if (_scoreTable.empty()) {
        return 0;
    }
    return _scoreTable.begin()->first;
}

std::string HighScoreTable::getTableString() {
    std::string retVal;
    char buff[32];
    int count = 1;
    retVal = "\nRank      Score \n";
    for (const auto& entry : _scoreTable) {
        std::snprintf(buff, sizeof(buff), "%2d     %7d\n", count, entry.first);
        retVal += buff;
        count++;
    }
    return retVal;
}


} // namespace Hunchback::Linumes