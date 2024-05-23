#include "io.hpp"

buffer::buffer(usize size) : ptr_(new char8[size]), size_(size), current_(0) {}

buffer::~buffer() {
    delete [] ptr_;
}

void buffer::push_symbols(char* str, usize n) {
    if (current_ + n > size_) {
        throw std::runtime_error{"Buffer is full!"};
    }

    snprintf(ptr_ + current_, n, "%s", str);
    current_ += n;
}

char8* buffer::get_buffer() {
    return ptr_;
}

buffered_ifstream::buffered_ifstream(FILE* fd, usize size) : buffer(size) {
    char8 sym = '\0';
    usize count = 0;

    while((sym = fgetc(fd)) != EOF || count < size_) ptr_[count++] = sym;
}

char8 buffered_ifstream::read_char() {
    if (current_ < size_) {
        char8 sym;

        current_ += sscanf(ptr_ + current_, "%c", &sym);
        return sym;
    }

    throw std::runtime_error{"Buffer is empty"};
}

real64 buffered_ifstream::read_double() {
    if (current_ < size_) {
        real64 val;
        
        current_ += sscanf(ptr_ + current_, "%lf", &val);
        return val;
    }

    throw std::runtime_error{"Buffer is empty"};
}

real32 buffered_ifstream::read_float() {
    if (current_ < size_) {
        real32 val;
        
        current_ += sscanf(ptr_ + current_, "%f", &val);
        return val;
    }

    throw std::runtime_error{"Buffer is empty"};
}

int32 buffered_ifstream::read_int() {
    if (current_ < size_) {
        int32 val;

        current_ += sscanf(ptr_ + current_, "%d", &val);
        return val;
    }

    throw std::runtime_error{"Buffer is empty"};
}

uint32 buffered_ifstream::read_uint() {
    if (current_ < size_) {
        uint32 val;

        current_ += sscanf(ptr_ + current_, "%u", &val);
        return val;
    }

    throw std::runtime_error{"Buffer is empty"};
}

buffered_ofstream::buffered_ofstream(usize size) : buffer(size) {}

void buffered_ofstream::write_char(char8 value) {
    char8 sym = value;
    push_symbols(&sym, 1);
}

void buffered_ofstream::write_double(real64 value) {
    char str[64];
    usize len = sprintf(str, "%lf", value);

    push_symbols(str, len);
}

void buffered_ofstream::write_float(real32 value) {
    char str[64];
    usize len = sprintf(str, "%f", value);

    push_symbols(str, len);
}

void buffered_ofstream::write_int(int32 value) {
    char str[16];
    usize len = sprintf(str, "%d", value);

    push_symbols(str, len);
}

void buffered_ofstream::write_uint(uint32 value) {
    char str[16];
    usize len = sprintf(str, "%u", value);

    push_symbols(str, len);
}

fstream::fstream(const std::string& filename) : handle_(fopen(filename.c_str(), "a+")) {}
fstream::fstream(const char* filename) : handle_(fopen(filename, "a+")) {}

fstream::~fstream() {
    fclose(handle_);
}

bool fstream::eof() const {
    return static_cast<bool>(std::feof(handle_));
}

bool fstream::is_open() const {
    return handle_ != nullptr;
}

void fstream::close() {
    fclose(handle_);
}

void fstream::write_int(int32 value) {
    fprintf(handle_, "%d", value);
}

void fstream::write_uint(uint32 value) {
    fprintf(handle_, "%u", value);
}

void fstream::write_float(real32 value) {
    fprintf(handle_, "%f", value);
}

void fstream::write_double(real64 value) {
    fprintf(handle_, "%lf", value);
}

void fstream::write_char(char8 value) {
    fprintf(handle_, "%c", value);
}

int32 fstream::read_int() {
    int32 var;
    fscanf(handle_, "%d", &var);
    
    return var;
}

uint32 fstream::read_uint() {
    uint32 var;
    fscanf(handle_, "%u", &var);
    
    return var;
}

real32 fstream::read_float() {
    real32 var;
    fscanf(handle_, "%f", &var);
    
    return var;
}

real64 fstream::read_double() {
    real64 var;
    fscanf(handle_, "%lf", &var);
    
    return var;
}

char8 fstream::read_char() {
    return std::fgetc(handle_);
}

sstream::sstream(std::string* source) : handle_(source) {}

bool sstream::is_open() const {
    return handle_ != nullptr;
}

bool sstream::eof() const {
    return reading_pos_ == handle_->size();
}

void sstream::close() {
    handle_ = nullptr;
}

void sstream::write_int(int32 value) {
    handle_->append(std::to_string(value));
}

void sstream::write_uint(uint32 value) {
    handle_->append(std::to_string(value));
}

void sstream::write_float(real32 value) {
    handle_->append(std::to_string(value));
}

void sstream::write_double(real64 value) {
    handle_->append(std::to_string(value));
}

void sstream::write_char(char8 value) {
    handle_->append(std::to_string(value));
}

int32 sstream::read_int() {
    int32 var;
    reading_pos_ += sscanf(handle_->c_str(), "%d", &var);

    return var;
}

uint32 sstream::read_uint() {
    uint32 var;
    reading_pos_ += sscanf(handle_->c_str(), "%u", &var);

    return var;
}

real32 sstream::read_float() {
    real32 var;
    reading_pos_ += sscanf(handle_->c_str(), "%f", &var);

    return var;
}

real64 sstream::read_double() {
    real64 var;
    reading_pos_ += sscanf(handle_->c_str(), "%lf", &var);

    return var;
}

char8 sstream::read_char() {
    char8 var;
    sscanf(handle_->c_str(), "%c", &var);
    
    reading_pos_++;

    return var;
}

//
buffered_fstream::buffered_fstream(const char* filename, usize buffer_size) :
fstream(filename), buffered_ifstream(handle_, buffer_size), buffered_ofstream(buffer_size) {}

// Using benefits of non-virtual diamond inheritance

char8* buffered_fstream::get_reading_buffer() {
    return buffered_ifstream::get_buffer();
}

char8* buffered_fstream::get_writing_buffer() {
    return buffered_ofstream::get_buffer();
}

// Using try-catch semantics (try to write to a buffer and if exceptions was thrown)
// Here's so much copy-pasted code, but in my organization of code I couldn't do better

void buffered_fstream::write_char(char8 value) {
    try {
        buffered_ofstream::write_char(value);
    } catch (...) {
        fstream::write_char(value);
    }
}

void buffered_fstream::write_float(real32 value) {
    try {
        buffered_ofstream::write_float(value);
    } catch (...) {
        fstream::write_float(value);
    }
}

void buffered_fstream::write_double(real64 value) {
    try {
        buffered_ofstream::write_double(value);
    } catch (...) {
        fstream::write_double(value);
    }
}

void buffered_fstream::write_int(int32 value) {
    try {
        buffered_ofstream::write_int(value);
    } catch (...) {
        fstream::write_int(value);
    }
}

void buffered_fstream::write_uint(uint32 value) {
    try {
        buffered_ofstream::write_uint(value);
    } catch (...) {
        fstream::write_uint(value);
    }
}

char8 buffered_fstream::read_char() {
    char8 value;

    try {
        value = buffered_ifstream::read_char();
    } catch(...) {
        value = fstream::read_char();
    }

    return value;
}

real32 buffered_fstream::read_float() {
    real32 value;

    try {
        value = buffered_ifstream::read_float();
    } catch(...) {
        value = fstream::read_float();
    }

    return value;
}

real64 buffered_fstream::read_double() {
    real64 value;

    try {
        value = buffered_ifstream::read_double();
    } catch(...) {
        value = fstream::read_double();
    }

    return value;
}

int32 buffered_fstream::read_int() {
    int32 value;

    try {
        value = buffered_ifstream::read_int();
    } catch(...) {
        value = fstream::read_int();
    }

    return value;
}

uint32 buffered_fstream::read_uint() {
    uint32 value;

    try {
        value = buffered_ifstream::read_uint();
    } catch(...) {
        value = fstream::read_uint();
    }

    return value;
}
