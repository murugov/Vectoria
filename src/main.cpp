#include "Vectoria/Interfaces/Core/IGraphicsAdapter.hpp"
#include "Vectoria/Interfaces/Windows/IDocumentWindow.hpp"
#include "Vectoria/Interfaces/Core/IController.hpp"

#include "Graphics/CGraphicsAdapter.hpp"
#include "Windows/CDocumentWindow.hpp"
#include "Core/CController.hpp"

int main() {
    Vectoria::IGraphicsAdapter* graphics_adapter = nullptr;
    
    // 1. Инициализируем графический движок через фабрику (откроет окно Raylib)
    if (!Vectoria::createGraphicsAdapter(1280, 720, "Vectoria CorelDraw (COM Edition)", &graphics_adapter)) {
        return -1; 
    }

    // 2. Создаем холст документа по правилам COM
    Vectoria::CDocumentWindow* doc_impl = new Vectoria::CDocumentWindow();
    Vectoria::IDocumentWindow* document_window = nullptr;
    
    doc_impl->queryInterface(Vectoria::IID_IDocumentWindow, (void**)&document_window);
    doc_impl->release(); // Уменьшаем счетчик после 'new'

    // Задаем границы холста на экране (используем явный Vectoria::Math::Vector2D)
    document_window->setBounds(
        Math::Vector2D{ 50.0f, 50.0f }, 
        Math::Vector2D{ 1180.0f, 620.0f }
    );

    // 3. Создаем центральный контроллер приложения
    Vectoria::CController* controller_impl = new Vectoria::CController();
    Vectoria::IController* app_controller = nullptr;
    
    controller_impl->queryInterface(Vectoria::IID_IController, (void**)&app_controller);
    controller_impl->release();

    // Связываем всю систему воедино внутри контроллера
    app_controller->initialize(graphics_adapter, document_window);

    // Локальный указатель на холст больше не нужен, контроллер сделал AddRef()
    document_window->release();

    // --- ГЛАВНЫЙ ИГРОВОЙ ЦИКЛ (Полная бинарная изоляция) ---
    while (!graphics_adapter->shouldClose()) {
        // 1. Обработка ввода и логика инструментов
        app_controller->update();

        // 2. Рендеринг сцены
        graphics_adapter->beginDrawing();
        
        // Очищаем фон приложения (используем явную структуру цвета из Graphic)
        graphics_adapter->clearBackground(Graphic::Colors::DarkGray);
        
        // Диспетчеризация отрисовки холста и превью через контроллер
        app_controller->render();
        
        graphics_adapter->endDrawing();
    }

    // 4. Финал: уничтожаем контроллер, он по цепочке освободит холст и инструменты
    app_controller->release();
    
    // Освобождаем адаптер — его деструктор безопасно закроет Raylib окно
    graphics_adapter->release(); 

    return 0;
}
