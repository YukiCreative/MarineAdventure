#pragma once

// ゲームオブジェクトの中でさらに細分化する必要が出たので
enum class ObjectAttribute
{
	kEnemy,
	// 実はEnemyかどうかが分かればよかったんだよね
	kOther
};