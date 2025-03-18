/**
* Author: Amani Hernandez (amh9766)
* Assignment: Lunar Lander
* Date due: 2025-3-18, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/
#define GL_SILENCE_DEPRECATION
#define STB_IMAGE_IMPLEMENTATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#define GL_GLEXT_PROTOTYPES 1
#include <SDL.h>
#include <SDL_opengl.h>

#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Entity.h"
#include "PlatformEntity.h"
#include "lunar_lib.h"

PlatformEntity::PlatformEntity(glm::vec3 position, float width, float height, 
    float x_offset, float y_offset, GLuint texture_id)
    : Entity(position, width, height, texture_id),
      m_x_offset(x_offset), m_y_offset(y_offset)
{
}

void PlatformEntity::update(float delta_time)
{
    if (m_is_moving)
    {
        if (m_position.x < 0.0f) m_velocity.x = PLATFORM_SPEED;
        else if (m_position.x + m_width > INTERNAL_WIDTH) m_velocity.x = -PLATFORM_SPEED;
    }

    Entity::update(delta_time);
}

