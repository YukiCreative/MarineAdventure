#include "ButtonSystem.h"
#include "Input.h"

ButtonSystem::ButtonSystem()
{
}

void ButtonSystem::Update()
{
	Input& input = Input::GetInstance();
	Vector2 inputAxis = input.GetInputAxis();
	// axis������ăt�H�[�J�X�̈ʒu�����炷

}
