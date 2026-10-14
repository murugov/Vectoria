#ifndef C_COLOR_PALETTE_HPP
#define C_COLOR_PALETTE_HPP

#include <vector>
#include "Vectoria/Base/CWindow.hpp"
#include "Vectoria/Interfaces/Core/IGraphicsAdapter.hpp"
#include "Vectoria/Interfaces/Windows/IColorPalette.hpp"
#include "Vectoria/Shared/Colors.hpp"

namespace Vectoria {

class CColorPalette : public CWindow, public IColorPalette {
private:
    struct ColorButton {
        unsigned int   id;
        Graphic::Color color;
        Math::Vector2D relative_pos;
        Math::Vector2D size;
    };

    std::vector<ColorButton> colors_ {};
    size_t active_color_index_ = 0;

    Graphic::Color active_color_ = Graphic::Colors::Black;

public:
    // -------------------------------------------------------------------------------
    // --- Constructor ---
    
    CColorPalette () {
        // ! DEBUG !
        
        colors_.push_back({ 0, Graphic::Colors::Red,   Math::Vector2D { 0.0f, 0.0f },   Math::Vector2D { 30.0f, 30.0f } }); 
        colors_.push_back({ 1, Graphic::Colors::Green, Math::Vector2D { 0.0f, 30.0f },  Math::Vector2D { 30.0f, 30.0f } }); 
        colors_.push_back({ 2, Graphic::Colors::Blue,  Math::Vector2D { 0.0f, 60.0f },  Math::Vector2D { 30.0f, 30.0f } }); 

        active_color_ = colors_[0].color;
        
        // ! END OF DEBUG !
    }

    ~CColorPalette () override = default;

    // -------------------------------------------------------------------------------
    // --- Implementing IUnknown ---

    bool queryInterface(const IID& iid, void** ppv) override {
        if (ppv == nullptr) return false;

        if (iid == IID_IUnknown || iid == IID_IWindow || iid == IID_IColorPalette) {
            *ppv = static_cast<IColorPalette*>(this); 
        } 
        else {
            *ppv = nullptr;
            return false;
        }

        static_cast<IUnknown*>(*ppv)->addRef();
        return true;
    }

    void addRef  () override { CUnknown::addRef(); }
    void release () override { CUnknown::release(); }

    // -------------------------------------------------------------------------------
    // --- Implementing IWindow ---

    void setBounds(const Math::Vector2D& pos, const Math::Vector2D& size) override {
        CWindow::setBounds(pos, size);
    }

    void getBounds(Math::Vector2D* pos, Math::Vector2D* size) override {
        CWindow::getBounds(pos, size);
    }

    void show(bool visible) override {
        CWindow::show(visible);
    }

    void refresh(IGraphicsAdapter* adapter) override {
        if (!visible_ || !adapter) return;

        adapter->drawRectangle(pos_, size_, Graphic::Colors::LightGray);

        Math::Vector2D mouse_pos = adapter->getMousePosition();

        for (const auto& btn : colors_) {
            Math::Vector2D btn_abs_pos{ pos_.x() + btn.relative_pos.x(), pos_.y() + btn.relative_pos.y() };

            bool is_hovered = (mouse_pos.x() >= btn_abs_pos.x() && mouse_pos.x() <= btn_abs_pos.x() + btn.size.x() &&
                               mouse_pos.y() >= btn_abs_pos.y() && mouse_pos.y() <= btn_abs_pos.y() + btn.size.y());

            adapter->drawRectangle(btn_abs_pos, btn.size, btn.color);
            
            Graphic::Color stroke_color = (btn.id == active_color_index_) ? Graphic::Colors::White : Graphic::Colors::Black;
            adapter->drawSelectBox(btn_abs_pos, btn.size, stroke_color, 1.0f);

            if (is_hovered && adapter->isMouseButtonPressed(0)) {
                active_color_index_ = static_cast<size_t>(btn.id);
                updateSelection();
            }
        }

        adapter->drawLine(Math::Vector2D{ pos_.x(), pos_.y() },
                          Math::Vector2D{ pos_.x() + size_.x(), pos_.y() },
                          Graphic::Colors::DarkGray, 1.0f);
    }

    // -------------------------------------------------------------------------------
    // --- Implementing IColorPalette ---

    bool setActiveColor (const Graphic::Color& color) override {
        active_color_ = color;
        return true;
    }
    
    bool getActiveColor (Graphic::Color* color) override {
        if (!color) return false;
        
        *color = active_color_;
        return true;
    }
    
    void updateSelection () override {
    }
};

} // namespace Vectoria

#endif
