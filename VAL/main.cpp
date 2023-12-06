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


    // Cr�ation de la map stations qui contiendra tous les stations dans l'ordre
    cout << "\tCr�ation des Stations" << endl << endl << "Vous allez cr�er vos stations avec les param�tres de votre choix." << endl << endl;
    map<int, string> stations;
    map<int, string>::iterator cible_s;

    // On remplit la map avec l'id de la station et son nom
    for (int i = 0;i < nbStation;i++) 
    {
        cout << "Cr�ation d'une station :" << endl;
	    Station station; // cr�ation d'une station
	    station.setStation(); // on donne les param�tres de la station (nom,position...)
        stations.insert(pair<int, string>(station.getStation_id(), station.getStation_noun())); // on insert dans la map, l'id et le nom de la station
    }

    // On affiche les stations dans l'ordre
    cout << "Votre m�tro contient les " << stations.size() << " stations suivantes : " << endl;
    for (cible_s = stations.begin();cible_s != stations.end();cible_s++)
    {
        cout << "- " << cible_s->first << " " << cible_s->second << endl;
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

	//stationA.printStation_stats();

    /***********************************     SFML     ******************************************/


    // Cr�ation de la fen�tre avec la r�solution, le titre de la fen�tre et la syncro verticale
    const Vector2u WIN_SIZE(WIN_WIDTH, WIN_HEIGHT);
    RenderWindow window(VideoMode(WIN_SIZE.x, WIN_SIZE.y), "Projet VAL !!!");
    window.setVerticalSyncEnabled(true);

    // Cr�ation des textures/sprites avec leur chargement
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






    // Affichage de la fen�tre
    while (window.isOpen()) // Boucle principale
    {
        Event event; // Ev�nement dans la fen�tre        
        while (window.pollEvent(event)) // Boucle qui va regarder chaque �v�nement dans la fen�tre
        {
            // V�rification des entr�es clavier
            InputHandler(event, window);
        }

        spriteTrain.move(Vector2f(1, 0));


        spriteDrapeau1.setPosition(200, 200);
        spriteDrapeau2.setPosition(500, 200);
        spriteDrapeau3.setPosition(700, 100);

        window.clear(); // on a une fen�tre vide

        // On dessine tous les �l�ments dans la fen�tre
        window.draw(spriteBackground);
        window.draw(spriteTrain);
        window.draw(spriteDrapeau1);
        window.draw(spriteDrapeau2);
        window.draw(spriteDrapeau3);



        window.display(); // � la fin de la boucle principale pour tout afficher � l'�cran
    }




	return EXIT_SUCCESS;
}