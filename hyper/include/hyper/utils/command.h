#ifndef __HYPER_COMMAND_H__
#define __HYPER_COMMAND_H__

namespace hyper
{
	class ICommand
	{
	public:
		virtual void Execute() = 0;
		virtual ~ICommand() = default;
	};
}

#endif // !__HYPER_COMMAND_H__
