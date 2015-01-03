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

#include "OKConfigPersistent.h"
#include <libxml++/libxml++.h>
#include <iostream>
#include <string>
#include <cstdlib>

void OKConfigPersistent::Write(std::string filename)
{
    xmlpp::Document doc;

    xmlpp::Element *rootNode = doc.create_root_node("ommikomm");

    std::ostringstream contrast_value;
    contrast_value << config->getContrastIndex();
    xmlpp::Element *contrastNode = rootNode->add_child("contrast");
    contrastNode->add_child_text(contrast_value.str());

    std::ostringstream font_value;
    font_value << config->getFontIndex();
    xmlpp::Element *fontNode = rootNode->add_child("font");
    fontNode->add_child_text(font_value.str());

    std::ostringstream linecount_value;
    linecount_value << config->getFontIndex();
    xmlpp::Element *linecountNode = rootNode->add_child("linecount");
    linecountNode->add_child_text(linecount_value.str());

    doc.write_to_file(filename);
}

void OKConfigPersistent::Read(std::string filename)
{
    try
    {
        xmlpp::DomParser parser;
        parser.parse_file(filename);

        xmlpp::Document *doc;
        doc = parser.get_document();

        xmlpp::Node *rootNode;
        rootNode = doc->get_root_node();

        const xmlpp::TextNode *contrastNode = dynamic_cast<const xmlpp::TextNode*>(rootNode->get_children("contrast").front());
        if (contrastNode) {
            config->setContrastIndex(atoi(contrastNode->get_content().c_str()));
        }

    }
    catch (const std::exception &ex)
    {
    }
}

 OKConfigPersistent::OKConfigPersistent(OKConfig *config)
{
    this->config = config;
}


