#ifndef PLAYER_ENTITY_H
#define PLAYER_ENTITY_H

#include "glm/glm.hpp"
#include "ShaderProgram.h"
#include "AnimatedEntity.h"
#include "PlatformEntity.h"
#include "lunar_lib.h"

enum PlayerAnim : int
{
    IDLE       = 0,
    UP         = 1,
    DOWN       = 2,
    HORIZONTAL = 3
};

class PlayerEntity : public AnimatedEntity 
{
    private:
        // ————— PHYSICS ————— //
        glm::vec3 m_propulsion;

        bool m_collide_bottom;
        bool m_collide_top;
        bool m_collide_left;
        bool m_collide_right;

        // ————— GAMEPLAY ————— //
        int m_fuel;

    public:
        // ————— GETTERS ————— //
        int  const get_fuel()           const { return m_fuel; }
        bool const get_collide_bottom() const { return m_collide_bottom; }

        // ————— GENERAL ————— //
        PlayerEntity(glm::vec3 init_scale, 
            float m_width, float m_height, 
            GLuint tex_id, std::vector<AnimationInfo> anim_frames, int max_frames);
        PlayerEntity(float m_width, float m_height, 
            GLuint tex_id, std::vector<AnimationInfo> anim_frames, int max_frames);

        void update(float delta_time, std::vector<PlatformEntity>& platforms);

        // ————— GAMEPLAY ————— //
        void reset()
        {
            m_position = SPAWN_POINT;
            m_velocity = glm::vec3(0.0f);
            m_acceleration = glm::vec3(0.0f);

            m_fuel = FUEL_AMOUNT; 
        }

        void use_fuel() { if (m_fuel > 0) m_fuel -= FUEL_USAGE; }

        // ————— PHYSICS ————— //
        void start_neutral() { m_propulsion = glm::vec3(0.0f); }

        void push_left()     { if (m_fuel > 0) { m_propulsion.x -= 1.0f; use_fuel(); } }
        void push_right()    { if (m_fuel > 0) { m_propulsion.x += 1.0f; use_fuel(); } }
        void push_up()       { if (m_fuel > 0) { m_propulsion.y -= 1.0f; use_fuel(); } }
        void push_down()     { if (m_fuel > 0) { m_propulsion.y += 1.0f; use_fuel(); } }

        // ————— COLLISIONS ————— //
        void reset_collision()
        {
            m_collide_bottom = false; 
            m_collide_top    = false;
            m_collide_left   = false;
            m_collide_right  = false;
        }

        void collides_with(glm::vec3& prev_position, PlatformEntity& platform);
        bool is_out_of_bounds();

        // ————— ANIMATION ————— //
        void update_anim();
};

#endif

