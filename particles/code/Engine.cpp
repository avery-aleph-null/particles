#include "Engine.h"

Engine::Engine() 
    : m_Window(VideoMode(800, 600), "Particles") {}

// Run will call all the private functions
void Engine::run() {
    Clock clock;
    while (m_Window.isOpen()) {
        Time dt = clock.restart();
        input();
        update(dt.asSeconds());
        draw();
    }
}

void Engine::input() {
    Event event;
    while (m_Window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            m_Window.close();
        } else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
            Vector2i mouseClickPosition = Mouse::getPosition(m_Window);
            m_particles.emplace_back(m_Window, 50, mouseClickPosition); // Adjust 50 as needed for the number of points
        }
    }
}

void Engine::update(float dtAsSeconds) {
    for (auto it = m_particles.begin(); it != m_particles.end();) {
        it->update(dtAsSeconds);
        if (it->getTTL() <= 0) {
            it = m_particles.erase(it);
        } else {
            ++it;
        }
    }
}

void Engine::draw() {
    m_Window.clear(Color::Black);

    for (const auto& particle : m_particles) {
        m_Window.draw(particle);
    }

    m_Window.display();
}
