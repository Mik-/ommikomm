/*
 (C) 2014 by Michael Neuendorf <michael@neuendorf-online.de>

 This file is part of OmmiKomm.

 OmmiKomm is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 OmmiKomm is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with OmmiKomm.  If not, see <http://www.gnu.org/licenses/>.

 Diese Datei ist Teil von OmmiKomm.

 OmmiKomm ist Freie Software: Sie können es unter den Bedingungen
 der GNU General Public License, wie von der Free Software Foundation,
 Version 3 der Lizenz oder (nach Ihrer Wahl) jeder späteren
 veröffentlichten Version, weiterverbreiten und/oder modifizieren.

 OmmiKomm wird in der Hoffnung, dass es nützlich sein wird, aber
 OHNE JEDE GEWÄHELEISTUNG, bereitgestellt; sogar ohne die implizite
 Gewährleistung der MARKTFÄHIGKEIT oder EIGNUNG FÜR EINEN BESTIMMTEN ZWECK.
 Siehe die GNU General Public License für weitere Details.

 Sie sollten eine Kopie der GNU General Public License zusammen mit OmmiKomm
 erhalten haben. Wenn nicht, siehe <http://www.gnu.org/licenses/>.
 */

#include "Settings.h"

Settings::Settings(ISettingsChange *changeCallback) {
	this->changeCallback = changeCallback;

	contrast = 0;
	font = 0;
	linecount = 0;
}

Settings::~Settings() {
	//dtor
}

void Settings::toggleContrast() {
	if (++contrast >= maxContrasts) {
		contrast = 0;
	}

	changeCallback->configChange();
}

int Settings::getContrastIndex() {
	return (contrast);
}

int Settings::getFontIndex() {
	return (font);
}

int Settings::getBackColor() {
	return (Contrasts[contrast].backColor);
}

int Settings::getTextColor() {
	return (Contrasts[contrast].textColor);
}

void Settings::toggleFont() {
	if (++font >= maxFonts) {
		font = 0;
	}

	changeCallback->configChange();
}

int Settings::getFont() {
	return (Fonts[font]);
}

void Settings::toggleLinecount() {
	if (++linecount >= maxLinecounts) {
		linecount = 0;
	}

	changeCallback->configChange();
}

int Settings::getLinecountIndex() {
	return (linecount);
}

int Settings::getLinecount() {
	return (Linecounts[linecount]);
}

void Settings::setFontIndex(int font) {
	this->font = font;
}

void Settings::setContrastIndex(int contrast) {
	this->contrast = contrast;
}

void Settings::setLinecountIntdex(int linecount) {
	this->linecount = linecount;
}

std::string Settings::getPIN() {
	return this->pin;
}

void Settings::setPIN(std::string pin) {
	this->pin = pin;
}
