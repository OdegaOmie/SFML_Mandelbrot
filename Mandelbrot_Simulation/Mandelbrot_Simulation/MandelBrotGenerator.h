#pragma once
#include <vector>
#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp"
#include "FillLineTask.h"
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

	float get(int const& x, int const& y) 
	{
		int  t = pixel_data[x][y];
		return pixel_data[x][y];
	}

	void initialise()
	{

		for (int i = 0; i < ptr->SCREENX; i++) {
			pixel_data.push_back(new float[ptr->SCREENY]);
		}

		image.create(ptr->SCREENX, ptr->SCREENY, Color::Black);
		//int a = ptr->SCREENX;
		//int b = ptr->SCREENY;
		//image.create(1024,768, Color::Black);


		texture.loadFromImage(image);
		sprite.setTexture(texture, true);
		colours.loadFromFile("color.jpg");
	}


public:


	MandelBrotGenerator()
	{
		ptr = Globals::sharedData();
		initialise();
	};



	void update()
	{
		setSprite();
	}

	Sprite& getSprite() {
		return sprite;
	}

	FillLineTask* getTask(int i) {
		return new FillLineTask(std::make_pair(pixel_data[i], i));
	}

};


















