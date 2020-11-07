#pragma once

#include <vector>
using std::vector;


#include "Object.h"
#include "Square.h"
#include "Circle.h"

using glm::mat4;

class DiceFace : public Object {
	private:
        const float dicePos[4] = {
            .0f,   .0f,
           -.35f,  .35,
        };

		Square *square;
		vector<Circle*>* circles;

        void FillDice();
    public:
        DiceFace(int const& diceNumber, glm::mat4 const& position, glm::mat4 const& rotation, glm::mat4 const& scale);
        DiceFace(DiceFace const& face);
        ~DiceFace();

        void Bind();
        void Draw(const unsigned int& uniform);

        void Translate(glm::vec3 const& translation);

        void Scale(glm::vec3 const& _scale);

        int diceNumber;
};

