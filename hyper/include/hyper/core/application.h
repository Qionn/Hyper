#ifndef __HYPER_APPLICATION_H__
#define __HYPER_APPLICATION_H__

namespace hyper
{
	class Application final
	{
	public:
		Application(const char* pName);

		void start();
		void stop();

		Application(const Application&)				= delete;
		Application(Application&&)					= delete;
		Application& operator=(const Application&)	= delete;
		Application& operator=(Application&&)		= delete;

		~Application() = default;

	private:
		bool m_IsRunning = false;
	};
}

#endif // !__HYPER_APPLICATION_H__
