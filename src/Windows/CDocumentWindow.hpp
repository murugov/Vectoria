#ifndef C_DOCUMENT_WINDOW_HPP
#define C_DOCUMENT_WINDOW_HPP

#include <vector>

#include "Vectoria/Interfaces/Windows/IDocumentWindow.hpp"

#include "Base/CWindow.hpp"

namespace Vectoria {

class CDocumentWindow : public CWindow, public IDocumentWindow {
private:
    std::vector<IShape*> shapes_;

public:
    // -------------------------------------------------------------------------------
    // --- Constructor ---
    
    CDocumentWindow () = default;

    // --- Virtual Destructor ---
    
    ~CDocumentWindow () override {
        clear();
    }
    
    // -------------------------------------------------------------------------------
    // --- Implementing IUnknown ---
    
    bool queryInterface (const IID& iid, void** ppv) override {
        if (ppv == nullptr) return false;

        if (iid == IID_IUnknown || iid == IID_IWindow || iid == IID_IDocumentWindow) {
            *ppv = static_cast<IDocumentWindow*>(this); 
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
    }
    
    void refresh (IGraphicsAdapter* adapter) override {
        if (!visible_) return;

        adapter->beginScissorMode(pos_, size_);
        
        // ! DEBUD !

        adapter->drawSelectBox(pos_, size_, Graphic::Colors::LightGray, 1.0f);

        // ! END OF DEBUD !
        
        for (auto* shape : shapes_) {
            shape->draw(adapter); 
        }

        adapter->endScissorMode(); 
    }

    // -------------------------------------------------------------------------------
    // --- Implementing IDocumentWindow ---
    
    bool addShape (IShape* shape) override {
        if (!shape) return false;
        
        shape->addRef();
        shapes_.push_back(shape);
        
        return true;
    }

    bool removeShape (IShape* shape) override {
        for (auto it = shapes_.begin(); it != shapes_.end(); ++it) {
            if (*it == shape) {
                shape->release();
                shapes_.erase(it);
                
                return true;
            }
        }
        return false;
    }

    size_t getShapeCount () override {
        return shapes_.size();
    }

    bool getShape (size_t index, IShape** shape) override {
        if (!shape || index < 0 || index >= getShapeCount()) return false;
        
        *shape = shapes_[index];
        (*shape)->addRef();
        
        return true;
    }

    void clear () override {
        for (auto* shape : shapes_) {
            shape->release();
        }
        shapes_.clear();
    }
};

} // namespace Vectoria

#endif