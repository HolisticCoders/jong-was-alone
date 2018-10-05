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
            m_mass = 10;
            m_color = YELLOW;
            m_velocity = {0, 0};
            m_jumpStrength = 60;
            m_moveSpeed = 10;
            m_maxVelocity = 20;
            m_decelerationRate = .3;
            m_cameraTrackingThreshold = 55;
            m_cameraTrackingSpeed = 2;
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
        void setCamera(Camera2D* camera) {
            m_camera = camera;
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
        void update() {
            m_velocity.y += GRAVITY_STRENGTH * m_mass * GetFrameTime();

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
            cameraTracking();

            DrawRectangle(m_position.x, m_position.y, m_size, m_size, m_color);
        }
    private:
        Vector2 m_position;
        float m_size;
        float m_mass;
        Color m_color;
        Vector2 m_velocity;
        float m_jumpStrength;
        float m_moveSpeed;
        float m_maxVelocity;
        float m_decelerationRate;
        Camera2D* m_camera;
        int m_cameraTrackingThreshold;
        float m_cameraTrackingSpeed;

        void cameraTracking() {
            const float frameTime = GetFrameTime();
            const int width = GetScreenWidth();
            const int height = GetScreenHeight();
            const float targetOffsetX = (width - m_size) / 2 - m_position.x;
            const float targetOffsetY = (height - m_size) / 2 - m_position.y;
            m_camera->offset.x = Lerp(m_camera->offset.x, targetOffsetX, m_cameraTrackingSpeed * frameTime);
            m_camera->offset.y = Lerp(m_camera->offset.y, targetOffsetY, m_cameraTrackingSpeed * frameTime);
        }

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
