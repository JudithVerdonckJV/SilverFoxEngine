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
        virtual ~TextureComponent();

        virtual void Render() const override;

        void SetTexture(const std::string& path);
        FVector2 GetDimensions() const;
        float GetWidth() const;
        float GetHeight() const;

    private:
        Texture2D* m_pTexture;
    };
}


