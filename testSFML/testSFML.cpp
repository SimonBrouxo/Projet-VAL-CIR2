#include "testSFML.hpp"

using namespace std;
using namespace sf;

// Prototypes des fonctions
void InputHandler(Event event, RenderWindow& window);

// Gestion des evenement et des inputs
void InputHandler(Event event, RenderWindow& window) 
{
    // On teste si on clique sur la croix
    if (event.type == sf::Event::Closed)
    {
        window.close();
    }
}


int main() 
{
    // Création de la fenêtre avec la résolution et le titre de la fenêtre
    RenderWindow window(VideoMode(WIN_WIDTH, WIN_HEIGHT), "SFML works!");

    // Création d'un cerlce vert
    CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    // Boucle qui tourne tant que le fichier est ouvert
    while (window.isOpen())
    {
        Event event; // Evènement dans la fenêtre
        // Boucle qui va regarder chaque évènement dans la fenêtre
        while (window.pollEvent(event))
        {
            InputHandler(event, window);
        }

        window.clear(Color::Red);
        window.draw(shape);
        window.display();
    }

    return 0;
}