#pragma once

#include "AbstractTask.h"
#include <complex>
#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp"
#include "Globals.h"




class FillLineTask : public AbstractTask
{
public:
	FillLineTask(std::pair<float*, float> _line_data ) : data(_line_data.first), x_index(_line_data.second)
	{
		
	};

	void run() override 
	{
		std::shared_ptr<Globals> ptr = Globals::sharedData();
		float real_val, imaginary_val;
		int count = 0;

		std::complex<float> c;
		std::complex<float> z;

		for (int j = 0; j < ptr->SCREENY; j++)
		{
			count = 0;
			z = 0;
			imaginary_val = ptr->focus_point.y - ((2 / ptr->scale) - (((4 / ptr->scale) / ptr->SCREENY) * j));
			c = (real_val, imaginary_val);
			z = (z * z) + c;
			while (abs(z) < 2.0 && count < ptr->precision) {
				z = (z * z) + c;
				count++;
			}
			data[j] = count;
		}
	};

private:
	float* data;
	float x_index;
};