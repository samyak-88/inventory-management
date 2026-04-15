#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

class Product {
public:
    int id;
    string name;
    int quantity;
    double price;

    Product(int i, string n, int q, double p) {
        id = i;
        name = n;
        quantity = q;
        price = p;
    }
};

vector<Product> products;

void loadProducts() {
    ifstream file("../data/products.csv");
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string id, name, qty, price;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, qty, ',');
        getline(ss, price, ',');

        if (id != "") {
            products.push_back(Product(stoi(id), name, stoi(qty), stod(price)));
        }
    }
}

void saveProducts() {
    ofstream file("../data/products.csv");

    for (auto &p : products) {
        file << p.id << "," << p.name << ","
             << p.quantity << "," << p.price << "\n";
    }
}

void addProduct() {
    int id, qty;
    string name;
    double price;

    cout << "ID: "; cin >> id;
    cout << "Name: "; cin >> name;
    cout << "Qty: "; cin >> qty;
    cout << "Price: "; cin >> price;

    products.push_back(Product(id, name, qty, price));
}

void restock() {
    int id, amt;
    cout << "ID: "; cin >> id;
    cout << "Amount: "; cin >> amt;

    for (auto &p : products) {
        if (p.id == id) {
            p.quantity += amt;
            cout << "Restocked\n";
            return;
        }
    }
}

void sell() {
    int id, qty;
    double discount;

    cout << "ID: "; cin >> id;
    cout << "Qty: "; cin >> qty;
    cout << "Discount: "; cin >> discount;

    for (auto &p : products) {
        if (p.id == id && p.quantity >= qty) {
            double total = p.price * qty - discount;
            p.quantity -= qty;
            cout << "Total: " << total << endl;
            return;
        }
    }

    cout << "Error\n";
}

void view() {
    for (auto &p : products) {
        cout << p.id << " | " << p.name
             << " | " << p.quantity
             << " | " << p.price << endl;
    }
}

int main() {
    loadProducts();

    int ch;

    while (true) {
        cout << "\n1.Add 2.Restock 3.Sell 4.View 5.Exit\n";
        cin >> ch;

        if (ch == 1) addProduct();
        else if (ch == 2) restock();
        else if (ch == 3) sell();
        else if (ch == 4) view();
        else if (ch == 5) {
            saveProducts();
            break;
        }
    }
}
