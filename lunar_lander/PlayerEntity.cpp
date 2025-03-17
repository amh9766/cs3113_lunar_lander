/**
* Author: Amani Hernandez 
* Assignment: Lunar Lander
* Date due: 2025-3-15, 11:59pm
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
#include "ShaderProgram.h"
#include "AnimatedEntity.h"
#include "PlayerEntity.h"
#include "lunar_lib.h"
#include "helper.h"

PlayerEntity::PlayerEntity(glm::vec3 init_pos, glm::vec3 init_scale, 
    float width, float height, GLuint tex_id, 
    std::vector<AnimationInfo> anims, int max_frames
    )
    : AnimatedEntity(init_pos, init_scale,
        width, height, 
        tex_id,
        anims, max_frames
      ),
      m_propulsion(0.0f), m_fuel(FUEL_AMOUNT) 
{
}

PlayerEntity::PlayerEntity(glm::vec3 init_pos, 
    float width, float height, GLuint tex_id, 
    std::vector<AnimationInfo> anims, int max_frames
    )
    : AnimatedEntity(init_pos,
        width, height, 
        tex_id,
        anims, max_frames
      ),
      m_propulsion(0.0f), m_fuel(FUEL_AMOUNT) 
{
}

void PlayerEntity::update(float delta_time)
{
    // Set initial acceleration to propulsion force 
    m_acceleration = ACCEL_OF_PROPULSION * m_propulsion;

    // Add natural forces on player 
    glm::vec3 gravity_accel = glm::vec3(0.0f, ACCEL_OF_GRAVITY, 0.0f);
    glm::vec3 drag_accel = -DRAG_COEFFICIENT * m_velocity;

    m_acceleration += gravity_accel + drag_accel;

    // Update animation based on propulsion
    update_anim();

    AnimatedEntity::update(delta_time);
}

void PlayerEntity::update_anim()
{
    // Flip based on direction player should be facing
    if (m_propulsion.x < 0.0f)      enable_x_flip();
    else if (m_propulsion.x > 0.0f) disable_x_flip();

    // Set the corresponding animation
    if (m_propulsion.y < 0.0f)       set_anim(PlayerAnim::UP);
    else if (m_propulsion.y > 0.0f)  set_anim(PlayerAnim::DOWN);
    else if (m_propulsion.x != 0.0f) set_anim(PlayerAnim::HORIZONTAL);
    else                             set_anim(PlayerAnim::IDLE);
}
