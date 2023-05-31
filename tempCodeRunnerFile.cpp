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

    virtual string display() const = 0;

    virtual ~Product() {}
};

class CeramicProduct : public Product
{
private:
    string material;

public:
    CeramicProduct(const string &productName, double productPrice, const string &productMaterial)
        : Product(productName, productPrice), material(productMaterial) {}

    string display() const override
    {
        string details;
        details += "Ceramic Product " + name + "\n";
        details += "Price: $" + to_string(price) + "\n";
        details += "Material: " + material + "\n";
        return details;
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

    void displayAllProducts() const
    {
        for (const Product *product : products)
        {
            cout << product->display() << endl;
        }
    }

    const Product *selectProduct(int index) const
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

        ifstream inputFile("products.txt");
        if (!inputFile)
        {
            cout << "Failed to open input file." << endl;
            return 1;
        }

        string productName;
        double productPrice;
        string productMaterial;

        while (inputFile >> productName >> productPrice >> productMaterial)
        {
            productManager.addProduct(new CeramicProduct(productName, productPrice, productMaterial));
        }
        inputFile.close();

        productManager.displayAllProducts();

        int productIndex;
        cout << "Select a product (enter the corresponding number): ";
        cin >> productIndex;
        cin.ignore();

        const Product *selectedProduct = productManager.selectProduct(productIndex - 1);
        if (selectedProduct == nullptr)
        {
            throw InvalidProductException();a
        }

        string customerName;
        string shippingAddress;
        string contactnumber;

        cout << "Enter your full name: ";
        getline(cin, customerName);

        cout << "Enter your shipping address: ";
        getline(cin, shippingAddress);

        cout << "Enter your contact number: ";
        getline(cin, contactnumber);

        cout << "Your order recorded successfully";

        ofstream outputFile("order_details.txt");
        if (!outputFile)
        {
            cout << "Failed to open output file." << endl;
            return 1;
        }

        outputFile << "Order Details:" << endl;
        outputFile << "-----------------------------" << endl;
        outputFile << "Product: " << selectedProduct->display() << endl;
        outputFile << "Customer: " << customerName << endl;
        outputFile << "Shipping Address: " << shippingAddress << endl;
        outputFile << "Contact Number: " << contactnumber << endl;
        outputFile.close();
    }
    catch (InvalidProductException &ex)
    {
        cout << "Error: " << ex.what() << endl;
    }

    return 0;
}
