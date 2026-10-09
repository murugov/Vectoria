#ifndef SCENE_HPP
#define SCENE_HPP

#include "Core/DrawManager.hpp"
#include "Graphic/Camera.hpp"
#include "Graphic/Canvas.hpp"
#include "Graphic/Texture.hpp"

namespace Core {
    
class Scene {
private:
    Graphic::Canvas document_canvas_;
    Graphic::Camera camera_;
    DrawManager draw_manager_;

public:
    // -------------------------------------------------------------------------------
    // --- Сonstructor ---

    Scene (Math::Vector2D pos, int width, int height, const std::string& texture_path)
        : document_canvas_(pos, width, height, Graphic::SpriteMaterial(Graphic::Texture(texture_path)))
        , camera_(pos, pos)
        {}

    Scene (Math::Vector2D pos, int width, int height, Graphic::Texture&& texture)
        : document_canvas_(pos, width, height, Graphic::SpriteMaterial(std::move(texture)))
        ,camera_(pos, pos)
        {}
            
    Scene (Math::Vector2D pos, int width, int height, Graphic::Color bg_color)
        : document_canvas_(pos, width, height, Graphic::SpriteMaterial(bg_color))
        ,camera_(pos, pos)
        {}

    Scene (Graphic::Canvas&& document_canvas) 
        : document_canvas_(std::move(document_canvas))
        , camera_(document_canvas_.pos(), document_canvas_.pos()) {}
        
    // --- Destructor ---

    ~Scene () = default;

    // -------------------------------------------------------------------------------
    // --- Getters ---
    
    const Graphic::Canvas& canvas () const { return document_canvas_; }
    Graphic::Canvas&       canvas ()       { return document_canvas_; }

    const Graphic::Camera& camera () const { return camera_; }
    Graphic::Camera&       camera ()       { return camera_; }
    
    const DrawManager& drawManager () const { return draw_manager_; }
    DrawManager&       drawManager ()       { return draw_manager_; }
    
    // -------------------------------------------------------------------------------
    // --- Methods Prototypes ---
    
    void bind   () const;
    void unbind () const;

    void update (float dt);
    void draw   () const;
    
    void clear ();
};

} // namespace Core

#endif