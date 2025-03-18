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
#include "PlatformEntity.h"
#include "lunar_lib.h"
#include "helper.h"

PlayerEntity::PlayerEntity(glm::vec3 init_scale, 
    float width, float height, GLuint tex_id, 
    std::vector<AnimationInfo> anims, int max_frames
    )
    : AnimatedEntity(SPAWN_POINT, init_scale,
        width, height, 
        tex_id,
        anims, max_frames
      ),
      m_propulsion(0.0f), m_fuel(FUEL_AMOUNT) 
{
}

PlayerEntity::PlayerEntity(float width, float height, GLuint tex_id, 
    std::vector<AnimationInfo> anims, int max_frames
    )
    : AnimatedEntity(SPAWN_POINT,
        width, height, 
        tex_id,
        anims, max_frames
      ),
      m_propulsion(0.0f), m_fuel(FUEL_AMOUNT) 
{
}

void PlayerEntity::collides_with(glm::vec3& prev_position, PlatformEntity& platform)
{
    float left_overlap   = platform.calculate_left_overlap(m_position.x, m_width);
    float right_overlap  = platform.calculate_right_overlap(m_position.x);
    float top_overlap    = platform.calculate_top_overlap(m_position.y, m_height);
    float bottom_overlap = platform.calculate_bottom_overlap(m_position.y);
    
    bool right = left_overlap < 0.0f;
    bool left = right_overlap > 0.0f;
    bool bottom = top_overlap < 0.0f;
    bool top = bottom_overlap > 0.0f;

    bool prev_right   =  platform.calculate_left_overlap(prev_position.x, m_width) < 0.0f;
    bool prev_left    =  platform.calculate_right_overlap(prev_position.x) > 0.0f;
    bool prev_bottom  =  platform.calculate_top_overlap(prev_position.y, m_height) < 0.0f;
    bool prev_top     =  platform.calculate_bottom_overlap(prev_position.y) > 0.0f;

    if (left && right && top && bottom)
    {
        m_collide_left = left != prev_left;
        m_collide_right = right != prev_right;
        m_collide_top = top != prev_top;
        m_collide_bottom = bottom != prev_bottom;

        if (m_collide_left)
        {
            m_position.x = prev_position.x + right_overlap;
            if (m_acceleration.x < 0.0f) m_acceleration.x = 0.0f;
            if (m_velocity.x < 0.0f) m_velocity.x = 0.0f;

        }
        if (m_collide_right)
        {
            m_position.x = prev_position.x + left_overlap;
            if (m_acceleration.x > 0.0f) m_acceleration.x = 0.0f;
            if (m_velocity.x > 0.0f) m_velocity.x = 0.0f;
        }
        if (m_collide_top) 
        {
            m_position.y = prev_position.y + bottom_overlap;
            if (m_acceleration.y < 0.0f) m_acceleration.y = 0.0f;
            if (m_velocity.y < 0.0f) m_velocity.y = 0.0f;
        }
        if (m_collide_bottom)
        {
            m_position.y = prev_position.y + top_overlap;
            if (m_acceleration.y > 0.0f) m_acceleration.y = 0.0f;
            if (m_velocity.y > 0.0f) m_velocity.y = 0.0f;
        }
    }
}

bool PlayerEntity::is_out_of_bounds()
{
    return (m_position.x < -BOUND) || 
           ((m_position.x + m_width) > (INTERNAL_WIDTH + BOUND)) ||
           (m_position.y < -BOUND) ||
           ((m_position.y + m_height) > (INTERNAL_HEIGHT + BOUND));
}

void PlayerEntity::update(float delta_time, std::vector<PlatformEntity>& platforms)
{
    // Record previous position and reset collision flags
    glm::vec3 prev_position = m_position;
    reset_collision();

    // Set initial acceleration to propulsion force 
    m_acceleration = ACCEL_OF_PROPULSION * m_propulsion;

    // Add natural forces on player 
    glm::vec3 gravity_accel = glm::vec3(0.0f, ACCEL_OF_GRAVITY, 0.0f);
    glm::vec3 drag_accel = -DRAG_COEFFICIENT * m_velocity;

    m_acceleration += gravity_accel + drag_accel;

    // Update animation based on propulsion
    update_anim();

    AnimatedEntity::update(delta_time);

    // Adjust new position, velocity, and acceleration based on any collisions
    for (int i = 0; i < platforms.size(); i++) collides_with(prev_position, platforms[i]);
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
