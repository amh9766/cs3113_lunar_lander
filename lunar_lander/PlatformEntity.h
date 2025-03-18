#ifndef PLATFORM_ENTITY_H
#define PLATFORM_ENTITY_H

#include "glm/glm.hpp"
#include "Entity.h"
#include "lunar_lib.h"

class PlatformEntity : public Entity
{
    private:
        // ————— COLLISIONS ————— //
        float m_x_offset,
              m_y_offset;

        // ————— GAMEPLAY ————— //
        bool  m_is_moving;

    public:
        // ————— GENERAL ————— //
        PlatformEntity(glm::vec3 position, float width, float height, 
            float x_offset, float y_offset, GLuint texture_id);

        void update(float delta_time);

        // ————— GAMEPLAY ————— //
        void set_dynamic() { m_is_moving = true; m_velocity.x = PLATFORM_SPEED; }
        void set_static()  { m_is_moving = false; m_velocity = glm::vec3(0.0f); }

        // ————— COLLISIONS ————— //
        float calculate_left_overlap(float x, float width)  { return m_position.x + m_x_offset - (x + width); }
        float calculate_right_overlap(float x)              { return m_position.x + m_width - m_x_offset - x; }
        float calculate_top_overlap(float y, float height)  { return m_position.y + m_y_offset - (y + height); }
        float calculate_bottom_overlap(float y)             { return m_position.y + m_height - m_y_offset - y; }
};

#endif
