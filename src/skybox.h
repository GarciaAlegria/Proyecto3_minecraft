#pragma once 
 
#include <string> 
#include <glm/glm.hpp> 
#include "color.h" 
 
class Skybox { 
public: 
    Skybox(const std::string& textureFile); 
    ~Skybox(); 
     
    Color getColor(const glm::vec3& direction) const; 
 
private: 
    SDL_Surface* texture; 
    void loadTexture(const std::string& textureFile); 
};