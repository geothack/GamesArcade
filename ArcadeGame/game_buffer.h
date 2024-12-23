#pragma once


struct game_buffer {
public:
    game_buffer() {}

    game_buffer(int x, int y) : m_row(x), m_col(y) 
    {
        m_buffer = new char* [m_row];
        for (int i = 0; i < m_row; ++i) {
            m_buffer[i] = new char[m_col];
        }
    };

    ~game_buffer() 
    {
        for (int i = 0; i < m_row; ++i) {
            delete[] m_buffer[i];
        }
        delete[] m_buffer;
    }

    game_buffer(game_buffer&& other) noexcept //Move Constructor
        : m_row(other.m_row), m_col(other.m_col), m_buffer(other.m_buffer)
    {
        // Reset the source object
        other.m_row = 0;
        other.m_col = 0;
        other.m_buffer = nullptr;
    }

    game_buffer& operator=(game_buffer&& other) noexcept //Move Assignment Operator
    {
        if (this != &other) {
            // Deallocate existing memory
            for (int i = 0; i < m_row; ++i) {
                delete[] m_buffer[i];
            }
            delete[] m_buffer;

            // Transfer ownership
            m_row = other.m_row;
            m_col = other.m_col;
            m_buffer = other.m_buffer;

            // Reset the source object
            other.m_row = 0;
            other.m_col = 0;
            other.m_buffer = nullptr;
        }
        return *this;
    }

    game_buffer(const game_buffer& other) : m_row(other.m_row), m_col(other.m_col) //Copy Constructor 
    {
        // Allocate memory for m_buffer
        m_buffer = new char* [m_row];
        for (int i = 0; i < m_row; ++i) {
            m_buffer[i] = new char[m_col];
        }

        // Copy the data from other to this object
        for (int i = 0; i < m_row; ++i) {
            for (int j = 0; j < m_col; ++j) {
                m_buffer[i][j] = other.m_buffer[i][j];
            }
        }
    }

    game_buffer& operator=(const game_buffer& other) // Copy Assignment Operator
    {
        if (this == &other) {
            return *this;
        }

        // Deallocate existing memory
        for (int i = 0; i < m_row; ++i) {
            delete[] m_buffer[i];
        }
        delete[] m_buffer;

        // Allocate memory for new data
        m_row = other.m_row;
        m_col = other.m_col;
        m_buffer = new char* [m_row];
        for (int i = 0; i < m_row; ++i) {
            m_buffer[i] = new char[m_col];
        }



        // Copy the data from other to this object
        for (int i = 0; i < m_row; ++i) {
            for (int j = 0; j < m_col; ++j) {
                m_buffer[i][j] = other.m_buffer[i][j];
            }
        }
        return *this;
    }

    char& get_char(int m_row, int m_col) 
    {
        return m_buffer[m_row][m_col];
    }

    void set_char(int m_row, int m_col, char value) 
    {
        m_buffer[m_row][m_col] = value;
    }



private:
    int m_row;
    int m_col;
    char** m_buffer;
};
