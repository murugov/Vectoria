#ifndef C_TOOL_BAR_BUILDER
#define C_TOOL_BAR_BUILDER

#include <fstream>
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>

#include "Vectoria/Interfaces/Core/IGraphicsAdapter.hpp"
#include "Vectoria/Interfaces/Windows/IToolBar.hpp"

#include "Base/CAction.hpp"
#include "Windows/CToolBar.hpp"

#include "Builders/CActionBuilder.hpp"

using json = nlohmann::json;

namespace Vectoria {

class CToolBarBuilder {
public:
    static IToolBar* build(const std::string& config_path, IGraphicsAdapter* adapter) {
        std::ifstream file(config_path);
        if (!file.is_open()) {
            std::cerr << "Failed to open config file: " << config_path << std::endl;
            return nullptr;
        }

        try {
            json config = json::parse(file);
        
            if (!config.contains("tool_bar")) return nullptr;
            const auto& tools_json = config["tool_bar"];
    
            CToolBar* tools_impl = new CToolBar();
            IToolBar* tool_bar = nullptr;
    
            if (tools_impl->queryInterface(IID_IToolBar, (void**)&tool_bar)) {
                // Parsing bounds
                if (tools_json.contains("bounds")) {
                    const auto& b = tools_json["bounds"];
                    float x = b.value("x", 0.0f);
                    float y = b.value("y", 0.0f);
                    float w = b.value("width", 100.0f);
                    float h = b.value("height", 25.0f);
                    
                    tool_bar->setBounds(
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