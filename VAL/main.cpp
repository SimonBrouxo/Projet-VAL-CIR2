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

    // Présentation du projet et initialisation du metro (nb de stations/rames)
    cout << "\t---- Projet VAL ----" << endl << endl <<"Ce projet consiste à refaire un métro." << endl << endl << "Donnez le nombre de station : ";
    cin >> nbStation;
    cout << "Donnez le nombre de rame : ";
    cin >> nbRame;
    cout << "Création du métro..." << endl;
    Superviseur superviseur(nbStation, nbRame);
    cout << "Votre métro contient : " << endl << "- " << superviseur.getNbStation() << " stations" << endl << "- " << superviseur.getNbRame() << " rames" << endl << endl;


    /**********************************     Stations     *****************************************/


    // Création de la map stations qui contiendra tous les stations dans l'ordre
    cout << "\tCréation des Stations" << endl << endl << "Vous allez créer vos stations avec les paramètres de votre choix." << endl << endl;
    map<int, string> stations;
    map<int, string>::iterator cible_s;

    // On remplit la map avec l'id de la station et son nom
    for (int i = 0;i < nbStation;i++) 
    {
        cout << "Création d'une station :" << endl;
	    Station station; // création d'une station
	    station.setStation(); // on donne les paramètres de la station (nom,position...)
        stations.insert(pair<int, string>(station.getStation_id(), station.getStation_noun())); // on insert dans la map, l'id et le nom de la station
    }

    // On affiche les stations dans l'ordre
    cout << "Votre métro contient les " << stations.size() << " stations suivantes : " << endl;
    for (cible_s = stations.begin();cible_s != stations.end();cible_s++)
    {
        cout << "- " << cible_s->first << " " << cible_s->second << endl;
    }
    cout << endl;


    /**********************************     Rames     *****************************************/


    // Création du set rames qui contiendra tous les rames dans l'ordre
    cout << "\tCréation des Rames" << endl << endl << "Vous allez ajouter les rames dans votre métro." << endl << endl;
    set<int> rames;

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
    for (const auto& elem :rames)
    {
        cout << "- " << elem << endl;
    }
    cout << endl;

	//stationA.printStation_stats();

    /***********************************     SFML     ******************************************/


    // Création de la fenêtre avec la résolution, le titre de la fenêtre et la syncro verticale
    const Vector2u WIN_SIZE(WIN_WIDTH, WIN_HEIGHT);
    RenderWindow window(VideoMode(WIN_SIZE.x, WIN_SIZE.y), "Projet VAL !!!");
    window.setVerticalSyncEnabled(true);

    // Création des textures/sprites avec leur chargement
    Texture textureTrain, textureBackground, textureDrapeau;
    Sprite spriteTrain, spriteBackground, spriteDrapeau1, spriteDrapeau2, spriteDrapeau3;

    // Chargement des images + erreur
    if (!textureTrain.loadFromFile(path_image + "train.png") || !textureBackground.loadFromFile(path_image + "background.png") || !textureDrapeau.loadFromFile(path_image + "drapeau.png"))
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




	return EXIT_SUCCESS;
}