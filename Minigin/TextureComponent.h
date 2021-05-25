#pragma once
#include "IComponent.h"
#include "utils.h"

namespace fox
{
    class GameObject;
    class Texture2D;

    class TextureComponent final : public IComponent
    {
    public:
        TextureComponent(GameObject* owner);
        TextureComponent(GameObject* owner, const std::string& path);
        virtual ~TextureComponent();

        virtual void Render() const override;
        virtual void Update(float deltaTime) override;

        void SetTexture(const std::string& path);
        
        void SetPivot(float x = 0.5f, float y = 0.5f);
        void SetPivot(FVector2 xy);
        
        FVector2 GetDimensions() const;
        float GetWidth() const;
        float GetHeight() const;

    private:
        Texture2D* m_pTexture;
       
        FVector2 m_Pivot;
        FVector2 m_RelativeLocation;
    };
}


