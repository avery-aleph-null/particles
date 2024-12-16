#include "Particle.h"

Particle::Particle(RenderTarget& target, int numPoints, Vector2i mouseClickPosition) 
    : m_ttl(TTL), m_numPoints(numPoints), m_centerCoordinate(mouseClickPosition), 
      m_radiansPerSec(static_cast<float>((rand() % 100) / 50.0 * M_PI)), 
      m_vx(rand() % 200 - 100), m_vy(rand() % 200 - 100), 
      m_cartesianPlane(target.getView()), 
      m_color1(Color(rand() % 255, rand() % 255, rand() % 255)),
      m_color2(Color(rand() % 255, rand() % 255, rand() % 255)),
      m_A(2, numPoints) {
    
    for (int i = 0; i < numPoints; ++i) {
        float angle = i * 2.0f * M_PI / numPoints;
        m_A(0, i) = cos(angle) * 50; // Radius of 50
        m_A(1, i) = sin(angle) * 50;
    }
}

void Particle::draw(RenderTarget& target, RenderStates states) const {
    VertexArray va(TriangleFan, m_numPoints + 2);
    va[0].position = m_centerCoordinate;
    va[0].color = m_color1;

    for (int i = 0; i < m_numPoints; ++i) {
        va[i + 1].position = m_centerCoordinate + Vector2f(m_A(0, i), m_A(1, i));
        va[i + 1].color = m_color2;
    }

    va[m_numPoints + 1] = va[1]; // Closes loop
    target.draw(va, states);
}

void Particle::update(float dt) {
    m_ttl -= dt;
    rotate(m_radiansPerSec * dt);
    scale(SCALE);
    translate(m_vx * dt, m_vy * dt);
}

void Particle::rotate(double theta) {
    RotationMatrix r(theta);
    m_A = r * m_A;
}

void Particle::scale(double c) {
    ScalingMatrix s(c);
    m_A = s * m_A;
}

void Particle::translate(double xShift, double yShift) {
    TranslationMatrix t(xShift, yShift, m_A.getCols());
    m_A = t + m_A;
}
