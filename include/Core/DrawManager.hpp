#ifndef DRAW_MANAGER_HPP
#define DRAW_MANAGER_HPP

#include <vector>
#include <memory>
#include "DrawObject.hpp"

namespace Core {

class DrawManager {
private:
    std::vector<std::unique_ptr<DrawObject>> objects_ {};
    Graphic::Color active_palette_color_ = Graphic::Colors::Black;

public:
    // -------------------------------------------------------------------------------
    // --- Сonstructor ---

    DrawManager () = default;

    // --- Copy Semantics Disabled ---
    
    DrawManager (const DrawManager&) = delete;
    DrawManager& operator = (const DrawManager&) = delete;
 
    // --- Move Semantics ---
    
    DrawManager (DrawManager&&) = default;
    DrawManager& operator = (DrawManager&&) = default;
     
    // --- Destructor ---

    ~DrawManager () = default;

    // -------------------------------------------------------------------------------
    // --- Getters ---

    const std::vector<std::unique_ptr<DrawObject>>& objects     () const { return objects_; }
    size_t                                          objectCount () const { return objects_.size(); }

    // -------------------------------------------------------------------------------
    // --- Setters ---

    void setActivePaletteColor (Graphic::Color color) { active_palette_color_ = color; }

    // -------------------------------------------------------------------------------
    // --- Methods Prototypes ---
    
    void addObject     (std::unique_ptr<DrawObject> obj);
    void setAllObjects (bool state);
    void removeObject  (const DrawObject* obj);


    void update (float dt);
    void draw   () const;
    
    void clear ();

};

} // namespace Core

#endif