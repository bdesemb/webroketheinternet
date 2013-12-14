#include "Pion.h"

using namespace model;

Pion::Pion(float nGrapheX, float nGrapheY, int nTableX, int nTableY) {
	this->grapheX = nGrapheX;
	this->grapheY = nGrapheY;
	this->tableX = nTableX;
	this->tableY = nTableY;
}

float Pion::getGrapheX() {
	return this->grapheX;
}
float Pion::getGrapheY() {
	return this->grapheY;
}
int Pion::getTableX() {
	return this->tableX;
}
int Pion::getTableY() {
	return this->tableY;
}

void Pion::deplacer(float nX, float nY) {
	this->grapheX = (grapheX + nX);
	this->grapheY = (grapheY + nY);
	this->tableX = (int)(tableX + nX * 2);
	this->tableY = (int)(tableY + nY * 2);
}