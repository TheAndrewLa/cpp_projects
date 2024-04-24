#include <cstdio>
#include <cstdint>

// My hierarchy
// IO <- {Reader, Writer} <- {ReaderWriter} <- {StringStream, FileStream}

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

class reader : virtual public io {
    public:

    virtual int32 read_int() = 0;
    virtual uint32 read_uint() = 0;

    virtual real32 read_float() = 0;
    virtual real64 read_double() = 0;

    virtual char8 read_char() = 0;
};

class writer : virtual public io {
    public:

    virtual void write_int(int32 value) = 0;
    virtual void write_uint(uint32 value) = 0;

    virtual void write_float(real32 value) = 0;
    virtual void write_double(real64 value) = 0;

    virtual void write_char(char8 value) = 0;
};

class reader_writer : public reader, public writer {};
