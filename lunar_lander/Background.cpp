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
#include "Background.h"
#include "ShaderProgram.h"
#include "helper.h"

Background::Background(float height, float width, GLuint texture_id)
    : m_texture_id(texture_id)
{
    m_model_mat = glm::scale(
        IDENTITY_MAT,
        glm::vec3(width, height, 0.0f)
    );
}

void Background::render(ShaderProgram* program)
{
    program->set_model_matrix(m_model_mat);
    glBindTexture(GL_TEXTURE_2D, m_texture_id);

    glVertexAttribPointer(program->get_position_attribute(),
        2, GL_FLOAT, false, 0, STANDARD_COORDINATES);
    glVertexAttribPointer(program->get_tex_coordinate_attribute(),
        2, GL_FLOAT, false, 0, STANDARD_COORDINATES);

    glDrawArrays(GL_TRIANGLES, 0, 6);

}
