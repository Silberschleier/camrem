//
// Created by Christopher Schmidt on 28.07.15.
//

#include "tests.h"


BOOST_AUTO_TEST_CASE( ConfigHandler_FaultyFiles ) {
    ConfigHandler *conf = ConfigHandler::getInstance();

    BOOST_REQUIRE(not conf->init("tests/test_fail.json"));
    BOOST_REQUIRE(not conf->init("tests/nonexistent.json"));
}

BOOST_AUTO_TEST_CASE( ConfigHandler_FileOperations ) {
    boost::filesystem::path example("tests/test.json");
    boost::filesystem::path file("tests/temp.json");
    boost::filesystem::copy_file(example, file);


    ConfigHandler *conf = ConfigHandler::getInstance();
    BOOST_REQUIRE(conf->init("tests/temp.json"));
    BOOST_CHECK_EQUAL(conf->config["key"], "value");

    boost::filesystem::remove(file);
}