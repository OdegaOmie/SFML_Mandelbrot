#pragma once
#include <vector>
#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include <complex>
using namespace sf;

class MandelBrotGenerator 
{
private:
	std::vector<float> pixel_data;
	float precision = 100;
	float width, height;
	float scale = 1;
	Image colours;
	Image image;
	Texture texture;
	Sprite sprite;

	bool ready;
	Vector2f focusPoint;

public:

	bool getReady() {
		return ready;
	}

	MandelBrotGenerator(int const& _width, int const& _height, float const& _zoom) : width(_width), height(_height), scale(_zoom)
	{
		initData();
		focusPoint = sf::Vector2f(0, 0);
		image.create(width, height, Color::Black);
		texture.loadFromImage(image);
		sprite.setTexture(texture, true);
		colours.loadFromFile("color.jpg");
	};



	Color colorGradient(float x)
	{
		if (x>0.999) x = 0.999;
		if (x<0.001) x = 0.001;
		return colours.getPixel((int)(x*colours.getSize().x), 0);
	}

	Sprite setSprite()
	{
		for (int i = 1; i < width - 1; i++)
		{
			for (int j = 1; j < height - 1; j++)
			{
				image.setPixel(i, j, colorGradient(get(i, j) / 1000));
			}
		}
		texture.loadFromImage(image);
		return sprite;
	}

	void initData()
	{
		pixel_data.clear();
		pixel_data.resize(width*height);
		for (int i = 1; i < width - 1; i++)
		{
			for (int j = 1; j < height - 1; j++)
			{
				set(i, j, 0);
			}
		}
		ready = false;
	}

	float get(int const& i, int const& j)
	{
		if (i>0 && i <width && j>0 && j<height)
			return pixel_data[i + (j - 1)*height];
		else return 0;
	}
	void set(int i, int  j, float _coeff)
	{
		if (i>0 && i <width && j>0 && j<height)
			pixel_data[i + infClamp(j - 1, 0)*height] = _coeff;
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


	void ChangeFocus(sf::Vector2f _mousePos) 
	{
		if (scale != 1) 
		{
			focusPoint.x = (_mousePos.x - (width / 2)) * ((4 / scale) / height);
			if (focusPoint.x - (2 / scale) < -2) 
			{
				focusPoint.x = -2 + (2 / scale);
			}
			else if (focusPoint.x + (2 / scale) > 2) 
			{
				focusPoint.x = 2 - (2 / scale);
			}
			focusPoint.y = ((4 / scale) / height) * (_mousePos.y + (height / 2));
			if (focusPoint.y - (2 / scale) < -2)
			{
				focusPoint.y = -2 + (2 / scale);
			}
			else if (focusPoint.x + (2 / scale) > 2)
			{
				focusPoint.y = 2 - (2 / scale);
			}
		}
		initData();
	}

	void ChangeScale(bool _dir) 
	{
		if (_dir) 
		{
			scale += 1;
		}
		else
		{
			if (scale != 1)
			{
				scale -= 1;
			}
		}
		initData();
	}

	void run() 
	{
		ready = false;
		int count = 0;
		float x, y, z;
		for (int i = 0; i < width + 1; i++)
		{
			x = focusPoint.x - ((2 / scale) - (((4 / scale) / width) * i));
			for (int j = 0; j < height + 1; j++)
			{
				count = 0;
				z = 0;
				y = focusPoint.y - ((2 / scale) - (((4 / scale) / height) * j));
				std::complex<float> c(x, y);
				std::complex<float> z(0);
				z = (z * z) + c;
				while (abs(z) < 2.0 && count < 1000) {
					z = (z * z) + c;
					count++;
				}
				set(i, j, count);
			}
		}
		sprite = setSprite();
		ready = true;
	}

	Sprite& getSprite() {
		return sprite;
	}
};


















