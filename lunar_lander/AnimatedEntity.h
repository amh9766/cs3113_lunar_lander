#ifndef ANIMATED_ENTITY_H
#define ANIMATED_ENTITY_H

#include <vector>

#include "glm/glm.hpp"
#include "ShaderProgram.h"
#include "Entity.h"
#include "AnimationInfo.h"

class AnimatedEntity : public Entity
{
    protected:
        // ————— ANIMATION ————— //
        float m_anim_time;
        std::vector<AnimationInfo> m_anims;

        int m_anim_cols,
            m_anim_rows;
        int m_anim_index,
            m_curr_anim;

    public:
        // ————— GENERAL ————— //
        AnimatedEntity(glm::vec3 init_pos, glm::vec3 init_scale, 
            float m_width, float m_height, 
            GLuint tex_id, std::vector<AnimationInfo> anim_frames, int max_frames);
        ~AnimatedEntity();

        void update(float delta_time);
        void render(ShaderProgram *program);

        // ————— ANIMATION ————— //
        void set_anim(int anim);
};

#endif
