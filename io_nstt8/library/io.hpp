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

class buffered_fstream : public fstream {
    buffered_fstream() = default;
    buffered_fstream(const char* filename, usize buffer_size);

    ~buffered_fstream();

    void write_int(int32 value) = 0;
    void write_uint(uint32 value) = 0;

    void write_float(real32 value) = 0;
    void write_double(real64 value) = 0;

    void write_char(char8 value) = 0;

    int32 read_int() = 0;
    uint32 read_uint() = 0;

    real32 read_float() = 0;
    real64 read_double() = 0;

    char8 read_char() = 0;

    bool is_open() const;
    bool eof() const;
    void close();

    private:
    FILE* handle_{nullptr};
    char8* buffer_{nullptr};
};
