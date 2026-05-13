#include "XMLSongBuilder.h"
#include "XMLSongTypes.h"
#include "XMLThemeTypes.h"
#include <cmath>
#include <cstdlib>

// themeNode is the root theme YAML node; song data is under the "song" key.
AudioInfo *XMLSongBuilder::createAudioInfo(const YAML::Node& themeNode) {
    if (!themeNode["song"]) return nullptr;
    const YAML::Node& s = themeNode["song"];

    AudioInfo *ai = new AudioInfo();

    std::string strType = s["type"] ? s["type"].as<std::string>() : "";
    Mix_MusicType type = MUS_NONE;
    if (strType == "mp3" || strType == "MP3") type = MUS_MP3;
    if (strType == "wav" || strType == "WAV") type = MUS_WAV;
    ai->setType(type);

    if (s["artist"])     ai->setArtist(s["artist"].as<std::string>());
    if (s["track_name"]) ai->setTrack(s["track_name"].as<std::string>());

    if (s["beats"]) {
        const YAML::Node& beats = s["beats"];
        std::string songUnit = s["unit"] ? s["unit"].as<std::string>() : "ms";
        std::string lengthStr = s["tracklength"] ? s["tracklength"].as<std::string>() : "0";
        if (songUnit == "seconds" || songUnit == "s") {
            ai->setSongLength(int(std::atof(lengthStr.c_str()) * 1000));
        } else {
            ai->setSongLength(int(std::atof(lengthStr.c_str())));
        }
        std::string beatUnit = beats["unit"] ? beats["unit"].as<std::string>() : "ms";
        if (beats["timings"]) {
            for (const auto& t : beats["timings"]) {
                double v = t.as<double>();
                if (beatUnit == "seconds" || beatUnit == "s") {
                    ai->addTiming(int(v * 1000));
                } else {
                    ai->addTiming(int(v));
                }
            }
        }
    }

    if (!ai->prepare()) {
        delete ai;
        return nullptr;
    }
    return ai;
}

MusicResource *XMLSongBuilder::createMusicResource(const YAML::Node& themeNode, std::string strThemeDir) {
    if (!themeNode["song"]) return nullptr;
    const YAML::Node& s = themeNode["song"];
    std::string track = s["track"] ? s["track"].as<std::string>() : "";
    if (track.empty()) return nullptr;
    std::string trackPath = strThemeDir + "/" + track;
    MusicResource *mr = new MusicResource(createAudioInfo(themeNode), trackPath);
    mr->load();
    return mr;
}
