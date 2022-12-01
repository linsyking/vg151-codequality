#ifndef public_member_variable_h
#define public_member_variable_h

class test {
private:
    int s;          // ok
    int pri_fun();  // ok

protected:
    int p;          // ok
    int d;          // ok
    int pro_fun();  // ok

public:
    test();
    int  a;      // bad
    int  b;      // bad
    int  c;      // bad
    void fun();  // ok
};

#endif
