#pragma once
#include <functional>
#include "IComponent.h"
#include "utils.h"

namespace fox
{
	class GameObject;

	class RectColliderComponent final : public IComponent
	{
	public:
		RectColliderComponent(GameObject* owner, FVector2 position, float width, float height);
		RectColliderComponent(GameObject* owner, FVector2 position, FVector2 widhtHeight);
		RectColliderComponent(GameObject* owner, float x, float y, float width, float height);
		RectColliderComponent(GameObject* owner, float width, float height);
		RectColliderComponent(GameObject* owner);
		~RectColliderComponent() = default;

		virtual void Render() const override;
		virtual void Update(float dt) override;
		virtual void FixedUpdate(float dt) override;

		void OnOverlap(GameObject* other);
		void SetOverlapCallback(std::function<void(GameObject*)> callback);

		FVector2 GetDimensions() const;
		float GetWidth() const;
		float GetHeight() const;
		FVector2 GetRelativePosition() const;
		float GetRelativeX() const;
		float GetRelativeY() const;
		FVector2 GetWorldLocation() const;

		void SetDimensions(FVector2 dimensions);
		void SetDimensions(float width, float height);
		void SetWidth(float width);
		void SetHeight(float height);
		void SetRelativePosition(FVector2 position);
		void SetRelativePosition(float x, float y);
		void SetRelativeX(float x);
		void SetRelativeY(float y);

		void DrawDebug(bool drawDebug);

	private:
		bool m_DrawDebug;


		FVector2 m_RelativeLocation;
		FVector2 m_WorldLocation;
		FVector2 m_Dimensions;

		std::function<void(GameObject*)> m_OverlapCallback;

		int m_Id;
	};
}

