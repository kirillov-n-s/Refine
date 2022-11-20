#include <iostream>
#include "Debug.h"

namespace Refine::Common {

    void exitOnError(const std::string &error, const int status)
    {
        if (!error.empty()) {
            std::cout << error << std::endl;
            exit(status);
        }
    }
}
