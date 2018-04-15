#include <cstdio>
#include <utility>

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

    friend void swap(FileWrapper &fw1, FileWrapper &fw2);
    friend int main();
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
    if (cnt && f) {
        --(*cnt);
        if (*cnt == 0) {
            delete cnt;
            fclose(f);
        }
    }
}

FileWrapper::FileWrapper(const FileWrapper &other) : f(other.f), cnt(other.cnt)
{
    ++(*cnt);
}

    
FileWrapper::FileWrapper(FileWrapper &&other) : f(other.f), cnt(other.cnt)
{
    if (this != &other) {
        other.f = NULL;
        other.cnt = nullptr;
    }
}

FileWrapper& FileWrapper::operator=(const FileWrapper &other)
{
    FileWrapper copied(other);
    swap(*this, copied);
    return *this;
}

FileWrapper& FileWrapper::operator=(FileWrapper &&other)
{
    FileWrapper copied(std::move(other));
    swap(*this, copied);
    return *this;
}

FileWrapper& FileWrapper::operator<<(char c)
{
    fputc(c, f);
    return *this;
}

void swap(FileWrapper &fw1, FileWrapper &fw2)
{
    std::swap(fw1.f, fw2.f);
    std::swap(fw1.cnt, fw2.cnt);
}
