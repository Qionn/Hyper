#include "layers/exercise_layer.h"

#include <hyper/core/application.h>

#include <memory>

#if _DEBUG
#	if __has_include(<vld.h>)
#		include <vld.h>
#	endif
#endif

using namespace hyper;
using namespace burger_time;

int main()
{
	auto pApp = std::make_unique<Application>("Burger Time");
	pApp->PushLayer<ExerciseLayer>();

	pApp->Start();
}
