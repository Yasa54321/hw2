#include "clothing.h"
#include <sstream>
#include <iomanip>

using namespace std;

Clothing::Clothing(const string name, double price, int qty, const string size, const string brand)
    : Product("clothing", name, price, qty), size_(size), brand_(brand)
{
}

Clothing::~Clothing()
{
}

set<string> Clothing::keywords() const
{
    set<string> nameWords = parseStringToWords(name_);
    set<string> brandWords = parseStringToWords(brand_);
    set<string> kws = setUnion(nameWords, brandWords);
    return kws;
}

string Clothing::displayString() const
{
    ostringstream os;
    os << name_ << "\n"
       << "Size: " << size_ << " Brand: " << brand_ << "\n"
       << fixed << setprecision(2) << price_ << " " << qty_ << " left.";
    return os.str();
}

void Clothing::dump(ostream& os) const
{
    os << category_ << "\n"
       << name_ << "\n"
       << price_ << "\n"
       << qty_ << "\n"
       << size_ << "\n"
       << brand_ << "\n";
}