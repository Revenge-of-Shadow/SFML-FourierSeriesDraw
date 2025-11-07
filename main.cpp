#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdint>
#include <ctime>


const double pi = std::acos(-1);

class Pen{
public:
  float r;
  float omega;
  float phi;

  Pen(){}
  Pen(float r, float o): r(r), omega(o), phi(0){}
  Pen(float r, float o, float p): r(r), omega(o), phi(p){}
};

int main()
{
  std::srand(std::time({}));

  sf::RenderWindow window(sf::VideoMode({800, 600}), "nya");

    
  int max_t = INT16_MAX;
  int r = 100;
  const int arrlen = std::rand()%10;
  Pen pens[arrlen];

  for(int i = 0; i < arrlen; ++i){
    pens[i] = Pen((std::rand()%r), (std::rand()%r-r/2), (std::rand()%360*(pi*2.f/360.f)));
  }

  while(window.isOpen()){
    sf::Event event;
    while(window.pollEvent(event)){
      if(event.type == sf::Event::Closed)
        window.close();
    }
    window.clear();

    sf::VertexArray pts(sf::PrimitiveType::Points, max_t);

    
    for(int t = 0; t < max_t; ++t) {
      //  Set starting point at the center.
      sf::Vector2f pos = sf::Vector2f(window.getSize().x/2.f, window.getSize().y/2.f);
      //  Move by the arrow thingies.
      for(int i = 0; i<arrlen; ++i){
        double angle = pens[i].phi 
                    + pi * 2.f / max_t * t * pens[i].omega  +  pi/2.f;
        sf::Vector2f offs = sf::Vector2f(std::cos(angle)*pens[i].r, std::sin(angle)*pens[i].r);
        pos += offs;
      }
      //  Set the final position as the drawing point.
      pts[t].position = pos;
    }
    window.draw(pts);
    window.display();
  }
}
