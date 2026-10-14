#ifndef I_TOOL_HPP
#define I_TOOL_HPP

#include "Vectoria/Interfaces/Core/IUnknown.hpp"
#include "Vectoria/Interfaces/Windows/IDocumentWindow.hpp"
#include "Vectoria/Shared/Vector.hpp"

namespace Vectoria {

extern const IID IID_ITool;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnon-virtual-dtor"

interface ITool : public IUnknown {
    virtual void onMouseDown (const Math::Vector2D& mouse_pos, IDocumentWindow* doc) = 0;
    virtual void onMouseMove (const Math::Vector2D& mouse_pos, IDocumentWindow* doc) = 0;
    virtual void onMouseUp   (const Math::Vector2D& mouse_pos, IDocumentWindow* doc) = 0;
    virtual void drawPreview (IGraphicsAdapter* adapter_ptr) = 0;
};

#pragma clang diagnostic pop

} // namespace Vectoria

#endif