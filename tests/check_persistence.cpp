#include <cxxtest/TestSuite.h>
#include "../src/settings/Settings.h"
#include "mock_config.cpp"
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <cstdio>

#include "../src/settings/SettingsPersistence.h"
#include "compare_files.cpp"

#define TEMPCONFIGFILENAME "./tests/test_data/temp.xml"

class OKConfigPersistentTest : public CxxTest::TestSuite {
		SettingsPersistence *configPersister;
		ISettings *config;
	public:
		void setUp() {
			config = new mock_Settings();
			configPersister = new SettingsPersistence(config);
		}

		void tearDown() {
			delete configPersister;
			delete config;
		}

		void test_FileExists() {
			std::string filename("./configure.ac");

			TSM_ASSERT("file should exist", configPersister->fileExists(filename));

			filename.assign("./xconfigure.acx");

			TSM_ASSERT("file should not exist", not configPersister->fileExists(filename));
		}

		void test_getHomeDir() {
			const char *homeDir;

			// get the current home directory
			if ((homeDir = getenv("HOME")) == NULL) {
				homeDir = getpwuid(getuid())->pw_dir;
			}

			TSM_ASSERT_EQUALS("home directory should be returned", homeDir, configPersister->getHomeDir());
		}

		void test_read() {
			std::string filename("./tests/test_data/config1.xml");

			configPersister->read(filename);

			TSM_ASSERT_EQUALS("contrast should be 1", 1, config->getContrastIndex());
			TSM_ASSERT_EQUALS("font should be 2", 2, config->getFontIndex());
			TSM_ASSERT_EQUALS("line count should be 3", 3, config->getLinecountIndex());
		}

		void test_read2() {
			std::string filename("./tests/test_data/config2.xml");

			configPersister->read(filename);

			TSM_ASSERT_EQUALS("contrast should be 0", 0, config->getContrastIndex());
			TSM_ASSERT_EQUALS("font should be 0", 0, config->getFontIndex());
			TSM_ASSERT_EQUALS("line count should be 0", 0, config->getLinecountIndex());
		}

		void test_write() {
			std::string filename(TEMPCONFIGFILENAME);

			config->setContrastIndex(1);
			config->setFontIndex(2);
			config->setLinecountIntdex(3);

			configPersister->write(filename);

			TSM_ASSERT("first write", equalFiles(TEMPCONFIGFILENAME, "./tests/test_data/config1.xml"));

			config->setContrastIndex(2);
			config->setFontIndex(3);
			config->setLinecountIntdex(4);

			configPersister->write(filename);
			TSM_ASSERT("second write", equalFiles(TEMPCONFIGFILENAME, "./tests/test_data/config3.xml"));

			std::remove(TEMPCONFIGFILENAME);
		}
};
