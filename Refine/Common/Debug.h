#ifndef REFINE_COMMON_DEBUG_H
#define REFINE_COMMON_DEBUG_H

#include <string>

namespace Refine::Common {

    void exitOnError(const std::string &error, const int status = 1);
}

#endif
