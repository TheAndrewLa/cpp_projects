#include <cstdio>
#include <cstdint>
#include <string>
#include <stdexcept>

// Wanted to use unix file reading/writing. But libc doing great
// #include <unistd.h>

using usize = std::size_t;
using isize = std::ptrdiff_t;

using int32 = std::int32_t;
using uint32 = std::uint32_t;

using real32 = float;
using real64 = double;

using char8 = char;

class io {
    public:
    virtual bool is_open() const = 0;
    virtual bool eof() const = 0;
    virtual void close() = 0;
};

class input_stream : virtual public io {
    public:

    virtual int32 read_int() = 0;
    virtual uint32 read_uint() = 0;

    virtual real32 read_float() = 0;
    virtual real64 read_double() = 0;

    virtual char8 read_char() = 0;

    protected:
    usize reading_pos_;
};

class output_stream : virtual public io {
    public:

    virtual void write_int(int32 value) = 0;
    virtual void write_uint(uint32 value) = 0;

    virtual void write_float(real32 value) = 0;
    virtual void write_double(real64 value) = 0;

    virtual void write_char(char8 value) = 0;
};

class io_stream : public input_stream, public output_stream {};

class fstream : public io_stream {
    public:
    fstream() = default;
    fstream(const std::string& filename);
    fstream(const char* filename);

    virtual ~fstream();

    virtual void write_int(int32 value);
    virtual void write_uint(uint32 value);

    virtual void write_float(real32 value);
    virtual void write_double(real64 value);

    virtual void write_char(char8 value);

    virtual int32 read_int();
    virtual uint32 read_uint();

    virtual real32 read_float();
    virtual real64 read_double();

    virtual char8 read_char();

    virtual bool is_open() const;
    virtual bool eof() const;
    virtual void close();

    protected:
    FILE* handle_{nullptr};
};

class sstream : public io_stream {
    public:
    sstream() = default;
    sstream(std::string* source);

    virtual ~sstream() = default;

    virtual void write_int(int32 value);
    virtual void write_uint(uint32 value);

    virtual void write_float(real32 value);
    virtual void write_double(real64 value);

    virtual void write_char(char8 value);

    virtual int32 read_int();
    virtual uint32 read_uint();

    virtual real32 read_float();
    virtual real64 read_double();

    virtual char8 read_char();

    virtual bool is_open() const;
    virtual bool eof() const;
    virtual void close();

    protected:
    std::string* handle_{nullptr};
};

class buffer {
    public:
    buffer() = default;
    buffer(usize size);

    virtual ~buffer();

    char8* get_buffer();

    protected:
    void push_symbols(char* str, usize n);

    char8* ptr_{nullptr};
    usize size_{0};
    usize current_{0};
};

class buffered_ifstream : public buffer {
    public:
    buffered_ifstream() = default;
    buffered_ifstream(FILE* fd, usize size);

    ~buffered_ifstream() = default;

    virtual int32 read_int();
    virtual uint32 read_uint();

    virtual real32 read_float();
    virtual real64 read_double();

    virtual char8 read_char();
};

class buffered_ofstream : public buffer {
    public:
    buffered_ofstream() = default;
    buffered_ofstream(usize size);

    ~buffered_ofstream() = default;

    virtual void write_int(int32 value);
    virtual void write_uint(uint32 value);

    virtual void write_float(real32 value);
    virtual void write_double(real64 value);

    virtual void write_char(char8 value);
};

class buffered_fstream : public fstream, public buffered_ifstream, public buffered_ofstream {
    public:
    buffered_fstream() = default;
    buffered_fstream(const char* filename, usize buffer_size);

    ~buffered_fstream() = default;

    void write_int(int32 value);
    void write_uint(uint32 value);

    void write_float(real32 value);
    void write_double(real64 value);

    void write_char(char8 value);

    int32 read_int();
    uint32 read_uint();

    real32 read_float();
    real64 read_double();

    char8 read_char();

    char8* get_reading_buffer();
    char8* get_writing_buffer();
};
