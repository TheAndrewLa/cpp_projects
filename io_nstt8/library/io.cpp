#include "io.hpp"

fstream::fstream(const std::string& filename) : handle_(fopen(filename.c_str(), "a+")) {}
fstream::fstream(const char* filename) : handle_(fopen(filename, "a+")) {}

fstream::~fstream() {
    fclose(handle_);
}

bool fstream::eof() const {
    return static_cast<bool>(feof(handle_));
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

buffer::buffer(usize size) : ptr_(new char8[size]()), size_(size), current_(0) {}

buffer::~buffer() {
    delete [] ptr_;
}

buffered_ifstream::buffered_ifstream(FILE* file, usize size) : buffer(size), handle_(file) {
    read_buffer();
}

void buffered_ifstream::read_buffer() {
    assert(handle_ != nullptr);
    assert(size_ > 0);

    char8 sym;
    usize i = 0;

    while ((sym = fgetc(handle_)) != EOF && i < size_) {
        ptr_[i] = sym;
        i++;
    }

    actual_size_ = i;
    current_ = 0;
}

int32 buffered_ifstream::read_int() {
    if (current_ >= actual_size_)
        read_buffer();

    int32 value;
    current_ += sscanf(ptr_ + current_, "%d", &value);

    return value;
}

uint32 buffered_ifstream::read_uint() {
    if (current_ >= actual_size_)
        read_buffer();

    uint32 value;
    current_ += sscanf(ptr_ + current_, "%u", &value);

    return value;
}

real32 buffered_ifstream::read_float() {
    if (current_ >= actual_size_)
        read_buffer();

    real32 value;
    current_ += sscanf(ptr_ + current_, "%f", &value);

    return value;
}

real64 buffered_ifstream::read_double() {
    if (current_ >= actual_size_)
        read_buffer();

    uint32 value;
    current_ += sscanf(ptr_ + current_, "%lf", &value);

    return value;
}

char8 buffered_ifstream::read_char() {
    if (current_ == actual_size_)
        read_buffer();

    char8 value = ptr_[current_];
    current_++;
}

buffered_ofstream::buffered_ofstream(FILE* file, usize size) : buffer(size), handle_(file) {}

void buffered_ofstream::write_buffer() {
    for (usize i = 0; i < size_; i++)
        fputc(ptr_[i], handle_);
    
    current_ = 0;
}

void buffered_ofstream::write_int(int32 value) {
    char8 buf[16];
    usize len = sprintf(buf, "%d", value);

    if (current_ + len == size_)
        write_buffer();

    snprintf(ptr_ + current_, len, buf);
}

void buffered_ofstream::write_uint(uint32 value) {
    char8 buf[16];
    usize len = sprintf(buf, "%u", value);

    if (current_ + len == size_)
        write_buffer();

    snprintf(ptr_ + current_, len, buf);
}

void buffered_ofstream::write_float(real32 value) {
    char8 buf[16];
    usize len = sprintf(buf, "%f", value);

    if (current_ + len == size_) {
        write_buffer();
        current_ = 0;
    }

    snprintf(ptr_ + current_, len, buf);
}

void buffered_ofstream::write_double(real64 value) {
    char8 buf[16];
    usize len = sprintf(buf, "%lf", value);

    if (current_ + len == size_)
        write_buffer();

    snprintf(ptr_ + current_, len, buf);
}

void buffered_ofstream::write_char(char8 value) {
    if (current_ == size_)
        write_buffer();

    ptr_[current_] = value;
}

buffered_fstream::buffered_fstream(const char* filename, usize out_buffer_size, usize in_buffer_size) :
    handle_(fopen(filename, "a+")),
    buffered_ifstream(handle_, in_buffer_size), buffered_ofstream(handle_, out_buffer_size) {}

buffered_fstream::~buffered_fstream() {
    fclose(handle_);
}

bool buffered_fstream::is_open() const {
    return handle_ != nullptr;
}

bool buffered_fstream::eof() const {
    return static_cast<bool>(feof(handle_));
}

void buffered_fstream::close() {
    fclose(handle_);
}
