#include <QtTest>
#include <typeinfo>
// add necessary includes here

#include <iostream>
using std::cout;
using std::endl;

#include "../Katalog/DeepPtr.h"
#include "../Katalog/Vector.h"

typedef unsigned int u_int;

class KatalogTest : public QObject
{
    Q_OBJECT

public:
    KatalogTest();
    ~KatalogTest();

private slots:
    void DeepPtrCopy();
    void DeepPtrValue();
    void DeepPtrPolymorphicClassType();
    void DeepPtrPolymorphicClassClone();
    void VectorCopyAssignement();
    void VectorAppend();
    void VectorInsert();
    void VectorErease();
};

KatalogTest::KatalogTest() {}

KatalogTest::~KatalogTest() {}

void KatalogTest::DeepPtrCopy()
{
    using namespace Katalog;
    Katalog::DeepPtr<int> ptr(new int(1));
    Katalog::DeepPtr<int> ptr2(ptr);
    QVERIFY(&(*ptr) != &(*ptr2));
}

void KatalogTest::DeepPtrValue()
{
    using namespace Katalog;
    Katalog::DeepPtr<int> ptr(new int(1));
    Katalog::DeepPtr<int> ptr1(new int(1));
    QVERIFY(*ptr == *ptr1);
}

void KatalogTest::DeepPtrPolymorphicClassType()
{
    using namespace Katalog;
    class A{
    public:
        virtual ~A() = default;
    };
    class B: public A{
    public:

    };

    DeepPtr<B> ptrB(new B);
    DeepPtr<A> ptr = new B;
    QVERIFY(typeid(*ptrB) == typeid (*ptr));
}

void KatalogTest::DeepPtrPolymorphicClassClone()
{
    using namespace Katalog;
    class A{
    public:
        virtual ~A() = default;
        virtual A* clone() const = 0;
    };
    class B: public A{
    public:
        B* clone() const override {
            return new B(*this);
        }

    };

    DeepPtr<B> ptrB(new B);
    DeepPtr<A> ptr(ptrB->clone());
    DeepPtr<A> ptr3(ptr->clone());
    QVERIFY(typeid(*ptrB) == typeid (*ptr3));
    QVERIFY(typeid(*ptr3) == typeid (*ptr));
}

void KatalogTest::VectorCopyAssignement()
{
    using namespace Katalog;

    Katalog::vector<int> a;
    for (int i = 0; i < 100; i++) {
        a.push_back(i);
    }

    vector<int> b = a;  //copia
    vector<int> c;
    c = a;  //assegnazione

    QVERIFY(a.size() == b.size() && b.size() == c.size() && a.capacity() == b.capacity() && b.capacity() == c.capacity());
    bool verify = true;
    for (u_int i = 0; i < a.size(); ++i) {
        verify &= (a[i] == b[i]);
        verify &= (a[i] == c[i]);
    }
    QVERIFY(verify);
}

void KatalogTest::VectorAppend()
{
    using namespace Katalog;
    vector<int> a;
    vector<int> b;
    for (int i = 0; i < 10; i++) {
        a.push_back(i);
        b.push_back(i);
    }
    a.append(b);
    QVERIFY(a.size() == 20);
    bool verify = true;
    for (int i = 0; i < 10; i++) {
        verify &= (a[i] == i);
        verify &= (a[i + 10] == i);
    }
    QVERIFY(verify);
}

void KatalogTest::VectorInsert()
{
    using namespace Katalog;
    vector<int> a;
    for (int i = 0; i < 10; i++) {
        a.push_back(i);
    }
    a.insert(20, a.begin() + 5);

    QVERIFY(a[5] == 20);
    int b[] = {0,1,2,3,4,20, 5, 6,7,8,9};
    bool verify = true;
    for(u_int i = 0; i < a.size(); i++){
        verify &= (b[i] == a[i]);
    }
    QVERIFY(verify);
}

void KatalogTest::VectorErease()
{
    using namespace Katalog;
    vector<int> a;
    for (int i = 0; i < 10; i++) {
        a.push_back(i);
    }
    a.erase((a.begin() + 4), (a.end() - 3));
    QVERIFY(a.size() == 7);
    int b[] = {0,1,2,3,7,8,9};
    bool verify = true;
    for(u_int i = 0; i < a.size(); i++){
        verify &= (b[i] == a[i]);
    }
    QVERIFY(verify);
}

QTEST_APPLESS_MAIN(KatalogTest)

#include "tst_katalogtest.moc"
