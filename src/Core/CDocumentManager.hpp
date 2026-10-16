#ifndef C_DOCUMENT_MANAGER_HPP
#define C_DOCUMENT_MANAGER_HPP

#include <vector>

#include "Vectoria/Interfaces/Core/IDocumentManager.hpp"

#include "Base/CUnknown.hpp"
#include "Windows/CDocumentWindow.hpp"

namespace Vectoria {

class CDocumentManager : public CUnknown, public IDocumentManager {
private:
    std::vector<IDocumentWindow*> docs_ {};
    unsigned int                  active_doc_index_ = 0;

public:
    // -------------------------------------------------------------------------------
    // --- Constructor ---
    
    CDocumentManager () = default;

    // --- Virtual Destructor ---
    
    ~CDocumentManager () override {
        for (auto* doc : docs_) {
            if (doc != nullptr) doc->release();
        }
        docs_.clear();
    }

    // -------------------------------------------------------------------------------
    // --- Implementing IUnknown ---
    
    bool queryInterface (const IID& iid, void** ppv) override {
        if (ppv == nullptr) return false;
        if (iid == IID_IUnknown || iid == IID_IEventListener || iid == IID_IDocumentManager) {
            *ppv = static_cast<IDocumentManager*>(this);
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
    // --- Implementing IDocumentManager ---
    
    bool create_document () override {
        CDocumentWindow* doc_impl = new CDocumentWindow();
        IDocumentWindow* new_doc = nullptr;
        
        if (doc_impl->queryInterface(IID_IDocumentWindow, (void**)&new_doc)) {
            new_doc->setBounds(Math::Vector2D{ 50.0f, 50.0f }, Math::Vector2D{ 1180.0f, 640.0f });
            
            docs_.push_back(new_doc);
            active_doc_index_ = static_cast<unsigned int>(docs_.size() - 1);
            
            doc_impl->release();
            return true;
        }
        doc_impl->release();
        return false;
    }

    void close_active_document () override {
        if (docs_.empty()) return;

        docs_[active_doc_index_]->release();
        docs_.erase(docs_.begin() + active_doc_index_);

        if (active_doc_index_ >= docs_.size() && !docs_.empty()) {
            active_doc_index_ = static_cast<unsigned int>(docs_.size() - 1);
        } else if (docs_.empty()) {
            active_doc_index_ = 0;
        }
    }

    IDocumentWindow* get_active_document () override {
        if (docs_.empty()) return nullptr;
        
        IDocumentWindow* active = docs_[active_doc_index_];
        if (active != nullptr) active->addRef();
        
        return active;
    }

    unsigned int get_document_count () override {
        return static_cast<unsigned int>(docs_.size());
    }

    void set_active_document_index (unsigned int index) override {
        if (index < docs_.size()) {
            active_doc_index_ = index;
        }
    }

    unsigned int get_active_document_index () override {
        return active_doc_index_;
    }

    // -------------------------------------------------------------------------------
    // --- Implementing IEventListener ---
    
    bool onEvent (const Event& event) override {
        if (docs_.empty()) return false;

        IDocumentWindow* active = docs_[active_doc_index_];
        IEventListener* listener = nullptr;
        
        if (active != nullptr && active->queryInterface(IID_IEventListener, (void**)&listener)) {
            bool consumed = listener->onEvent(event);
            listener->release();
            return consumed;
        }
        return false;
    }
};

} // namespace Vectoria

#endif