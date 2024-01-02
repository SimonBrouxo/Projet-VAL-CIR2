#include "VAL.hpp"

const int MAX_RAMES = 10;

std::mutex keepMovingMutex;
std::atomic<bool> keepMoving(true);

void moveRame(int id, float x, float y, float speed, int nb_passenger, const vector<float>& coord_x_s, const vector<float>& coord_y_s, vector<sf::Vector2f>& ramePositions) {
    Rame rame(id, x, y, speed, nb_passenger);

    std::atomic<size_t> idx_station(1);
    int direction = 1;

    while (true) {
        {
            std::unique_lock<std::mutex> lock(keepMovingMutex);
            if (!keepMoving) {
                break;
            }
        }

        // Mouvement de la rame
        if (idx_station < coord_x_s.size()) 
        {
            Vector2f positionActuelle = Vector2f(rame.getRame_x(), rame.getRame_y());
            Vector2f positionCible = Vector2f(coord_x_s[idx_station], coord_y_s[idx_station]);
            Vector2f direction_ActCible = positionCible - positionActuelle;
            float distance_station = distance(positionActuelle, positionCible);

            // On se déplace
            if (distance_station > 5.0f) 
            {
                direction_ActCible = direction_ActCible / distance_station;
                rame.setRame_xy(rame.getRame_x() + direction_ActCible.x * 0.8f, rame.getRame_y() + direction_ActCible.y * 0.8f);
            }

            // On va rencontrer une station
            else 
            {
                idx_station += direction;

                // On change la direction si on atteint la première ou la dernière station
                if (idx_station == 0 || idx_station == coord_x_s.size() - 1) 
                {
                    direction *= -1;
                }
            }

            // Sortie de débogage
            std::cout << "Rame " << id << " - Position : (" << rame.getRame_x() << ", " << rame.getRame_y() << ") - Station : " << idx_station << std::endl;
        }

        // Pause pour simuler un déplacement réaliste
        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        {
            std::unique_lock<std::mutex> lock(keepMovingMutex);
            ramePositions[id - 1] = sf::Vector2f(rame.getRame_x(), rame.getRame_y());
        }
    }
}

int main()
{
    locale::global(locale{ "fr-FR" });

    cout << "\t---- Projet VAL ----" << endl << endl << "Ce projet consiste à refaire un métro." << endl << endl;

    /**********************************     Setup     ******************************************/

    int nbStation = 0;
    int nbRame = 0;

    // Présentation du projet et initialisation du metro (nb de stations/rames)
    cout << "Donnez le nombre de station : "; 
    cin >> nbStation;
    cout << "Donnez le nombre de rame : "; 
    cin >> nbRame;
    cout << endl;
    Superviseur superviseur(nbStation, nbRame);
    cout << "Votre métro contient : " << endl << "- " << superviseur.getNbStation() << " stations" << endl << "- " << superviseur.getNbRame() << " rames" << endl << endl;


    /**********************************     Stations     *****************************************/


    // Création de la map stations qui contiendra tous les stations dans l'ordre et stations_coord qui contient les coordonnées des stations dans l'ordre
    cout << "\tCréation des Stations" << endl << endl << "Vous allez créer vos stations avec les paramètres de votre choix." << endl << endl;
    map<int, string> stations; // noms de stations par id de stations
    map<int, string>::iterator cible_s;
    map<int, float> stations_coord_x; // coordonnées x par id de stations
    map<int, float> stations_coord_y; // coordonnées y par id de stations

    // On remplit la map avec l'id de la station et son nom
    for (int i = 0;i < nbStation;i++) 
    {
        cout << "Création d'une station :" << endl;
	    Station station; // création d'une station
	    station.setStation(); // on donne les paramètres de la station (nom,position...)
        stations.insert(pair<int, string>(station.getStation_id(), station.getStation_noun())); // on insert dans la map, l'id et le nom de la station
        stations_coord_x.insert(pair<int, float>(station.getStation_id(), station.getStation_x()));
        stations_coord_y.insert(pair<int, float>(station.getStation_id(), station.getStation_y()));
    }

    // On affiche les stations dans l'ordre
    cout << "Votre métro contient les " << stations.size() << " stations suivantes : " << endl;
    for (cible_s = stations.begin(); cible_s != stations.end(); cible_s++) 
    { 
        cout << "- " << cible_s->first << " " << cible_s->second << endl; // donne le numéro de la station et son nom
    }
    cout << endl;

    // On récupère les coordonnées x et y des stations
    map<int, float>::iterator cible_s_coord_x;
    map<int, float>::iterator cible_s_coord_y;
    vector<float>coord_x_s;
    vector<float>coord_y_s;
    vector<float>::iterator cible_coord_x_s;
    vector<float>::iterator cible_coord_y_s;

    for (cible_s_coord_x = stations_coord_x.begin();cible_s_coord_x != stations_coord_x.end();cible_s_coord_x++) // on parcours tous les éléments de l'itérateur de stations pour les x
    {
        coord_x_s.push_back(cible_s_coord_x->second); // on range les x en fin du vecteur (pour l'ordre), celui-ci contient les éléments seconds de la map, autrement dit les x
    }
    for (cible_s_coord_y = stations_coord_y.begin();cible_s_coord_y != stations_coord_y.end();cible_s_coord_y++)
    {
        coord_y_s.push_back(cible_s_coord_y->second);
    }


    /**********************************     Rames     *****************************************/

    Texture textureRame;
    Sprite spritesRame[MAX_RAMES];
    vector<Vector2f> ramePositions(MAX_RAMES, Vector2f(0.0f, 0.0f));
    vector<thread> threads;
  
    // Création des threads pour chaque rame
    for (int i = 0; i < nbRame; ++i) {
        // Décalage de démarrage pour chaque rame (5 secondes de décalage)
        std::this_thread::sleep_for(std::chrono::seconds(5));
        threads.emplace_back(moveRame, i + 1, coord_x_s[0], coord_y_s[0], 0.8f, 0, coord_x_s, coord_y_s, std::ref(ramePositions));
    }

    /***********************************     SFML     ******************************************/


    // Création de la fenêtre avec la résolution, le titre de la fenêtre et la syncro verticale
    const Vector2u WIN_SIZE(WIN_WIDTH, WIN_HEIGHT);
    RenderWindow window(VideoMode(WIN_SIZE.x, WIN_SIZE.y), "Projet VAL !!!");
    window.setVerticalSyncEnabled(true);

    // Création des textures/sprites avec leur chargement
    Texture textureBackground, textureStation;
    Sprite spriteBackground, spriteStation;
    

    // Chargement des images + erreur
    if (!textureRame.loadFromFile(path_image + "rame.png") || !textureBackground.loadFromFile(path_image + "background.png") || !textureStation.loadFromFile(path_image + "station.png")) { cerr << "Erreur de chargement d'image" << endl; return EXIT_FAILURE; }

    // Background
    spriteBackground.setTexture(textureBackground);
    spriteBackground.setScale(WIN_SIZE.x, WIN_SIZE.y);

    // Rame
    for (int i = 0; i < nbRame; ++i) {
        spritesRame[i].setTexture(textureRame);
        spritesRame[i].setScale(0.1f, 0.1f);
        spritesRame[i].setPosition(Vector2f(ramePositions[i].x, ramePositions[i].y));
    }

    //size_t idx_station = 0; // Pour savoir si la rame a atteint une station
    //int direction = 1; // direction = 1 si on avance pour aller vers la dernière station ou direction = -1 si on recule pour revenir à la première station 


    // Stations
    spriteStation.setTexture(textureStation);
    spriteStation.setScale(0.2f, 0.2f);

    while (window.isOpen()) // Boucle principale et ouverture de la fenêtre
    {

        // Vérification des entrées clavier
        Event event; // Evènement dans la fenêtre        
        while (window.pollEvent(event)) // Boucle qui va regarder chaque évènement dans la fenêtre
        { 
            if (event.type == Event::Closed) 
            {
                {
                    std::unique_lock<std::mutex> lock(keepMovingMutex);
                    keepMoving = false;
                }
                window.close();
            }
        }

        window.clear(); // On "nettoie" la fenêtre (littéralement...) pour qu'elle soit vide
        window.draw(spriteBackground); // on dessine le background


        // On dessine toutes les stations
        for (int i = 0; i < coord_x_s.size(); i++)
        {
            spriteStation.setPosition(coord_x_s[i], coord_y_s[i]);
            window.draw(spriteStation);
        }

        // On dessine toutes les rames en mouvement
        
        //cout << "Position de la rame : " << currentspriteRame.getPosition().x << ", " << currentspriteRame.getPosition().y << endl;
        for (int i = 0; i < nbRame; i++) 
        {
            if (ramePositions[i].x < coord_x_s.size() - 1)
            {
                Vector2f positionActuelle = spritesRame[i].getPosition();
                Vector2f positionCible = Vector2f(coord_x_s[ramePositions[i].x], coord_y_s[ramePositions[i].x]);
                Vector2f direction_ActCible = positionCible - positionActuelle;
                float distance_station = distance(positionActuelle, positionCible);

                // On se déplace
                if (distance_station > 5.0f) 
                {
                    direction_ActCible = direction_ActCible / distance_station;
                    ramePositions[i] = sf::Vector2f(ramePositions[i].x + direction_ActCible.x * 0.8f, ramePositions[i].y + direction_ActCible.y * 0.8f);
                }

                // On va rencontrer une station
                else 
                {
                    ramePositions[i].x += ramePositions[i].y;

                    // On change la direction si on atteint la première ou la dernière station
                    if (ramePositions[i].x == 0 || ramePositions[i].x == coord_x_s.size() - 1) 
                    {
                        // Peut être une erreur il faut remonter le vecteur 
                        ramePositions[i].y *= -1;
                    }
                }
            }
            spritesRame[i].setPosition(ramePositions[i]);
            window.draw(spritesRame[i]);


            //std::cout << "Rame " << i << " - Position : (" << spritesRame[i].getPosition().x << ", " << spritesRame[i].getPosition().y << ") - Station : " << ramePositions[i].x << std::endl;
        }
          
        window.display(); // à la fin de la boucle principale pour tout afficher à l'écran
    }

    {
        std::unique_lock<std::mutex> lock(keepMovingMutex);
        keepMoving = false;
    }

    // Joindre tous les threads avant de quitter
    for (auto& thread : threads) {
        thread.join();
    }

	return EXIT_SUCCESS;
}