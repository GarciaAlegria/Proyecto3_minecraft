#include "skybox.h" 
#include <SDL_image.h> 
 
Skybox::Skybox(const std::string& textureFile) { 
    loadTexture(textureFile); 
} 
 
Skybox::~Skybox() { 
    SDL_FreeSurface(texture); 
} 
 
void Skybox::loadTexture(const std::string& textureFile) { 
    /* 
    texture = IMG_Load(textureFile.c_str()); 
    if (!texture) { 
        throw std::runtime_error("Failed to load skybox texture: " + std::string(IMG_GetError())); 
    } 
    */ 
     
    SDL_Surface* rawTexture = IMG_Load(textureFile.c_str()); 
    if (!rawTexture) { 
        throw std::runtime_error("Failed to load skybox texture: " + std::string(IMG_GetError())); 
    } 
    // Convert the loaded image to RGB format 
    texture = SDL_ConvertSurfaceFormat(rawTexture, SDL_PIXELFORMAT_RGB24, 0); 
    if (!texture) { 
        SDL_FreeSurface(rawTexture); 
        throw std::runtime_error("Failed to convert skybox texture to RGB: " + std::string(SDL_GetError())); 
    } 
    SDL_FreeSurface(rawTexture); 
} 
 
Color Skybox::getColor(const glm::vec3& direction) const { 
    // Normalizar la dirección para asegurar un cálculo preciso 
    glm::vec3 normalizedDirection = glm::normalize(direction); 
 
    // Calcular las coordenadas de textura basadas en la dirección del rayo 
    float u = 0.5f + atan2(normalizedDirection.z, normalizedDirection.x) / (2.0f * M_PI); 
    float v = 0.5f - asin(normalizedDirection.y) / M_PI; 
 
    // Asegurarse de que las coordenadas estén en el rango [0, 1] 
    u = glm::clamp(u, 0.0f, 1.0f); 
    v = glm::clamp(v, 0.0f, 1.0f); 
 
    // Mapear coordenadas de textura a píxeles 
    int x = static_cast<int>(u * texture->w) % texture->w; 
    int y = static_cast<int>(v * texture->h) % texture->h; 
 
    // Obtener el color del píxel de la textura 
    Uint8 r, g, b; 
    Uint8* pixel = &((Uint8*)texture->pixels)[3 * (y * texture->w + x)]; 
    r = pixel[0]; 
    g = pixel[1]; 
    b = pixel[2]; 
 
    return Color(r, g, b); 
}