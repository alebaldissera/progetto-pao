#include <QtTest>
#include <typeinfo>
// add necessary includes here

#include "../Katalog/DeepPtr.h"
//#include "../Katalog/Vector.h"

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
    QVERIFY(true);
}

QTEST_APPLESS_MAIN(KatalogTest)
//QTEST_MAIN(KatalogTest)

#include "tst_katalogtest.moc"
