//
// Created by David on 5/22/2026.
//

#include "catch2/catch_test_macros.hpp"
#include <Repository.h>

TEST_CASE("Repository add and remove", "[Repository]") {
    Repository<std::string> strRepo;
    strRepo.add("string");
    strRepo.add("something");
    REQUIRE(strRepo.size() == 2);
    REQUIRE(strRepo.findByIndex(0) == "string");
    strRepo.remove("string");
    REQUIRE(strRepo.size() == 1);

    Repository<int> intRepo;
    intRepo.add(10);
    intRepo.add(20);
    REQUIRE(intRepo.size() == 2);
    intRepo.remove(10);
    REQUIRE(intRepo.size() == 1);
    REQUIRE(intRepo.findByIndex(0) == 20);
}