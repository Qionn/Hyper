#ifndef __HYPER_FWD_H__
#define __HYPER_FWD_H__

namespace hyper
{
	class AudioClip;

	class Application;
	class Renderer;
	class Window;

	class Dispatcher;
	class AEvent;
	class IObserver;
	class WindowCloseEvent;
	class SceneStopRequestEvent;
	class SceneLoadRequestEvent;

	class IContext;
	class ITexture;

	class Input;
	class Keyboard;

	class Actor;
	class AComponent;
	class Scene;

	class SpriteComponent;
	class TextComponent;
	class TransformComponent;

	class Clock;
	class ICommand;
	class ILogService;
	class NullLogService;
	class ConsoleLogService;
	class ServiceHub;
	class ISoundService;
	class NullSoundService;
	class DefaultSoundService;
}

#endif // !__HYPER_FWD_H__
