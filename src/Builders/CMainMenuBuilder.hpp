#ifndef C_MAIN_MENU_BUILDER
#define C_MAIN_MENU_BUILDER

#include <fstream>
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>

#include "Vectoria/Interfaces/Core/IGraphicsAdapter.hpp"
#include "Vectoria/Interfaces/Windows/IMainMenu.hpp"

#include "Base/CAction.hpp"
#include "Windows/CMainMenu.hpp"

#include "Builders/CActionBuilder.hpp"

using json = nlohmann::json;

namespace Vectoria {

class CMainMenuBuilder {
public:
    static IMainMenu* build(const std::string& config_path, IGraphicsAdapter* adapter) {
        std::ifstream file(config_path);
        if (!file.is_open()) {
            std::cerr << "Failed to open config file: " << config_path << std::endl;
            return nullptr;
        }

        try {
            json config = json::parse(file);
        
            if (!config.contains("main_menu")) return nullptr;
            const auto& menu_json = config["main_menu"];
    
            CMainMenu* menu_impl = new CMainMenu();
            IMainMenu* main_menu = nullptr;
    
            if (menu_impl->queryInterface(IID_IMainMenu, (void**)&main_menu)) {
                // Parsing color
                if (menu_json.contains("color") && menu_json["color"].is_array()) {
                    Graphic::Color menu_color = Graphic::Colors::Black;
                    
                    auto color_node = menu_json["color"];
                    
                    if (color_node.is_string()) {
                        std::string color_name = color_node.get<std::string>();
                        menu_color = Graphic::Colors::FromString(color_name);
                    }
                    else if (color_node.is_array() && color_node.size() >= 3) {
                        menu_color.r = color_node[0].get<unsigned char>();
                        menu_color.g = color_node[1].get<unsigned char>();
                        menu_color.b = color_node[2].get<unsigned char>();
                        
                        if (color_node.size() == 4) {
                            menu_color.a = color_node[3].get<unsigned char>();
                        } else {
                            menu_color.a = 255;
                        }
                    }
                    main_menu->setColor(menu_color);
                }
    
                // Parsing font
                if (menu_json.contains("font") && adapter) {
                    std::string path = menu_json["font"].value("path", "");
                    int size = menu_json["font"].value("size", 14);
                    main_menu->setFont(adapter->loadFont(path.c_str(), size));
                }
    
                // Parsing bounds
                if (menu_json.contains("bounds")) {
                    const auto& b = menu_json["bounds"];
                    float x = b.value("x", 0.0f);
                    float y = b.value("y", 0.0f);
                    float w = b.value("width", 100.0f);
                    float h = b.value("height", 25.0f);
                    
                    main_menu->setBounds(
                        Math::Vector2D{ x, y },
                        Math::Vector2D{ w, h }
                    );
                }
    
                // Building the CAction structure
                if (menu_json.contains("structure") && menu_json["structure"].is_array()) {
                    for (const auto& group_json : menu_json["structure"]) {
                        CAction* group = CActionBuilder::build(group_json);
                        menu_impl->addActionGroup(group);
                        group->release();
                    }
                }
            }
    
            menu_impl->release();
            return main_menu;
        }
        catch (const json::parse_error& e) {
            std::cerr << "JSON Parse error: " << e.what() << std::endl;
            return nullptr;
        }
    }
};

} // namespace Vectoria

#endif