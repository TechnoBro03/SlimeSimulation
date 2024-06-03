#pragma once

#include "Buffer.h"
#include <SFML/Graphics.hpp>
#include <string>

class Renderer
{

private:
    sf::Texture texture;     // Creates texture. Stores pixel array
    sf::Sprite sprite;       // Creates sprite. Allows texture to interface with the render window
    sf::RenderWindow window; // Creates window.
    sf::Text text;
    sf::Font f;
public:
    Renderer(unsigned int width, unsigned int height, unsigned int framerate_limit)
    {

        texture.create(width, height);
        sprite.setTexture(texture);

        // Create main window
        window.create(sf::VideoMode(width, height), "Slime Simulation");
        window.setFramerateLimit(framerate_limit);

        f.loadFromFile("C:/Users/matth/AppData/Local/Microsoft/Windows/Fonts/JetBrainsMono-Medium.ttf");
        text.setFont(f);
        text.setCharacterSize(12); // in pixels, not points!
        text.setFillColor(sf::Color::Red);
    }

    ~Renderer()
    {
    }

    void draw(Buffer<unsigned char>* buffer, float frame_rate)
    {
        window.clear();          // Clear previous frame
        texture.update(buffer->get_pixels());  // Update texture
        window.draw(sprite);     // Draw the sprite (texted)


        text.setString(std::to_string(frame_rate));
        window.draw(text);

        window.display();        // Display update


    }

    void handle_events()
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.scancode == sf::Keyboard::Scan::Escape)
                    window.close();
                if (event.key.scancode == sf::Keyboard::Scan::Enter)
                    window.close();
            }
        }
    }

    bool is_open() const { return window.isOpen(); }
};