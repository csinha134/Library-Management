#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Product {
private:
    int pno;
    std::string name;
    std::string brand;
    float price, qty, tax, dis;

public:
    void createProduct() {
        std::cout << "Please Enter the Product Number: ";
        std::cin >> pno;
        std::cout << "Please Enter the Brand of the item: ";
        std::cin.ignore();
        std::getline(std::cin, brand);
        std::cout << "Please Enter the Description of the item: ";
        std::getline(std::cin, name);
        std::cout << "Please Enter the Price of the item: ";
        std::cin >> price;
        std::cout << "Please Enter the discount (%): ";
        std::cin >> dis;
    }

    void showProduct() {
        std::cout << "Product no. Of the product: " << pno << std::endl;
        std::cout << "Brand of the product is: " << brand << std::endl;
        std::cout << "Price Of the product is: " << price << std::endl;
        std::cout << "Discount: " << dis << std::endl;
    }

    int getNumber() { return pno; }
    float getPrice() { return price; }
    const std::string& getName() { return name; }
    const std::string& getBrand() { return brand; }
    int getDiscount() { return dis; }
};

std::fstream file;
std::vector<Product> products;

void writeProduct() {
    file.open("Stationery.dat", std::ios::app | std::ios::binary);
    Product prod;
    prod.createProduct();
    file.write(reinterpret_cast<char*>(&prod), sizeof(Product));
    file.close();
    std::cout << "\nThe product has been created." << std::endl;
}

void displayAll() {
    std::cout << "ALL RECORDS" << std::endl << std::endl;
    file.open("Stationery.dat", std::ios::in | std::ios::binary);
    Product prod;
    while (file.read(reinterpret_cast<char*>(&prod), sizeof(Product))) {
        prod.showProduct();
        std::cout << "\n-------------\n";
    }
    file.close();
}

void displaySpecificProduct(int n) {
    file.open("Stationery.dat", std::ios::in | std::ios::binary);
    Product prod;
    bool found = false;
    while (file.read(reinterpret_cast<char*>(&prod), sizeof(Product))) {
        if (prod.getNumber() == n) {
            prod.showProduct();
            found = true;
        }
    }
    file.close();
    if (!found) {
        std::cout << "\n\nRecord does not exist" << std::endl;
    }
}

void modifyProduct() {
    int no;
    bool found = false;
    std::cout << "\n\nPlease enter the product No. of the Product: ";
    std::cin >> no;
    file.open("Stationery.dat", std::ios::in | std::ios::out | std::ios::binary);
    Product prod;
    while (file.read(reinterpret_cast<char*>(&prod), sizeof(Product)) && !found) {
        if (prod.getNumber() == no) {
            prod.showProduct();
            std::cout << "\nPlease Enter the New Details of product" << std::endl;
            prod.createProduct();
            int pos = -static_cast<int>(sizeof(Product));
            file.seekp(pos, std::ios::cur);
            file.write(reinterpret_cast<char*>(&prod), sizeof(Product));
            std::cout << "\n\nRecord Updated" << std::endl;
            found = true;
        }
    }
    if (!found) {
        std::cout << "\n\nRecord Not Found" << std::endl;
    }
    file.close();
}

void deleteProduct() {
    int no;
    std::cout << "\n\n\nDelete Record" << std::endl;
    std::cout << "Please Enter the Product no. Of the Product you want to Delete: ";
    std::cin >> no;
    file.open("Stationery.dat", std::ios::in | std::ios::out | std::ios::binary);
    std::fstream tempFile("Temp.dat", std::ios::out | std::ios::binary);
    Product prod;
    while (file.read(reinterpret_cast<char*>(&prod), sizeof(Product))) {
        if (prod.getNumber() != no) {
            tempFile.write(reinterpret_cast<char*>(&prod), sizeof(Product));
        }
    }
    tempFile.close();
    file.close();
    std::remove("Stationery.dat");
    std::rename("Temp.dat", "Stationery.dat");
    std::cout << "\n\nRecord Deleted" << std::endl;
}

void displayMenu() {
    file.open("Stationery.dat", std::ios::in | std::ios::binary);
    if (!file) {
        std::cout << "ERROR: FILE COULD NOT BE OPEN" << std::endl;
        std::cout << "GO TO ADMIN MENU TO CREATE FILE" << std::endl;
        std::cout << "Program is Closing..." << std::endl;
        std::cin.get();
        exit(0);
    }

    std::cout << "\nProduct MENU" << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "P.NO.\tNAME\tBRAND\tPRICE" << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;

    Product prod;
    while (file.read(reinterpret_cast<char*>(&prod), sizeof(Product))) {
        std::cout << prod.getNumber() << "\t" << prod.getName() << "\t" << prod.getBrand() << "\t" << prod.getPrice() << std::endl;
    }
    file.close();
}

void placeOrder() {
    int order_arr[50], quan[50], c = 0;
    float amt, amt1, total = 0;
    char ch;
    displayMenu();
    std::cout << "\n----------------------------------------------------" << std::endl;
    std::cout << "PLACE YOUR ORDER" << std::endl;
    std::cout << "----------------------------------------------------" << std::endl;

    do {
        std::cout << "Enter the Product No.: ";
        std::cin >> order_arr[c];
        std::cout << "Quantity: ";
        std::cin >> quan[c];
        c++;

        std::cout << "Do You Wish To Order Another Product? (y/n): ";
        std::cin >> ch;
    } while (ch == 'y' || ch == 'Y');

    std::cout << "\nThank You For Placing The Order." << std::endl;
    std::cout << "**********************************INVOICE***********************************************" << std::endl;
    std::cout << "PrNo\tPrName\tQuantity\tCOST\tAmount\tDISCOUNT" << std::endl;

    for (int x = 0; x < c; x++) {
        file.open("Stationery.dat", std::ios::in | std::ios::binary);
        Product prod;
        while (file.read(reinterpret_cast<char*>(&prod), sizeof(Product))) {
            if (prod.getNumber() == order_arr[x]) {
                amt = prod.getPrice() * quan[x];
                amt1 = amt - (amt * prod.getDiscount() / 100);

                std::cout << order_arr[x] << "\t" << prod.getName() << "\t" << quan[x] << "\t" << prod.getPrice()
                          << "\t" << amt << "\t" << amt1 << std::endl;

                total += amt1;
            }
        }
        file.close();
    }

    std::cout << "TOTAL = " << total << std::endl << std::endl;
    std::cin.get();
}

void adminMenu() {
    char ch, c;
    do {
        std::cout << "ADMIN MENU" << std::endl;
        std::cout << "1. CREATE PRODUCT" << std::endl;
        std::cout << "2. DISPLAY ALL PRODUCTS" << std::endl;
        std::cout << "3. QUERY" << std::endl;
        std::cout << "4. MODIFY PRODUCT" << std::endl;
        std::cout << "5. DELETE PRODUCT" << std::endl;
        std::cout << "6. VIEW PRODUCT MENU" << std::endl;
        std::cout << "7. EXIT" << std::endl;
        std::cout << "Enter your option: ";
        std::cin >> ch;

        switch (ch) {
            case '1':
                writeProduct();
                break;
            case '2':
                displayAll();
                break;
            case '3':
                int num;
                std::cout << "\nPlease Enter the Product No.: ";
                std::cin >> num;
                displaySpecificProduct(num);
                break;
            case '4':
                modifyProduct();
                break;
            case '5':
                deleteProduct();
                break;
            case '6':
                displayMenu();
                break;
            case '7':
                std::cout << "PROGRAM TERMINATED" << std::endl;
                exit(0);
            default:
                std::cout << "Please Enter your Choice b/w (1-7)" << std::endl;
        }

        std::cout << "Do you wish to continue? (y/n): ";
        std::cin >> c;
    } while (c == 'y' || c == 'Y');
}

int main() {
    char ch, c;
    do {
        std::cout << "MAIN MENU" << std::endl << std::endl;
        std::cout << "1. CUSTOMER" << std::endl;
        std::cout << "2. ADMINISTRATOR" << std::endl;
        std::cout << "3. EXIT" << std::endl << std::endl;
        std::cout << "Enter your option: ";
        std::cin >> ch;

        switch (ch) {
            case '1':
                placeOrder();
                std::cin.get();
                break;
            case '2':
                std::string pass;
                std::cout << "Please Enter The Password: ";
                std::cin >> pass;
                if (pass == "stationery") {
                    adminMenu();
                }
                break;
            case '3':
                std::cout << "PROGRAM TERMINATED" << std::endl;
                exit(0);
            default:
                std::cout << "Please Select your Option b/w (1-3)" << std::endl;
        }

        std::cout << "Do you wish to continue? (y/n): ";
        std::cin >> c;
    } while (c == 'y' || c == 'Y');

    return 0;
}
