
/*   Singletonパターン   */

#pragma once

class Singleton
{
protected:                                          //外部でコンストラクタと代入演算子を呼び出せないようにする→外部でインスタンスの生成をできないようにする
	Singleton(){};
	Singleton(const Singleton&){};
	Singleton& operator =(const Singleton&){};
};