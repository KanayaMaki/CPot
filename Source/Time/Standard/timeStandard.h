//
//	content	:	Standard�ł̎��ԂɊւ���N���X
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Time/time.h"


namespace cpot {

namespace standard {


//UnixTime���擾����f�o�C�X
class UnixTimeDevice {
	
public:
	//UnixTime���擾
	static UnixTimeType Get();

};


//DateTime���擾����f�o�C�X
class DateTimeDevice {

public:
	//UnixTime�����݂̓����ɕϊ�����
	static DateTimeData ToDateTime(UnixTimeType aUnixTime);

};


}

}
