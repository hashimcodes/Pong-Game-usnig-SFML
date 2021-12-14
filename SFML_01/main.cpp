#include <SFML\Graphics.hpp>
#include <iostream>

int main() {

	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Works");
	//window.setVerticalSyncEnabled( true );
	window.setFramerateLimit(60);

	std::cout << "Game started" << std::endl;

	bool up_key = false;

	while (window.isOpen())
	{
		//Event part on the main game loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			//Process events
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Up)
				{
					up_key = true;
				}
			}

			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Up)
				{
					up_key = false;
				}
			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					std::cout << "Left mouse key pressed" << std::endl;
					std::cout << event.mouseButton.x << std::endl;
					std::cout << event.mouseButton.y << std::endl;
				}
			}

			/*if (event.type == sf::Event::MouseMoved)
			{
				std::cout << event.mouseMove.x << std::endl;
				std::cout << event.mouseMove.y << std::endl;
			}*/
		}

		//Logic handling
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) 
		{
			std::cout << "up key pressed then releassed" << std::endl;
		}

		//Rendering part on the main loop
		window.clear();

		//Draw things

		window.display();
	}

	return 0;
}