#include "Scene.h"

void Scene::ScreenFade::Update()
{
}

void Scene::ScreenFade::Draw() const
{
}

Scene::ScreenFade::ScreenFade(int frame, float fadePercent, unsigned int color) :
	m_color(color),
	m_lifeFrame(frame),
	m_percent(fadePercent)
{
}