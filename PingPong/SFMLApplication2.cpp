// SFMLApplication2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
/*
#include <SFML/Graphics.hpp>
#include "Ball.h"

int main() {
  const int width = 1000;
  const int height = 600;

  sf::RenderWindow window(sf::VideoMode({ width, height }), "Ping Pong");
  window.setFramerateLimit(60);
  Ball ball(500, 300, 30);
  
  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>())
        window.close();
    }

    ball.move(width, height);

    window.clear();
    ball.draw(window);
    window.display();
  }
}
*/

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>
int main() { 
  const int width = 1000;
  const int height = 700;
  sf::RenderWindow window(sf::VideoMode({ width, height }), "Poligon"); 
  std::srand(static_cast<unsigned>(std::time(nullptr))); 
  sf::ConvexShape pentagon;
  pentagon.setPointCount(5); 
  pentagon.setPoint(0, sf::Vector2f(0, 100));
  pentagon.setPoint(1, sf::Vector2f(100, 150)); 
  pentagon.setPoint(2, sf::Vector2f(150, 200)); 
  pentagon.setPoint(3, sf::Vector2f(200, 250));
  pentagon.setPoint(4, sf::Vector2f(250, 300));
  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) window.close(); 
    }
    pentagon.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
    window.clear();  window.draw(pentagon); window.display(); } }