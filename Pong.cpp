#include "stdafx.h"
#include <iostream>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <utility>
#include <iomanip>
#include <limits>
#include <cmath>
#include <algorithm>
#include <list>
#include "Mechanics.h"

int main()
{
	std::srand(static_cast<unsigned>(std::time(nullptr)));
	Pong game;
	game.run();
}
