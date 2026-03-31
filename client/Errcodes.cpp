#include "Errcodes.h"

Errcodes& Errcodes::get() {
    static Errcodes instance;
    return instance;
}
std::string& Errcodes::getErrorMsg()
{
    return lore;
}

void Errcodes::makeError(int errn)
{
    no = errn;
    switch (errn) {
    case -1:
    {
        lore = "ERROR";
        break;
    }
    case -2:
    {
        lore = "INVALID COMMAND";
        break;
    }
    }
}
