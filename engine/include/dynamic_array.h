#pragma once

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
        }
    }

    void fill(T element) {
        for (unsigned int i = 0; i < this->_size; i++) {
            this->_array[i] = element;
        }
    }

    void clear() {
        this->fill(this->_empty_element);
        this->_next_index = 0;
        this->_element_count = 0;
        this->downsize();
    }

    bool contains(const T &element) {
        return this->raw_index_of(element) != -1;
    }

    int raw_index_of(const T &element) {
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

    T &raw_at(unsigned int index) { return this->_array[index]; }

    T &at(unsigned int index) {
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

        for (unsigned int i = 0; i < this->_size - 1; i++) {
            new_array[i] = this->_array[i];
        }

        new_array[this->_size - 1] = element;
        this->_element_count++;

        delete[] this->_array;
        this->_array = new_array;
    }

    bool remove(const T &element) {
        if (element == this->_empty_element) {
            return false;
        }

        int index = this->raw_index_of(element);

        if (index == -1) {
            return false;
        }

        this->_array[index] = this->_empty_element;
        this->_element_count--;
        this->downsize();

        return true;
    }

    bool raw_remove_at(unsigned int index) {
        if (this->_array[index] == this->_empty_element) {
            return false;
        }

        this->_array[index] = this->_empty_element;
        this->_element_count--;
        this->downsize();

        return true;
    }

    bool remove_at(unsigned int index) {
        unsigned int counted_index = 0;

        for (unsigned int i = 0; i < this->_size; i++) {
            if (this->_array[i] != this->_empty_element) {
                if (counted_index == index) {
                    if (this->_array[i] == this->_empty_element) {
                        break;
                    }

                    this->_array[i] = this->_empty_element;
                    this->_element_count--;
                    this->downsize();
                    
                    return true;
                }

                counted_index++;
            }
        }

        return false;
    }

    void downsize() {
        unsigned int excess_sections = (this->_size - this->_element_count) / this->_section_size;

        if (excess_sections > 0) {
            unsigned int new_size = this->_size / this->_section_size - excess_sections;
            T *new_array = new T[new_size];

            for (unsigned int i = 0; i < this->_size; i++) {
                if (this->_array[i] != this->_empty_element) {
                    new_array[i] = this->_array[i];
                }
            }

            delete[] this->_array;
            this->_array = new_array;
            this->_size = new_size;
        }
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