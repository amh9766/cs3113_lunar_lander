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
#include "ShaderProgram.h"
#include "Entity.h"
#include "lunar_lib.h"
#include "helper.h"

Entity::Entity(glm::vec3 init_pos, glm::vec3 init_scale, 
    float width, float height, GLuint tex_id)
    : m_position(init_pos), m_velocity(0.0f), m_acceleration(0.0f),
      m_scale(init_scale), m_model_mat(IDENTITY_MAT), m_texture_id(tex_id),
      m_width(width), m_height(height),
      m_is_active(false)
{
}

Entity::Entity(glm::vec3 init_pos, float width, float height, GLuint tex_id)
    : m_position(init_pos), m_velocity(0.0f), m_acceleration(0.0f),
      m_model_mat(IDENTITY_MAT), m_texture_id(tex_id),
      m_width(width), m_height(height),
      m_is_active(false)
{
    m_scale = glm::vec3(width, height, 0.0f);
}

Entity::~Entity()
{
}

void Entity::update_model_mat()
{
    m_model_mat = glm::scale(
        glm::translate(
            IDENTITY_MAT,
            m_position
        ),
        m_scale 
    );
}

void Entity::update(float delta_time)
{
    // Apply resulting forces on entity
    m_velocity += m_acceleration * delta_time;
    m_position += m_velocity * delta_time;

    // Update model matrix
    update_model_mat();
}

void Entity::render(ShaderProgram* program)
{
    program->set_model_matrix(m_model_mat);
    glBindTexture(GL_TEXTURE_2D, m_texture_id);

    glVertexAttribPointer(program->get_position_attribute(),
        2, GL_FLOAT, false, 0, STANDARD_COORDINATES);
    glVertexAttribPointer(program->get_tex_coordinate_attribute(),
        2, GL_FLOAT, false, 0, STANDARD_COORDINATES);

    glDrawArrays(GL_TRIANGLES, 0, 6);
}

