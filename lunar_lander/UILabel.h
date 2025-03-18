#ifndef UI_LABEL_H
#define UI_LABEL_H

#include <string>

#include "glm/glm.hpp"
#include "ShaderProgram.h"

class UILabel
{
    private:
        // ————— DRAWING ————— //
        glm::mat4 m_model_mat;
        float* m_vertices,
             * m_texture_coordinates;
        GLuint m_texture_id;
        int m_length,
            m_label_length,
            m_num_length;

    public:
        // ————— GENERAL ————— //
        UILabel(glm::vec3 position, glm::vec3 scale, GLuint texture_id, std::string label, int num_length);
        ~UILabel();

        void update(int num);
        void render(ShaderProgram* program);
};

#endif
