#include "testSFML.cpp"

float distance(const sf::Vector2f& v1, const sf::Vector2f& v2) {
    float dx = v2.x - v1.x;
    float dy = v2.y - v1.y;
    return std::sqrt(dx * dx + dy * dy);
}

int main()
{
    locale::global(locale{ "fr-FR" });


    /**********************************     Setup     ******************************************/

    // Présentation du projet et initialisation du metro (nb de stations/rames)
    cout << "\t---- Projet VAL ----" << endl << endl << "Ce projet consiste à refaire un métro." << endl << endl;
    int nbStation = 5, nbRame = 1;
    Superviseur superviseur(nbStation, nbRame);
    cout << "Votre métro contient : " << endl << "- " << superviseur.getNbStation() << " stations" << endl << "- " << superviseur.getNbRame() << " rames" << endl << endl;

    /**********************************     Stations     *****************************************/


    Station station1("Gare", 1, 100, 100, 10);
    Station station2("Flandres", 2, 200, 200, 10);
    Station station3("Solférino", 3, 300, 300, 10);
    Station station4("République", 4, 250, 400, 10);
    Station station5("Eglise", 5, 100, 500, 10);

    cout << "Le métro contient les" << nbStation << "différentes :" << endl;
    cout << "- " << station1.getStation_id() << " " << station1.getStation_noun() << endl;
    cout << "- " << station2.getStation_id() << " " << station2.getStation_noun() << endl;
    cout << "- " << station3.getStation_id() << " " << station3.getStation_noun() << endl;
    cout << "- " << station4.getStation_id() << " " << station4.getStation_noun() << endl;
    cout << "- " << station5.getStation_id() << " " << station5.getStation_noun() << endl << endl;


    /**********************************     Rames     *****************************************/

    Rame rame1(1, station1.getStation_x(), station1.getStation_y(), 0.5, 1);

    cout << "Le métro contient" << nbRame << " :" << endl;
    cout << "- " << rame1.getRame_id() << endl << endl;


    /***********************************     Affichage     ******************************************/


    // Création de la fenêtre avec la résolution, le titre de la fenêtre et la syncro verticale
    const Vector2u WIN_SIZE(WIN_WIDTH, WIN_HEIGHT);
    RenderWindow window(VideoMode(WIN_SIZE.x, WIN_SIZE.y), "Projet VAL !!!");
    window.setVerticalSyncEnabled(true);

    // Création des textures/sprites avec leur chargement
    Texture textureRame, textureBackground, textureStation;
    Sprite spriteRame, spriteBackground, spriteStation;

    // Chargement des images + erreur
    if (!textureRame.loadFromFile(path_image + "rame.png") || !textureBackground.loadFromFile(path_image + "background.png") || !textureStation.loadFromFile(path_image + "station.png"))
    {
        cerr << "Erreur de chargement d'image" << endl;
        return EXIT_FAILURE;
    }

    // Background
    spriteBackground.setTexture(textureBackground);
    spriteBackground.setScale(WIN_SIZE.x, WIN_SIZE.y);

    // Rame
    spriteRame.setTexture(textureRame);
    spriteRame.setScale(0.1f, 0.1f);
    spriteRame.setPosition(station1.getStation_x(), station1.getStation_y());

    // Stations
    spriteStation.setTexture(textureStation);
    spriteStation.setScale(0.1f, 0.1f);

    // Affichage de la fenêtre
    while (window.isOpen()) // Boucle principale
    {

        // Vérification des entrées clavier
        Event event; // Evènement dans la fenêtre        
        while (window.pollEvent(event)) { InputHandler(event, window); }

        // On "nettoie" la fenêtre (littéralement...) pour qu'elle soit vide
        window.clear();

        // On dessine tous les éléments dans la fenêtre
        // 
        // Background
        window.draw(spriteBackground);

        // Stations
        spriteStation.setPosition(station1.getStation_x(), station1.getStation_y());
        window.draw(spriteStation);
        spriteStation.setPosition(station2.getStation_x(), station2.getStation_y());
        window.draw(spriteStation);
        spriteStation.setPosition(station3.getStation_x(), station3.getStation_y());
        window.draw(spriteStation);
        spriteStation.setPosition(station4.getStation_x(), station4.getStation_y());
        window.draw(spriteStation);
        spriteStation.setPosition(station5.getStation_x(), station5.getStation_y());
        window.draw(spriteStation);


        // Rames

        window.draw(spriteRame);
        Vector2f targetPosition = Vector2f(station2.getStation_x(), station2.getStation_y());
        Vector2f currentPosition = Vector2f(rame1.getRame_x(), rame1.getRame_y());
        Vector2f direction = targetPosition - currentPosition;


        float distanceToStation2 = distance(currentPosition, targetPosition);

        if (distanceToStation2 != 0.5) {
            // Calculer la direction normalisée
            Vector2f direction = targetPosition - spriteRame.getPosition();
            direction = direction / distanceToStation2;

            // Déplacer la rame dans la direction normalisée avec la vitesse spécifiée
            spriteRame.move(direction * rame1.getRame_speed());
        }
        else {
            // La rame est arrivée à la station2
            spriteRame.setPosition(station2.getStation_x(), station2.getStation_y());
        }

        //spriteRame.setPosition(rame1.getRame_x(),rame1.getRame_y());
        //window.draw(spriteRame);
        //spriteRame.move(Vector2f(station2.getStation_x(), station2.getStation_y()));


        //spriteRame.move(Vector2f(station3.getStation_x(), station3.getStation_y()));
        //spriteRame.move(Vector2f(station4.getStation_x(), station4.getStation_y()));
        //spriteRame.move(Vector2f(station5.getStation_x(), station5.getStation_y()));



        window.display(); // à la fin de la boucle principale pour tout afficher à l'écran
    }


    return EXIT_SUCCESS;
}



/*
        spriteRame.move(Vector2f(((float)*ity - (float)*ity + 1) / distance(Vector2f(elem, (float)*ity), Vector2f(elem + 1, (float)*ity + 1))),
                                    (elem - elem + 1)               / distance(Vector2f(elem, (float)*ity), Vector2f(elem + 1, (float)*ity + 1)));
        */