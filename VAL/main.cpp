#include "VAL.hpp"


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


/*******************************************************************************************/
/***********************************     SFML     ******************************************/
/*******************************************************************************************/


int main()
{
    locale::global(locale{ "fr-FR" });


    /**********************************     Setup     ******************************************/
	

    int nbStation = 0;
    int nbRame = 0;

    // Pr�sentation du projet et initialisation du metro (nb de stations/rames)
    cout << "\t---- Projet VAL ----" << endl << endl <<"Ce projet consiste � refaire un m�tro." << endl << endl << "Donnez le nombre de station : ";
    cin >> nbStation;
    cout << "Donnez le nombre de rame : ";
    cin >> nbRame;
    cout << "Cr�ation du m�tro..." << endl;
    Superviseur superviseur(nbStation, nbRame);
    cout << "Votre m�tro contient : " << endl << "- " << superviseur.getNbStation() << " stations" << endl << "- " << superviseur.getNbRame() << " rames" << endl << endl;


    /**********************************     Stations     *****************************************/


    // Cr�ation de la map stations qui contiendra tous les stations dans l'ordre et stations_coord qui contient les coordonn�es des stations dans l'ordre
    cout << "\tCr�ation des Stations" << endl << endl << "Vous allez cr�er vos stations avec les param�tres de votre choix." << endl << endl;
    map<int, string> stations; // noms de stations par id de stations
    map<int, string>::iterator cible_s;
    map<int, float> stations_coord_x; // coordonn�es x par id de stations
    map<int, float>::iterator cible_s_coord_x;
    map<int, float> stations_coord_y; // coordonn�es y par id de stations
    map<int, float>::iterator cible_s_coord_y;

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

    // Cr�ation de la map stations_coord qui contient les coordonn�es des stations dans l'ordre

    // On affiche les stations dans l'ordre
    cout << "Votre m�tro contient les " << stations.size() << " stations suivantes : " << endl;
    for (cible_s = stations.begin();cible_s != stations.end();cible_s++)
    {
        cout << "- " << cible_s->first << " " << cible_s->second << endl; // donne le num�ro de la station et son nom
    }
    cout << endl;


    /**********************************     Rames     *****************************************/


    // Cr�ation du set rames qui contiendra tous les rames dans l'ordre
    cout << "\tCr�ation des Rames" << endl << endl << "Vous allez ajouter les rames dans votre m�tro." << endl << endl;
    set<int> rames;

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
    for (const auto& elem :rames)
    {
        cout << "- " << elem << endl;
    }
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

    // Stations
    spriteStation.setTexture(textureStation);
    spriteStation.setScale(0.1f, 0.1f);

    /*
    Note 
    
    On va utiliser les framerate pour acc�l�rer et ralentir les rame
    
    */

    // Affichage de la fen�tre
    while (window.isOpen()) // Boucle principale
    {
        Event event; // Ev�nement dans la fen�tre        
        // V�rification des entr�es clavier
        while (window.pollEvent(event)) // Boucle qui va regarder chaque �v�nement dans la fen�tre
        {
            InputHandler(event, window);
        }

        // On bouge le train (sert juste � voir si le programme toune...)
        spriteRame.move(Vector2f(1, 0));

        // On r�cup�re les coordonn�es x des stations
        vector<float>coord_x;
        for (cible_s_coord_x = stations_coord_x.begin();cible_s_coord_x != stations_coord_x.end();cible_s_coord_x++) // on parcours tous les �l�ments de l'it�rateur de stations pour les x
        {
            coord_x.push_back(cible_s_coord_x->second); // on range les x en fin du vecteur (pour l'ordre), celui-ci contient les �l�ments seconds de la map, autrement dit les x
        }

        // On r�cup�re les coordonn�es y des stations (m�me m�thodes que pour les x)
        vector<float>coord_y;
        for (cible_s_coord_y = stations_coord_y.begin();cible_s_coord_y != stations_coord_y.end();cible_s_coord_y++)
        {
            coord_y.push_back(cible_s_coord_y->second);
        }

        window.clear(); // on a une fen�tre vide

        // On dessine tous les �l�ments dans la fen�tre
        window.draw(spriteBackground);
        window.draw(spriteRame);

        vector<Vector2f>coord_stations;
        auto ity = coord_y.begin();
        for (const auto& elem : coord_x)
        {
            spriteStation.setPosition(elem, (float)*ity); // on a le sprite au bonne endroit
            coord_stations.push_back(spriteStation.getPosition()); // on r�cup les coord DU SPRITE
            window.draw(spriteStation);
            ity++;
        }

        window.display(); // � la fin de la boucle principale pour tout afficher � l'�cran
    }




	return EXIT_SUCCESS;
}