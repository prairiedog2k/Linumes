#include "Boss.h"

#include <iostream>
#include <yaml-cpp/yaml.h>
#include "framework/FileUtils.h"

#include "BossModeTypes.h"

#include "framework/XMLUtils.h"
#include "framework/XMLThemeTypes.h"
#include "framework/TextureResource.h"
#include "framework/AudioResource.h"

Boss::Boss(std::string bossFile) : _bossFile(bossFile),
    _name(),
    _dir(),
    _preferredTheme(),
    _turnsToAttack(0),
    _currentTurn(0),
    _turnAttack(0),
    _cumulativeBlocks(0),
    _attackReduce(0),
    _hitPoints(0),
    _currentHitPoints(0) {
    for (int i = 0; i < (16 * 10); i++) {
        _shape[i] = false;
        _currentShape[i] = false;
    }
    for (int i = 0; i < 4; i++) {
        _pattern[i] = -1;
    }
}

Boss::~Boss() = default;

void Boss::reset() {
    _currentTurn = 0;
    _cumulativeBlocks = 0;
    _currentHitPoints = _hitPoints;
}

bool Boss::attackAt(int x, int y) {
    if (!isBossBlock(x, y)) return false;
    _currentShape[(16 * y) + x] = false;
    _currentHitPoints--;
    return true;
}

void Boss::tokenize(const std::string& str,
                    std::vector<std::string>& tokens,
                    const std::string& delimiters)
{
    std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    std::string::size_type pos     = str.find_first_of(delimiters, lastPos);
    while (std::string::npos != pos || std::string::npos != lastPos) {
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        lastPos = str.find_first_not_of(delimiters, pos);
        pos     = str.find_first_of(delimiters, lastPos);
    }
}

int Boss::getPatternColor(int x, int y) {
    if (!isBossBlock(x, y)) return -1;
    int ipos = x % 2;
    int jpos = y % 2;
    return _pattern[jpos * 2 + ipos];
}

void Boss::load() {
    if (!fileExists(_bossFile)) return;
    YAML::Node root = YAML::LoadFile(_bossFile);
    if (!root) return;

    _name = nodeAttributeAsString(root, BOSS_ATTR_NAME);
    _dir  = nodeAttributeAsString(root, BOSS_ATTR_DIR);
    _turnsToAttack = root[BOSS_ATTACK_TURN]   ? root[BOSS_ATTACK_TURN].as<int>()   : 0;
    _turnAttack    = root[BOSS_ATTACK_DAMAGE]  ? root[BOSS_ATTACK_DAMAGE].as<int>() : 0;
    _attackReduce  = root[BOSS_ATTACK_REDUCE]  ? root[BOSS_ATTACK_REDUCE].as<int>() : 0;

    if (root[BOSS_THEME]) {
        _preferredTheme = root[BOSS_THEME].as<std::string>();
    }

    // media
    if (root["media"]) {
        for (const auto& res : root["media"]) {
            std::string target = nodeAttributeAsString(res, THEME_ATTR_NAME);
            if (target == BOSS_COLOR0)            _color0.reset(dynamic_cast<TextureResource*>(createResourceFromNode(res, _dir)));
            else if (target == BOSS_COLOR1)       _color1.reset(dynamic_cast<TextureResource*>(createResourceFromNode(res, _dir)));
            else if (target == BOSS_ATT_BG)       _bg.reset(dynamic_cast<TextureResource*>(createResourceFromNode(res, _dir)));
            else if (target == BOSS_ATT_FG)       _fg.reset(dynamic_cast<TextureResource*>(createResourceFromNode(res, _dir)));
            else if (target == BOSS_ICON)         _icon.reset(dynamic_cast<TextureResource*>(createResourceFromNode(res, _dir)));
            else if (target == BOSS_ATT_BG_MASK)  _bgMask.reset(dynamic_cast<TextureResource*>(createResourceFromNode(res, _dir)));
            else if (target == BOSS_ATT_FG_MASK)  _fgMask.reset(dynamic_cast<TextureResource*>(createResourceFromNode(res, _dir)));
            else if (target == BOSS_ICON_MASK)    _iconMask.reset(dynamic_cast<TextureResource*>(createResourceFromNode(res, _dir)));
            else if (target == BOSS_AUDIO_ATTACK) _attack.reset(dynamic_cast<AudioResource*>(createResourceFromNode(res, _dir)));
            else if (target == BOSS_AUDIO_DAMAGE) _damage.reset(dynamic_cast<AudioResource*>(createResourceFromNode(res, _dir)));
            else if (target == BOSS_AUDIO_DIE)    _die.reset(dynamic_cast<AudioResource*>(createResourceFromNode(res, _dir)));
            else if (target == BOSS_AUDIO_WIN)    _win.reset(dynamic_cast<AudioResource*>(createResourceFromNode(res, _dir)));
        }
    }

    // shape — rows listed top-to-bottom in YAML but stored bottom-to-top internally
    if (root["shape"]) {
        int count = 9;
        for (const auto& row_node : root["shape"]) {
            std::string strRow = row_node.as<std::string>();
            std::vector<std::string> tokens;
            tokenize(strRow, tokens);
            int col = 0;
            for (const auto& tok : tokens) {
                bool isHP = (tok == "0");
                _shape[(count * 16) + col] = isHP;
                _currentShape[(count * 16) + col] = isHP;
                if (isHP) _hitPoints++;
                col++;
            }
            count--;
        }
    }

    _currentHitPoints = _hitPoints;

    // pattern — 2 rows stored as _pattern[row*2 + col]
    if (root["pattern"]) {
        int count = 1;
        for (const auto& row_node : root["pattern"]) {
            std::string strRow = row_node.as<std::string>();
            std::vector<std::string> tokens;
            tokenize(strRow, tokens);
            int col = 0;
            for (const auto& tok : tokens) {
                _pattern[count * 2 + col] = (tok == "O") ? 0 : 1;
                col++;
            }
            count--;
        }
    }
}

GLuint Boss::getTexture(int x, int y) {
    int color = getPatternColor(x, y);
    if (color < 0 || color > 1) return 0;
    return (color == 0) ? _color0->getResource() : _color1->getResource();
}

GLuint Boss::getBGTexture() {
    return _bg ? _bg->getResource() : 0;
}

GLuint Boss::getFGTexture() {
    return _fg ? _fg->getResource() : 0;
}

GLuint Boss::getIconTexture() {
    return _icon ? _icon->getResource() : 0;
}

GLuint Boss::getBGMask() {
    return _bgMask ? _bgMask->getResource() : 0;
}

GLuint Boss::getFGMask() {
    return _fgMask ? _fgMask->getResource() : 0;
}

GLuint Boss::getIconMask() {
    return _iconMask ? _iconMask->getResource() : 0;
}

void Boss::dump() {
    std::cout << "Name : " << _name << std::endl;
    std::cout << "Turns To Attack : " << _turnsToAttack << std::endl;
    std::cout << "Attack Damage : " << _turnAttack << std::endl;
    std::cout << "Blocks for Attack Reduction " << _attackReduce << std::endl;
    std::cout << "Shape : " << std::endl;
    for (int i = 9; i >= 0; i--) {
        for (int j = 0; j < 16; j++) {
            std::cout << "|" << (_shape[(16 * i) + j] ? "X" : ".");
        }
        std::cout << "|" << std::endl;
    }
    std::cout << "Pattern : " << std::endl;
    for (int i = 0; i < 2; i++) {
        for (int j = 1; j >= 0; j--) {
            std::cout << "|" << _pattern[j * 2 + i];
        }
        std::cout << "|" << std::endl;
    }
}
