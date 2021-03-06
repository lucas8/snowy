
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

#include "reveil.hpp"

void Reveil::load(Screen* scr, Sound* snd)
{
	m_scr = scr;
	m_snd = snd;
	m_date.load();
	m_rev.load();
	m_rev.addM();
	m_used = &m_date;
	m_edit = false;
	m_beep = false;

	pinMode(pinUp, INPUT);
	m_upSt = digitalRead(pinUp);
	pinMode(pinDown, INPUT);
	m_downSt = digitalRead(pinDown);

	pinMode(pinREye, OUTPUT);
	pinMode(pinLEye, OUTPUT);
	for(int i = 0; i < 3; ++i)
		pinMode(pinLeds[i], OUTPUT);

	pinMode(13, OUTPUT);
	digitalWrite(13, HIGH);
}

void Reveil::update()
{
	m_edit = (digitalRead(pinEdit) == HIGH);
	// m_edit = false;
	m_beep = (digitalRead(pinBeep) == HIGH);
	// m_beep = true;

	if( m_beep && m_edit )
		m_used = &m_rev;
	else
		m_used = &m_date;

	bool upSt = digitalRead(pinUp);
	if( upSt == HIGH && m_upSt == LOW )
		upButtonClic();
	m_upSt = upSt;

	bool downSt = digitalRead(pinDown);
	if( downSt == HIGH && m_downSt == LOW )
		downButtonClic();
	m_downSt = downSt;

	m_date.update();
	print();

	if( m_beep
			&& m_rev == m_date )
		buzz();
}

void Reveil::upButtonClic()
{
	if( m_edit )
		m_used->addM();
}

void Reveil::downButtonClic()
{
	if( m_edit )
		m_used->subM();
}

void Reveil::print()
{
	/* if( m_edit )
		m_scr->printE();
	if( m_beep )
		m_scr->printB(0, 1);

	if( m_used->getH() < 10 )
	{
		m_scr->print("0", 4);
		m_scr->print(m_used->getH(), 5);
	}
	else
		m_scr->print(m_used->getH(), 4);
	m_scr->print(":", 6);

	if( m_used->getM() < 10 )
	{
		m_scr->print("0", 7);
		m_scr->print(m_used->getM(), 8);
	}
	else
		m_scr->print(m_used->getM(), 7);
	m_scr->print(":", 9);

	if( m_used->getS() < 10 )
	{
		m_scr->print("0", 10);
		m_scr->print(m_used->getS(), 11);
	}
	else
		m_scr->print(m_used->getS(), 10);
		*/
	Serial.print(m_used->getH());
	Serial.print(":");
	Serial.print(m_used->getM());
	Serial.print(":");
	Serial.print(m_used->getS());
	Serial.print(" ");
	if( m_edit )
		Serial.print("(E) ");
	if( m_beep )
		Serial.print("(B)");
	Serial.println("");
}

void Reveil::buzz()
{
	m_snd->setCb(toggleLeds);
	m_snd->play();
	while( digitalRead(pinStop) != HIGH )
		m_snd->update();

	m_snd->stop();
	m_snd->setCb(NULL);

	for(int i = 0; i < 3; ++i)
		analogWrite(pinLeds[i], 0);
	analogWrite(pinREye, 0);
	analogWrite(pinLEye, 0);
}

void toggleLeds()
{
	digitalWrite(pinREye, HIGH);
	digitalWrite(pinLEye, HIGH);

	static int i (0);
	if (i == 0)
	{
		digitalWrite (pinLeds[0], HIGH);
		digitalWrite (pinLeds[1], LOW);
		digitalWrite (pinLeds[2], LOW);
		++i;
	}

	if (i == 1)
	{
		digitalWrite (pinLeds[0], HIGH);
		digitalWrite (pinLeds[1], HIGH);
		digitalWrite (pinLeds[2], LOW);
		++i;
	}

	if (i == 2)
	{
		digitalWrite (pinLeds[0], HIGH);
		digitalWrite (pinLeds[1], HIGH);
		digitalWrite (pinLeds[2], HIGH);
		++i;
	}

	if (i == 3)
	{
		digitalWrite (pinLeds[0], LOW);
		digitalWrite (pinLeds[1], HIGH);
		digitalWrite (pinLeds[2], HIGH);
		++i;
	}

	if (i == 4)
	{
		digitalWrite (pinLeds[0], LOW);
		digitalWrite (pinLeds[1], LOW);
		digitalWrite (pinLeds[2], HIGH);
		i = 0;
	}
}

