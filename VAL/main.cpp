#include "VAL.hpp"

std::mutex keepRunningMutex;
bool keepRunning = true;


void moveRame(int id, float x, float y, float speed, int nb_passenger, const vector<float>& coord_x_s, const vector<float>& coord_y_s, vector<Vector2f>& ramePositions, Station& station)
{
    srand(time(NULL));

    // On créé une rame quand le thread se lance
    Rame rame(id, x, y, speed, nb_passenger);

    int idx_station = 0;

    float acceleration = 0.03f;
    float deceleration = 0.05f;
    float vitesseMax = 2.0f;
    float vitesseMin = 0.2f;
    int tempsAttente = 3;
    bool enStation = false;
    auto chronometre = chrono::steady_clock::now();


    while (keepRunning) {
        {
            std::unique_lock<std::mutex> lock(keepRunningMutex);
            if (!keepRunning) {
                break;
            }
        }

        // Vérifier si la rame est à la station et attendre si nécessaire
        if (enStation) {
            cout << endl << "La rame " << rame.getRame_id() << " est arrivé à la station " << station.getStation_id() << endl;
            sortirPersonnesRame(rame);
            entrerPersonnesRame(rame);
            //entrerPersonnesStation(station);
            cout << endl;
            std::this_thread::sleep_for(std::chrono::seconds(tempsAttente));
            enStation = false;
        }

        // Mouvement de la rame
        if (idx_station < coord_x_s.size()) 
        {
            // On va calculer la distance qui sépare une rame d'une station
            Vector2f positionActuelle = Vector2f(rame.getRame_x(), rame.getRame_y());
            Vector2f positionCible = Vector2f(coord_x_s[idx_station], coord_y_s[idx_station]);
            Vector2f direction_ActCible = positionCible - positionActuelle;
            float distance_station = distance(positionActuelle, positionCible);

            // Décélération à l'approche de la station
            if (distance_station < 50.0f) 
            {
                rame.setRame_speed(std::max(rame.getRame_speed() - deceleration, vitesseMin)); // on prend la plus grande valeur entre la décélération en cours et la vitesse min
            }
            // Accélération
            else 
            {
                rame.setRame_speed(std::min(rame.getRame_speed() + acceleration, vitesseMax)); // on prend la plus petite valeur entre l'accélération en cours et la vitesse max
            }

            // On se déplace
            if (distance_station > 0.5f) 
            {
                direction_ActCible = direction_ActCible / distance_station; // on réduit la distance entre qui nous sépare de la station suivante
                rame.setRame_xy(rame.getRame_x() + direction_ActCible.x * rame.getRame_speed(), rame.getRame_y() + direction_ActCible.y * rame.getRame_speed()); // on met à jour la position de la rame
            }

            // On va atteindre une station
            else 
            {
                rame.setRame_speed(0.0f); // on est à l'arrêt car on a atteint une station
                enStation = true;

                // Revenir à la première station si on atteint la dernière
                if (idx_station == coord_x_s.size() - 1)
                {
                    idx_station = 0;
                }
                else
                {
                    idx_station++;
                }
            }

            auto tempsAct = chrono::steady_clock::now();
            auto tempsPasse = chrono::duration_cast<chrono::seconds>(tempsAct - chronometre).count();
            if (tempsPasse >= 5) 
            {
            std::cout << "Rame " << id  << " - Position : (" << rame.getRame_x() << "," << rame.getRame_y() << ") - Direction : station " << idx_station + 1 << " - Vitesse : " << rame.getRame_speed() << " - Passager : " << rame.getRame_nb_passenger() << "/" << NB_MAX_PERSONNE_RAME << endl;
            chronometre = tempsAct;
            }

        }

        // Pause pour simuler un déplacement réaliste
        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        {
            std::unique_lock<std::mutex> lock(keepRunningMutex);
            ramePositions[id - 1] = sf::Vector2f(rame.getRame_x(), rame.getRame_y());
        }
    }
}

int main()
{
    locale::global(locale{ "fr-FR" });

    cout << "\t---- Projet VAL ----" << endl << endl << "Ce projet consiste à refaire un métro." << endl << endl;

    /**********************************     Superviseur     ******************************************/

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
	Station station; // création d'une station
    map<int, string> stations; // noms de stations par id de stations
    map<int, string>::iterator cible_s;
    map<int, float> stations_coord_x; // coordonnées x par id de stations
    map<int, float> stations_coord_y; // coordonnées y par id de stations
    map<int, float>::iterator cible_s_coord_x;
    map<int, float>::iterator cible_s_coord_y;
    map<int, int> stations_nb_people;
    map<int, int>::iterator cible_s_nb_people;

    // On remplit la map avec l'id de la station et son nom
    for (int i = 0;i < nbStation;i++) 
    {
        cout << "Création d'une station :" << endl;
	    station.setStation(); // on donne les paramètres de la station (nom,position...)
        stations.insert(pair<int, string>(station.getStation_id(), station.getStation_noun())); // on insert dans la map, l'id et le nom de la station
        stations_coord_x.insert(pair<int, float>(station.getStation_id(), station.getStation_x()));
        stations_coord_y.insert(pair<int, float>(station.getStation_id(), station.getStation_y()));
        stations_nb_people.insert(pair<int, int>(station.getStation_id(), station.getStation_nb_people()));
    }

    // On récupère les coordonnées x et y des stations
    vector<float>coord_x_s;
    vector<float>coord_y_s;

    for (cible_s_coord_x = stations_coord_x.begin();cible_s_coord_x != stations_coord_x.end();cible_s_coord_x++) // on parcours tous les éléments de l'itérateur de stations pour les x
    {
        coord_x_s.push_back(cible_s_coord_x->second); // on range les x en fin du vecteur (pour l'ordre), celui-ci contient les éléments seconds de la map, autrement dit les x
    }
    for (cible_s_coord_y = stations_coord_y.begin();cible_s_coord_y != stations_coord_y.end();cible_s_coord_y++)
    {
        coord_y_s.push_back(cible_s_coord_y->second);
    }

    // On affiche les stations dans l'ordre
    cout << "Votre métro contient les " << stations.size() << " stations suivantes : " << endl;
    for (cible_s = stations.begin(); cible_s != stations.end(); cible_s++) 
    { 
        cout << "- " << cible_s->first << " : " << cible_s->second << endl; // donne le numéro de la station et son nom
                }
    cout << endl;


    /**********************************     Rames     *****************************************/


    Texture textureRame;
    Sprite spritesRame[MAX_SPRITE_RAMES]; // création de 20 sprites
    vector<Vector2f> ramePositions(MAX_SPRITE_RAMES, Vector2f(coord_x_s[0], coord_y_s[0]));
    vector<thread> threadsRame;
  
    // Création des threads pour chaque rame
    for (int i = 0; i < nbRame; i++)
    {
        // On attends 10 secondes avant de lancer une autre rame
        std::this_thread::sleep_for(std::chrono::seconds(10));
        threadsRame.emplace_back([&]() { moveRame(i, coord_x_s[0], coord_y_s[0], 0.8f, 0, coord_x_s, coord_y_s, std::ref(ramePositions), std::ref(station)); });
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
    for (int i = 0; i < nbRame; ++i) 
    {
        spritesRame[i].setTexture(textureRame);
        spritesRame[i].setScale(0.6f, 0.6f);
        spritesRame[i].setPosition(Vector2f(ramePositions[i].x, ramePositions[i].y));
    }

    // Stations
    spriteStation.setTexture(textureStation);
    spriteStation.setScale(1.0f, 1.0f);

    // Boucle principale et ouverture de la fenêtre
    while (window.isOpen()) 
    {
        // Vérification des entrées clavier
        Event event; // Evènement dans la fenêtre        
        while (window.pollEvent(event)) // Boucle qui va regarder chaque évènement dans la fenêtre
        { 
            if (event.type == Event::Closed) 
            {
                {
                    std::unique_lock<std::mutex> lock(keepRunningMutex);
                    keepRunning = false;
                }
                window.close();
            }
        }

        // On "nettoie" la fenêtre pour qu'elle soit vide
        window.clear();

        // On dessine le background
        window.draw(spriteBackground); 

        // On dessine toutes les stations
        for (int i = 0; i < coord_x_s.size(); i++)
        {
            spriteStation.setPosition(coord_x_s[i], coord_y_s[i]);
            window.draw(spriteStation);

        }

        // On dessine des lignes pour relier les stations par rapport au centre du sprite
        for (int i = 0; i < coord_x_s.size() - 1; i++)
        {
            Vertex line[] = 
            {
                Vertex(Vector2f(coord_x_s[i] + spriteStation.getLocalBounds().width / 2, coord_y_s[i] + spriteStation.getLocalBounds().height / 2)),
                Vertex(Vector2f(coord_x_s[i + 1] + spriteStation.getLocalBounds().width / 2, coord_y_s[i + 1] + spriteStation.getLocalBounds().height / 2))
            };
            window.draw(line, 2, Lines);
        }

        // On dessine le chemin de reserve en rouge entre la première et la dernière station
        Vertex derniereLine[] = 
        {
            Vertex(Vector2f(coord_x_s.back() + spriteStation.getLocalBounds().width / 2, coord_y_s.back() + spriteStation.getLocalBounds().height / 2)),
            Vertex(Vector2f(coord_x_s.front() + spriteStation.getLocalBounds().width / 2, coord_y_s.front() + spriteStation.getLocalBounds().height / 2))
        };
        derniereLine[0].color = Color::Red;
        derniereLine[1].color = Color::Red;
        window.draw(derniereLine, 2, Lines);

        // On dessine toutes les rames en mouvement        
        for (int i = 0; i < nbRame; i++) 
        {
            if (ramePositions[i].x < coord_x_s.size() - 1)
            {
                // On va calculer la distance qui sépare une rame d'une station
                Vector2f positionActuelle = spritesRame[i].getPosition();
                Vector2f positionCible = Vector2f(coord_x_s[ramePositions[i].x], coord_y_s[ramePositions[i].x]);
                Vector2f direction_ActCible = positionCible - positionActuelle;
                float distance_station = distance(positionActuelle, positionCible);

                // On déplace une rame en réduisant la distance entre la rame et la prochaine station
                if (distance_station > 0.5f) 
                {
                    direction_ActCible = direction_ActCible / distance_station; // on réduit la distance
                    ramePositions[i] = Vector2f(ramePositions[i].x + direction_ActCible.x * 0.8f, ramePositions[i].y + direction_ActCible.y * 0.8f); // on met à jour la position de la rame
                }

                // On va revenir à la première station
                else 
                {
                    ramePositions[i].x = 0;
                }
            }            
            spritesRame[i].setPosition(ramePositions[i]); // on place le sprite selon la position de la rame
            window.draw(spritesRame[i]); // on dessine le sprite de la rame
        }
          
        window.display(); // à la fin de la boucle principale pour tout afficher à l'écran
    }

    {
        std::unique_lock<std::mutex> lock(keepRunningMutex);
        keepRunning = false;
    }

    // Joindre tous les threads avant de quitter
    for (auto& thread : threadsRame) 
    {
        thread.join();
    }

	return EXIT_SUCCESS;
}