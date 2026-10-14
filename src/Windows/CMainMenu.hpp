#ifndef C_MAIN_MENU_HPP
#define C_MAIN_MENU_HPP

#include <vector>
#include <string>
#include "Vectoria/Base/CWindow.hpp"
#include "Vectoria/Interfaces/Windows/IMainMenu.hpp"
#include "Vectoria/Interfaces/Core/IGraphicsAdapter.hpp"

namespace Vectoria {

class CMainMenu : public CWindow, public IMainMenu {
private:
    struct MenuItem {
        unsigned int id;
        std::string label;
        bool is_enabled;
    };

    std::vector<MenuItem> items_ {};

public:
    // -------------------------------------------------------------------------------
    // --- Constructor ---
    
    CMainMenu () {
        // ! DEBUG !
        
        items_.push_back({ 101, "File", true });
        items_.push_back({ 102, "Edit", true });
        items_.push_back({ 103, "Help", true });

        // ! END OF DEBUD !
    }

    // --- Virtual Destructor ---
    
    ~CMainMenu() override = default;

    // -------------------------------------------------------------------------------
    // --- Implementing IUnknown ---

    bool queryInterface(const IID& iid, void** ppv) override {
        if (ppv == nullptr) return false;

        if (iid == IID_IUnknown || iid == IID_IWindow || iid == IID_IMainMenu) {
            *ppv = static_cast<IMainMenu*>(this); 
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

        float current_x = pos_.x() + 20.0f;
        // float text_y = pos_.y() + 10.0f;

        for (const auto& item : items_) {
            Graphic::Color text_color = item.is_enabled ? Graphic::Colors::Black : Graphic::Colors::Gray;
            
            Math::Vector2D mouse_pos = adapter->getMousePosition();
            
            bool is_hovered = (mouse_pos.x() >= current_x && mouse_pos.x() <= current_x + 60.0f &&
                               mouse_pos.y() >= pos_.y() && mouse_pos.y() <= pos_.y() + size_.y());

            if (is_hovered && item.is_enabled) {
                adapter->drawRectangle(Math::Vector2D{ current_x - 5.0f, pos_.y() + 2.0f }, 
                                       Math::Vector2D{ 70.0f, size_.y() - 4.0f }, 
                                       Graphic::Colors::Gray);
                
                if (adapter->isMouseButtonPressed(0)) {
                    onMenuCommand(item.id);
                }
            }

            // ! DEBUG !
            adapter->drawSelectBox(Math::Vector2D{ current_x, pos_.y() + 5.0f }, 
                                   Math::Vector2D{ 60.0f, size_.y() - 10.0f }, 
                                   text_color, 1.0f);

            current_x += 80.0f;

            // ! END OF DEBUD !
        }

        adapter->drawLine(Math::Vector2D{ pos_.x(), pos_.y() + size_.y() }, 
                          Math::Vector2D{ pos_.x() + size_.x(), pos_.y() + size_.y() }, 
                          Graphic::Colors::DarkGray, 1.0f);
    }

    // -------------------------------------------------------------------------------
    // --- Implementing IMainMenu ---

    void setItemEnabled(unsigned int command_id, bool enabled) override {
        for (auto& item : items_) {
            if (item.id == command_id) {
                item.is_enabled = enabled;
                break;
            }
        }
    }

    void onMenuCommand(unsigned int command_id) override {
        if (command_id == 101) {
            // click File
        }
    }
};

} // namespace Vectoria

#endif
