#include "VAL.hpp"

/*******************************************************************************************/
/***********************************     SFML     ******************************************/
/*******************************************************************************************/


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


    // Création du set rames qui contiendra tous les rames dans l'ordre
    cout << "\tCréation des Rames" << endl << endl << "Vous allez ajouter les rames dans votre métro." << endl << endl;
    set<int> rames; // Ordre des rames

    // On remplit le vecteur avec tous les rames
    for (int i = 0;i < nbRame;i++)
    {
        cout << "Création d'une rame :" << endl;
        Rame rame; // création d'une rame
        rame.setRame(); // on donne les paramètres de la rame
        rames.insert(rame.getRame_id()); // on récupère l'id pour la mettre dans le set
    }

    // On affiche les rames dans l'ordre
    cout << "Votre métro contient les " << rames.size() << " rames suivantes : " << endl;
    for (const auto& elem : rames) { cout << "- " << elem << endl; }
    cout << endl;


    /***********************************     SFML     ******************************************/


    // Création de la fenêtre avec la résolution, le titre de la fenêtre et la syncro verticale
    const Vector2u WIN_SIZE(WIN_WIDTH, WIN_HEIGHT);
    RenderWindow window(VideoMode(WIN_SIZE.x, WIN_SIZE.y), "Projet VAL !!!");
    window.setVerticalSyncEnabled(true);

    // Création des textures/sprites avec leur chargement
    Texture textureRame, textureBackground, textureStation;
    Sprite spriteRame, spriteBackground, spriteStation, spriteStation1, spriteStation2, spriteStation3;

    // Chargement des images + erreur
    if (!textureRame.loadFromFile(path_image + "rame.png") || !textureBackground.loadFromFile(path_image + "background.png") || !textureStation.loadFromFile(path_image + "station.png")) { cerr << "Erreur de chargement d'image" << endl; return EXIT_FAILURE; }

    // Background
    spriteBackground.setTexture(textureBackground);
    spriteBackground.setScale(WIN_SIZE.x, WIN_SIZE.y);

    // Rame
    spriteRame.setTexture(textureRame);
    spriteRame.setScale(0.1f, 0.1f);
    spriteRame.setPosition(Vector2f(coord_x_s[0], coord_y_s[0])); // On place la rame à la première station
    size_t idx_station = 0; // Pour savoir si la rame a atteint une station
    int direction = 1; // direction = 1 si on avance pour aller vers la dernière station ou direction = -1 si on recule pour revenir à la première station 


    // Stations
    spriteStation.setTexture(textureStation);
    spriteStation.setScale(0.2f, 0.2f);


    while (window.isOpen()) // Boucle principale et ouverture de la fenêtre
    {

        // Vérification des entrées clavier
        Event event; // Evènement dans la fenêtre        
        while (window.pollEvent(event)) { InputHandler(event, window); }// Boucle qui va regarder chaque évènement dans la fenêtre

        window.clear(); // On "nettoie" la fenêtre (littéralement...) pour qu'elle soit vide
        window.draw(spriteBackground); // on dessine le background


        // On dessine toutes les stations
        for (int i = 0; i < coord_x_s.size(); i++)
        {
            spriteStation.setPosition(coord_x_s[i], coord_y_s[i]);
            window.draw(spriteStation);
        }

        // On dessine la rame en mouvement
        if (idx_station < coord_x_s.size())
        {
            Vector2f positionActuelle = spriteRame.getPosition();
            Vector2f positionCible = Vector2f(coord_x_s[idx_station], coord_y_s[idx_station]);
            Vector2f chemin = positionCible - positionActuelle;
            float distance_station = distance(positionActuelle, positionCible);

            // On se déplace
            if (distance_station > 5.0f)
            {
                chemin = chemin / distance_station;
                spriteRame.move(chemin * 0.8f);
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
        }
        window.draw(spriteRame);
  
        window.display(); // à la fin de la boucle principale pour tout afficher à l'écran
    }


	return EXIT_SUCCESS;
}