// ClassTemplate.h
#ifndef ClassTemplate_HH
#define ClassTemplate_HH

using namespace std;

// class or typename 
template<class T1,class T2>
class myClass{
private:
    T1 I;
    T2 J;
public:
    myClass(T1 a, T2 b);//Constructor
    void show();
};

template <class T1,class T2>
myClass<T1,T2>::myClass(T1 a,T2 b):I(a),J(b){}

template <class T1,class T2>
void myClass<T1,T2>::show()
{
    cout<<"I="<<I<<", J="<<J<<endl;
}
#endif