#include "turtle.h"
#include "draw.h"

Turtle::Turtle()
{
   mx0 = 0;
   mx0 = 0;
   mdir0 = 0;
   mcolor = draw::BLACK;
   mtransparency = 0;
};

Turtle::Turtle(double inputx0, double inputy0, double inputdir0)
{
   mx0 = inputx0;
   my0 = inputy0;
   mdir0 = inputdir0;
   mcolor = draw::BLACK;
   mtransparency = 0;
};

void Turtle::move(double dist)
{
   if (mtransparency == 0)
   {
      draw::settransparency(0.0);
      draw::setcolor(mcolor);
      double x2 = mx0+dist*cos(mdir0*M_PI/180);
      double y2 = my0+dist*sin(mdir0*M_PI/180);
      draw::line(mx0, my0, x2, y2);
      mx0 = x2;
      my0 = y2;
   }
   else
   {
      draw::settransparency(1.0);
      draw::setcolor(mcolor);
      double x2 = mx0+dist*cos(mdir0*M_PI/180);
      double y2 = my0+dist*sin(mdir0*M_PI/180);
      mx0 = x2;
      my0 = y2;
   }
};

void Turtle::turn(double deg)
{
   mdir0 += deg;
};


void Turtle::setColor(Color c)
{
   mcolor = c;
}; 


void Turtle::off()
{
   mtransparency = 1;
};

void Turtle::on()
{
   mtransparency = 0;
};
