#include "testSFML.hpp"

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
    // Création de la fenêtre avec la résolution, le titre de la fenêtre et la syncro verticale
    const Vector2u WIN_SIZE(WIN_WIDTH, WIN_HEIGHT);
    RenderWindow window(VideoMode(WIN_SIZE.x, WIN_SIZE.y), "Projet VAL !!!");
    window.setVerticalSyncEnabled(true);


    // Création des textures/sprites avec leur chargement
    Texture textureTrain, textureBackground, textureDrapeau;
    Sprite spriteTrain, spriteBackground, spriteDrapeau1, spriteDrapeau2, spriteDrapeau3;
    
    // Chargement des images + erreur
    if (!textureTrain.loadFromFile(path_image+"train.png") || !textureBackground.loadFromFile(path_image+"background.png")|| !textureDrapeau.loadFromFile(path_image+"drapeau.png"))
    {
        cerr << "Erreur de chargement d'image" << endl;
        return EXIT_FAILURE;
    }
    // Background
    spriteBackground.setTexture(textureBackground);
    // Train
    spriteTrain.setTexture(textureTrain);
    spriteTrain.setScale(-0.5f, 0.5f);      // on met des (-) pour retourner le train 
    // Drapeaux
    spriteDrapeau1.setTexture(textureDrapeau);
    spriteDrapeau1.setScale(0.04f, 0.04f);
    spriteDrapeau2.setTexture(textureDrapeau);
    spriteDrapeau2.setScale(0.04f, 0.04f);
    spriteDrapeau3.setTexture(textureDrapeau);
    spriteDrapeau3.setScale(0.04f, 0.04f);
    





    // Affichage de la fenêtre
    while (window.isOpen()) // Boucle principale
    {
        Event event; // Evènement dans la fenêtre        
        while (window.pollEvent(event)) // Boucle qui va regarder chaque évènement dans la fenêtre
        {
            // Vérification des entrées clavier
            InputHandler(event, window);
        }

        spriteTrain.move(Vector2f(1, 0));


        spriteDrapeau1.setPosition(200, 200);
        spriteDrapeau2.setPosition(500, 200);
        spriteDrapeau3.setPosition(700, 100);

        window.clear(); // on a une fenêtre vide

        // On dessine tous les éléments dans la fenêtre
        window.draw(spriteBackground);
        window.draw(spriteTrain);
        window.draw(spriteDrapeau1);
        window.draw(spriteDrapeau2);
        window.draw(spriteDrapeau3);



        window.display(); // à la fin de la boucle principale pour tout afficher à l'écran
    }

    return 0;
}