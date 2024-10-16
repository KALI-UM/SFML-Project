#include <SFML/Graphics.hpp>
#include <random>

int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Transparent);

	sf::Texture tx;
	sf::Sprite sp;
	tx.loadFromFile("resource/ex.png");
	sp.setTexture(tx);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.draw(sp);
		window.display();

		shape.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255, 150));
		shape.setRadius(rand() % 100);
	}



	return 0;
}