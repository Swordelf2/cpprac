class Sum
{
    int result = 0;
    public:
    Sum(int a, int b) : result(a + b) {};
    int get() const { return result; };
};
