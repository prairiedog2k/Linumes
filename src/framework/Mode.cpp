#include "Mode.h"

namespace Hunchback::Framework {

Mode::Mode() : done(false), modeComplete(false)
{
	name = std::string("BASE");
}

Mode::~Mode()
{
}

} // namespace Hunchback::Framework
