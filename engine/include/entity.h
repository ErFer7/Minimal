#pragma once

#include <string>

#include "dynamic_array.h"

class Entity {
   public:
    Entity(std::string name = "", bool auto_managed = true);
    ~Entity();
    inline unsigned int get_id() { return this->_id; }
    inline bool is_active() const { return this->_active; }
    inline bool is_auto_managed() const { return this->_auto_managed; }
    inline std::string get_name() const { return this->_name; }
    inline void set_name(std::string name) { this->_name = name; }
    inline Entity *get_parent() const { return this->_parent; }
    inline unsigned int get_child_count() const { return this->_children->get_element_count(); }
    inline bool is_registered() const { return this->_registered; }
    inline bool has_unregistered_descendants() const { return this->_unregistered_descendants; }
    inline bool has_descendants_marked_for_deletion() const { return this->_descendants_marked_for_deletion; }
    inline bool should_delete() const { return this->_delete; }
    void set_registered(bool ready);
    void set_unregistered_descendants(bool unregistered_descendants);
    void set_descendants_marked_for_deletion(bool descendants_marked_for_deletion);
    void mark_for_deletion();
    void set_active(bool is_active);
    void set_auto_managed(bool auto_managed);
    void set_parent(Entity *parent);
    void add_child(Entity *entity);
    void register_all_descendants(DynamicArray<Entity *> *entities);
    bool has_child(Entity *entity);
    bool has_child(unsigned int entity_id);
    bool has_child(std::string entity_name);
    bool has_descendant(Entity *entity);
    bool has_descendant(unsigned int entity_id);
    bool has_descendant(std::string entity_name);
    Entity *get_child_at(unsigned int index);
    Entity *get_child(unsigned int entity_id);
    Entity *get_child(std::string entity_name);
    Entity *get_descendant(unsigned int entity_id);
    Entity *get_descendant(std::string entity_name);
    bool remove_child(Entity *entity);
    bool remove_child(unsigned int entity_id);
    bool remove_child(std::string entity_name);
    bool remove_descendant(Entity *entity);
    bool remove_descendant(unsigned int entity_id);
    bool remove_descendant(std::string entity_name);
    bool remove_reference_to_child(Entity *entity);
    Entity *remove_reference_to_child(unsigned int entity_id);
    Entity *remove_reference_to_child(std::string entity_name);
    bool remove_reference_to_descendant(Entity *entity);
    Entity *remove_reference_to_descendant(unsigned int entity_id);
    Entity *remove_reference_to_descendant(std::string entity_name);
    void remove_all_children();
    void remove_references_to_all_children();
    void remove();
    void remove_reference();

   private:
    static unsigned int _next_id;
    unsigned int _id;
    std::string _name;
    bool _active;
    bool _auto_managed;
    bool _registered;
    bool _delete;
    bool _unregistered_descendants;
    bool _descendants_marked_for_deletion;
    DynamicArray<Entity *> *_children;
    Entity *_parent;
};