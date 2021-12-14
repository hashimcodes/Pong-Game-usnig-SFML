#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>

int main() {

	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Pong Game");
	window.setFramerateLimit(60);

	std::cout << "Game started" << std::endl;

	//Fonts
	sf::Font font;
	if (!font.loadFromFile("Data/Consolas.ttf")) 
		std::cout << "Font is not found" << std::endl;

	sf::Text score;
	score.setFont(font);
	score.setCharacterSize(30);
	score.setFillColor(sf::Color(255, 0, 0));
	score.setPosition(350, 10);
	score.setString("0 : 0");


	//Images
	sf::Texture pad_texture;
	if(!pad_texture.loadFromFile("Data/pad.png"))
		std::cout << "Pad texture is not found" << std::endl;

	sf::Texture ball_texture;
	if (!ball_texture.loadFromFile("Data/ball.png"))
		std::cout << "Ball texture is not found" << std::endl;

	sf::Texture backGround_texture;
	if (!backGround_texture.loadFromFile("Data/background.png"))
		std::cout << "Background texture is not found" << std::endl;


	//Sounds
	sf::SoundBuffer ballCrashBuffer;
	if(!ballCrashBuffer.loadFromFile("Data/DrumHit.wav"))
		std::cout << "Ball crashing sound is not found" << std::endl;

	sf::Sound ballCrashSound;
	ballCrashSound.setBuffer(ballCrashBuffer);

	sf::SoundBuffer ballOutBuffer;
	if (!ballOutBuffer.loadFromFile("Data/A7eh.wav"))
		std::cout << "Ball out sound is not found" << std::endl;

	sf::Sound ballOutSound;
	ballOutSound.setBuffer(ballOutBuffer);
	

	//Shapes
	//BackGround
	sf::RectangleShape backGround;
	backGround.setSize(sf::Vector2f(800, 600));
	backGround.setPosition(0, 0);
	backGround.setTexture(&backGround_texture);

	//Pad1
	sf::RectangleShape pad1;
	pad1.setSize(sf::Vector2f(50, 100));
	pad1.setPosition(50, 200);
	pad1.setTexture(&pad_texture);

	//Pad2
	sf::RectangleShape pad2;
	pad2.setSize(sf::Vector2f(50, 100));
	pad2.setPosition(700, 200);
	pad2.setTexture(&pad_texture);

	//Ball
	sf::RectangleShape ball;
	ball.setSize(sf::Vector2f(50, 50));
	ball.setPosition(400, 200);
	ball.setTexture(&ball_texture);


	//States
	bool upArrow = false;
	bool downArrow = false;


	//variables
	float yVelocityPad1 = 0.0;
	float yVelocityPad2 = 0.0;
	float xVelocityBall = -6.0;
	float yVelocityBall = -6.0;
	int pad1Score = 0;
	int pad2Score = 0;


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

			//State handling
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) upArrow = true;
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Up) upArrow = false;
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down) downArrow = true;
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Down) downArrow = false;
		}

		//Logic handling
		//Pad 1 movement
		if (upArrow) yVelocityPad1 = -5.0;
		if (downArrow) yVelocityPad1 = 5.0;
		if (upArrow && downArrow) yVelocityPad1 = 0.0;
		if (upArrow == false && downArrow == false) yVelocityPad1 = 0.0;

		pad1.move(0, yVelocityPad1);

		//Pad 1 Boundries checking
		if (pad1.getPosition().y < 0) pad1.setPosition(50, 0);
		if (pad1.getPosition().y > 500) pad1.setPosition(50, 500);

		//Pad 2 AI movement
		if (ball.getPosition().y > pad2.getPosition().y) yVelocityPad2 = -3.0;
		if (ball.getPosition().y < pad2.getPosition().y) yVelocityPad2 = 3.0;

		pad2.move(0, yVelocityPad2);

		//Pad 2 Boundries checking
		if (pad2.getPosition().y < 0) pad2.setPosition(700, 0);
		if (pad2.getPosition().y > 500) pad2.setPosition(700, 500);

		//Ball movement
		ball.move(xVelocityBall, yVelocityBall);

		if (ball.getPosition().y < 0) yVelocityBall = -yVelocityBall;
		if (ball.getPosition().y > 550) yVelocityBall = -yVelocityBall;
		
		if (ball.getPosition().x < -50)
		{
			pad2Score += 5;
			ball.setPosition(300, 200);
			ballOutSound.play();
		}
		if (ball.getPosition().x > 800)
		{
			pad1Score += 5;
			ball.setPosition(300, 200);
			ballOutSound.play();
		}

		//Collision of the pads
		if (ball.getGlobalBounds().intersects(pad1.getGlobalBounds()))
		{
			xVelocityBall = -xVelocityBall;
			pad1Score++;
			ballCrashSound.play();
		}
			
		if (ball.getGlobalBounds().intersects(pad2.getGlobalBounds()))
		{
			xVelocityBall = -xVelocityBall;
			pad2Score++;
			ballCrashSound.play();
		}


		//Rendering part on the main loop
		window.clear();


		//Draw things
		window.draw(backGround);
		window.draw(pad1);
		window.draw(pad2);
		window.draw(ball);

		//Score
		std::stringstream text;
		text << pad1Score << " : " << pad2Score;
		score.setString(text.str());
		window.draw(score);


		window.display();
	}

	return 0;
}