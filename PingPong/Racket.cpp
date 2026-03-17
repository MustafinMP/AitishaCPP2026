#include "Racket.h"
#include "Ball.h"
#include <SFML/Graphics.hpp>

Racket::Racket(int x, int y) {
  this->x = x;
  this->y = y;
  this->w = 50;
  this->h = 150;
  this->rect.setSize(sf::Vector2f(this->w, this->h));
  this->rect.setPosition(sf::Vector2f(x, y));
  this->vy = 0;
}

void Racket::moveUp() {};

void Racket::moveDown() {};

void Racket::update(const int height) {};

bool Racket::collideWithBall(Ball& ball) { return true; };

void Racket::draw(sf::RenderWindow& window) {
  window.draw(rect);
};