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
#include <string>

#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"
#include "UILabel.h"
#include "helper.h"

UILabel::UILabel(glm::vec3 position, glm::vec3 scale, GLuint texture_id, std::string label, int num_length)
    : m_num_length(num_length), m_texture_id(texture_id)
{
    m_model_mat = glm::scale(
        glm::translate(
            IDENTITY_MAT,
            position
        ),
        scale 
    );

    m_label_length = (int) label.length();

    m_length = m_label_length + 1 + m_num_length;
    int vertex_count = m_length * 12;

    m_vertices = new float[vertex_count];
    m_texture_coordinates = new float[vertex_count];

    // Set vertices
    for (int i = 0; i < m_length; i++)
    {
        int index_offset = i * 12;
        for (int j = 0; j < 12; j += 2)
        {
            int index = index_offset + j;
            // Vertex coordinate
            m_vertices[index] = i + STANDARD_COORDINATES[j];     // X
            m_vertices[index + 1] = STANDARD_COORDINATES[j + 1]; // Y
        }
    }

    float width = 1.0f / 26.0f;
    for (int i = 0; i < m_label_length; i++)
    {
        int letter_index = (int) (label[i] - 'A');
        int index = i * 12;

        float u = (float) (letter_index % 26) * width;

        // Triangle 1
        m_texture_coordinates[index + 0] = u;
        m_texture_coordinates[index + 1] = 0.5f;

        m_texture_coordinates[index + 2] = u + width;
        m_texture_coordinates[index + 3] = 0.5f;

        m_texture_coordinates[index + 4] = u + width;
        m_texture_coordinates[index + 5] = 0.0f;

        // Triangle 2
        m_texture_coordinates[index + 6] = u;
        m_texture_coordinates[index + 7] = 0.5f;

        m_texture_coordinates[index + 8] = u + width;
        m_texture_coordinates[index + 9] = 0.0f;

        m_texture_coordinates[index + 10] = u;
        m_texture_coordinates[index + 11] = 0.0f;
    }
}

UILabel::~UILabel()
{
    delete [] m_vertices;
    delete [] m_texture_coordinates;
}

void UILabel::update(int num)
{
    float width = 1.0f / 26.0f;
    for (int i = 0; i < m_num_length; i++)
    {
        int index = (i + m_label_length + 1) * 12;

        int denom = 1;

        for (int n = 1; n < m_num_length - i; n++)
        {
            denom *= 10;
        }

        int number_index = (num / denom) % 10;

        float u = (float) (number_index % 26) * width;

        // Triangle 1
        m_texture_coordinates[index + 0] = u;
        m_texture_coordinates[index + 1] = 1.0f;

        m_texture_coordinates[index + 2] = u + width;
        m_texture_coordinates[index + 3] = 1.0f;

        m_texture_coordinates[index + 4] = u + width;
        m_texture_coordinates[index + 5] = 0.5f;

        // Triangle 2
        m_texture_coordinates[index + 6] = u;
        m_texture_coordinates[index + 7] = 1.0f;

        m_texture_coordinates[index + 8] = u + width;
        m_texture_coordinates[index + 9] = 0.5f;

        m_texture_coordinates[index + 10] = u;
        m_texture_coordinates[index + 11] = 0.5f;
    }
}

void UILabel::render(ShaderProgram* program) 
{
    program->set_model_matrix(m_model_mat);
    glBindTexture(GL_TEXTURE_2D, m_texture_id);

    glVertexAttribPointer(program->get_position_attribute(),
        2, GL_FLOAT, false, 0, m_vertices);
    glVertexAttribPointer(program->get_tex_coordinate_attribute(),
        2, GL_FLOAT, false, 0, m_texture_coordinates);

    glDrawArrays(GL_TRIANGLES, 0, m_length * 6);
}
