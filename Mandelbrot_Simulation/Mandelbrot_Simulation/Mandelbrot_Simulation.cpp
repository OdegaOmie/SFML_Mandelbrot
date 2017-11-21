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
#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include "Globals.h"
#include "MandelBrotGenerator.h"
#include "ThreadManager.h"

using namespace sf;




int main()
{
	int NUM_CELLS_X = 1024;
	int NUM_CELLS_Y = 768;

	int SCREEN_X = 1024;
	int SCREEN_Y = 768;

	ThreadManager* tmangr = new ThreadManager();
	std::shared_ptr<Globals> g = Globals::sharedData(NUM_CELLS_X, NUM_CELLS_Y, std::thread::hardware_concurrency());
	MandelBrotGenerator mgenerator = MandelBrotGenerator();
	float scale_X = NUM_CELLS_X / NUM_CELLS_X;
	float scale_Y = NUM_CELLS_X / NUM_CELLS_Y;
	sf::RenderWindow App(sf::VideoMode(SCREEN_X, SCREEN_Y, 32), "SFML OpenGL");
	
	//App.setPosition(sf::Vector2i(1444, -320));


	glClearDepth(1.f);
	glClearColor(0.0f, 0.0f, 0.0f, 0.f); //background colour
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	Vector2f mousePos;
	bool computeSet =  true;
	sf::Sprite s = Sprite();


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

		if (zoomIn) g->ChangeScale(1);
		else if (zoomOut) g->ChangeScale(-1);
		else if (zoomInMega) g->ChangeScale(10);
		else if (zoomOutMega) g->ChangeScale(-10);

		if (changePos) { 
			g->ChangeFocus(mousePos);
		}
		if (zoomIn || zoomOut || zoomInMega || zoomOutMega || changePos) {
			computeSet = true;
		}
		//Prepare for drawing 
		// Clear color and depth buffer 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Apply some transformations 
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		App.clear(sf::Color::Black);
		if (computeSet) 
		{
			
			for (int i = 0; i < g->SCREENX; i++) {
				tmangr->add_task(mgenerator.getTask(i));
			}
			tmangr->create_workers(g->MAXTHREADS);
			computeSet = false;
		}
		if (tmangr->is_done()) {
			tmangr->join_workers();
			mgenerator.update();
			s = mgenerator.getSprite();
  			//ssetScale(sf::Vector2f(scale_X, scale_Y));
			s.scale(scale_X, scale_Y);
		}


		App.draw(s);
		App.display();
	}

	return EXIT_SUCCESS;
}




