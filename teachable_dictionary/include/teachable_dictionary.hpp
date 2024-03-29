#ifndef TEACHABLE_DICTIONARY_HPP
#define TEACHABLE_DICTIONARY_HPP

#include <iostream>
#include <fstream>

#include "hash_table.hpp"

namespace dictionary {

struct word_freq_dist_t;

class teachable_dictionary final {
public:
    explicit teachable_dictionary(const std::string &data_path = {}, const bool read_bytes = false);
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
    bool save_data_binary(const std::string &path_to_save) const;

    bool correct_text(const std::string &text_for_correct_path, const bool is_multithread = false,
                      const int lev_const = 2) const;
    std::string find_min_levenshtein_distance(const std::string &word, const int lev_const = 2) const;

private:
    void create_data_from_bytes_(const std::string &data_path);
    word_freq_dist_t find_word_freq_dist_(const std::string &word, const int lenth, const int lev_const) const;

    using numeric_hash_table = typename my_containers::hash_table<std::string, int>;
    my_containers::hash_table<int, numeric_hash_table> dictionary_;

    std::string data_dictionary_path_;
    int size_;
    int size_data_in_bytes_;
};

}  // namespace dictionary

#endif
