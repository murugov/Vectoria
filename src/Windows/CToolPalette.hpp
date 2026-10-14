#ifndef C_TOOL_PALETTE_HPP
#define C_TOOL_PALETTE_HPP

#include <cstddef>
#include <vector>
#include <string>
#include "Vectoria/Base/CWindow.hpp"
#include "Vectoria/Interfaces/Components/ITool.hpp"
#include "Vectoria/Interfaces/Core/IGraphicsAdapter.hpp"
#include "Vectoria/Interfaces/Windows/IToolPalette.hpp"

#include "Tools/CSelectTool.hpp"

namespace Vectoria {

class CToolPalette : public CWindow, public IToolPalette {
private:
    std::vector<ITool*> tools_ {};
    size_t active_tool_index_ = 0;

    struct ToolButton {
        unsigned int id;
        std::string label;
        Math::Vector2D relative_pos;
        Math::Vector2D size;
    };

    std::vector<ToolButton> buttons_ {};

public:
    // -------------------------------------------------------------------------------
    // --- Constructor ---
    
    CToolPalette () {

        // ! DEBUG !

        buttons_.push_back({ 0, "S", Math::Vector2D { 0.0f, 0.0f },  Math::Vector2D { 30.0f, 30.0f } }); // Select
        buttons_.push_back({ 1, "R", Math::Vector2D { 0.0f, 30.0f }, Math::Vector2D { 30.0f, 30.0f } }); // Rectangle

        CSelectTool* select_impl = new CSelectTool();
        ITool* select_tool = nullptr;
        if (select_impl->queryInterface(IID_ITool, (void**)&select_tool)) {
            tools_.push_back(select_tool);
        }
        select_impl->release();

        // ! END OF DEBUG !

    }

    // --- Virtual Destructor ---
    
    ~CToolPalette () override {
        for (auto* tool : tools_) {
            if (tool) tool->release();
        }
        tools_.clear();
    }

    // -------------------------------------------------------------------------------
    // --- Implementing IUnknown ---

    bool queryInterface(const IID& iid, void** ppv) override {
        if (ppv == nullptr) return false;

        if (iid == IID_IUnknown || iid == IID_IWindow || iid == IID_IToolPalette) {
            *ppv = static_cast<IToolPalette*>(this); 
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

        for (const auto& btn : buttons_) {
            Math::Vector2D btn_abs_pos{ pos_.x() + btn.relative_pos.x(), pos_.y() + btn.relative_pos.y() };

            bool is_hovered = (mouse_pos.x() >= btn_abs_pos.x() && mouse_pos.x() <= btn_abs_pos.x() + btn.size.x() &&
                               mouse_pos.y() >= btn_abs_pos.y() && mouse_pos.y() <= btn_abs_pos.y() + btn.size.y());

            Graphic::Color bg_color = (btn.id == active_tool_index_) ? Graphic::Colors::Gray : Graphic::Colors::LightGray;
            if (is_hovered) {
                bg_color = Graphic::Colors::DarkGray;
            }

            adapter->drawRectangle(btn_abs_pos, btn.size, bg_color);
            adapter->drawSelectBox(btn_abs_pos, btn.size, Graphic::Colors::Black, 1.0f);

            if (is_hovered && adapter->isMouseButtonPressed(0)) {
                active_tool_index_ = btn.id;
                updateSelection();
            }
        }

        adapter->drawLine(Math::Vector2D{ pos_.x() + size_.x(), pos_.y() },
                          Math::Vector2D{ pos_.x() + size_.x(), pos_.y() + size_.y() },
                          Graphic::Colors::DarkGray, 1.0f);
    }

    // -------------------------------------------------------------------------------
    // --- Implementing IToolPalette ---

    bool setActiveTool (const IID& tool_id, ITool** tool) override {
        if (tool_id == IID_ITool) {
            active_tool_index_ = 0;
            return getActiveTool(tool);
        }
        return false;
    }
    
    bool getActiveTool (ITool** tool) override {
        if (tool == nullptr || active_tool_index_ >= tools_.size()) return false;

        *tool = tools_[active_tool_index_];
        (*tool)->addRef(); 
        
        return true;
    }
    
    void updateSelection () override {
        // for context bar
    }
};

} // namespace Vectoria

#endif