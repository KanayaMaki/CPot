//
//	content	:	Audioのファイル名の環境による違いを吸収する
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