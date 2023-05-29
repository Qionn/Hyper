#ifndef __HYPER_FWD_H__
#define __HYPER_FWD_H__

namespace hyper
{
	class AudioClip;

	class Application;
	class Renderer;
	class Time;
	class Window;

	class Dispatcher;
	class AEvent;
	class IObserver;
	class WindowCloseEvent;

	class IContext;
	class ITexture;

	class Body;
	class World;

	class Actor;
	class AComponent;
	class Scene;
	class SceneFactory;

	class BodyComponent;
	class SpriteComponent;
	class TransformComponent;

	class ILogService;
	class NullLogService;
	class ConsoleLogService;
	class ServiceHub;
	class ISoundService;
	class NullSoundService;
	class DefaultSoundService;
}

#endif // !__HYPER_FWD_H__
