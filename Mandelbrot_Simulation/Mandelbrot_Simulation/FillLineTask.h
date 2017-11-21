#pragma once

#include "AbstractTask.h"
#include <complex>
#include <iostream>
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
		float imaginaryVal, pointWidthY, pointWidthX, startPoint, realVal;
		int count = 0;
		std::complex<float> c;
		std::complex<float> z;


		pointWidthY = (4 / float(ptr->scale)) / ptr->SCREENY;
		pointWidthX = (4 / float(ptr->scale)) / ptr->SCREENX;
		startPoint = 2 / float(ptr->scale);
		realVal = ptr->focusPoint.x - (startPoint - (pointWidthX * float(x_index)));


		for (int j = 0; j < ptr->SCREENY; j++)
		{
			count = 0;
			z = 0;
			imaginaryVal = ptr->focusPoint.y - (startPoint - (pointWidthY * float(j)));
			std::complex<float> c(realVal, imaginaryVal);
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