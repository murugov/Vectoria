#ifndef C_SUB_MENU_HPP
#define C_SUB_MENU_HPP

#include <vector>
#include <algorithm>

#include "Vectoria/Interfaces/Core/IActionGroup.hpp"
#include "Vectoria/Interfaces/Core/IEventListener.hpp"

#include "Base/CWindow.hpp"

namespace Vectoria {

constexpr unsigned int MAX_ACTION_COUNT = 32;

class CSubMenu : public CWindow, public IEventListener {
private:
    IActionGroup* action_group_     = nullptr;
    unsigned int  hovered_item_id_  = 0;
    float         item_height_      = 25.0f;

public:
    // -------------------------------------------------------------------------------
    // --- Constructor ---
    
    CSubMenu (IActionGroup* group) {
        if (group) {
            action_group_ = group;
            action_group_->addRef();
        }
    }

    // --- Virtual Destructor ---
    
    ~CSubMenu () override {
        if (action_group_) action_group_->release();
    }

    // -------------------------------------------------------------------------------
    // --- Implementing IUnknown ---

    bool queryInterface (const IID& iid, void** ppv) override {
        if (ppv == nullptr) return false;
        if (iid == IID_IUnknown || iid == IID_IWindow || iid == IID_IWindow || iid == IID_IEventListener) {
            *ppv = static_cast<IEventListener*>(this); 
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

    void refresh (IGraphicsAdapter* adapter) override {
        if (!visible_ || !adapter || !action_group_) return;

        IAction* children[MAX_ACTION_COUNT] = { nullptr };
        size_t total = action_group_->getChildren(children, MAX_ACTION_COUNT);
        size_t count = std::min(total, size_t{ MAX_ACTION_COUNT });

        adapter->drawRectangle(pos_, size_, Graphic::Colors::LightGray);
        adapter->drawRectangleLines(pos_, size_, Graphic::Colors::DarkGray, 1.0f);

        float current_y = pos_.y() + 5.0f;

        for (size_t i = 0; i < count; ++i) {
            IAction* child = children[i];
            if (!child) continue;

            Graphic::Color text_color = child->isEnabled() ? Graphic::Colors::Black : Graphic::Colors::Gray;

            if (child->getID() == hovered_item_id_) {
                adapter->drawRectangle(
                    Math::Vector2D{ pos_.x() + 2.0f, current_y }, 
                    Math::Vector2D{ size_.x() - 4.0f, item_height_ }, 
                    Graphic::Color{ 200, 200, 200, 255 }
                );
            }

            adapter->drawText(child->getLabel(), Math::Vector2D{ pos_.x() + 15.0f, current_y + 4.0f }, 14, text_color);
            current_y += item_height_;
            child->release();
        }
    }

    // -------------------------------------------------------------------------------
    // --- Implementing IEventListener ---

    bool onEvent(const Event& event) override {
        if (!visible_ || !action_group_) return false;

        IAction* children[MAX_ACTION_COUNT] = { nullptr };
        size_t total = action_group_->getChildren(children, 32);
        size_t count = std::min(total, size_t{ 32 });

        // Mouse movement
        if (event.type == EventType::mouse_move) {
            Math::Vector2D mouse_pos = event.mouse.position;
            unsigned int new_hover_id = 0;

            float current_y = pos_.y() + 5.0f;
            for (size_t i = 0; i < count; ++i) {
                if (children[i]) {
                    bool hit = (mouse_pos.x() >= pos_.x() && mouse_pos.x() <= pos_.x() + size_.x() &&
                                mouse_pos.y() >= current_y && mouse_pos.y() <= current_y + item_height_);
                    if (hit && children[i]->isEnabled()) {
                        new_hover_id = children[i]->getID();
                    }
                    current_y += item_height_;
                    children[i]->release();
                }
            }
            hovered_item_id_ = new_hover_id;
            return true;
        }

        // Mouse click
        if (event.type == EventType::mouse_down && event.mouse.button == 0) {
            Math::Vector2D click_pos = event.mouse.position;
            
            bool inside = (click_pos.x() >= pos_.x() && click_pos.x() <= pos_.x() + size_.x() &&
                           click_pos.y() >= pos_.y() && click_pos.y() <= pos_.y() + size_.y());

            if (inside) {
                for (size_t i = 0; i < count; ++i) {
                    if (children[i]) {
                        if (children[i]->getID() == hovered_item_id_) {
                            children[i]->execute();
                            
                            this->close_popup(); 
                            
                            for (size_t j = 0; j < count; ++j) if (children[j]) children[j]->release();
                            return true;
                        }
                        children[i]->release();
                    }
                }
                for (size_t i = 0; i < count; ++i) if (children[i]) children[i]->release();
                return true;
            }

            for (size_t i = 0; i < count; ++i) if (children[i]) children[i]->release();
            this->close_popup();
            return false; 
        }

        for (size_t i = 0; i < count; ++i) if (children[i]) children[i]->release();
        return false;
    }
};

} // namespace Vectoria

#endif