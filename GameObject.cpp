#include "GameObject.h"
#include <iostream>

std::vector< GameObject* > GameObject::s_vUpdateList;
std::vector< GameObject* > GameObject::s_vDrawList;

GameObject::GameObject(Point2f pos)
{
	m_pos = pos;

	s_vUpdateList.push_back(this);
	s_vDrawList.push_back(this);
}

GameObject::~GameObject()
{
	s_vDrawList.erase(std::find(s_vDrawList.begin(), s_vDrawList.end(), this));
	s_vUpdateList.erase(std::find(s_vUpdateList.begin(), s_vUpdateList.end(), this));
}

void GameObject::UpdateAll(GameState& state)
{
	std::sort(s_vUpdateList.begin(), s_vUpdateList.end(), GameObject::UpdateOrder);

	for (size_t n = 0; n < s_vUpdateList.size(); n++)
	{
		s_vUpdateList[n]->Update(state);

		if (!s_vUpdateList[n]->m_active)
			delete s_vUpdateList[n--];
	}
}

void GameObject::DrawAll(GameState& state)
{
	std::sort(s_vDrawList.begin(), s_vDrawList.end(), GameObject::DrawOrder);

	for (size_t n = 0; n < s_vDrawList.size(); n++)
		s_vDrawList[n]->Draw(state);
}

int GameObject::GetObjectCount(GameObject::Type type)
{
	int count = 0;

	for (GameObject* p : s_vUpdateList)
	{
		if (p->m_type == type || type == OBJ_ALL)
			count++;
	}

	return count;
}

int GameObject::GetObjectList(GameObject::Type type, std::vector< GameObject* >& vList)
{
	vList.clear();

	for (GameObject* p : s_vUpdateList)
	{
		if (p->m_type == type || type == OBJ_ALL)
			vList.push_back(p);
	}

	return vList.size();
}

void GameObject::DestroyAll()
{
	for (size_t n = 0; n < s_vDrawList.size(); n++)
		delete s_vUpdateList[n--];
}

int GameObject::RandomRoll(int sides)
{
	return (rand() % sides) + 1;
}