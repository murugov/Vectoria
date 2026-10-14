#ifndef I_UNKNOWN_HPP
#define I_UNKNOWN_HPP

#include <string.h>

namespace Vectoria {

struct GUID {
    unsigned long  Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned char  Data4[8];

    // Оператор сравнения, чтобы QueryInterface работал мгновенно
    bool operator == (const GUID& other) const {
        return ::memcmp(this, &other, sizeof(GUID)) == 0;
    }
};

typedef GUID IID; 

extern const IID IID_IUnknown;

#define interface struct

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnon-virtual-dtor"

interface IUnknown {
    virtual bool queryInterface (const IID& iid, void** ppv) = 0;
    virtual void addRef () = 0;
    virtual void release () = 0;
};

#pragma clang diagnostic pop

} // namespace Vectoria

#endif
