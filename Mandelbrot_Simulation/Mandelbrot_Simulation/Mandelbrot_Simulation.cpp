//////////////////////////////////////////////////////////// 
// Headers 
//////////////////////////////////////////////////////////// 
#include "stdafx.h" 
#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 


#include <iostream> 
#include <vector>
#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include <complex>
#include "MandelBrotGenerator.h"

int width = 300;
int height = 300;
float zoom = 2;



int main()
{


	sf::RenderWindow App(sf::VideoMode(width, height, 32), "SFML OpenGL");


	MandelBrotGenerator mandel = MandelBrotGenerator(width, height, zoom);



	glClearDepth(1.f);
	glClearColor(0.0f, 0.0f, 0.0f, 0.f); //background colour
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	Vector2f mousePos;

	// Start game loop 
	while (App.isOpen())
	{
		// Process events 
		sf::Event Event;
		while (App.pollEvent(Event))
		{
			// Close window : exit 
			if (Event.type == sf::Event::Closed)
				App.close();

			// Escape key : exit 
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
				App.close();


		}
		mousePos = Vector2f(Mouse::getPosition(App).x, Mouse::getPosition(App).y);

		bool changePos = Mouse::isButtonPressed(Mouse::Left);
		bool zoomIn = Keyboard::isKeyPressed(Keyboard::A);
		bool zoomOut = Keyboard::isKeyPressed(Keyboard::D);

		bool zoomInMega = Keyboard::isKeyPressed(Keyboard::W);
		bool zoomOutMega = Keyboard::isKeyPressed(Keyboard::S);


		if (zoomIn) mandel.ChangeScale(true);
		else if (zoomOut) mandel.ChangeScale(false);
		else if (zoomInMega) mandel.ChangeScaleSuper(false);
		else if (zoomOutMega) mandel.ChangeScaleSuper(false);

		if (changePos) mandel.ChangeFocus(mousePos);
		//Prepare for drawing 
		// Clear color and depth buffer 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Apply some transformations 
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		App.clear(sf::Color::Black);
		if (!mandel.getReady()) {
			mandel.run();
		}
		else {
			App.draw(mandel.getSprite());
		}
		


		///HERE BE STUFF////
		

		App.display();
	}

	return EXIT_SUCCESS;
}
