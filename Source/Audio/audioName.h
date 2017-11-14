//
//	content	:	Audio‚Ìƒtƒ@ƒCƒ‹–¼‚ÌŠÂ‹«‚É‚æ‚éˆá‚¢‚ð‹zŽû‚·‚é
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Atom/atom.h"
#include "./Usefull/singleton.h"
#include "./List/resourceName.h"

namespace cpot {

class AudioName : public Singleton<AudioName>, public ResourceName {
	friend class Singleton<AudioName>;
};

}