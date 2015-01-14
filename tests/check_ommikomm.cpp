/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#include "../src/config.h"
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>
#include "/home/michael/src/ommikomm/tests/check_persistence.cpp"

bool suite_OKConfigPersistentTest_init = false;


static OKConfigPersistentTest suite_OKConfigPersistentTest;

static CxxTest::List Tests_OKConfigPersistentTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_OKConfigPersistentTest( "tests/check_persistence.cpp", 4, "OKConfigPersistentTest", suite_OKConfigPersistentTest, Tests_OKConfigPersistentTest );

static class TestDescription_suite_OKConfigPersistentTest_testFileExists : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_OKConfigPersistentTest_testFileExists() : CxxTest::RealTestDescription( Tests_OKConfigPersistentTest, suiteDescription_OKConfigPersistentTest, 5, "testFileExists" ) {}
 void runTest() { suite_OKConfigPersistentTest.testFileExists(); }
} testDescription_suite_OKConfigPersistentTest_testFileExists;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
