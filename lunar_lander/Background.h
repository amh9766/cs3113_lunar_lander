#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "glm/glm.hpp"
#include "ShaderProgram.h"

class Background
{
    private:
        glm::mat4 m_model_mat;
        GLuint m_texture_id;

    public:
        Background(float height, float width, GLuint texture_id);

        void render(ShaderProgram* program);
};

#endif
