#pragma once
#include <vector>
#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp"
using namespace sf;




class MandelBrotGenerator 
{
private:

	std::vector<float*> pixel_data;
	Image colours;
	Image image;
	Texture texture;
	Sprite sprite;
	std::shared_ptr<Globals> ptr;




	Color colorGradient(float const& x)
	{
		if (x>0.999) return colours.getPixel((int)((0.999)*colours.getSize().x), 0);
		else if (x<0.001) return colours.getPixel((int)((0.001)*colours.getSize().x), 0);
		else return colours.getPixel((int)(x*colours.getSize().x), 0);
	}

	Sprite setSprite()
	{
		for (int i = 0; i < ptr->SCREENX; i++)
		{
			for (int j = 0; j < ptr->SCREENY; j++)
			{
				image.setPixel(i, j, colorGradient(get(i, j) / ptr->precision));
			}
		}
		texture.loadFromImage(image);
		return sprite;
	}

	float get(int const& i, int const& j)
	{
		if (i >= 0 && i <ptr->SCREENX && j >= 0 && j<ptr->SCREENY)
			return pixel_data[i + (j - 1)*(ptr->SCREENY)];
		else return 0;
	}

	void set(int i, int  j, float _coeff)
	{
		if (i>=0 && i <ptr->SCREENX && j>=0 && j<ptr->SCREENY)
			pixel_data[i + infClamp(j - 1, 0)*ptr->SCREENY] = _coeff;
	}

	float infClamp(float value, float min)
	{
		float result;
		if (value < min)
			result = min;
		else
			result = value;
		return result;
	}



public:

	MandelBrotGenerator()
	{
		ptr = Globals::sharedData();
	};

	void initialise()
	{
		
		pixel_data.clear();
		pixel_data.resize(ptr->SCREENX*ptr->SCREENY);
		for (int i = 0; i < ptr->SCREENX; i++)
		{
			for (int j = 0; j < ptr->SCREENY; j++)
			{
				set(i, j, 0);
			}
		}

		image.create(ptr->SCREENX, ptr->SCREENY, Color::Black);
		texture.loadFromImage(image);
		sprite.setTexture(texture, true);
		colours.loadFromFile("color.jpg");
	}

	void run()
	{

	}

	Sprite& getSprite() {
		return sprite;
	}

};


















