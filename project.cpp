#include <bits/stdc++.h>

using namespace std;

class Product
{
protected:
    string name;
    double price;

public:
    Product(const string &productName, double productPrice)
        : name(productName), price(productPrice) {}

    virtual void display() = 0;

    virtual ~Product() {}
};

class CeramicProduct : public Product
{
private:
    string material;

public:
    CeramicProduct(const string &productName, double productPrice, const string &productMaterial)
        : Product(productName, productPrice), material(productMaterial) {}

    void display() override
    {
        cout << "Ceramic Product: " << name << endl;
        cout << "Price: $" << price << endl;
        cout << "Material: " << material << endl;
    }
};

class InvalidProductException : public exception
{
public:
    const char *what() const throw()
    {
        return "Invalid product. Please enter valid details.";
    }
};

class ProductManager
{
private:
    vector<Product *> products;

public:
    void addProduct(Product *product)
    {
        products.push_back(product);
    }

    void displayAllProducts()
    {
        for (Product *product : products)
        {
            product->display();
            cout << endl;
        }
    }

    Product *selectProduct(int index)
    {
        if (index >= 0 && index < products.size())
        {
            return products[index];
        }
        return nullptr;
    }

    ~ProductManager()
    {
        for (Product *product : products)
        {
            delete product;
        }
    }
};

int main()
{
    try
    {
        ProductManager productManager;

        productManager.addProduct(new CeramicProduct("Vase", 19.99, "Porcelain"));
        productManager.addProduct(new CeramicProduct("Mug", 9.99, "Stoneware"));
        productManager.addProduct(new CeramicProduct("Ceramic Tiles", 29.99, "Terracotta"));
        productManager.addProduct(new CeramicProduct("Plate", 29.99, "Earthenware"));

        productManager.displayAllProducts();

        int productIndex;
        cout << "Select a product (enter the corresponding number): ";
        cin >> productIndex;
        cin.ignore();

        Product *selectedProduct = productManager.selectProduct(productIndex - 1);
        if (selectedProduct == nullptr)
        {
            throw InvalidProductException();
        }

        string customerName;
        string shippingAddress;

        cout << "Enter your name: ";
        getline(cin, customerName);

        cout << "Enter your shipping address: ";
        getline(cin, shippingAddress);

        cout << endl;
        cout << "Order Details:" << endl;
        cout << "-----------------------------" << endl;
        cout << "Product: ";
        selectedProduct->display();
        cout << "Customer: " << customerName << endl;
        cout << "Shipping Address: " << shippingAddress << endl;
    }
    catch (InvalidProductException &ex)
    {
        cout << "Error: " << ex.what() << endl;
    }

    return 0;
}
