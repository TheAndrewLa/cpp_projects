#include <cstdio>
#include <cstdint>
#include <string>

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

    ~fstream();

    virtual void write_int(int32 value) = 0;
    virtual void write_uint(uint32 value) = 0;

    virtual void write_float(real32 value) = 0;
    virtual void write_double(real64 value) = 0;

    virtual void write_char(char8 value) = 0;

    virtual int32 read_int() = 0;
    virtual uint32 read_uint() = 0;

    virtual real32 read_float() = 0;
    virtual real64 read_double() = 0;

    virtual char8 read_char() = 0;

    virtual bool is_open() const;
    virtual bool eof() const;
    virtual void close();

    private:
    FILE* handle_{nullptr};
};

class sstream : public io_stream {
    public:
    sstream() = default;
    sstream(std::string* source);

    ~sstream() = default;

    virtual void write_int(int32 value) = 0;
    virtual void write_uint(uint32 value) = 0;

    virtual void write_float(real32 value) = 0;
    virtual void write_double(real64 value) = 0;

    virtual void write_char(char8 value) = 0;

    virtual int32 read_int() = 0;
    virtual uint32 read_uint() = 0;

    virtual real32 read_float() = 0;
    virtual real64 read_double() = 0;

    virtual char8 read_char() = 0;

    virtual bool is_open() const;
    virtual bool eof() const;
    virtual void close();

    private:
    std::string* handle_{nullptr};
};

/// @todo later

class buffered_fstream : public fstream {};

class buffered_sstream : public sstream {};