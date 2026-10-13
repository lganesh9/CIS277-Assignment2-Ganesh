#include <vector>
template  <typename T>
class MyStack{
    public:

    void push(const T& value){v1.push_back(value);}
    T pop(){
        T x = std::move(v1.back());
        v1.pop_back();
        return x;
    }
    T& top(){return v1.back();}
    bool empty() const{return v1.empty();}
    std::size_t size() const{return v1.size();}

    private:
    std::vector <T> v1;
};

