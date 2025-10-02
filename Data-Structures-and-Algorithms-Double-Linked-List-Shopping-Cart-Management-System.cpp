#include <iostream>
#include <string>
using namespace std;
struct Node {
    int productID;
    string productName;
    int quantity;
    double price;
    Node* prev;
    Node* next;
    Node(int id, string name, int qty, double p) : productID(id), productName(name), quantity(qty), price(p), prev(nullptr), next(nullptr) {}
};

class ShoppingCart {
private:
    Node* head;
    Node* tail;

public:
    ShoppingCart() : head(nullptr), tail(nullptr) {}
    void addProduct(int id, string name, int qty, double p) {
        Node* newProduct = new Node(id, name, qty, p);
        if (!head) {
            head = tail = newProduct;
        } else {
            tail->next = newProduct;
            newProduct->prev = tail;
            tail = newProduct;
        }
        cout << "Product added: " << name << endl;
    }

    void removeProduct(int id) {
        Node* temp = head;
        while (temp) {
            if (temp->productID == id) {
                if (temp->prev) temp->prev->next = temp->next;
                if (temp->next) temp->next->prev = temp->prev;
                if (temp == head) head = temp->next;
                if (temp == tail) tail = temp->prev;
                delete temp;
                cout << "Product with ID " << id << " removed from cart." << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Product with ID " << id << " not found!" << endl;
    }

    double calculateTotalPrice() {
        double total = 0.0;
        Node* temp = head;
        while (temp) {
            total += temp->quantity * temp->price;
            temp = temp->next;
        }
        return total;
    }
    void displayCart() {
        if (!head) {
            cout << "Cart is empty!" << endl;
            return;
        }
        Node* temp = head;
        cout << "Products in your cart (in order):" << endl;
        while (temp) {
            cout << "ID: " << temp->productID << ", Name: " << temp->productName
                 << ", Quantity: " << temp->quantity << ", Price: " << temp->price << endl;
            temp = temp->next;
        }
    }

    void displayCartReverse() {
        if (!tail) {
            cout << "Cart is empty!" << endl;
            return;
        }
        Node* temp = tail;
        cout << "Products in your cart (reverse order):" << endl;
        while (temp) {
            cout << "ID: " << temp->productID << ", Name: " << temp->productName
                 << ", Quantity: " << temp->quantity << ", Price: " << temp->price << endl;
            temp = temp->prev;
        }
    }
};
int main() {
    ShoppingCart cart;
    int choice = 0;
    while (choice != 6) {
        cout << "\nShopping Cart Menu:" << endl;
        cout << "1. Add Product to Cart" << endl;
        cout << "2. Remove Product from Cart" << endl;
        cout << "3. Display Cart" << endl;
        cout << "4. Display Cart in Reverse Order" << endl;
        cout << "5. Calculate Total Price" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: {
                int id, qty;
                string name;
                double price;
                cout << "Enter Product ID: ";
                cin >> id;
                cout << "Enter Product Name: ";
                cin >> name;
                cout << "Enter Quantity: ";
                cin >> qty;
                cout << "Enter Price: ";
                cin >> price;
                cart.addProduct(id, name, qty, price);
                break;
            }
            case 2: {
                int id;
                cout << "Enter Product ID to remove: ";
                cin >> id;
                cart.removeProduct(id);
                break;
            }
            case 3:
                cart.displayCart();
                break;
            case 4:
                cart.displayCartReverse();
                break;
            case 5:
                cout << "Total Price: $" << cart.calculateTotalPrice() << endl;
                break;
            case 6:
                cout << "Exiting the shopping cart program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
    return 0;
}
