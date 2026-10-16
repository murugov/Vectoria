#ifndef C_SELECT_TOOL_HPP
#define C_SELECT_TOOL_HPP

#include "Vectoria/Interfaces/Base/IShape.hpp"
#include "Vectoria/Interfaces/Base/ITool.hpp"
#include "Vectoria/Interfaces/Core/IGraphicsAdapter.hpp"
#include "Vectoria/Interfaces/Windows/IDocumentWindow.hpp"
#include "Vectoria/Shared/Graphic/Colors.hpp"

#include "Base/CUnknown.hpp"

namespace Vectoria {

class CSelectTool : public CUnknown, public ITool {
private:
    IShape* selected_shape_ = nullptr;
    bool is_dragging_ = false;
    
    Math::Vector2D click_offset_ { 0.0f, 0.0f };
    Math::Vector2D last_mouse_pos_ { 0.0f, 0.0f };
    
    Graphic::Color select_box_color_ = Graphic::Colors::LightGray; 

public:
    CSelectTool() = default;
    
    ~CSelectTool() override {
        if (selected_shape_) {
            selected_shape_->release();
        }
    }

    // -------------------------------------------------------------------------------
    // --- Implementing IUnknown ---

    bool queryInterface (const IID& iid, void** ppv) override {
        if (ppv == nullptr) return false;

        if (iid == IID_IUnknown || iid == IID_ITool) {
            *ppv = static_cast<ITool*>(this);
        }
        else {
            *ppv = nullptr;
            return false;
        }

        static_cast<IUnknown*>(*ppv)->addRef();
        return true;
    }

    void addRef  ()  override { CUnknown::addRef(); }
    void release () override { CUnknown::release(); }

    // -------------------------------------------------------------------------------
    // --- Implementing ITool ---

    void onMouseDown(const Math::Vector2D& pos, IDocumentWindow* doc_ptr) override {
        if (!doc_ptr) return;

        if (selected_shape_) {
            selected_shape_->release();
            selected_shape_ = nullptr;
        }
        is_dragging_ = false;
        last_mouse_pos_ = pos;

        size_t shape_count = doc_ptr->getShapeCount();
        for (size_t i = shape_count - 1; i >= 0; --i) {
            IShape* current_shape = nullptr;
            if (doc_ptr->getShape(i, &current_shape) && current_shape) {
                
                if (current_shape->contains(pos)) {
                    selected_shape_ = current_shape;
                    is_dragging_ = true;
                    
                    Math::Vector2D shape_pos, shape_size;
                    selected_shape_->getBounds(&shape_pos, &shape_size);
                    click_offset_ = Math::Vector2D{ pos.x() - shape_pos.x(), pos.y() - shape_pos.y() };
                    break; 
                }
                
                current_shape->release();
            }
        }
    }

    void onMouseMove (const Math::Vector2D& pos, IDocumentWindow* /*doc_ptr*/) override {
        if (is_dragging_ && selected_shape_) {
            Math::Vector2D shape_pos, shape_size;
            selected_shape_->getBounds(&shape_pos, &shape_size);
            
            Math::Vector2D new_pos{ pos.x() - click_offset_.x(), pos.y() - click_offset_.y() };
            selected_shape_->setBounds(new_pos, shape_size);
        }
        last_mouse_pos_ = pos;
    }

    void onMouseUp (const Math::Vector2D& /*pos*/, IDocumentWindow* /*doc_ptr*/) override {
        is_dragging_ = false;
    }

    void drawPreview (IGraphicsAdapter* adapter_ptr) override {
        if (!adapter_ptr || !selected_shape_) return;

        Math::Vector2D shape_pos, shape_size;
        selected_shape_->getBounds(&shape_pos, &shape_size);

        adapter_ptr->drawSelectBox(shape_pos, shape_size, select_box_color_, 1.0f);
    }
};

} // namespace Vectoria

#endif