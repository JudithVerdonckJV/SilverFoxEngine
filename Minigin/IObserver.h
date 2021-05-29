#pragma once
namespace fox
{
	class GameObject;

	class IObserver
	{
	public:
		IObserver() = default;
		virtual ~IObserver() = default;

		virtual void OnNotify(GameObject* pSubject, const std::string& event) = 0;
	};
}