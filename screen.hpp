
#ifndef DEF_SCREEN
#define DEF_SCREEN

#include "Arduino.h"
#include "LiquidCrystal.h"

class Screen
{
	public:
		Screen();
		~Screen();

		void print(const char* txt);
		void refresh();

	private:
		LiquidCrystal m_lcd;
};

#endif//DEF_SCREEN

