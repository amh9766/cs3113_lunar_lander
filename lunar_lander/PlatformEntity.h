#ifndef PLATFORM_ENTITY_H
#define PLATFORM_ENTITY_H

#include "glm/glm.hpp"
#include "Entity.h"
#include "lunar_lib.h"

class PlatformEntity : public Entity
{
    private:
        float m_x_offset,
              m_y_offset;
        bool  m_is_moving;

    public:
        PlatformEntity(glm::vec3 position, float width, float height, 
            float x_offset, float y_offset, GLuint texture_id);

        void update(float delta_time);

        void set_dynamic() { m_is_moving = true; m_velocity.x = PLATFORM_SPEED; }
        void set_static()  { m_is_moving = false; m_velocity = glm::vec3(0.0f); }
};

#endif
