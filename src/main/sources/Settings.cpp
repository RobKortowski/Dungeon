#include "util/Settings.h"

namespace Settings {
    bool debug = false;

    void setDebug(bool a) {
        debug = a;
    }

    bool shouldDebug() {
        return debug;
    }
}
