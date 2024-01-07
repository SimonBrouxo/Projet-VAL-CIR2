#include "VAL.hpp"

bool keepRunning = true;
mutex keepRunningMutex;



/**********************************************************************************/
/*******************************      Thread      *********************************/
/**********************************************************************************/


// Thread qui va g�rer les coordonn�es des rames pendant les d�placements, en donnant des inforamtions sur les rames et les stations du m�tro
void moveRame(int id, float x, float y, float speed, int nb_passenger, const vector<float>& coord_x_s, const vector<float>& coord_y_s, vector<Vector2f>& ramePositions, vector<Station>& stations)
{
    srand(time(NULL));
    cout << "==========================================================================" << endl << endl << "\tMise en place de la simulation du m�tro" << endl << endl << "==========================================================================" << endl;

    // On cr�� une rame quand le thread se lance
    Rame rame(id, x, y, speed, nb_passenger);

    int idx_station = 0; // on va d�finir un indexe pour �valuer chaque stations selon une rame

    float acceleration = 0.03f;
    float deceleration = 0.05f;
    float vitesseMax = 2.0f;
    float vitesseMin = 0.3f;
    int tempsAttente = 3;
    bool enStation = false;

    auto chronometre = chrono::steady_clock::now();


    while (keepRunning) {
        {
            unique_lock<mutex> lock(keepRunningMutex);
            if (!keepRunning) {
                break;
            }
        }

        // V�rifier si la rame est � la station et attendre si n�cessaire
        if (enStation) {
            cout << endl << "La rame " << rame.getRame_id() << " va se diriger vers la station " << stations[idx_station].getStation_noun() << " (" << idx_station + 1 << ")" << endl;
            sortirPersonnesRame(rame);
            entrerPersonnesRame(rame);
            //entrerPersonnesStation(station);
            cout << endl;
            std::this_thread::sleep_for(chrono::seconds(tempsAttente)); // on reste 3 secondes en station
            enStation = false;
        }

        // Mouvement de la rame
        if (idx_station < coord_x_s.size()) 
        {
            // On va calculer la distance qui s�pare une rame d'une station
            Vector2f positionActuelle = Vector2f(rame.getRame_x(), rame.getRame_y());
            Vector2f positionCible = Vector2f(coord_x_s[idx_station], coord_y_s[idx_station]);
            Vector2f direction_ActCible = positionCible - positionActuelle;
            float distance_station = distance(positionActuelle, positionCible);

            // D�c�l�ration � l'approche de la station
            if (distance_station < 50.0f) 
            {
                rame.setRame_speed(max(rame.getRame_speed() - deceleration, vitesseMin)); // on prend la plus grande valeur entre la d�c�l�ration en cours et la vitesse min
            }
            // Acc�l�ration
            else 
            {
                rame.setRame_speed(min(rame.getRame_speed() + acceleration, vitesseMax)); // on prend la plus petite valeur entre l'acc�l�ration en cours et la vitesse max
            }

            // On se d�place
            if (distance_station > 0.5f) 
            {
                direction_ActCible = direction_ActCible / distance_station; // on r�duit la distance entre qui nous s�pare de la station suivante
                rame.setRame_xy(rame.getRame_x() + direction_ActCible.x * rame.getRame_speed(), rame.getRame_y() + direction_ActCible.y * rame.getRame_speed()); // on met � jour la position de la rame
            }

            // On va atteindre une station
            else 
            {
                rame.setRame_speed(0.0f); // on est � l'arr�t car on a atteint une station
                enStation = true;

                // On revient � la premi�re station si on atteint le terminus
                if (idx_station == coord_x_s.size() - 1)
                {
                    idx_station = 0;
                }
                else
                {
                    idx_station++;
                }
            }

            // On calcule le temps pour afficher un message d'info sur les rames (toutes les 5 secondes)
            auto tempsAct = chrono::steady_clock::now();
            auto tempsPasse = chrono::duration_cast<chrono::seconds>(tempsAct - chronometre).count();
            if (tempsPasse >= 5) 
            {
            cout << "Rame " << id  << 
                    " - Position : ("  << static_cast<int>(round(rame.getRame_x())) << "," << static_cast<int>(round(rame.getRame_y())) << // on utilise static cast pour garder des nombres entiers
                    ") - Direction : " << stations[idx_station].getStation_noun() << " (" << idx_station + 1 << // on donne la prochaine station
                    ") - Vitesse : "   << setprecision(2) << rame.getRame_speed() << // on affiche la vitesse avec deux chiffres apr�s la virgule (setprecision) m�me si la vitesse est un entier (fixed)
                    " - Passager : "   << rame.getRame_nb_passenger() << "/" << NB_MAX_PERSONNE_RAME << endl; // on affiche le nombre de passagers dans la rame
            chronometre = tempsAct;
            }

        }

        // Pause pour simuler un d�placement r�aliste
        std::this_thread::sleep_for(chrono::milliseconds(50));

        {
            unique_lock<mutex> lock(keepRunningMutex);
            ramePositions[id - 1] = Vector2f(rame.getRame_x(), rame.getRame_y());
        }
    }
}



/**********************************************************************************/
/*******************************      Main      ***********************************/
/**********************************************************************************/



int main()
{
    locale::global(locale{ "fr-FR" });

    cout << "\t---- Projet VAL ----" << endl << endl << "Ce projet consiste � refaire un m�tro." << endl << endl;

    /**********************************     Superviseur     ******************************************/

    int nbStation = 0;
    int nbRame = 0;

    // Pr�sentation du projet et initialisation du metro (nb de stations/rames)
    cout << "Donnez le nombre de station : "; 
    cin >> nbStation;
    cout << "Donnez le nombre de rame : "; 
    cin >> nbRame;
    cout << endl;
    Superviseur superviseur(nbStation, nbRame);
    cout << "Votre m�tro contient : " << endl << "- " << superviseur.getNbStation() << " stations" << endl << "- " << superviseur.getNbRame() << " rames" << endl << endl;


    /**********************************     Stations     *****************************************/


    // Cr�ation de la map stations qui contiendra tous les stations dans l'ordre et stations_coord qui contient les coordonn�es des stations dans l'ordre
    cout << "\t\tCr�ation des Stations" << endl << endl << "Vous allez cr�er vos stations avec les param�tres de votre choix." << endl << endl;
	vector <Station> stations; // vecteur qui contiendra toutes les stations
    vector<pair<int, string>> stations_nom; // noms de stations par id de stations
    map<int, float> stations_coord_x; // coordonn�es x par id de stations
    map<int, float> stations_coord_y; // coordonn�es y par id de stations
    map<int, float>::iterator cible_s_coord_x;
    map<int, float>::iterator cible_s_coord_y;
    map<int, int> stations_nb_people;
    map<int, int>::iterator cible_s_nb_people;

    // On remplit la map avec l'id de la station et son nom
    for (int i = 0; i < nbStation; i++)
    {
        cout << "\tCr�ation d'une station :" << endl;
        Station station; // on cr�� un objet station
	    station.setStation(); // on donne les param�tres de la station (nom,position...)
        stations_nom.emplace_back(station.getStation_id(), station.getStation_noun()); // on insert dans le vecteur, l'id et le nom de la station
        stations_coord_x.insert(pair<int, float>(station.getStation_id(), station.getStation_x()));
        stations_coord_y.insert(pair<int, float>(station.getStation_id(), station.getStation_y()));
        stations_nb_people.insert(pair<int, int>(station.getStation_id(), station.getStation_nb_people()));
        stations.push_back(station); // on ajoute la station dans le vecteur
    }

    // On r�cup�re les coordonn�es x et y des stations
    vector<float>coord_x_s;
    vector<float>coord_y_s;

    for (cible_s_coord_x = stations_coord_x.begin();cible_s_coord_x != stations_coord_x.end();cible_s_coord_x++) // on parcours tous les �l�ments de l'it�rateur de stations pour les x
    {
        coord_x_s.push_back(cible_s_coord_x->second); // on range les x en fin du vecteur (pour l'ordre), celui-ci contient les �l�ments seconds de la map, autrement dit les x
    }
    for (cible_s_coord_y = stations_coord_y.begin();cible_s_coord_y != stations_coord_y.end();cible_s_coord_y++)
    {
        coord_y_s.push_back(cible_s_coord_y->second);
    }

    // Tri du vecteur stations_nom par num�ro de station avec une fonction lambda
    sort(stations_nom.begin(), stations_nom.end(), [](const pair<int, string>& a, const pair<int, string>& b) {return a.first < b.first; });

    // On affiche les stations dans l'ordre
    cout << "Votre m�tro contient les " << stations_nom.size() << " stations suivantes : " << endl;
    for (const auto& station : stations_nom)
    {
        cout << "- " << station.first << " : " << station.second << endl; // donne le num�ro de la station et son nom
    }
    cout << endl;


    /**********************************     Rames     *****************************************/


    Texture textureRame;
    Sprite spritesRame[MAX_SPRITE_RAMES]; // cr�ation de 20 sprites
    vector<Vector2f> ramePositions(MAX_SPRITE_RAMES, Vector2f(coord_x_s[0], coord_y_s[0]));
    vector<thread> threadsRame;
  
    // Cr�ation des threads pour chaque rame
    for (int i = 0; i < nbRame; i++)
    {
        // Cr�ation de threads pout g�rer le d�placement de chaque rames toutes les 10 secondes
        std::this_thread::sleep_for(chrono::seconds(10));
        threadsRame.emplace_back([&]() { moveRame(i, coord_x_s[0], coord_y_s[0], 0.8f, 0, coord_x_s, coord_y_s, ramePositions,stations); });
    }


    /***********************************     SFML     ******************************************/


    // Cr�ation de la fen�tre avec la r�solution, le titre de la fen�tre et la syncro verticale
    const Vector2u WIN_SIZE(WIN_WIDTH, WIN_HEIGHT);
    RenderWindow window(VideoMode(WIN_SIZE.x, WIN_SIZE.y), "Projet VAL !!!");
    window.setVerticalSyncEnabled(true);

    // Cr�ation des textures/sprites avec leur chargement
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
        spritesRame[i].setScale(0.55f, 0.55f);
        spritesRame[i].setPosition(Vector2f(ramePositions[i].x, ramePositions[i].y));
    }

    // Stations
    spriteStation.setTexture(textureStation);
    spriteStation.setScale(1.0f, 1.0f);

    // Boucle principale et ouverture de la fen�tre
    while (window.isOpen()) 
    {
        // V�rification des entr�es clavier
        Event event; // Ev�nement dans la fen�tre        
        while (window.pollEvent(event)) // Boucle qui va regarder chaque �v�nement dans la fen�tre
        { 
            if (event.type == Event::Closed) 
            {
                {
                    unique_lock<mutex> lock(keepRunningMutex);
                    keepRunning = false;
                }
                window.close();
            }
        }

        // On "nettoie" la fen�tre pour qu'elle soit vide
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

        // On dessine un chemin rouge entre la premi�re et la derni�re station
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
                // On va calculer la distance qui s�pare une rame d'une station
                Vector2f positionActuelle = spritesRame[i].getPosition();
                Vector2f positionCible = Vector2f(coord_x_s[ramePositions[i].x], coord_y_s[ramePositions[i].x]);
                Vector2f direction_ActCible = positionCible - positionActuelle;
                float distance_station = distance(positionActuelle, positionCible);

                // On d�place une rame en r�duisant la distance entre la rame et la prochaine station
                if (distance_station > 0.5f) 
                {
                    direction_ActCible = direction_ActCible / distance_station; // on r�duit la distance
                    ramePositions[i] = Vector2f(ramePositions[i].x + direction_ActCible.x * 0.8f, ramePositions[i].y + direction_ActCible.y * 0.8f); // on met � jour la position de la rame
                }

                // On va revenir � la premi�re station
                else 
                {
                    ramePositions[i].x = 0;
                }
            }            
            spritesRame[i].setPosition(ramePositions[i].x + 22, ramePositions[i].y); // on place le sprite selon la position de la rame (petite correction de l'axe x pour le sprite)
            window.draw(spritesRame[i]); // on dessine le sprite de la rame
        }
          
        window.display(); // � la fin de la boucle principale pour tout afficher � l'�cran
    }

    {
        unique_lock<mutex> lock(keepRunningMutex);
        keepRunning = false;
    }

    // Joindre tous les threads avant de quitter
    for (auto& thread : threadsRame) 
    {
        thread.join();
    }

	return EXIT_SUCCESS;
}