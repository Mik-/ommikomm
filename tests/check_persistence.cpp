#include <cxxtest/TestSuite.h>
#include "../src/config/OKConfigPersistent.h"
#include "../src/config/IOKConfig.h"
#include "mock_config.cpp"
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

class OKConfigPersistentTest : public CxxTest::TestSuite {
		OKConfigPersistent *configPersister;
		IOKConfig *config;
	public:
		void setUp() {
			config = new mock_OKConfig();
			configPersister = new OKConfigPersistent(config);
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
};
