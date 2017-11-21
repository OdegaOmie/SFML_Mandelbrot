#pragma once
#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp"
#include <memory>
#include "Globals.h"
using namespace sf;



class Globals 
{
private:
	static std::weak_ptr<Globals> m_instance;


public:
	Globals(int const& sx = 0, int const& sy  = 0, int const& num_cores = 1) : SCREENX(sx), SCREENY(sy), MAXTHREADS(num_cores - 1)
	{

		focusPoint = Vector2f(0.0, 0.0);
		scale = 1;
		precision = 100;
	};


	static std::shared_ptr<Globals> sharedData(int const& sx = 0, int const& sy = 0, int const& num_cores = 1) {
		std::shared_ptr<Globals> ptr = m_instance.lock();
		if (!ptr)
		{
			ptr = std::make_shared<Globals>(Globals(sx, sy, num_cores));
			m_instance = std::weak_ptr<Globals>(ptr);
		}
		return ptr;
	};

	const int SCREENX;
	const int SCREENY;
	const int MAXTHREADS;


	Vector2f focusPoint;
	int scale;
	int precision;




	void ChangeFocus(sf::Vector2f _mousePos)
	{
		if (scale != 1)
		{
			focusPoint.x += (_mousePos.x - (SCREENX / 2)) * ((4 / scale) / SCREENX);

			if (focusPoint.x - (2 / scale) < -2)
			{
				focusPoint.x = -2 + (2 / scale);
			}
			else if (focusPoint.x + (2 / scale) > 2)
			{
				focusPoint.x = 2 - (2 / scale);
			}

			focusPoint.y += (_mousePos.y - (SCREENY / 2)) * ((4 / scale) / SCREENY);

			if (focusPoint.y - (2 / scale) < -2)
			{
				focusPoint.y = -2 + (2 / scale);
			}
			else if (focusPoint.x + (2 / scale) > 2)
			{
				focusPoint.y = 2 - (2 / scale);
			}
		}
	}

	void ChangeScale(int _delta)
	{
		scale += _delta;
	}
};


std::weak_ptr<Globals> Globals::m_instance;