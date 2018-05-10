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
    struct SharedFile
    {
        FILE *f;
        int cnt = 1;
    };

    SharedFile *sf;
};

FileWrapper::FileWrapper(const char *s)
{
    sf = new SharedFile();
    sf->f = fopen(s, "w+");
}

FileWrapper::~FileWrapper()
{
    if (sf) {
        --sf->cnt;
        if (sf->cnt == 0) {
            fclose(sf->f);
            delete sf;
        }
    }
}

FileWrapper::FileWrapper(const FileWrapper &other) : sf(other.sf)
{
    ++sf->cnt;
}

    
FileWrapper::FileWrapper(FileWrapper &&other) : sf(other.sf)
{
    if (this != &other) {
        other.sf = nullptr;
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
    fputc(c, sf->f);
    return *this;
}

void swap(FileWrapper &fw1, FileWrapper &fw2)
{
    std::swap(fw1.sf, fw2.sf);
}
