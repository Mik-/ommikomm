/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include "../src/config.h"
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>
#include <cxxtest/ErrorPrinter.h>

int main( int argc, char *argv[] ) {
 int status;
    CxxTest::ErrorPrinter tmp;
    CxxTest::RealWorldDescription::_worldName = "cxxtest";
    status = CxxTest::Main< CxxTest::ErrorPrinter >( tmp, argc, argv );
    return status;
}
bool suite_OKConfigPersistentTest_init = false;
#include "/home/michael/src/ommikomm/tests/check_persistence.cpp"

static OKConfigPersistentTest suite_OKConfigPersistentTest;

static CxxTest::List Tests_OKConfigPersistentTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_OKConfigPersistentTest( "tests/check_persistence.cpp", 11, "OKConfigPersistentTest", suite_OKConfigPersistentTest, Tests_OKConfigPersistentTest );

static class TestDescription_suite_OKConfigPersistentTest_test_FileExists : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_OKConfigPersistentTest_test_FileExists() : CxxTest::RealTestDescription( Tests_OKConfigPersistentTest, suiteDescription_OKConfigPersistentTest, 25, "test_FileExists" ) {}
 void runTest() { suite_OKConfigPersistentTest.test_FileExists(); }
} testDescription_suite_OKConfigPersistentTest_test_FileExists;

static class TestDescription_suite_OKConfigPersistentTest_test_getHomeDir : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_OKConfigPersistentTest_test_getHomeDir() : CxxTest::RealTestDescription( Tests_OKConfigPersistentTest, suiteDescription_OKConfigPersistentTest, 34, "test_getHomeDir" ) {}
 void runTest() { suite_OKConfigPersistentTest.test_getHomeDir(); }
} testDescription_suite_OKConfigPersistentTest_test_getHomeDir;

static class TestDescription_suite_OKConfigPersistentTest_test_read : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_OKConfigPersistentTest_test_read() : CxxTest::RealTestDescription( Tests_OKConfigPersistentTest, suiteDescription_OKConfigPersistentTest, 45, "test_read" ) {}
 void runTest() { suite_OKConfigPersistentTest.test_read(); }
} testDescription_suite_OKConfigPersistentTest_test_read;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
