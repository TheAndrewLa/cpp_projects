#include "io.hpp"

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
    real32 var;
    reading_pos_ += sscanf(handle_->c_str(), "%lf", &var);

    return var;
}

char8 sstream::read_char() {
    char8 var;
    sscanf(handle_->c_str(), "%c", &var);
    
    reading_pos_++;

    return var;
}
