//test pour github partie Laurent

#include <iostream>
#include <SFML/graphics.hpp>

#define vitesseDeplacement 240 // en pixel par seconde || un define car prend moins de place qu'une constante.
std::vector <sf::Drawable*> mesObjets; // tableau de dessins sfml que je nomme mes objets
sf::CircleShape *cercleCourant;

int main() {
	//cercle
	cercleCourant = new sf::CircleShape(100); // attention la création dynamique doit se faire dans le main absolument 
	cercleCourant->setFillColor(sf::Color::Green);
	mesObjets.push_back(cercleCourant);
	//fenetre
	sf::RenderWindow window(sf::VideoMode(800, 800), "Fenêtre SFML"); //création de la fenètre (dimension, titre)
	//clock
	sf::Clock clock;
	sf::Time TempsDebut = sf::Time::Zero; // la clock est initialisée a zéro
	//variables
	bool moveUp = 0, moveDown = 0, moveRight = 0, moveLeft = 0;
	//début de la boucle fenetre ouverte
	while (window.isOpen()) {
		TempsDebut = clock.restart(); // démarer la clock
		sf::Event event; //  création d'un object evenement
		window.setFramerateLimit(100); //FPS limit 100
		while (window.pollEvent(event)) {

			switch (event.type)
			{
			case sf::Event::Closed:  // permet de fermer la fenêtre si on clique sur la croix
				window.close();
				break;
			case sf::Event::KeyPressed: // passe les variables bool à 1 si la touche est enfoncée

				switch (event.key.code)
				{
				case sf::Keyboard::Z:
					moveUp = 1;
					break;
				case sf::Keyboard::Q:
					moveLeft = 1;
					break;
				case sf::Keyboard::S:
					moveDown = 1;
					break;
				case sf::Keyboard::D:
					moveRight = 1;
					break;
				case sf::Keyboard::Space:
					cercleCourant = new sf::CircleShape(100);
					cercleCourant->setFillColor(sf::Color::Green);
					mesObjets.push_back(cercleCourant);
				}
				break;
			case sf::Event::KeyReleased:// passe les variables à zéro si la touche est relachée

				switch (event.key.code)
				{
				case sf::Keyboard::Z:
					moveUp = 0;
					break;
				case sf::Keyboard::Q:
					moveLeft = 0;
					break;
				case sf::Keyboard::S:
					moveDown = 0;
					break;
				case sf::Keyboard::D:
					moveRight = 0;
					break;
				}
				break;
			}

		}
		// il va constament tester ( 100 fois par seconde ) s'il doit bouger. Si les variables sont vraies alors il va bouger
		// Le problème de calculer la vitesse avec des pixels c'est que si la machine ram bah le personnage est lent et ça doit être independant.
		// Donc on va calculer le déplacement avec temps passé avec la touche enfoncée.
		if (moveUp)cercleCourant->move(0, TempsDebut.asSeconds() * -vitesseDeplacement);
		if (moveDown)cercleCourant->move(0, TempsDebut.asSeconds() * vitesseDeplacement);
		if (moveLeft)cercleCourant->move(TempsDebut.asSeconds() * -vitesseDeplacement, 0);
		if (moveRight)cercleCourant->move(TempsDebut.asSeconds() * vitesseDeplacement, 0);
		window.clear(); //nettoyage
		for (auto cercleCourant : mesObjets)
		{
			window.draw(*cercleCourant);
		}
		// apparition du cercle dans la fenêtre 
		window.display();//affichage de la fenêtre
	}


}