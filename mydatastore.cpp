#include "mydatastore.h"
#include <iostream>

using namespace std;

MyDataStore::MyDataStore() {}

MyDataStore::~MyDataStore() {
    // Delete all dynamically allocated products
    for (size_t i = 0; i < products_.size(); ++i) {
        delete products_[i];
    }

    // Delete all dynamically allocated users
    for (map<string, User*>::iterator it = users_.begin(); it != users_.end(); ++it) {
        delete it->second;
    }
}

void MyDataStore::addProduct(Product* p) {
    products_.push_back(p);

    // Index product by all of its keywords
    set<string> kws = p->keywords();
    for (set<string>::iterator it = kws.begin(); it != kws.end(); ++it) {
        keywordIndex_[*it].insert(p);
    }
}

void MyDataStore::addUser(User* u) {
    string lowerName = convToLower(u->getName());
    
    // Store user and initialize empty cart
    users_[lowerName] = u;
    carts_[lowerName] = vector<Product*>();
}

vector<Product*> MyDataStore::search(vector<string>& terms, int type) {
    vector<Product*> results;
    if (terms.empty()) return results;

    set<Product*> matchingSet;
    bool firstValidTerm = true;

    for (size_t i = 0; i < terms.size(); ++i) {
        string term = convToLower(terms[i]);
        set<Product*> termSet;

        if (keywordIndex_.find(term) != keywordIndex_.end()) {
            termSet = keywordIndex_[term];
        }

        if (firstValidTerm) {
            matchingSet = termSet;
            firstValidTerm = false;
        } else {
            if (type == 0) { // AND Search
                matchingSet = setIntersection(matchingSet, termSet);
            } else {        // OR Search
                matchingSet = setUnion(matchingSet, termSet);
            }
        }
    }

    // Convert result set to vector
    for (set<Product*>::iterator it = matchingSet.begin(); it != matchingSet.end(); ++it) {
        results.push_back(*it);
    }

    return results;
}

void MyDataStore::dump(ostream& ofile) {
    ofile << "<products>\n";
    for (size_t i = 0; i < products_.size(); ++i) {
        products_[i]->dump(ofile);
    }
    ofile << "</products>\n";

    ofile << "<users>\n";
    for (map<string, User*>::iterator it = users_.begin(); it != users_.end(); ++it) {
        it->second->dump(ofile);
    }
    ofile << "</users>\n";
}

void MyDataStore::addToCart(const string& username, Product* p) {
    string lowerName = convToLower(username);
    if (users_.find(lowerName) == users_.end()) {
        cout << "Invalid request" << endl;
        return;
    }

    // FIFO order using vector push_back
    carts_[lowerName].push_back(p);
}

void MyDataStore::viewCart(const string& username) {
    string lowerName = convToLower(username);
    if (users_.find(lowerName) == users_.end()) {
        cout << "Invalid username" << endl;
        return;
    }

    const vector<Product*>& cart = carts_[lowerName];
    for (size_t i = 0; i < cart.size(); ++i) {
        cout << "Item " << (i + 1) << "\n" << cart[i]->displayString() << "\n" << endl;
    }
}

void MyDataStore::buyCart(const string& username) {
    string lowerName = convToLower(username);
    if (users_.find(lowerName) == users_.end()) {
        cout << "Invalid username" << endl;
        return;
    }

    User* u = users_[lowerName];
    vector<Product*>& cart = carts_[lowerName];
    vector<Product*> unpurchased;

    for (size_t i = 0; i < cart.size(); ++i) {
        Product* p = cart[i];

        // Buy if in stock AND user has sufficient balance
        if (p->getQty() >= 1 && u->getBalance() >= p->getPrice()) {
            p->subtractQty(1);
            u->deductAmount(p->getPrice());
        } else {
            // Keep in cart in FIFO order
            unpurchased.push_back(p);
        }
    }

    cart = unpurchased;
}