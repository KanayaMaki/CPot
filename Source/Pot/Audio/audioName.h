//
//	content	:	Audio‚Ìƒtƒ@ƒCƒ‹–¼‚ÌŠÂ‹«‚É‚æ‚éˆá‚¢‚ð‹zŽû‚·‚é
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Usefull/singleton.h"
#include "./Pot/List/resourceName.h"

namespace cpot {

class AudioName : public Singleton<AudioName>, public ResourceName {
	friend class Singleton<AudioName>;
};

}