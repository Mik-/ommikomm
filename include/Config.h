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

#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

struct contrastItem {
    Fl_Color backColor;
    Fl_Color textColor;
};

const int maxContrasts = 5;

const contrastItem Contrasts[maxContrasts] = {
    {FL_WHITE, FL_BLACK},
    {FL_GRAY, FL_BLACK},
    {FL_BLACK, FL_GRAY},
    {FL_BLACK, FL_WHITE},
    {FL_BLUE, FL_YELLOW}
};

const int maxFonts = 6;

const Fl_Font Fonts[maxFonts] = {
    FL_HELVETICA,
    FL_HELVETICA_BOLD,
    FL_TIMES,
    FL_TIMES_BOLD,
    FL_COURIER,
    FL_COURIER_BOLD
};

const int maxLinecounts = 4;

const int Linecounts[maxLinecounts] = {
    1,
    2,
    3,
    4
};

#endif // CONFIG_H_INCLUDED
