#ifndef TEACHABLE_DICTIONARY_HPP
#define TEACHABLE_DICTIONARY_HPP

#include <iostream>
#include <fstream>

#include "hash_table.hpp"

class teachable_dictionary final {
public:
    explicit teachable_dictionary(const std::string &data_path);
    teachable_dictionary(const teachable_dictionary &other) = default;
    teachable_dictionary(teachable_dictionary &&other) noexcept = default;

    teachable_dictionary &operator=(const teachable_dictionary &other) = default;
    teachable_dictionary &operator=(teachable_dictionary &&other) noexcept = default;

    ~teachable_dictionary();

    size_t size() const;
    bool empty() const;

    int get_freq(const std::string &word) const;

    bool read_text(const std::string &teachable_text);
    bool save_data(const std::string &path_to_save) const;

private:
    std::string data_dictionary_path_;
    my_containers::hash_table<std::string, int> dictionary_;
};

#endif
