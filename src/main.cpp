#include <cstdarg>
#include <iostream>
#include <list>
#include <sstream>
using namespace std;


struct Entity {
    virtual string getName() const = 0;
    friend ostream& operator<<(ostream& out, const Entity& current)
    {
        return out << current.getName() << "{" << &current << "}";
    }
};


struct AbstractProvider: Entity {};

struct FilledBufferProvider : AbstractProvider {
    string getName() const final override
    {
        return "FilledBufferProvider";
    }
};

struct InstantDataProvider : AbstractProvider {
    string getName() const final override
    {
        return "InstantDataProvider";
    }
};

struct AbstractSupplier: Entity {};

struct DiskWriter : AbstractSupplier {
    string getName() const final override
    {
        return "DiskWriter";
    }
};

struct Eraser: AbstractSupplier {
    string getName() const final override
    {
        return "Eraser";
    }
};

class StreamWritter {
public:
    template <typename... T>
    void setMapping(const AbstractProvider& provider, const AbstractSupplier& supplier, const T&... otherSuppliers)
    {
        setMapping(provider, supplier);
        setMapping(provider, otherSuppliers...);
    }
    void setMapping(const AbstractProvider& provider, const AbstractSupplier& supplier)
    {
        cout << "data from " << provider << " will be processed by " << supplier << endl;
    }
};

int main(int argc, char* argv[])
{
    cout << "stream-writter started" << endl;
    FilledBufferProvider first;
    InstantDataProvider second;
    DiskWriter s1, s2;
	Eraser s3;

    StreamWritter streamWritter;
    streamWritter.setMapping(first, s1, s2);
    streamWritter.setMapping(second, s1, s3);

    cout << "stream-writter stopped" << endl;
    return 0;
}