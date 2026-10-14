#ifndef C_DESKTOP_HPP
#define C_DESKTOP_HPP

#include <vector>
#include "Vectoria/Base/CUnknown.hpp"
#include "Vectoria/Interfaces/Components/ITool.hpp"
#include "Vectoria/Interfaces/Core/IDesktop.hpp"
#include "Vectoria/Interfaces/Core/IGraphicsAdapter.hpp"
#include "Vectoria/Interfaces/Windows/IColorPalette.hpp"
#include "Vectoria/Interfaces/Windows/IDocumentWindow.hpp"
#include "Vectoria/Interfaces/Windows/IMainMenu.hpp"
#include "Vectoria/Interfaces/Windows/IToolPalette.hpp"

#include "Windows/CColorPalette.hpp"
#include "Windows/CDocumentWindow.hpp"
#include "Windows/CMainMenu.hpp"
#include "Windows/CToolPalette.hpp"

namespace Vectoria {

class CDesktop : public CUnknown, public IDesktop {
private:
    std::vector<IDocumentWindow*> docs_ {};
    size_t active_doc_index_ = 0; 

    IMainMenu*     main_menu_     = nullptr;
    IToolPalette*  tool_palette_  = nullptr;
    IColorPalette* color_palette_ = nullptr;
    
    IGraphicsAdapter* adapter_ = nullptr;

public:
    // -------------------------------------------------------------------------------
    // --- Constructor ---
    
    CDesktop () = default;

    // --- Virtual Destructor ---
    
    ~CDesktop () override {
        for (auto* doc : docs_) {
            if (doc) doc->release();
        }
        docs_.clear();

        if (main_menu_)     main_menu_->release();
        if (tool_palette_)  tool_palette_->release();
        if (color_palette_) color_palette_->release();
        
        if (adapter_)       adapter_->release();
    }

    // -------------------------------------------------------------------------------
    // --- Implementing IUnknown ---
    
    bool queryInterface (const IID& iid, void** ppv) override {
        if (ppv == nullptr) return false;
        if (iid == IID_IUnknown || iid == IID_IDesktop) {
            *ppv = static_cast<IDesktop*>(this);
        } else {
            *ppv = nullptr;
            return false;
        }
        static_cast<IUnknown*>(*ppv)->addRef();
        return true;
    }

    void addRef  () override { CUnknown::addRef(); }
    void release () override { CUnknown::release(); }

    // -------------------------------------------------------------------------------
    // --- Implementing IDesktop ---
    
    void initialize (IGraphicsAdapter* adapter) override {
        if (adapter) { 
            adapter_ = adapter; 
            adapter_->addRef(); 
        }

        CMainMenu* menu_impl = new CMainMenu();
        if (menu_impl->queryInterface(IID_IMainMenu, (void**)&main_menu_)) {
            main_menu_->setBounds(
                Math::Vector2D{ 0.0f, 0.0f },
                Math::Vector2D{ 1280.0f, 25.0f }
            );
        }
        menu_impl->release(); 

        CToolPalette* tool_plt_impl = new CToolPalette();
        if (tool_plt_impl->queryInterface(IID_IToolPalette, (void**)&tool_palette_)) {
            tool_palette_->setBounds(
                Math::Vector2D{ 0.0f, 75.0f },
                Math::Vector2D{ 30.0f, 645.0f }
            );
        }
        tool_plt_impl->release();
       
        CColorPalette* color_plt_impl = new CColorPalette();
        if (color_plt_impl->queryInterface(IID_IColorPalette, (void**)&color_palette_)) {
            color_palette_->setBounds(
                Math::Vector2D{ 1250.0f, 75.0f },
                Math::Vector2D{ 30.0f, 645.0f }
            );
        }
        color_plt_impl->release();  
        
        setActiveDocument(IID_IDocumentWindow); 
    }

    bool setActiveDocument (const IID& doc_id) override {
        if (doc_id == IID_IDocumentWindow) {
            CDocumentWindow* doc_impl = new CDocumentWindow();
            IDocumentWindow* new_doc = nullptr;
            
            if (doc_impl->queryInterface(IID_IDocumentWindow, (void**)&new_doc)) {
                new_doc->setBounds(
                       Math::Vector2D{ 50.0f, 50.0f }, 
                       Math::Vector2D{ 1180.0f, 620.0f }
                );
                
                docs_.push_back(new_doc);
                active_doc_index_ = docs_.size() - 1;
                doc_impl->release();
                return true;
            }
            doc_impl->release();
        }
        return false;
    }

    void update() override {
        if (!adapter_ || docs_.empty() || !tool_palette_) return;

        if (main_menu_) {
            main_menu_->refresh(adapter_);
        }
        
        ITool* active_tool = nullptr;
        if (!tool_palette_->getActiveTool(&active_tool) || !active_tool) return;
        
        Math::Vector2D mouse_pos = adapter_->getMousePosition();
        IDocumentWindow* current_doc = docs_[active_doc_index_];

        if (adapter_->isMouseButtonPressed(0)) {
            active_tool->onMouseDown(mouse_pos, current_doc);
        }
        
        active_tool->onMouseMove(mouse_pos, current_doc);

        if (adapter_->isMouseButtonReleased(0)) {
            active_tool->onMouseUp(mouse_pos, current_doc);
        }

        active_tool->release();

        if (color_palette_) {
            color_palette_->refresh(adapter_);
        }
    }

    void render() override {
        if (!adapter_ || docs_.empty() || !tool_palette_) return;

        docs_[active_doc_index_]->refresh(adapter_); 

        if (main_menu_) {
            main_menu_->refresh(adapter_);
        }
        
        ITool* active_tool = nullptr;
        if (tool_palette_->getActiveTool(&active_tool) && active_tool) {
            active_tool->drawPreview(adapter_);
            active_tool->release();
        }

        tool_palette_->refresh(adapter_);
        
        if (color_palette_) {
            color_palette_->refresh(adapter_);
        }
    }
};

} // namespace Vectoria

#endif