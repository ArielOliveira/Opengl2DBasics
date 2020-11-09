#include "DiceFace.h"

DiceFace::DiceFace(int const& diceNumber, mat4 const& position, mat4 const& rotation, mat4 const& scale) :
	Object(position, rotation, scale) {
	this->diceNumber = diceNumber;
	square = new Square(position, rotation, scale);
	circles = new vector<Circle*>();
	FillDice();
}

DiceFace::DiceFace(DiceFace const& face) : Object(face) {
	diceNumber = face.diceNumber;
	square = new Square(position, rotation, scale);
	circles = new vector<Circle*>();
	FillDice();
}

DiceFace::~DiceFace() {
	delete square;
	for (auto& circle : *circles)
		delete circle;
	delete circles;
}

void DiceFace::GenBuffer() {

}

void DiceFace::FillDice() {
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

void DiceFace::Translate(glm::vec3 const& translation) {
	Object::Translate(translation);

	square->Translate(translation);
	for (auto& circle : *circles)
		(circle)->Translate(translation);
}

void DiceFace::Scale(glm::vec3 const& _scale) {
	Object::Scale(_scale);

	square->Scale(_scale);
	for (auto& circle : *circles)
		(circle)->Scale(_scale);
}

void DiceFace::Bind() {
	square->Bind();
}

void DiceFace::Draw(const unsigned int& uniform) {
	square->Draw(uniform);

	for (auto& circle : *circles) {
		(circle)->Bind();
		(circle)->Draw(uniform);
	}
}
