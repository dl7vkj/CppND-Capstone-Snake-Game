#include "star_component.h"

#include "game.h"

StarComponent::StarComponent(GameObject *owner)
: Component(owner),
  sdl_renderer(owner->GetGame()->GetRenderer()->GetSDLRendererHandle())
{
    owner->GetGame()->GetRenderer()->RegisterTextureComponent(this);
}

StarComponent::~StarComponent() {
    owner->GetGame()->GetRenderer()->UnregisterTextureComponent(this);
}
