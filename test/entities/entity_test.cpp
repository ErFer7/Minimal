#include "entities/entity.hpp"

#include <catch2/catch_test_macros.hpp>

#include "../../engine/include/components/transform2D_component.hpp"
#include "../../engine/include/minimal.hpp"
#include "components/component.hpp"

// TODO: Melhorar os nomes

TEST_CASE("Test entity", "[entity]") {
    EngineCore engine_core = EngineCore(1600, 800, "Test", 75, false, false, true);
    engine_core.create_main_behaviour_manager<MainBehaviourManager>();

    SECTION("Must create an entity without crashing") { REQUIRE_NOTHROW(engine_core.get_entity_container()->create_entity<Entity>()); }

    SECTION("get_parent() must return nullptr for the root entity") {
        Entity *entity = engine_core.get_entity_container()->create_entity<Entity>();

        REQUIRE(entity->get_parent()->get_parent() == nullptr);
    }

    SECTION("create_child() must create a child entity without crashing") {
        Entity *parent = engine_core.get_entity_container()->create_entity<Entity>();

        REQUIRE_NOTHROW(parent->create_child<Entity>());
    }

    SECTION("get_parent() must return the parent of an entity") {
        Entity *parent = engine_core.get_entity_container()->create_entity<Entity>();
        Entity *child = parent->create_child<Entity>();

        REQUIRE(child->get_parent() == parent);
    }

    SECTION("get_child() must return the correct child entity by their index") {
        Entity *parent = engine_core.get_entity_container()->create_entity<Entity>();
        Entity *child_0 = parent->create_child<Entity>();
        Entity *child_1 = parent->create_child<Entity>();
        Entity *child_2 = parent->create_child<Entity>();

        REQUIRE(parent->get_child(0) == child_0);
        REQUIRE(parent->get_child(1) == child_1);
        REQUIRE(parent->get_child(2) == child_2);
    }

    SECTION("get_child() must throw an exception for an out-of-bounds index") {
        Entity *parent = engine_core.get_entity_container()->create_entity<Entity>();
        parent->create_child<Entity>();

        REQUIRE_THROWS_AS(parent->get_child(1), std::out_of_range);
    }

    SECTION("get_child_index() must return the correct index of a child entity") {
        Entity *parent = engine_core.get_entity_container()->create_entity<Entity>();
        Entity *child_0 = parent->create_child<Entity>();
        Entity *child_1 = parent->create_child<Entity>();
        Entity *child_2 = parent->create_child<Entity>();

        REQUIRE(parent->get_child_index(child_0) == 0);
        REQUIRE(parent->get_child_index(child_1) == 1);
        REQUIRE(parent->get_child_index(child_2) == 2);
    }

    SECTION("get_child_index() must return -1 for a non-child entity") {
        Entity *parent = engine_core.get_entity_container()->create_entity<Entity>();
        Entity *child = parent->create_child<Entity>();
        Entity *not_child = engine_core.get_entity_container()->create_entity<Entity>();

        REQUIRE(parent->get_child_index(not_child) == -1);
    }

    SECTION("get_child_count() must return the correct number of children") {
        Entity *parent = engine_core.get_entity_container()->create_entity<Entity>();
        parent->create_child<Entity>();
        parent->create_child<Entity>();
        parent->create_child<Entity>();

        REQUIRE(parent->get_child_count() == 3);
    }

    SECTION("destroy_child() must destroy the correct child by index") {
        Entity *parent = engine_core.get_entity_container()->create_entity<Entity>();
        Entity *child_0 = parent->create_child<Entity>();
        Entity *child_1 = parent->create_child<Entity>();
        Entity *child_2 = parent->create_child<Entity>();

        parent->destroy_child(1);

        REQUIRE(parent->get_child_count() == 2);
        REQUIRE(parent->get_child(0) == child_0);
        REQUIRE(parent->get_child(1) == child_2);
    }

    SECTION("destroy_all_children() must destroy all children of an entity") {
        Entity *parent = engine_core.get_entity_container()->create_entity<Entity>();
        parent->create_child<Entity>();
        parent->create_child<Entity>();
        parent->create_child<Entity>();

        parent->destroy_all_children();

        REQUIRE(parent->get_child_count() == 0);
    }

    SECTION("destroy() must destroy an entity without crashing") {
        Entity *entity = engine_core.get_entity_container()->create_entity<Entity>();

        REQUIRE_NOTHROW(entity->destroy());
    }

    SECTION("create_component() must create a component without crashing") {
        Entity *entity = engine_core.get_entity_container()->create_entity<Entity>();

        REQUIRE_NOTHROW(entity->create_component<Component>());
    }

    SECTION("has_component() must return true for an existing component by type") {
        Entity *entity = engine_core.get_entity_container()->create_entity<Entity>();
        entity->create_component<Component>();

        REQUIRE(entity->has_component<Component>());
    }

    SECTION("has_component() must return false for a non-existing component by type") {
        Entity *entity = engine_core.get_entity_container()->create_entity<Entity>();
        Transform2DComponent *component = entity->create_component<Transform2DComponent>();

        REQUIRE(!entity->has_component<Component>());
    }

    SECTION("get_component() must return the correct component by index") {
        Entity *entity = engine_core.get_entity_container()->create_entity<Entity>();
        Component *component_0 = entity->create_component<Component>();
        Component *component_1 = entity->create_component<Component>();
        Component *component_2 = entity->create_component<Component>();

        REQUIRE(entity->get_component(0) == component_0);
        REQUIRE(entity->get_component(1) == component_1);
        REQUIRE(entity->get_component(2) == component_2);
    }

    SECTION("get_component() must throw an exception for an out-of-bounds index") {
        Entity *entity = engine_core.get_entity_container()->create_entity<Entity>();
        entity->create_component<Component>();

        REQUIRE_THROWS_AS(entity->get_component(1), std::out_of_range);
    }

    SECTION("get_component() must return nullptr for a non-existing component by type") {
        Entity *entity = engine_core.get_entity_container()->create_entity<Entity>();
        Component *component = entity->get_component<Component>();

        REQUIRE(component == nullptr);
    }

    SECTION("get_component() must return the correct component by type") {
        Entity *entity = engine_core.get_entity_container()->create_entity<Entity>();
        Component *component = entity->create_component<Component>();
        Transform2DComponent *component_1 = entity->create_component<Transform2DComponent>();

        REQUIRE(entity->get_component<Component>() == component);
        REQUIRE(entity->get_component<Transform2DComponent>() == component_1);
    }

    SECTION("get_component_index() must return the correct index of a component") {
        Entity *entity = engine_core.get_entity_container()->create_entity<Entity>();
        Component *component_0 = entity->create_component<Component>();
        Component *component_1 = entity->create_component<Component>();
        Component *component_2 = entity->create_component<Component>();

        REQUIRE(entity->get_component_index(component_0) == 0);
        REQUIRE(entity->get_component_index(component_1) == 1);
        REQUIRE(entity->get_component_index(component_2) == 2);
    }

    SECTION("get_component_index() must return -1 for a non-existing component") {
        Entity *entity = engine_core.get_entity_container()->create_entity<Entity>();
        Component dummy_component(&engine_core, entity);

        REQUIRE(entity->get_component_index(&dummy_component) == -1);
    }

    SECTION("get_component_index() must return the correct index for a component by type id") {
        Entity *entity = engine_core.get_entity_container()->create_entity<Entity>();
        Component *component_0 = entity->create_component<Component>();
        Transform2DComponent *component_1 = entity->create_component<Transform2DComponent>();

        REQUIRE(entity->get_component_index<Component>() == 0);
        REQUIRE(entity->get_component_index<Transform2DComponent>() == 1);
    }

    SECTION("get_component_index() must return -1 for a non-existing component by type id") {
        Entity *entity = engine_core.get_entity_container()->create_entity<Entity>();
        Transform2DComponent *component = entity->create_component<Transform2DComponent>();

        REQUIRE(entity->get_component_index<Component>() == -1);
    }

    SECTION("get_component_count() must return the correct number of components") {
        Entity *entity = engine_core.get_entity_container()->create_entity<Entity>();
        entity->create_component<Component>();
        entity->create_component<Component>();

        REQUIRE(entity->get_component_count() == 2);
    }

    SECTION("destroy_component() must destroy a component by index") {
        Entity *entity = engine_core.get_entity_container()->create_entity<Entity>();
        Component *component_0 = entity->create_component<Component>();
        Component *component_1 = entity->create_component<Component>();

        entity->destroy_component(0);

        REQUIRE(entity->get_component_count() == 1);
        REQUIRE(entity->get_component(0) == component_1);
    }

    SECTION("destroy_component() must destroy a component by type") {
        Entity *entity = engine_core.get_entity_container()->create_entity<Entity>();
        Component *component_0 = entity->create_component<Component>();
        Transform2DComponent *component_1 = entity->create_component<Transform2DComponent>();

        entity->destroy_component<Component>();

        REQUIRE(entity->get_component_count() == 1);
        REQUIRE(entity->get_component(0) == component_1);
    }

    SECTION("destroy_all_components() must destroy all components of an entity") {
        Entity *entity = engine_core.get_entity_container()->create_entity<Entity>();
        entity->create_component<Component>();
        entity->create_component<Component>();

        entity->destroy_all_components();

        REQUIRE(entity->get_component_count() == 0);
    }

    // TODO: Colocar estes testes no padrão AAA

    SECTION("Nested children hierarchy") {
        Entity *root = engine_core.get_entity_container()->create_entity<Entity>();
        Entity *child_0 = root->create_child<Entity>();
        Entity *grandchild_0 = child_0->create_child<Entity>();
        Entity *grandchild_1 = child_0->create_child<Entity>();
        Entity *child_1 = root->create_child<Entity>();

        REQUIRE(root->get_child_count() == 2);
        REQUIRE(child_0->get_child_count() == 2);
        REQUIRE(child_1->get_child_count() == 0);

        REQUIRE(grandchild_0->get_parent() == child_0);
        REQUIRE(grandchild_1->get_parent() == child_0);
        REQUIRE(child_0->get_parent() == root);
        REQUIRE(child_1->get_parent() == root);

        root->destroy_child(0);
        REQUIRE(root->get_child_count() == 1);
        REQUIRE(root->get_child(0) == child_1);
    }

    SECTION("Entity events") {
        Entity *parent = engine_core.get_entity_container()->create_entity<Entity>();

        bool child_created = false;
        bool child_destroyed = false;
        bool component_created = false;
        bool component_destroyed = false;
        bool entity_destroyed = false;

        Event<Entity *>::Listener child_create_listener([&](Entity *child) { child_created = true; });

        Event<Entity *>::Listener child_destroy_listener([&](Entity *child) { child_destroyed = true; });

        Event<Entity *, Component *>::Listener component_create_listener(
            [&](Entity *entity, Component *component) { component_created = true; });

        Event<Entity *, Component *>::Listener component_destroy_listener(
            [&](Entity *entity, Component *component) { component_destroyed = true; });

        Event<Entity *>::Listener entity_destroy_listener([&](Entity *entity) { entity_destroyed = true; });

        child_create_listener.subscribe(&parent->get_on_child_create_event());
        child_destroy_listener.subscribe(&parent->get_on_child_destroy_event());
        component_create_listener.subscribe(&parent->get_on_component_create_event());
        component_destroy_listener.subscribe(&parent->get_on_component_destroy_event());

        Entity *child = parent->create_child<Entity>();
        REQUIRE(child_created == true);

        entity_destroy_listener.subscribe(&child->get_on_destroy_event());

        Component *component = parent->create_component<Component>();
        REQUIRE(component_created == true);

        parent->destroy_component<Component>();
        REQUIRE(component_destroyed == true);

        parent->destroy_child(0);
        REQUIRE(child_destroyed == true);
        REQUIRE(entity_destroyed == true);
    }
}
