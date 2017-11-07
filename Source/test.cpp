#include "./Atom/atom.h"

#include "./Usefull/buffer.h"
#include "./Usefull/singleton.h"

using namespace cpot;

class A : public Singleton<A> {
	friend Singleton<A>;

public:
	u32 GetNum() {
		return 3;
	}
};


void TestTest() {

	A::S().GetNum();

	Buffer b;
}