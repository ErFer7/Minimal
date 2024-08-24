#include <catch2/catch_test_macros.hpp>

#include "../engine/include/minimal.hpp"

TEST_CASE("Test engine core", "[engine_core]") {
    EngineCore engine_core = EngineCore(1600, 800, "Test", 75, false, false, true);

    REQUIRE(engine_core.get_behaviour_manager() != nullptr);
    REQUIRE(engine_core.get_entity_container() != nullptr);
    REQUIRE(engine_core.get_graphics_manager() != nullptr);
    REQUIRE(engine_core.get_main_behaviour_manager() == nullptr);

    SECTION("Creating a custom behaviour manager doesn't crash") {
        engine_core.create_main_behaviour_manager<MainBehaviourManager>();

        REQUIRE(engine_core.get_main_behaviour_manager() != nullptr);
    }

    // TODO: Find a way to do service testing with the current setup
}