#include "VAL.hpp"

/*******************************************************************************************/
/***********************************     SFML     ******************************************/
/*******************************************************************************************/


int main()
{
    locale::global(locale{ "fr-FR" });

    cout << "\t---- Projet VAL ----" << endl << endl << "Ce projet consiste � refaire un m�tro." << endl << endl;

    /**********************************     Setup     ******************************************/

    int nbStation = 0;
    int nbRame = 0;

    // Pr�sentation du projet et initialisation du metro (nb de stations/rames)
    cout << "Donnez le nombre de station : "; cin >> nbStation;
    cout << "Donnez le nombre de rame : "; cin >> nbRame;
    cout << "Cr�ation du m�tro..." << endl;
    Superviseur superviseur(nbStation, nbRame);
    cout << "Votre m�tro contient : " << endl << "- " << superviseur.getNbStation() << " stations" << endl << "- " << superviseur.getNbRame() << " rames" << endl << endl;


    /**********************************     Stations     *****************************************/


    // Cr�ation de la map stations qui contiendra tous les stations dans l'ordre et stations_coord qui contient les coordonn�es des stations dans l'ordre
    cout << "\tCr�ation des Stations" << endl << endl << "Vous allez cr�er vos stations avec les param�tres de votre choix." << endl << endl;
    map<int, string> stations; // noms de stations par id de stations
    map<int, string>::iterator cible_s;
    map<int, float> stations_coord_x; // coordonn�es x par id de stations
    map<int, float> stations_coord_y; // coordonn�es y par id de stations

    // On remplit la map avec l'id de la station et son nom
    for (int i = 0;i < nbStation;i++) 
    {
        cout << "Cr�ation d'une station :" << endl;
	    Station station; // cr�ation d'une station
	    station.setStation(); // on donne les param�tres de la station (nom,position...)
        stations.insert(pair<int, string>(station.getStation_id(), station.getStation_noun())); // on insert dans la map, l'id et le nom de la station
        stations_coord_x.insert(pair<int, float>(station.getStation_id(), station.getStation_x()));
        stations_coord_y.insert(pair<int, float>(station.getStation_id(), station.getStation_y()));
    }

    // On affiche les stations dans l'ordre
    cout << "Votre m�tro contient les " << stations.size() << " stations suivantes : " << endl;
    for (cible_s = stations.begin(); cible_s != stations.end(); cible_s++) { cout << "- " << cible_s->first << " " << cible_s->second << endl; }// donne le num�ro de la station et son nom
    cout << endl;

    // On r�cup�re les coordonn�es x et y des stations
    map<int, float>::iterator cible_s_coord_x;
    map<int, float>::iterator cible_s_coord_y;
    vector<float>coord_x_s;
    vector<float>coord_y_s;
    vector<float>::iterator cible_coord_x_s;
    vector<float>::iterator cible_coord_y_s;

    for (cible_s_coord_x = stations_coord_x.begin();cible_s_coord_x != stations_coord_x.end();cible_s_coord_x++) // on parcours tous les �l�ments de l'it�rateur de stations pour les x
    {
        coord_x_s.push_back(cible_s_coord_x->second); // on range les x en fin du vecteur (pour l'ordre), celui-ci contient les �l�ments seconds de la map, autrement dit les x
    }
    for (cible_s_coord_y = stations_coord_y.begin();cible_s_coord_y != stations_coord_y.end();cible_s_coord_y++)
    {
        coord_y_s.push_back(cible_s_coord_y->second);
    }


    /**********************************     Rames     *****************************************/


    // Cr�ation du set rames qui contiendra tous les rames dans l'ordre
    cout << "\tCr�ation des Rames" << endl << endl << "Vous allez ajouter les rames dans votre m�tro." << endl << endl;
    set<int> rames; // Ordre des rames

    // On remplit le vecteur avec tous les rames
    for (int i = 0;i < nbRame;i++)
    {
        cout << "Cr�ation d'une rame :" << endl;
        Rame rame; // cr�ation d'une rame
        rame.setRame(); // on donne les param�tres de la rame
        rames.insert(rame.getRame_id()); // on r�cup�re l'id pour la mettre dans le set
    }

    // On affiche les rames dans l'ordre
    cout << "Votre m�tro contient les " << rames.size() << " rames suivantes : " << endl;
    for (const auto& elem : rames) { cout << "- " << elem << endl; }
    cout << endl;


    /***********************************     SFML     ******************************************/


    // Cr�ation de la fen�tre avec la r�solution, le titre de la fen�tre et la syncro verticale
    const Vector2u WIN_SIZE(WIN_WIDTH, WIN_HEIGHT);
    RenderWindow window(VideoMode(WIN_SIZE.x, WIN_SIZE.y), "Projet VAL !!!");
    window.setVerticalSyncEnabled(true);

    // Cr�ation des textures/sprites avec leur chargement
    Texture textureRame, textureBackground, textureStation;
    Sprite spriteRame, spriteBackground, spriteStation, spriteStation1, spriteStation2, spriteStation3;

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
    spriteRame.setPosition(Vector2f(coord_x_s[0], coord_y_s[0]));

    size_t currentStationIndex = 0;

    // Stations
    spriteStation.setTexture(textureStation);
    spriteStation.setScale(0.2f, 0.2f);

    for (int i = 0; i < coord_x_s.size(); i++)
    {
        cout << coord_x_s[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < coord_y_s.size(); i++)
    {
        cout << coord_y_s[i] << " ";
    }
    cout << endl;


    // Affichage de la fen�tre
    while (window.isOpen()) // Boucle principale
    {

        // V�rification des entr�es clavier
        Event event; // Ev�nement dans la fen�tre        
        while (window.pollEvent(event)) // Boucle qui va regarder chaque �v�nement dans la fen�tre
        {
            InputHandler(event, window);
        }

        window.clear(); // On "nettoie" la fen�tre (litt�ralement...) pour qu'elle soit vide
        window.draw(spriteBackground); // on dessine le background
        window.draw(spriteRame); // On dessine la rame


        // On dessine toutes les stations
        for (size_t i = 0; i < coord_x_s.size(); i++)
        {
            spriteStation.setPosition(coord_x_s[i], coord_y_s[i]);
            window.draw(spriteStation);
        }

        // On dessine la rame en mouvement
        if (currentStationIndex < coord_x_s.size())
        {
            Vector2f positionActuelle = spriteRame.getPosition();
            Vector2f positionCible = Vector2f(coord_x_s[currentStationIndex], coord_y_s[currentStationIndex]);
            Vector2f direction = positionCible - positionActuelle;
            float distance_station = distance(positionActuelle, positionCible);

            // On se d�place
            if (distance_station > 5.0f)
            {
                direction = direction / distance_station;
                spriteRame.move(direction * 0.5f);
            }
            else // On est arriv� � la station, on passe � la suivante
            {
                currentStationIndex++;
            }
        }
        /*
            if (cible_coord_x_s != coord_x_s.end() && cible_coord_y_s != coord_y_s.end())
            {
                Vector2f positionActuelle = spriteRame.getPosition();
                Vector2f positionCible = Vector2f(*cible_coord_x_s, *cible_coord_y_s);
                Vector2f direction = positionCible - positionActuelle;
                float distance_station = distance(positionActuelle, positionCible);

                // D�placement de la rame
                if (distance_station != 0)
                {
                    direction = direction / distance_station;
                    spriteRame.move(direction * 0.5f);

                    // Si on arrive pr�s de la station cible, on passe � la suivante
                    if (distance(positionActuelle, positionCible) < 5.0f)
                    {
                        cible_coord_x_s++;
                        cible_coord_y_s++;
                    }
                }
            }
        }
            */

  
        window.display(); // � la fin de la boucle principale pour tout afficher � l'�cran
    }




	return EXIT_SUCCESS;
}