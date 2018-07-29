#pragma once

#include <string>
#include <vector>

class GridImpl
{
public:
    GridImpl(const size_t width, const size_t height);

    bool initialize_random();
    bool initialize_from_file(const std::string& file_path);

    char get_cell(const size_t x, const size_t y) const;
    int get_live_neighbors_count(const size_t cell_x, const size_t cell_y) const;

    char calc_cell(const char cur_state, const int num_live_neighbors) const;
    void recalculate(const GridImpl& previous_generation, const size_t num_of_threads);

    void print(const std::string& file_path, const bool append_to_file) const;

private:
    inline bool get_grid_size(size_t& x, size_t& y) const;

    void calc_generation_in_range(const GridImpl& previous_generation, const size_t x_begin, const size_t x_end);
    void split_on_threads(const GridImpl& previous_generation, const size_t num_of_threads);

private:
    std::vector< std::vector<char> > m_grid;
};
