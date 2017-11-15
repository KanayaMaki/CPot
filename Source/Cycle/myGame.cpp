//
//	content	:	ÉQÅ[ÉÄ
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Cycle/myGame.h"

namespace cpot {

cpot::GameBase* CreateGame() {
	return new myspc::MyGame;
}

}
