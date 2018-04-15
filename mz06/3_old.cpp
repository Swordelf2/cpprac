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
    int *cnt;
};

FileWrapper::FileWrapper(const char *s)
{
    f = fopen(s, "w+");
    cnt = new int(1);
}

FileWrapper::~FileWrapper()
{
    --(*cnt);
    if (*cnt == 0) {
        delete cnt;
        fclose(f);
    }
}

FileWrapper::FileWrapper(const FileWrapper &other) : f(other.f)
{
    cnt = other.cnt;
    ++(*cnt);
}

    
FileWrapper::FileWrapper(FileWrapper &&other) : f(other.f)
{
    cnt = other.cnt;
    ++(*cnt);
}

FileWrapper& FileWrapper::operator=(const FileWrapper &other)
{
    f = other.f;
    cnt = other.cnt;
    ++(*cnt);
    return *this;
}

FileWrapper& FileWrapper::operator=(FileWrapper &&other)
{
    f = other.f;
    cnt = other.cnt;
    ++(*cnt);
    return *this;
}

FileWrapper& FileWrapper::operator<<(char c)
{
    fputc(c, f);
    return *this;
}
