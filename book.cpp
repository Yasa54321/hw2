#include "book.h"
#include <sstream>
#include <iomanip>

using namespace std;

Book::Book(const string name, double price, int qty, const string isbn, const string author)
    : Product("book", name, price, qty), isbn_(isbn), author_(author) {}

Book::~Book() {}

set<string> Book::keywords() const {
    set<string> kws = parseStringToWords(name_);
    set<string> authorKws = parseStringToWords(author_);
    kws = setUnion(kws, authorKws);
    // ISBN is added verbatim (lowercase) without splitting punctuation
    kws.insert(convToLower(isbn_));
    return kws;
}

string Book::displayString() const {
  ostringstream os;
  os << name_ << "\n"
      << "Author: " << author_ << " ISBN: " << isbn_ << "\n"
      << fixed << setprecision(2) << price_ << " " << qty_ << " left.";
  return os.str();
}

void Book::dump(ostream& os) const {
    os << "book\n"
       << name_ << "\n"
       << price_ << "\n"
       << qty_ << "\n"
       << isbn_ << "\n"
       << author_ << "\n";
}