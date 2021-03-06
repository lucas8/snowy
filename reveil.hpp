
/*
 * Copyright (C) 2013 Chabassier Luc
 * Copyright (C) 2013 Héloïse Badaroux
 * Copyright (C) 2013 Marie Qiu
 * Copyright (C) 2013 Marie Elisabelar
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef DEF_REVEIL
#define DEF_REVEIL

#include "pins.hpp"
#include "screen.hpp"
#include "sound.hpp"
#include "date.hpp"

void toggleLeds();

class Reveil
{
	public:
		void load(Screen* scr, Sound* snd);

		void update(); // Lance la sonnerie si l'heure est arrivée

	private:
		Screen* m_scr;
		Sound* m_snd; 
		Date* m_used;
		Date m_date;
		Date m_rev;

		bool m_edit;
		bool m_beep;

		bool m_upSt;
		bool m_downSt;

		void print();
		void buzz();
		void upButtonClic();
		void downButtonClic();
};

#endif//DEF_REVEIL

