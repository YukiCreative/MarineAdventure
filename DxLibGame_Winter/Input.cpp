#include "Input.h"
#include <DxLib.h>

Input::Input() :
    m_input(GetJoypadInputState(DX_INPUT_KEY_PAD1)),
    m_beforeInput(0)
{

}

Input& Input::GetInstance()
{
    static Input instance;
    return instance;
}

void Input::Update()
{
    // �O�̃t���[���̂��L��
    m_beforeInput = m_input;
    m_input = GetJoypadInputState(DX_INPUT_KEY_PAD1);
}

bool Input::IsTrigger(int id)
{
    // ����ȂɃJ�b�R����Ȃ�����
    return ((m_input & id) && !(m_beforeInput & id));
}

bool Input::IsPressed(int id)
{
    return (m_input & id);
}
