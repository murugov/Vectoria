#ifndef C_APPLICATION_HPP
#define C_APPLICATION_HPP

#include "Vectoria/Interfaces/Core/IEventListener.hpp"
#include "Vectoria/Interfaces/Core/IGraphicsAdapter.hpp"
#include "Vectoria/Interfaces/Windows/IColorBar.hpp"
#include "Vectoria/Interfaces/Windows/IDocumentWindow.hpp"
#include "Vectoria/Interfaces/Windows/IMainMenu.hpp"
#include "Vectoria/Interfaces/Windows/IToolBar.hpp"

#include "Base/CUnknown.hpp"
#include "Core/CInputController.hpp"
#include "Core/CDocumentManager.hpp"

#include "Builders/CMainMenuBuilder.hpp"

namespace Vectoria {

class CApplication : public CUnknown, public IEventListener {
private:
    IGraphicsAdapter* graphics_adapter_ = nullptr;
    CInputController  input_controller_ {};
    
    IMainMenu*        main_menu_        = nullptr;
    IToolBar*         tool_bar_         = nullptr;
    IColorBar*        color_bar_        = nullptr;
    
    IDocumentManager* document_manager_ = nullptr;
    
    bool              should_close_     = false;

public:
    // -------------------------------------------------------------------------------
    // --- Constructor ---
    
    CApplication () = default;

    // --- Virtual Destructor ---
    
    ~CApplication () override {
        if (graphics_adapter_ != nullptr) graphics_adapter_->release();
        
        if (main_menu_        != nullptr) main_menu_->release();
        if (tool_bar_         != nullptr) tool_bar_->release();
        if (color_bar_        != nullptr) color_bar_->release();
        
        if (document_manager_ != nullptr) document_manager_->release();

    }

    // -------------------------------------------------------------------------------
    // --- Implementing IUnknown ---

    // NOTE: CApplication registers itself as a root EventListener

    bool queryInterface (const IID& iid, void** ppv) override {
        if (ppv == nullptr) return false;
        if (iid == IID_IUnknown || iid == IID_IEventListener) {
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
    // --- Initialization and configuration of the UI tree ---

    bool init (IGraphicsAdapter* adapter) {
        if (adapter == nullptr) return false;
        
        graphics_adapter_ = adapter;
        graphics_adapter_->addRef();

        CDocumentManager* doc_mgr_impl = new CDocumentManager();
        if (!doc_mgr_impl->queryInterface(IID_IDocumentManager, (void**)&document_manager_)) {
            doc_mgr_impl->release();
            return false;
        }
        doc_mgr_impl->release();

        // Main Menu Building
        main_menu_ = CMainMenuBuilder::build("config.json", graphics_adapter_);
        
        if (!main_menu_) {
            // Фолбэк/обработка ошибки, если JSON не загрузился
        }

        // Tool Bar Building
        // tool_bar_ = CToolBarBuilder::build("config.json", graphics_adapter_);
        
        // if (!tool_bar_) {
        // }

        // Color Bar Building
        // color_bar_ = CColorBarBuilder::build("config.json", graphics_adapter_);
        
        // if (!color_bar_) {
        // }

        if (document_manager_ != nullptr) {
            document_manager_->create_document();
        }

        return true;
    }

    // -------------------------------------------------------------------------------
    // --- Main Engine Loop ---

    void run () {
         if (graphics_adapter_ == nullptr) return;
 
         while (!graphics_adapter_->shouldClose() && !should_close_) {
             update();
 
             graphics_adapter_->beginDrawing();
             graphics_adapter_->clearBackground(Graphic::Colors::Black);
             
             render();
             
             graphics_adapter_->endDrawing();
         }
     }
     
private:
    // -------------------------------------------------------------------------------
    // --- Implementing Of Methods ---
    
    void update() {
        input_controller_.update(graphics_adapter_);

        const auto& events = input_controller_.get_events();
        
        for (const auto& event : events) {
            this->onEvent(event);
        }
    }

    void render() {
        if (document_manager_ != nullptr) {
            IDocumentWindow* active_doc = document_manager_->get_active_document();
            if (active_doc != nullptr) {
                active_doc->refresh(graphics_adapter_);
                active_doc->release();
            }
        }

        if (main_menu_ != nullptr) main_menu_->refresh(graphics_adapter_);
        if (tool_bar_  != nullptr) tool_bar_->refresh(graphics_adapter_);
        if (color_bar_ != nullptr) color_bar_->refresh(graphics_adapter_);
    }

    // -------------------------------------------------------------------------------
    // --- Implementing IEventListener ---

    bool onEvent(const Event& event) override {
        if (main_menu_ != nullptr) {
            IEventListener* listener = nullptr;
            if (main_menu_->queryInterface(IID_IEventListener, (void**)&listener)) {
                bool consumed = listener->onEvent(event);
                listener->release();
                if (consumed) return true;
            }
        }

        if (tool_bar_ != nullptr) {
            IEventListener* listener = nullptr;
            if (tool_bar_->queryInterface(IID_IEventListener, (void**)&listener)) {
                bool consumed = listener->onEvent(event);
                listener->release();
                if (consumed) return true;
            }
        }

        if (color_bar_ != nullptr) {
            IEventListener* listener = nullptr;
            if (color_bar_->queryInterface(IID_IEventListener, (void**)&listener)) {
                bool consumed = listener->onEvent(event);
                listener->release();
                if (consumed) return true;
            }
        }

        if (document_manager_ != nullptr) {
            if (document_manager_->onEvent(event)) {
                return true;
            }
        }

        return false;
    }
};

} // namespace Vectoria

#endif