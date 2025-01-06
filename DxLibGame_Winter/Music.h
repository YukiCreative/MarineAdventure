#pragma once
#include <string>

class Music
{
private:
	Music();
	Music(const Music&) = delete;
	void operator=(const Music&) = delete;
public:
	static M GetInstance();
	static void PlayBGM(const std::string& path);
	static void 
};