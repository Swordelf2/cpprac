#include <cstdio>

class FileWrapper
{
public:
    FileWrapper(const char *s);
    FileWrapper(const FileWrapper &other);
    FileWrapper(FileWrapper &&other);
    FileWrapper& operator=(const FileWrapper &other);
    FileWrapper& operator=(FileWrapper &&other);

    FileWrapper& operator<<(char c);

    ~FileWrapper();

private:
    FILE *f;
};

FileWrapper::FileWrapper(const char *s)
{
    f = fopen(s, "w+");
}
FileWrapper::~FileWrapper()
{
    fclose(f);
}

FileWrapper::FileWrapper(const FileWrapper &other) : f(other.f) {}

FileWrapper::FileWrapper(FileWrapper &&other) : f(other.f)
{
    other.f = NULL;
}

FileWrapper& FileWrapper::operator=(const FileWrapper &other)
{
    f = other.f;
    return *this;
}

FileWrapper& FileWrapper::operator=(FileWrapper &&other)
{
    f = other.f;
    other.f = NULL;
    return *this;
}

FileWrapper& FileWrapper::operator<<(char c)
{
    fputc(c, f);
    return *this;
}
