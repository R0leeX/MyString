#include <iostream>
#include "mystring.h"

using namespace std;

int main()
{
    MyString s;
    cin >> s;
    MyString a;
    MyString b("test");
    MyString c = "c_test";
    c = a;
    b[1] = 'B';
    b[2] = a[1];
    c = b;
    MyString d(MyString("rightvalue"));
    MyString e, f, g, h;
    e = f = g = h = a;
    e += 'a';
    f = d + 'D' + g;
    g = a + b;
    h += h;
    e += s;
    MyString i = MyString(g);

    cout << "s:  " << s << "\t" << "refCount: " << s.getValueRefCount() << endl;
    cout << "a:  " << a << "\t" << " refCount: " << a.getValueRefCount() << endl;
    cout << "b:  " << b << "\t" << " refCount: " << b.getValueRefCount() << endl;
    cout << "c:  " << c << "\t" << " refCount: " << c.getValueRefCount() << endl;
    cout << "d:  " << d << "\t" << " refCount: " << d.getValueRefCount() << endl;
    cout << "e:  " << e << "\t" << " refCount: " << e.getValueRefCount() << endl;
    cout << "f:  " << f << "\t" << " refCount: " << f.getValueRefCount() << endl;
    cout << "g:  " << g << "\t" << " refCount: " << g.getValueRefCount() << endl;
    cout << "h:  " << h << "\t" << " refCount: " << h.getValueRefCount() << endl;
    cout << "i:  " << i << "\t" << " refCount: " << i.getValueRefCount() << endl;
    cout << "length of g: " << g.length() << endl;

    return 0;
}
