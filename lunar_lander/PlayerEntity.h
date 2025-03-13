#ifndef PLAYER_ENTITY_H
#define PLAYER_ENTITY_H

#include "glm/glm.hpp"
#include "ShaderProgram.h"
#include "AnimatedEntity.h"
#include "lunar_lib.h"

enum PlayerAnim : int
{
    IDLE = 0,
    UP = 1,
    DOWN = 2,
    HORIZONTAL = 3
};

class PlayerEntity : public AnimatedEntity 
{
    private:
        // ————— PHYSICS ————— //
        glm::vec3 m_propulsion;

        // ————— GAMEPLAY ————— //
        int m_fuel;

    public:
        // ————— GETTERS ————— //
        int const get_fuel() const { return m_fuel; }

        // ————— GENERAL ————— //
        PlayerEntity(glm::vec3 init_pos, glm::vec3 init_scale, 
            float m_width, float m_height, 
            GLuint tex_id, std::vector<AnimationInfo> anim_frames, int max_frames);

        void update(float delta_time);

        // ————— GAMEPLAY ————— //
        void use_fuel() { if (m_fuel > 0) m_fuel -= FUEL_USAGE; }

        // ————— PHYSICS ————— //
        void start_neutral() { m_propulsion = glm::vec3(0.0f); }

        void push_left()     { if (m_fuel > 0) { m_propulsion.x -= 1.0f; use_fuel(); } }
        void push_right()    { if (m_fuel > 0) { m_propulsion.x += 1.0f; use_fuel(); } }
        void push_up()       { if (m_fuel > 0) { m_propulsion.y -= 1.0f; use_fuel(); } }
        void push_down()     { if (m_fuel > 0) { m_propulsion.y += 1.0f; use_fuel(); } }

        // ————— ANIMATION ————— //
        void update_anim();
};

#endif

