#include "draw.h"
#include "turtle.h"

int main()
{
   draw::setpenwidth(10); // thick lines
   draw::setrange(-100, 100);
   
   Turtle outside(-50, 50, 0);
   outside.setColor(draw::BLACK);
   outside.move(100);
   draw::show(1000);
   outside.turn(-90);
   outside.move(100);
   draw::show(1000);
   outside.turn(-90);
   outside.move(100);
   draw::show(1000);
   outside.turn(-90);
   outside.move(100);
   draw::show(1000);
   
   
   Turtle eyes(-25, 25, 45);
   eyes.setColor(draw::BLUE);
   eyes.move(5);
   draw::show(1000);
   eyes.turn(-45);
   eyes.move(5);
   draw::show(1000);
   eyes.turn(-45);
   eyes.move(5);
   draw::show(1000);
   eyes.off();
   eyes.turn(45);
   eyes.move(25);
   draw::show(1000);
   eyes.on();
   eyes.turn(45);
   eyes.move(5);
   draw::show(1000);
   eyes.turn(-45);
   eyes.move(5);
   draw::show(1000);
   eyes.turn(-45);
   eyes.move(5);
   draw::show(1000);
   
   Turtle nose(-6, 0, 45);
   nose.setColor(draw::YELLOW);
   nose.move(5);
   draw::show(1000);
   nose.turn(-45);
   nose.move(5);
   draw::show(1000);
   nose.turn(-45);
   nose.move(5);
   draw::show(1000);
   
   Turtle mouth(-30, -10, -45);
   mouth.setColor(draw::CORAL);
   mouth.move(25);
   draw::show(1000);
   mouth.turn(45);
   mouth.move(25);
   draw::show(1000);
   mouth.turn(45);
   mouth.move(25);
   draw::show(1000);
   
   
   
   
   return 0;
}
