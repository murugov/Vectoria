#ifndef C_MAIN_MENU_HPP
#define C_MAIN_MENU_HPP

#include <vector>
#include <string>
#include <algorithm>

#include "Vectoria/Interfaces/Base/IAction.hpp"
#include "Vectoria/Interfaces/Core/IActionGroup.hpp"
#include "Vectoria/Interfaces/Core/IEventListener.hpp"
#include "Vectoria/Interfaces/Core/IGraphicsAdapter.hpp"
#include "Vectoria/Interfaces/Windows/IMainMenu.hpp"
#include "Vectoria/Shared/Graphic/Colors.hpp"
#include "Vectoria/Shared/Graphic/Font.hpp"

#include "Base/CWindow.hpp"

namespace Vectoria {

class CMainMenu : public CWindow, public IMainMenu, public IEventListener { 
private:
    std::vector<IAction*> root_actions_ {};
    IAction*              active_submenu_ = nullptr;
    unsigned int          hovered_item_id_ = 0;

    Graphic::Color        bg_color_ = Graphic::Colors::White;
    Graphic::Font         menu_font_ {};
    
    float                 item_width_       = 70.0f;
    float                 item_height_      = 25.0f; 
    int                   font_size_root_   = 16;
    int                   font_size_sub_    = 14; 
    


public:
    // -------------------------------------------------------------------------------
    // --- Constructor ---
    
    CMainMenu () = default;

    // --- Destructor ---
    
    ~CMainMenu () override {
        if (active_submenu_ != nullptr) {
            active_submenu_->release();
        }
        for (auto* action : root_actions_) {
            action->release();
        }
    }

    // -------------------------------------------------------------------------------
    // --- Public method for configuring the menu from the outside ---
    
    void addActionGroup (IAction* action_group) {
        if (action_group != nullptr) {
            action_group->addRef();
            root_actions_.push_back(action_group);
        }
    }

    // -------------------------------------------------------------------------------
    // --- Implementing IUnknown ---

    bool queryInterface (const IID& iid, void** ppv) override {
        if (ppv == nullptr) return false;
        if (iid == IID_IUnknown || iid == IID_IWindow || iid == IID_IMainMenu || iid == IID_IEventListener) {
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

    void setBounds (const Math::Vector2D& pos, const Math::Vector2D& size) override {
        CWindow::setBounds(pos, size);
    }

    void getBounds (Math::Vector2D* pos, Math::Vector2D* size) override {
        CWindow::getBounds(pos, size);
    }

    void show (bool visible) override {
        CWindow::show(visible);
        if (!visible && active_submenu_ != nullptr) {
            active_submenu_->release();
            active_submenu_ = nullptr;
        }
    }

    // -------------------------------------------------------------------------------
    // --- UI Layout & Rendering (Immediate Mode) ---

    void refresh (IGraphicsAdapter* adapter) override {
        
    }

    // -------------------------------------------------------------------------------
    // --- Implementing IEventListener ---
    
    bool onEvent (const Event& event) override {
        
    }
    
    // -------------------------------------------------------------------------------
    // --- Implementing IMainMenu ---

    void setColor (const Graphic::Color& color) override {
        bg_color_ = color;
    }
    
    void setFont (const Graphic::Font& font) override {
        menu_font_ = font;
    }
    
//     void setItemEnabled (unsigned int command_id, bool enabled) override {
//         IAction* target = findActionByID(command_id);
//         if (target != nullptr) {
//             target->setEnabled(enabled);
//         }
//     }

//     void onMenuCommand (unsigned int command_id) override {
//         IAction* target = findActionByID(command_id);
//         if (target != nullptr && target->isEnabled()) {
//             target->execute();
//         }
//     }

// private:
//     IAction* findActionByID (unsigned int id) {
//         for (auto* action : root_actions_) {
//             IAction* res = findRecursive(action, id);
//             if (res != nullptr) return res;
//         }
//         return nullptr;
//     }

//     IAction* findRecursive (IAction* current, unsigned int id) {
//         if (current == nullptr) return nullptr;
//         if (current->getID() == id) return current;
    
//         if (current->isGroup()) {
//             IAction* children[32] = { nullptr };
//             size_t total = current->getChildren(children, 32);
//             size_t count = std::min(total, size_t{ 32 });
    
//             IAction* found_target = nullptr;
    
//             for (size_t i = 0; i < count; ++i) {
//                 if (children[i] != nullptr) {
//                     if (found_target == nullptr) {
//                         found_target = findRecursive(children[i], id);
//                     }
//                     children[i]->release(); 
//                 }
//             }
//             return found_target;
//         }
//         return nullptr;
//     }
};

} // namespace Vectoria

#endif