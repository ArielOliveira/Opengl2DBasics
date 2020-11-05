#include "Dice.h"

Dice::Dice(int const& diceNumber, mat4 const& position, mat4 const& rotation, mat4 const& scale) :
	Object(position, rotation, scale) {
	this->diceNumber = diceNumber;
	square = new Square(position, rotation, scale);
	circles = new vector<Circle*>();
	FillDice();
}

Dice::Dice(Dice const& dice) : Object(dice) {
	diceNumber = dice.diceNumber;
	square = new Square(position, rotation, scale);
	circles = new vector<Circle*>();
	for (vector<Circle*>::iterator it = circles->begin(); it != dice.circles->end(); it++)
		circles->push_back(new Circle(**it));
}

void Dice::FillDice() {
	if (diceNumber == 1 || diceNumber == 3 || diceNumber == 5)
		circles->push_back(new Circle(0.05f, position, rotation, scale));
	if (diceNumber >= 2) {
		circles->push_back(new Circle(0.05f, glm::translate(transform, glm::vec3(dicePos[2], dicePos[3], .0f)), rotation, scale));
		circles->push_back(new Circle(0.05f, glm::translate(transform, glm::vec3(dicePos[3], dicePos[2], .0f)), rotation, scale));
	}
	if (diceNumber >= 4) {
		circles->push_back(new Circle(0.05f, glm::translate(transform, glm::vec3(dicePos[2], dicePos[2], .0f)), rotation, scale));
		circles->push_back(new Circle(0.05f, glm::translate(transform, glm::vec3(dicePos[3], dicePos[3], .0f)), rotation, scale));
	}

	if (diceNumber == 6) {
		circles->push_back(new Circle(0.05f, glm::translate(transform, glm::vec3(dicePos[2], dicePos[0], .0f)), rotation, scale));
		circles->push_back(new Circle(0.05f, glm::translate(transform, glm::vec3(dicePos[3], dicePos[0], .0f)), rotation, scale));
	}
}

void Dice::Translate(glm::vec3 const& translation) {
	Object::Translate(translation);

	square->Translate(translation);
	for (vector<Circle*>::iterator it = circles->begin(); it != circles->end(); it++)
		(*it)->Translate(translation);
}

void Dice::Scale(glm::vec3 const& _scale) {
	Object::Scale(_scale);

	square->Scale(_scale);
	for (vector<Circle*>::iterator it = circles->begin(); it != circles->end(); it++)
		(*it)->Scale(_scale);
}

void Dice::Bind() {
	Object::Bind();
	square->Bind();
}

void Dice::Draw(const unsigned int& uniform) {
	square->Draw(uniform);

	for (vector<Circle*>::iterator it = circles->begin(); it != circles->end(); it++) {
		(*it)->Bind();
		(*it)->Draw(uniform);
	}
}
