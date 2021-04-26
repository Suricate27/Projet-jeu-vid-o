//test pour github partie Laurent

#include <iostream>
#include <SFML/graphics.hpp>

#define vitesseDeplacement 240 // en pixel par seconde || un define car prend moins de place qu'une constante.
#define taillePersonnage 192

int delai = 0;
enum direction{haut,gauche,bas,droite};
sf::Vector2i animation(0,haut); // tableau à 2 dimension et que pour des int ( d'où le 2i) , x et y
bool updateFPS = false;

int main() {
	sf::Texture texturePerso;
	sf::Sprite spritePerso;
	//fenetre
	sf::RenderWindow window(sf::VideoMode(800, 800), "Fenêtre SFML"); //création de la fenètre (dimension, titre)
	//clock
	sf::Clock clock;
	sf::Time TempsDebut = sf::Time::Zero; // la clock est initialisée a zéro
	//variables
	bool moveUp = 0, moveDown = 0, moveRight = 0, moveLeft = 0;
	//chargement du fichier personnage
	if (!texturePerso.loadFromFile("Textures/sprites.png")) // vérif ouverture fichier
	{
		std::cout << "Erreur chargement texture" << std::endl;
	}
	texturePerso.setSmooth(true); // petit lissage

	spritePerso.setTexture(texturePerso);
	spritePerso.setTextureRect(sf::IntRect(1* taillePersonnage,3* taillePersonnage, taillePersonnage, taillePersonnage)); // Pour que le premier affichage du personnage soit vers la droite
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
		delai++; // permet de ralentir le nombre d'affichage d'animation 
		if (delai >= 8)
		{
			animation.x++; //passer à l'animation suivante
			delai = 0;
		}
		if (updateFPS) { // Si l'utilisateur à une touche enfoncée on vas jouer les animation en boucle
			if (animation.x * taillePersonnage >= 9 * taillePersonnage)animation.x = 0; // il n'y en a que 9
			spritePerso.setTextureRect(sf::IntRect(animation.x * taillePersonnage, animation.y * taillePersonnage, taillePersonnage, taillePersonnage)); //x et y c'est parce qu'on va utiliser les sprites comme un tableau
		}
		updateFPS = false; //repasse à faux à chaque boucle comme ça il n'est vrai que si une touche est enfoncée.
		// il va constament tester ( 100 fois par seconde ) s'il doit bouger. Si les variables sont vraies alors il va bouger
		// Le problème de calculer la vitesse avec des pixels c'est que si la machine ram bah le personnage est lent et ça doit être independant.
		// Donc on va calculer le déplacement avec temps passé avec la touche enfoncée.
		if (moveUp) {
			spritePerso.move(0, TempsDebut.asSeconds() * -vitesseDeplacement);
			animation.y = haut;
			updateFPS = true;
		}
		if (moveDown) {
			spritePerso.move(0, TempsDebut.asSeconds() * vitesseDeplacement);
			animation.y = bas;
			updateFPS = true;
		}
		if (moveLeft)
		{
			spritePerso.move(TempsDebut.asSeconds() * -vitesseDeplacement, 0);
			animation.y = gauche;
			updateFPS = true;
		}
		if (moveRight) {
			spritePerso.move(TempsDebut.asSeconds() * vitesseDeplacement, 0);
			animation.y = droite;
			updateFPS = true;
		}
		window.clear(); //nettoyage
		window.draw(spritePerso); // affichage de notre personnage
		window.display();//affichage de la fenêtre
	}


}