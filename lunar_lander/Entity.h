#ifndef ENTITY_H
#define ENTITY_H

#include "glm/glm.hpp"
#include "ShaderProgram.h"

class Entity
{
    protected:
        // ————— PHYSICS ————— //
        glm::vec3 m_position,
                  m_velocity,
                  m_acceleration;
        float     m_width,
                  m_height;
        
        // ————— DRAWING ————— //
        glm::vec3 m_scale;
        glm::mat4 m_model_mat;
        GLuint    m_texture_id;

        void update_model_mat();

        // ————— MISCELLANEOUS ————— //
        bool      m_is_active;

    public:
        // ————— GETTERS ————— //
        glm::vec3 const get_position()     const { return m_position; }
        glm::vec3 const get_velocity()     const { return m_velocity; }
        glm::vec3 const get_acceleration() const { return m_acceleration; }
        glm::vec3 const get_scale()        const { return m_scale; }
        GLuint    const get_texture_id()   const { return m_texture_id; }

        // ————— SETTERS ————— //
        void set_position(glm::vec3 new_position)         { m_position = new_position; }
        void set_velocity(glm::vec3 new_velocity)         { m_velocity = new_velocity; }
        void set_acceleration(glm::vec3 new_acceleration) { m_acceleration = new_acceleration; }
        void set_scale(glm::vec3 new_scale)               { m_scale = new_scale; }

        // ————— GENERAL ————— //
        Entity(glm::vec3 init_pos, glm::vec3 init_scale, float m_width, float m_height, GLuint tex_id);
        ~Entity();

        virtual void update(float delta_time);
        virtual void render(ShaderProgram *program);
};

#endif

