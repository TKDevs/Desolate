#ifndef RTSCONTROLLER_H
#define RTSCONTROLLER_H

#include <vector>

#include "Pawn.h"

class RTSController {
public:
	RTSController() {

	}

	void update();

	void render();
private:
	std::vector<Pawn> pawns_;
};

#endif