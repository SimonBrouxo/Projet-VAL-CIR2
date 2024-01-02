//#include "VAL.hpp"
//
//std::atomic<bool> keepMoving(true); // Variable pour contr�ler la boucle while
//std::mutex keepMovingMutex;
//std::mutex ramePositionsMutex;
//
//// Structure pour stocker la nouvelle position de la rame calcul�e par le thread
//struct RamePosition {
//    std::atomic<float> x;
//    std::atomic<float> y;
//};
//
//RamePosition ramePosition;
//
//void moveRame(int id, float x, float y, float speed, int nb_passenger, vector<float>& coord_x_s, vector<float>& coord_y_s, vector<RamePosition>& ramePositions, std::mutex& ramePositionsMutex) {
//    Rame rame(id, x, y, speed, nb_passenger);
//
//    std::atomic<size_t> idx_station(0);
//    int direction = 1;
//
//    while (true) {
//        {
//            std::unique_lock<std::mutex> lock(keepMovingMutex);
//            if (!keepMoving) {
//                break;
//            }
//        }
//
//        // Mouvement de la rame
//        if (idx_station < coord_x_s.size()) {
//            Vector2f positionActuelle = Vector2f(rame.getRame_x(), rame.getRame_y());
//            Vector2f positionCible = Vector2f(coord_x_s[idx_station], coord_y_s[idx_station]);
//            Vector2f direction_ActCible = positionCible - positionActuelle;
//            float distance_station = distance(positionActuelle, positionCible);
//
//            // On se d�place
//            if (distance_station > 5.0f) {
//                direction_ActCible = direction_ActCible / distance_station;
//                rame.setRame_xy(rame.getRame_x() + direction_ActCible.x * 0.8f, rame.getRame_y() + direction_ActCible.y * 0.8f);
//            }
//
//            // On va rencontrer une station
//            else {
//                idx_station += direction;
//
//                // On change la direction si on atteint la premi�re ou la derni�re station
//                if (idx_station == 0 || idx_station == coord_x_s.size() - 1) {
//                    direction *= -1;
//                }
//            }
//        }
//
//        // Pause pour simuler un d�placement r�aliste
//        std::this_thread::sleep_for(std::chrono::milliseconds(50));
//
//        {
//            std::unique_lock<std::mutex> lock(ramePositionsMutex);
//            ramePositions[id - 1] = sf::Vector2f(rame.getRame_x(), rame.getRame_y());
//        }
//
//        // Mettez � jour la position de la rame dans la structure partag�e
//        ramePosition.x = rame.getRame_x();
//        ramePosition.y = rame.getRame_y();
//    }
//
//    cout << "fin du thread" << endl;
//}
//
//int main()
//{
//    locale::global(locale{ "fr-FR" });
//
//    cout << "\t---- Projet VAL ----" << endl << endl << "Ce projet consiste � refaire un m�tro." << endl << endl;
//
//    /**********************************     Setup     ******************************************/
//
//    int nbStation = 0;
//    int nbRame = 0;
//
//    // Pr�sentation du projet et initialisation du metro (nb de stations/rames)
//    cout << "Donnez le nombre de station : ";
//    cin >> nbStation;
//    cout << "Donnez le nombre de rame : ";
//    cin >> nbRame;
//    cout << endl;
//    Superviseur superviseur(nbStation, nbRame);
//    cout << "Votre m�tro contient : " << endl << "- " << superviseur.getNbStation() << " stations" << endl << "- " << superviseur.getNbRame() << " rames" << endl << endl;
//
//
//    /**********************************     Stations     *****************************************/
//
//
//    // Cr�ation de la map stations qui contiendra tous les stations dans l'ordre et stations_coord qui contient les coordonn�es des stations dans l'ordre
//    cout << "\tCr�ation des Stations" << endl << endl << "Vous allez cr�er vos stations avec les param�tres de votre choix." << endl << endl;
//    map<int, string> stations; // noms de stations par id de stations
//    map<int, string>::iterator cible_s;
//    map<int, float> stations_coord_x; // coordonn�es x par id de stations
//    map<int, float> stations_coord_y; // coordonn�es y par id de stations
//
//    // On remplit la map avec l'id de la station et son nom
//    for (int i = 0; i < nbStation; i++)
//    {
//        cout << "Cr�ation d'une station :" << endl;
//        Station station; // cr�ation d'une station
//        station.setStation(); // on donne les param�tres de la station (nom,position...)
//        stations.insert(pair<int, string>(station.getStation_id(), station.getStation_noun())); // on insert dans la map, l'id et le nom de la station
//        stations_coord_x.insert(pair<int, float>(station.getStation_id(), station.getStation_x()));
//        stations_coord_y.insert(pair<int, float>(station.getStation_id(), station.getStation_y()));
//    }
//
//    // On affiche les stations dans l'ordre
//    cout << "Votre m�tro contient les " << stations.size() << " stations suivantes : " << endl;
//    for (cible_s = stations.begin(); cible_s != stations.end(); cible_s++)
//    {
//        cout << "- " << cible_s->first << " " << cible_s->second << endl; // donne le num�ro de la station et son nom
//    }
//    cout << endl;
//
//    // On r�cup�re les coordonn�es x et y des stations
//    map<int, float>::iterator cible_s_coord_x;
//    map<int, float>::iterator cible_s_coord_y;
//    vector<float>coord_x_s;
//    vector<float>coord_y_s;
//    vector<float>::iterator cible_coord_x_s;
//    vector<float>::iterator cible_coord_y_s;
//
//    for (cible_s_coord_x = stations_coord_x.begin(); cible_s_coord_x != stations_coord_x.end(); cible_s_coord_x++) // on parcours tous les �l�ments de l'it�rateur de stations pour les x
//    {
//        coord_x_s.push_back(cible_s_coord_x->second); // on range les x en fin du vecteur (pour l'ordre), celui-ci contient les �l�ments seconds de la map, autrement dit les x
//    }
//    for (cible_s_coord_y = stations_coord_y.begin(); cible_s_coord_y != stations_coord_y.end(); cible_s_coord_y++)
//    {
//        coord_y_s.push_back(cible_s_coord_y->second);
//    }
//
//
//    /**********************************     Rames     *****************************************/
//
//    Texture textureRame;
//    Sprite spriteRame;
//    vector<Sprite> spritesRame;
//    vector<std::thread> threads;
//    vector<sf::Vector2f> ramePositions;
//
//    // Cr�ation des threads pour chaque rame + sprite distinct pour chaque rame
//    for (int i = 0; i < nbRame; ++i) {
//        spritesRame.emplace_back(textureRame);
//        spritesRame.back().setScale(0.1f, 0.1f);
//        spritesRame.back().setPosition(Vector2f(coord_x_s[0], coord_y_s[0]));  // On place la rame � la premi�re station
//        ramePositions.push_back(sf::Vector2f(coord_x_s[0], coord_y_s[0]));
//
//        std::this_thread::sleep_for(std::chrono::seconds(5)); // D�calage de d�marrage pour chaque rame (5 secondes de d�calage)
//        threads.emplace_back(moveRame, i + 1, coord_x_s[0], coord_y_s[0], 0.8f, 0, coord_x_s, coord_y_s, std::ref(ramePositions), std::ref(ramePositionsMutex));
//        spritesRame[i].setPosition(Vector2f(coord_x_s[0], coord_y_s[0]));  // Position initiale
//    }
//    std::this_thread::sleep_for(std::chrono::seconds(5)); // Pause suppl�mentaire pour permettre l'initialisation des threads
//
//
//    /***********************************     SFML     ******************************************/
//
//
//    // Cr�ation de la fen�tre avec la r�solution, le titre de la fen�tre et la syncro verticale
//    const Vector2u WIN_SIZE(WIN_WIDTH, WIN_HEIGHT);
//    RenderWindow window(VideoMode(WIN_SIZE.x, WIN_SIZE.y), "Projet VAL !!!");
//    window.setVerticalSyncEnabled(true);
//
//    // Cr�ation des textures/sprites avec leur chargement
//    Texture textureBackground, textureStation;
//    Sprite spriteBackground, spriteStation;
//
//
//    // Chargement des images + erreur
//    if (!textureRame.loadFromFile(path_image + "rame.png") || !textureBackground.loadFromFile(path_image + "background.png") || !textureStation.loadFromFile(path_image + "station.png")) { cerr << "Erreur de chargement d'image" << endl; return EXIT_FAILURE; }
//
//    // Background
//    spriteBackground.setTexture(textureBackground);
//    spriteBackground.setScale(WIN_SIZE.x, WIN_SIZE.y);
//
//    // Rame
//    spriteRame.setTexture(textureRame);
//    spriteRame.setScale(0.1f, 0.1f);
//    spriteRame.setPosition(Vector2f(coord_x_s[0], coord_y_s[0])); // On place la rame � la premi�re station
//    size_t idx_station = 0; // Pour savoir si la rame a atteint une station
//    int direction = 1; // direction = 1 si on avance pour aller vers la derni�re station ou direction = -1 si on recule pour revenir � la premi�re station 
//
//
//    // Stations
//    spriteStation.setTexture(textureStation);
//    spriteStation.setScale(0.2f, 0.2f);
//
//    while (keepMoving && window.isOpen()) // Boucle principale et ouverture de la fen�tre
//    {
//
//        // V�rification des entr�es clavier
//        Event event; // Ev�nement dans la fen�tre        
//        while (window.pollEvent(event)) // Boucle qui va regarder chaque �v�nement dans la fen�tre
//        {
//            if (event.type == Event::Closed)
//            {
//                {
//                    std::unique_lock<std::mutex> lock(keepMovingMutex);
//                    keepMoving = false;
//                }
//                window.close();
//            }
//        }
//
//        window.clear(); // On "nettoie" la fen�tre (litt�ralement...) pour qu'elle soit vide
//        window.draw(spriteBackground); // on dessine le background
//
//
//        // On dessine toutes les stations
//        for (int i = 0; i < coord_x_s.size(); i++)
//        {
//            spriteStation.setPosition(coord_x_s[i], coord_y_s[i]);
//            window.draw(spriteStation);
//        }
//
//        // On dessine la rame en mouvement
//        for (auto& currentspriteRame : spritesRame)
//        {
//            cout << "Position de la rame : " << currentspriteRame.getPosition().x << ", " << currentspriteRame.getPosition().y << endl;
//            if (idx_station < coord_x_s.size())
//            {
//                Vector2f positionActuelle = currentspriteRame.getPosition();
//                Vector2f positionCible = Vector2f(coord_x_s[idx_station], coord_y_s[idx_station]);
//                Vector2f direction_ActCible = positionCible - positionActuelle;
//                float distance_station = distance(positionActuelle, positionCible);
//
//                // On se d�place
//                if (distance_station > 5.0f)
//                {
//                    direction_ActCible = direction_ActCible / distance_station;
//                    currentspriteRame.move(direction_ActCible * 0.8f);
//                }
//
//                // On va rencontrer une station
//                else
//                {
//                    idx_station += direction;
//
//                    // On change la direction si on atteint la premi�re ou la derni�re station
//                    if (idx_station == 0 || idx_station == coord_x_s.size() - 1)
//                    {
//                        direction *= -1;
//                    }
//                }
//            }
//
//            window.draw(currentspriteRame);
//        }
//
//        {
//            std::unique_lock<std::mutex> lock(ramePositionsMutex);
//            for (int i = 0; i < ramePositions.size(); ++i) {
//                auto ramePos = ramePositions[i];
//                spritesRame[i].setPosition(ramePos.x, ramePos.y);
//            }
//        }
//
//        window.display(); // � la fin de la boucle principale pour tout afficher � l'�cran
//    }
//
//    {
//        std::unique_lock<std::mutex> lock(keepMovingMutex);
//        keepMoving = false;
//    }
//
//    // Joindre tous les threads avant de quitter
//    for (auto& thread : threads) {
//        thread.join();
//    }
//
//    return EXIT_SUCCESS;
//}