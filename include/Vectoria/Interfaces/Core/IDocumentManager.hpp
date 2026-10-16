#ifndef I_DOCUMENT_MANAGER_HPP
#define I_DOCUMENT_MANAGER_HPP

#include "Vectoria/Interfaces/Base/IUnknown.hpp"
#include "Vectoria/Interfaces/Core/IEventListener.hpp"
#include "Vectoria/Interfaces/Windows/IDocumentWindow.hpp"

namespace Vectoria {

extern const IID IID_IDocumentManager;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnon-virtual-dtor"

interface IDocumentManager : public IEventListener {
    virtual bool             create_document() = 0;
    virtual void             close_active_document() = 0;
    
    virtual IDocumentWindow* get_active_document() = 0;
    virtual unsigned int     get_document_count() = 0;
    
    virtual void             set_active_document_index(unsigned int index) = 0;
    virtual unsigned int     get_active_document_index() = 0;
};

#pragma clang diagnostic pop

} // namespace Vectoria

#endif