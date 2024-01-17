#pragma once

#include <algorithm>
#include <iostream>

template <typename T>
class DynamicArray {
   public:
    DynamicArray(unsigned int initial_size = 1, unsigned int section_size = 1, T empty_element = nullptr) {
        this->_size = initial_size;
        this->_empty_element = empty_element;
        this->_array = new T[this->_size];
        this->_next_index = 0;
        this->_section_size = section_size;
        this->_element_count = 0;

        this->fill(this->_empty_element);
    }

    ~DynamicArray() {
        if (this->_array != nullptr) {
            delete[] this->_array;
            this->_array = nullptr;
        }
    }

    inline T get_empty_element() { return this->_empty_element; }

    void fill(T element) {
        for (unsigned int i = 0; i < this->_size; i++) {
            this->_array[i] = element;
        }
    }

    void clear() {
        this->fill(this->_empty_element);
        this->_next_index = 0;
        this->_element_count = 0;
        this->optimize();
    }

    bool contains(const T &element) { return this->nullable_index_of(element) != -1; }

    int nullable_index_of(const T &element) {
        for (unsigned int i = 0; i < this->_size; i++) {
            if (this->_array[i] == element) {
                return i;
            }
        }

        return -1;
    }

    int index_of(const T &element) {
        unsigned int counted_index = 0;

        for (unsigned int i = 0; i < this->_size; i++) {
            if (this->_array[i] != this->_empty_element) {
                if (this->_array[i] == element) {
                    return counted_index;
                }

                counted_index++;
            }
        }

        return -1;
    }

    T &nullable_at(unsigned int index) {
        if (index >= this->_size) {
            return this->_empty_element;
        }

        return this->_array[index];
    }

    T &at(unsigned int index) {
        if (index >= this->_element_count) {
            return this->_empty_element;
        }

        unsigned int counted_index = 0;

        for (unsigned int i = 0; i < this->_size; i++) {
            if (this->_array[i] != this->_empty_element) {
                if (counted_index == index) {
                    return this->_array[i];
                }

                counted_index++;
            }
        }

        return this->_empty_element;
    }

    void add(const T &element) {
        if (element == this->_empty_element) {
            return;
        }

        unsigned int previous_next_index = this->_next_index;

        while (true) {
            if (this->_next_index < this->_size) {
                if (this->_array[this->_next_index] == this->_empty_element) {
                    this->_array[this->_next_index] = element;
                    this->_element_count++;
                    this->_next_index++;
                    return;
                }

                this->_next_index++;
            } else {
                this->_next_index = 0;
            }

            if (this->_next_index == previous_next_index) {
                break;
            }
        }

        this->_size += this->_section_size;
        T *new_array = new T[this->_size];

        std::copy(this->_array, this->_array + this->_size - 1, new_array);

        new_array[this->_size - 1] = element;
        this->_element_count++;

        delete[] this->_array;
        this->_array = new_array;
    }

    bool remove(const T &element, bool optimize = true) {
        if (element == this->_empty_element) {
            return false;
        }

        int index = this->nullable_index_of(element);

        if (index == -1) {
            return false;
        }

        this->_array[index] = this->_empty_element;
        this->_element_count--;

        if (optimize) {
            this->optimize();
        }

        return true;
    }

    bool nullable_remove_at(unsigned int index, bool optimize = true) {
        if (this->_array[index] == this->_empty_element) {
            return false;
        }

        this->_array[index] = this->_empty_element;
        this->_element_count--;

        if (optimize) {
            this->optimize();
        }

        return true;
    }

    bool remove_at(unsigned int index, bool optimize = true) {
        unsigned int counted_index = 0;

        for (unsigned int i = 0; i < this->_size; i++) {
            if (this->_array[i] != this->_empty_element) {
                if (counted_index == index) {
                    this->_array[i] = this->_empty_element;
                    this->_element_count--;

                    if (optimize) {
                        this->optimize();
                    }

                    return true;
                }

                counted_index++;
            }
        }

        return false;
    }

    T nullable_pop_at(unsigned int index, bool optimize = true) {
        T element = this->_array[index];
        this->_array[index] = this->_empty_element;
        this->_element_count--;

        if (optimize) {
            this->optimize();
        }

        return element;
    }

    T pop_at(unsigned int index, bool optimize = true) {
        unsigned int counted_index = 0;

        for (unsigned int i = 0; i < this->_size; i++) {
            if (this->_array[i] != this->_empty_element) {
                if (counted_index == index) {
                    T element = this->_array[i];
                    this->_array[i] = this->_empty_element;
                    this->_element_count--;

                    if (optimize) {
                        this->optimize();
                    }

                    return element;
                }

                counted_index++;
            }
        }

        return this->_empty_element;
    }

    T *get_elements() {
        T *elements = new T[this->_element_count];
        unsigned int counted_index = 0;

        for (unsigned int i = 0; i < this->_size; i++) {
            if (this->_array[i] != this->_empty_element) {
                elements[counted_index] = this->_array[i];
                counted_index++;
            }
        }

        return elements;
    }

    bool optimize() {
        unsigned int excess_sections = (this->_size - this->_element_count) / this->_section_size;

        if (excess_sections > 0 && this->_element_count > 0) {
            unsigned int new_size = (this->_size / this->_section_size - excess_sections) * this->_section_size;

            T *new_array = new T[new_size];

            unsigned int counted_index = 0;

            for (unsigned int i = 0; i < this->_size; i++) {
                if (this->_array[i] != this->_empty_element) {
                    new_array[counted_index] = this->_array[i];
                    counted_index++;
                }
            }

            for (unsigned int i = counted_index; i < new_size; i++) {
                new_array[i] = this->_empty_element;
            }

            delete[] this->_array;
            this->_array = new_array;
            this->_size = new_size;

            return true;
        }

        return false;
    }

    template <typename Compare>
    void sort(Compare comp) {
        std::sort(this->_array, this->_array + this->_size, comp);
    }

    inline unsigned int get_size() { return this->_size; };
    inline unsigned int get_element_count() { return this->_element_count; };

   private:
    T *_array;
    T _empty_element;
    unsigned int _size;
    unsigned int _next_index;
    unsigned int _section_size;
    unsigned int _element_count;
};

template <typename T>
class DynamicArrayIterator {
   public:
    DynamicArrayIterator(DynamicArray<T> *dynamic_array) {
        this->_dynamic_array = dynamic_array;
        this->_nullable_index = 0;
        this->_index = 0;
    }

    ~DynamicArrayIterator() = default;

    inline bool has_nullable_next() { return this->_nullable_index < this->_dynamic_array->get_element_count(); }
    inline bool has_next() { return this->_index < this->_dynamic_array->get_size(); }

    T nullable_next() {
        T element = this->_dynamic_array->nullable_at(this->_nullable_index++);
        return element;
    }

    T next() {
        while (true) {
            if (this->_index >= this->_dynamic_array->get_size()) {
                break;
            }

            T element = this->_dynamic_array->nullable_at(this->_index++);

            if (element != this->_dynamic_array->get_empty_element()) {
                return element;
            }
        }

        return this->_dynamic_array->get_empty_element();
    }

    void nullable_reset() { this->_nullable_index = 0; }
    void reset() { this->_index = 0; }

   private:
    DynamicArray<T> *_dynamic_array;
    unsigned int _nullable_index;
    unsigned int _index;
};
