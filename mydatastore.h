#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include "product.h"
#include "user.h"
#include "util.h"
#include <map>
#include <set>
#include <vector>
#include <string>
#include <iostream>

class MyDataStore : public DataStore {
public:
    MyDataStore();
    ~MyDataStore();

    /**
     * Inherited interface methods from DataStore
     */
    void addProduct(Product* p);
    void addUser(User* u);
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    void dump(std::ostream& ofile);

    /**
     * Custom helper methods for menu commands
     */
    void addToCart(const std::string& username, Product* p);
    void viewCart(const std::string& username);
    void buyCart(const std::string& username);

private:
    std::vector<Product*> products_;
    std::map<std::string, User*> users_;                                // Case-insensitive lookup (lowercase username -> User*)
    std::map<std::string, std::set<Product*>> keywordIndex_;            // Keyword (lowercase) -> Set of matching products
    std::map<std::string, std::vector<Product*>> carts_;               // Case-insensitive lookup (lowercase username -> FIFO Cart)
};

#endif