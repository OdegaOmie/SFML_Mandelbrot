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
	Globals(int const& sx = 0, int const& sy  = 0) : SCREENX(sx), SCREENY(sy)
	{
		focus_point = Vector2f(0.0, 0.0);
		scale = 1;
		precision = 100;
	};

	static std::shared_ptr<Globals> sharedData() {
		std::shared_ptr<Globals> ptr = m_instance.lock();
		if (!ptr)
		{
			ptr = std::make_shared<Globals>(Globals());
			m_instance = std::weak_ptr<Globals>(ptr);
		}
		return ptr;
	};

	const int SCREENX;
	const int SCREENY;

	Vector2f focus_point;
	int scale;
	int precision;
};


