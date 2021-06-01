#pragma once
namespace fox
{
	class GameObject;

	class IObserver
	{
	public:
		IObserver();
		virtual ~IObserver() = default;

		virtual void OnNotify(GameObject* pSubject, int event) = 0;
	};
}