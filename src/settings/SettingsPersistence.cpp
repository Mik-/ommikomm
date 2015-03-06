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

#include "SettingsPersistence.h"

#include <glibmm/ustring.h>
#include <libxml++/document.h>
#include <libxml++/nodes/element.h>
#include <libxml++/nodes/textnode.h>
#include <libxml++/parsers/domparser.h>
#include <pwd.h>
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>

const char* SettingsPersistence::ROOTNODENAME = "ommikomm";
const char* SettingsPersistence::CONTRASTNODENAME = "contrast";
const char* SettingsPersistence::FONTNODENAME = "font";
const char* SettingsPersistence::LINECOUNTNODENAME = "linecount";
const char* SettingsPersistence::PINNODENAME = "pin";

void SettingsPersistence::write(std::string filename) {

	xmlpp::Document doc;

	xmlpp::Element *rootNode = doc.create_root_node(ROOTNODENAME);

	std::ostringstream contrast_value;
	contrast_value << config->getContrastIndex();
	xmlpp::Element *contrastNode = rootNode->add_child(CONTRASTNODENAME);
	contrastNode->add_child_text(contrast_value.str());

	std::ostringstream font_value;
	font_value << config->getFontIndex();
	xmlpp::Element *fontNode = rootNode->add_child(FONTNODENAME);
	fontNode->add_child_text(font_value.str());

	std::ostringstream linecount_value;
	linecount_value << config->getLinecountIndex();
	xmlpp::Element *linecountNode = rootNode->add_child(LINECOUNTNODENAME);
	linecountNode->add_child_text(linecount_value.str());

	xmlpp::Element *pinNode = rootNode->add_child(PINNODENAME);
	pinNode->add_child_text(config->getPIN());

	doc.write_to_file(filename);
}

int getIntValue(xmlpp::Node *rootNode, const Glib::ustring &nodeName) {
	xmlpp::Element *elementNode =
			dynamic_cast<xmlpp::Element*>(rootNode->get_first_child(nodeName));

	if (elementNode && elementNode->has_child_text()) {
		std::stringstream s;
		int result;

		s << elementNode->get_child_text()->get_content();
		s >> result;
		return result;
	} else {
		std::cerr << "Configuration node '" << nodeName << "' not found!";
		return 0;
	}
}

std::string getStrValue(xmlpp::Node *rootNode, const Glib::ustring &nodeName) {
	xmlpp::Element *elementNode =
			dynamic_cast<xmlpp::Element*>(rootNode->get_first_child(nodeName));

	if (elementNode && elementNode->has_child_text()) {
		std::stringstream s;
		std::string result;

		s << elementNode->get_child_text()->get_content();
		s >> result;
		return result;
	} else {
		std::cerr << "Configuration node '" << nodeName << "' not found!";
		return "";
	}
}

void SettingsPersistence::read(std::string filename) {
	if (fileExists(filename)) {
		xmlpp::DomParser parser;
		parser.parse_file(filename);

		xmlpp::Document *doc;
		doc = parser.get_document();
		if (doc) {
			xmlpp::Node *rootNode;
			rootNode = doc->get_root_node();

			if (rootNode && rootNode->get_name().compare(ROOTNODENAME) == 0) {
				config->setContrastIndex(
						getIntValue(rootNode, CONTRASTNODENAME));
				config->setFontIndex(getIntValue(rootNode, FONTNODENAME));
				config->setLinecountIntdex(
						getIntValue(rootNode, LINECOUNTNODENAME));
				config->setPIN(getStrValue(rootNode, PINNODENAME));
			} else {
				std::cerr << "Root node '" << ROOTNODENAME << "' not found!\n";
			}
		} else {
			std::cerr << "Not a valid configuration file!\n";
		}
	} else {
		std::cerr << "Configuration file '" << filename << "' not found!\n";
	}
}

SettingsPersistence::SettingsPersistence(ISettings *config) {
	this->config = config;
}

bool SettingsPersistence::fileExists(std::string filename) {
	std::ifstream configFile(filename.c_str());
	return configFile;
}

const char* SettingsPersistence::getHomeDir() {
	const char *homeDir;

	if ((homeDir = getenv("HOME")) == NULL) {
		homeDir = getpwuid(getuid())->pw_dir;
	}

	return homeDir;
}
