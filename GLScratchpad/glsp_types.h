#pragma once

#include <functional>
#include <string>

#include "Application.h"

namespace glsp {

using Command = std::function<void(glsp::Application*)>;
using AttributeKey = std::string;

} // namespace glsp
