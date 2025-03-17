#ifndef PLATFORM_ENTITY_H
#define PLATFORM_ENTITY_H

#include "glm/glm.hpp"
#include "Entity.h"

class PlatformEntity : public Entity
{
    private:
        float m_x_offset,
              m_y_offset;

    public:
        PlatformEntity(glm::vec3 position, float width, float height, 
            float x_offset, float y_offset, GLuint texture_id, bool active);

        void update(float delta_time);
};

#endif
