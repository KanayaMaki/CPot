//
//	content	:	�R���|�[�l���g
//	author	:	SaitoYoshiki
//

#include "././Pot/Game/renderer.h"

namespace cpot {


Renderer::Renderer() {
	RendererManager::S().Regist(this);
}

Renderer::~Renderer() {
	RendererManager::S().Remove(this);
}


}