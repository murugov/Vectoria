#ifndef I_DOCUMENT_WINDOW_HPP
#define I_DOCUMENT_WINDOW_HPP

#include "Vectoria/Interfaces/Components/IShape.hpp"
#include "Vectoria/Interfaces/Core/IWindow.hpp"

namespace Vectoria {

extern const IID IID_IDocumentWindow;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnon-virtual-dtor"

interface IDocumentWindow : public IWindow {
    virtual bool addShape      (IShape* shape) = 0;
    virtual bool   removeShape   (IShape* shape) = 0;
    virtual bool   getShape      (size_t index, IShape** shape) = 0;
    virtual size_t getShapeCount () = 0;
    
    virtual void clear () = 0;
};

#pragma clang diagnostic pop

} // namespace Vectoria

#endif