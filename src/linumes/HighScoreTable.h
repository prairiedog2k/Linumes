#pragma once

#include <string>
#include <set>
#include <yaml-cpp/yaml.h>

namespace Hunchback::Linumes {

struct hscomp{
    bool operator()(const std::pair<int, std::string> &lhs, const std::pair<int, std::string> &rhs) const{
        return lhs.first > rhs.first;
    };
};

typedef std::set< std::pair<int, std::string>, hscomp > ScoreTable;

class HighScoreTable
{
private:
    unsigned int _maxSize;
    std::string _tableName;
    ScoreTable _scoreTable;

public:
    HighScoreTable();
    HighScoreTable(std::string tableName, int maxSize);
    virtual ~HighScoreTable();
    void fillYaml(YAML::Node& gameModes);
    void fillTable(const YAML::Node& node);
    bool addScore(int score, std::string name = "Player");
    int getHighestScore();
    std::string getTableString();
};

} // namespace Hunchback::Linumes
