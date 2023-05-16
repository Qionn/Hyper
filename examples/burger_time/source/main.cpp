#include <hyper/core/application.h>

#include <memory>

int main()
{
	auto pApp = std::make_unique<hyper::Application>("Burger Time");
	pApp->Start();
}
