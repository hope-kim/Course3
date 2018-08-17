#pragma once
#include <iostream>
#include <cmath>
#include "draw.h"

class Turtle
{
	private:
		double mx0;
		double my0;
		double mdir0;
		Color mcolor;
		int mtransparency;
	public:
		Turtle();
		Turtle(double inputx0, double inputy0, double inputdir0);
		void move(double dist);
		void turn(double deg);
		void setColor(Color c); 
		void off();
      void on();
};
