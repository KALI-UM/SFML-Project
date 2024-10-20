#include "pch.h"
#include <SFML/Graphics.hpp>
#include <random>
#include <time.h>

#include "Scene_Test.h"

int main()
{

	sf::RenderWindow window(sf::VideoMode(1920, 1050), "SFML works!");
	GameManager::GetInstance()->Initialize(&window);

	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color(20,20,20));
	shape.setOrigin(shape.getRadius(), shape.getRadius());

	//GameManager::GetInstance()->GetResourceManager()->LoadYaml();

	SceneBase* scene = new Scene_Test();
	GameManager::GetInstance()->GetSceneManager()->PushScene(scene);


	sf::Clock clock;
	while (window.isOpen())
	{
		sf::Event evt;

		sf::Time dt = clock.restart();
		float deltaTime = dt.asSeconds();

		while (window.pollEvent(evt))
		{
			GameManager::GetInstance()->UpdateEvent(evt);

			switch (evt.type)
			{
			case sf::Event::Closed:
			{
				window.close();
				break;
			}
			default:
				break;
			}
		}

		window.clear();
		GameManager::GetInstance()->Update(deltaTime);
		shape.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

		window.draw(shape);
		GameManager::GetInstance()->Render();
		window.display();

		GameManager::GetInstance()->LateUpdate();
	}

	return 0;
}