/*
 * mock_config.cpp
 *
 *  Created on: 01.02.2015
 *      Author: michael
 */

#include "../src/settings/ISettings.h"

class mock_Settings : public ISettings {
    private:
        int contrast;
        int font;
        int linecount;
    public:
		mock_Settings() {
			contrast = 0;
			font = 0;
			linecount = 0;
		};
        virtual ~mock_Settings() {};

        virtual void toggleContrast() { this->contrast++; };
        virtual int getContrastIndex() { return this->contrast; };
        virtual void setContrastIndex(int contrast) { this->contrast = contrast; };
        virtual void toggleFont() { this->font++; };
        virtual int getFontIndex() { return this->font; };
        virtual void setFontIndex(int font) { this->font = font; };
        virtual void toggleLinecount() { this->linecount++; };
        virtual int getLinecountIndex() { return this->linecount; };
        virtual void setLinecountIntdex(int linecount) { this->linecount = linecount; };
    };


