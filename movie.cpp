#include "movie.h"
#include <sstream>
#include <iomanip>

using namespace std;

Movie::Movie(const string name, double price, int qty, const string genre, const string rating)
    : Product("movie", name, price, qty), genre_(genre), rating_(rating) {}

Movie::~Movie() {}

set<string> Movie::keywords() const {
    set<string> kws = parseStringToWords(name_);
    // Genre is added verbatim (lowercase) without splitting punctuation
    kws.insert(convToLower(genre_));
    return kws;
}

string Movie::displayString() const {
    ostringstream os;
    os << name_ << "\n"
       << "Genre: " << genre_ << " Rating: " << rating_ << "\n"
       << fixed << setprecision(2) << price_ << " " << qty_ << " left.";
    return os.str();
}

void Movie::dump(ostream& os) const {
    os << "movie\n"
       << name_ << "\n"
       << price_ << "\n"
       << qty_ << "\n"
       << genre_ << "\n"
       << rating_ << "\n";
}