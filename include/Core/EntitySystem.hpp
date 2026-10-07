#include <iostream>
#include <vector>
#include <memory>
#include <unordered_map>
#include <algorithm>

// Идентификатор сущности — обычное число
using EntityID = unsigned int;

// Простой интерфейс команды для логики кнопки
class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
};

class SaveCommand : public Command {
public:
    void execute() override { std::cout << "[Команда] Документ сохранен!\n"; }
};

// =================================================================
// 1. КОМПОНЕНТЫ (Чистые данные, никакой логики)
// =================================================================

// Компонент геометрии (где находится объект)
struct TransformComponent {
    float x, y, w, h;
};

// Графический компонент (как выглядит). Текстура лежит строго здесь!
struct RenderComponent {
    std::string textureName; 
    std::string color;
};

// Состояния кнопки для графики
enum class ButtonState { Normal, Hovered, Pressed };

// Компонент кликабельности (клики, состояния, команды)
struct UIBehaviorComponent {
    ButtonState state = ButtonState::Normal;
    std::shared_ptr<Command> command;
};

// =================================================================
// 2. РЕЕСТР / МЕНЕДЖЕР СУЩНОСТЕЙ (Entity Manager)
// =================================================================
// Хранит списки компонентов, сопоставленные с ID сущностей.
class Registry {
private:
    EntityID m_nextEntityID = 0;

public:
    // Хранилища для каждого типа компонентов (карта: EntityID -> Компонент)
    std::unordered_map<EntityID, TransformComponent> transforms;
    std::unordered_map<EntityID, RenderComponent> renders;
    std::unordered_map<EntityID, UIBehaviorComponent> uiBehaviors;

    // Создать новую пустую сущность
    EntityID createEntity() {
        return m_nextEntityID++;
    }
};

// =================================================================
// 3. СИСТЕМЫ (Чистая логика, у них нет своих данных)
// =================================================================

// --- СИСТЕМА ВВОДА (InputSystem) ---
// Занимается ТОЛЬКО координатами и кликами. Про текстуры она ничего не знает!
class UISystem {
public:
    void update(Registry& registry, float mouseX, float mouseY, bool isMouseClicked) {
        // Проходим по всем сущностям, у которых есть И координаты, И UI-поведение
        for (auto& [entity, ui] : registry.uiBehaviors) {
            // Проверяем, есть ли у этой сущности координаты
            if (registry.transforms.find(entity) == registry.transforms.end()) continue;
            
            const auto& transform = registry.transforms[entity];

            // Проверка: находится ли мышь над объектом (AABB тест)
            bool isHovered = (mouseX >= transform.x && mouseX <= transform.x + transform.w &&
                              mouseY >= transform.y && mouseY <= transform.y + transform.h);

            // Логика изменения состояний
            if (isHovered) {
                if (isMouseClicked) {
                    ui.state = ButtonState::Pressed;
                    if (ui.command) {
                        ui.command->execute(); // Выполняем команду кнопки
                    }
                } else {
                    ui.state = ButtonState::Hovered;
                }
            } else {
                ui.state = ButtonState::Normal;
            }
        }
    }
};

// --- СИСТЕМА ОТРИСОВКИ (RenderSystem) ---
// Занимается ТОЛЬКО рисованием картинок по координатам. Про клики она ничего не знает!
class RenderSystem {
public:
    void render(const Registry& registry) {
        // Проходим по всем сущностям, у которых есть И координаты, И графика
        for (const auto& [entity, render] : registry.renders) {
            if (registry.transforms.find(entity) == registry.transforms.end()) continue;

            const auto& transform = registry.transforms.at(entity);
            
            // Проверяем, есть ли у объекта состояние UI, чтобы скорректировать цвет
            std::string finalColor = render.color;
            if (registry.uiBehaviors.find(entity) != registry.uiBehaviors.end()) {
                auto state = registry.uiBehaviors.at(entity).state;
                if (state == ButtonState::Hovered) finalColor = "Светло-" + finalColor;
                if (state == ButtonState::Pressed) finalColor = "Темно-" + finalColor;
            }

            // Имитация вызова графического движка
            std::cout ()}; // Логика клика

    // --- СОЗДАЕМ ДЕКОРАТИВНОЕ ДЕРЕВО (Для сравнения) ---
    // У дерева есть координаты и текстура, но нет компонента UIBehavior. 
    // UISystem его просто проигнорирует, а RenderSystem — нарисует!
    EntityID tree = registry.createEntity();
    registry.transforms[tree] = {500.0f, 400.0f, 64.0f, 128.0f};
    registry.renders[tree] = {"tree_texture.png", "Зеленый"};

    // --- ИГРОВОЙ / UI ЦИКЛ ---
    std::cout << "--- Кадр 1: Мышь далеко ---\n";
    uiSystem.update(registry, 0.0f, 0.0f, false);
    renderSystem.render(registry);
    std::cout << "--------------------------------------\n\n";

    std::cout << "--- Кадр 2: Мышь наведена на кнопку ---\n";
    uiSystem.update(registry, 150.0f, 160.0f, false); // Мышь внутри кнопки (100-300, 150-200)
    renderSystem.render(registry);
    std::cout << "--------------------------------------\n\n";

    std::cout << "--- Кадр 3: Клик по кнопке ---\n";
    uiSystem.update(registry, 150.0f, 160.0f, true); // Клик мышкой
    renderSystem.render(registry);
    std::cout << "--------------------------------------\n";

    return 0;
}
