#ifndef C_CONTROLLER_HPP
#define C_CONTROLLER_HPP

#ifndef interface
#define interface struct
#endif

#include "Vectoria/Base/CUnknown.hpp"
#include "Vectoria/Interfaces/Components/ITool.hpp"
#include "Vectoria/Interfaces/Core/IController.hpp"
#include "Vectoria/Interfaces/Core/IGraphicsAdapter.hpp"
#include "Vectoria/Interfaces/Windows/IDocumentWindow.hpp"

#include "Tools/CSelectTool.hpp"

namespace Vectoria {

class CController : public CUnknown, public IController {
private:
    IGraphicsAdapter* adapter_ = nullptr;
    IDocumentWindow*  doc_ = nullptr;
    ITool*            active_tool_ = nullptr;

public:
    CController() = default;
    
    ~CController() override {
        if (active_tool_)    active_tool_->release();
        if (doc_)            doc_->release();
        if (adapter_)        adapter_->release();
    }

    // --- Implementing IUnknown ---
    bool queryInterface(const IID& iid, void** ppv) override {
        if (ppv == nullptr) return false;
        if (iid == IID_IUnknown || iid == IID_IController) {
            *ppv = static_cast<IController*>(this);
        } else {
            *ppv = nullptr;
            return false;
        }
        static_cast<IUnknown*>(*ppv)->addRef();
        return true;
    }

    void addRef() override { CUnknown::addRef(); }
    void release() override { CUnknown::release(); }

    // --- Implementing IController ---
    
    void initialize(IGraphicsAdapter* adapter, IDocumentWindow* doc) override {
        if (adapter) { adapter_ = adapter; adapter_->addRef(); }
        if (doc)     { doc_ = doc;         doc_->addRef(); }
        
        // По умолчанию при старте включаем инструмент выделения
        setInstrument(IID_ITool); 
    }

    bool setInstrument(const IID& tool_id) override {
        // Зачищаем старый инструмент
        if (active_tool_) {
            active_tool_->release();
            active_tool_ = nullptr;
        }

        // Простейшая фабрика инструментов на основе GUID (Глава 7 Роджерсона)
        if (tool_id == IID_ITool) { // Предположим, это ID для SelectTool
            CSelectTool* select_impl = new CSelectTool();
            select_impl->queryInterface(IID_ITool, (void**)&active_tool_);
            select_impl->release();
            return true;
        }
        // Здесь в будущем будет: else if (tool_id == IID_IPenTool) { ... }

        return false;
    }

    void update() override {
        if (!adapter_ || !active_tool_ || !doc_) return;

        Math::Vector2D mouse_pos = adapter_->getMousePosition();

        // 0 - MOUSE_BUTTON_LEFT в Raylib
        if (adapter_->isMouseButtonPressed(0)) {
            active_tool_->onMouseDown(mouse_pos, doc_);
        }
        
        active_tool_->onMouseMove(mouse_pos, doc_);

        if (adapter_->isMouseButtonReleased(0)) {
            active_tool_->onMouseUp(mouse_pos, doc_);
        }

        // Пример переключения инструментов с клавиатуры:
        // Если нажали 'S' -> включаем SelectTool, если 'P' -> PenTool
        if (adapter_->isKeyPressed(83)) { // 83 = KEY_S
            setInstrument(IID_ITool);
        }
    }

    void render() override {
        if (!adapter_ || !doc_) return;

        // Холст документа рисует стабильную геометрию
        doc_->refresh(adapter_);
        
        // Инструмент дорисовывает пунктирные превьюшки выделения или создания
        if (active_tool_) {
            active_tool_->drawPreview(adapter_);
        }
    }
};

} // namespace Vectoria

#endif