#pragma once

#include "Theme.h"
#include "AudioInfo.h"
#include <yaml-cpp/yaml.h>
#include "BaseResource.h"

namespace Hunchback::Framework {

class FileTheme : public Theme
{
public:
    FileTheme();
    FileTheme(std::string resourcefile);
    FileTheme(std::string resourcefile, std::string resourcedir);
    virtual ~FileTheme() {};

    bool loadResourcesFromNode(const YAML::Node& node);

    virtual bool init();

    virtual void release();

private:
    std::string _resourcedir;
    bool loadResources();
};

} // namespace Hunchback::Framework
