#include "raylib.h"


const float GRAVITY_STRENGTH = 9.81;

float Lerp(float start, float end, float amount)
{
    return start + amount*(end - start);
}


class Character {
    public:
        Character() {
            m_position = {0, 0};
            m_size = 100;
            m_color = YELLOW;
            m_velocity = {0, 0};
            m_jumpStrength = 60;
            m_moveSpeed = 10;
            m_maxVelocity = 20;
            m_decelerationRate = .3;
        }
        void update() {
            /* const float frameTime = GetFrameTime(); */
            m_velocity.y += GRAVITY_STRENGTH;

            m_velocity.x = Lerp(m_velocity.x, 0, m_decelerationRate);

            // Cap horizontal velocity.
            if (m_velocity.x < -m_maxVelocity)
                m_velocity.x = -m_maxVelocity;
            if (m_velocity.x > m_maxVelocity)
                m_velocity.x = m_maxVelocity;

            // Update the position and draw me !
            m_position.x += m_velocity.x;
            m_position.y += m_velocity.y;

            limitToScreenBoundaries();

            DrawRectangle(m_position.x, m_position.y, m_size, m_size, m_color);
        }
        Vector2 position() {
            return m_position;
        }
        float size() {
            return m_size;
        }
        Color color() {
            return m_color;
        }
        bool isGrounded() {
            if (m_position.y >= GetScreenHeight() - m_size)
                return true;
            return false;
        }
        void jump() {
            if (!isGrounded())
                return;
            m_velocity.y -= m_jumpStrength;
        }
        void go_left() {
            m_velocity.x -= m_moveSpeed;
        }
        void go_right() {
            m_velocity.x += m_moveSpeed;
        }
    private:
        Vector2 m_position;
        float m_size;
        Color m_color;
        Vector2 m_velocity;
        float m_jumpStrength;
        float m_moveSpeed;
        float m_maxVelocity;
        float m_decelerationRate;

        void limitToScreenBoundaries() {
            const int width = GetScreenWidth();
            const int height = GetScreenHeight();
            if (m_position.x > width - m_size) {
                m_position.x = width - m_size;
                m_velocity.x = 0;
            }
            if (m_position.x < 0) {
                m_position.x = 0;
                m_velocity.x = 0;
            }
            if (m_position.y > height - m_size) {
                m_position.y = height - m_size;
                m_velocity.y = 0;
            }
            if (m_position.y < 0) {
                m_position.y = 0;
                m_velocity.y = 0;
            }
        }
};
