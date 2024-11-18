#include "Input.h"
#include <DxLib.h>

Input::Input() :
    m_input(GetJoypadInputState(DX_INPUT_KEY_PAD1)),
    m_beforeInput(0),
    m_inputAxis()
{

}

Input& Input::GetInstance()
{
    static Input instance;
    return instance;
}

void Input::Update()
{
    // 前のフレームのを記憶
    m_beforeInput = m_input;
    m_input = GetJoypadInputState(DX_INPUT_KEY_PAD1);
    // スティックの入力を取得
    int analogX, analogY;
    GetJoypadAnalogInput(&analogX, &analogY, DX_INPUT_PAD1);
    m_inputAxis.x = static_cast<float>(analogX);
    m_inputAxis.y = static_cast<float>(analogY);
}

bool Input::IsTrigger(int id)
{
    // こんなにカッコいらないだろ
    return ((m_input & id) && !(m_beforeInput & id));
}

bool Input::IsPressed(int id)
{
    return (m_input & id);
}

Vector2 Input::GetInputAxis()
{
    return m_inputAxis;
}
