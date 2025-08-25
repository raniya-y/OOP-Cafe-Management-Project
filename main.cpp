#include <iostream>
#include <string>

using namespace std;

// Abstract base class for menu items
class MenuItem
{
    public:
        virtual void display() = 0;  // Pure virtual function to display menu item details
        virtual double getPrice() = 0;  // Pure virtual function to get the price of the item
};

// Derived class for food items
class FoodItem : public MenuItem
{
    private:
        string name;
        double price;

    public:
        FoodItem(string name, double price): name(name), price(price) {}

        void display() override
        {
            cout << name << "................... Rs." << price << endl;
        }

        double getPrice() override
        {
            return price;
        }
};

// Derived class for beverage items
class BeverageItem : public MenuItem
{
    private:
        string name;
        double price;

    public:
        BeverageItem(string name, double price): name(name), price(price) {}

        void display() override
        {
            cout << name << " ................... Rs." << price << endl;
        }

        double getPrice() override
        {
            return price;
        }
};

// Cafe class (Base class)
class Cafe
{
    public:
        static int customerCount;  // Static member variable for counting customers
        MenuItem* menuItems[19];   // Array of pointers to menu items (fixed size 19)
        double taxRate = 0.1;      // Default tax rate

        Cafe()
        {
            // Adding menu items
            menuItems[0] = new BeverageItem("Coffee", 450);
            menuItems[1] = new BeverageItem("Latte", 500);
            menuItems[2] = new BeverageItem("Cappuccino", 475);
            menuItems[3] = new BeverageItem("French Vanilla", 600);
            menuItems[4] = new BeverageItem("Earl Grey Tea", 300);
            menuItems[5] = new BeverageItem("Espresso", 250);
            menuItems[6] = new BeverageItem("Hot Chocolate", 150);
            menuItems[7] = new BeverageItem("Chai Tea", 150);
            menuItems[8] = new BeverageItem("Iced Americano", 200);
            menuItems[9] = new BeverageItem("Iced Latte", 150);
            menuItems[10] = new BeverageItem("Strawberry Refresher", 400);
            menuItems[11] = new BeverageItem("Blueberry Mint Lemonade", 400);
            menuItems[12] = new BeverageItem("Raspberry Mint Lemonade", 400);

            menuItems[13] = new FoodItem("Strawberry Shortcake", 1200);
            menuItems[14] = new FoodItem("Red Velvet Cake", 1400);
            menuItems[15] = new FoodItem("Chocolate Chip Cookie", 700);
            menuItems[16] = new FoodItem("Brownies", 600);
            menuItems[17] = new FoodItem("Apple Pie", 800);
            menuItems[18] = new FoodItem("Blueberry Muffin", 500);
        }

        virtual void displayMenu()
        {
            cout << "\nCafe Menu:\n";
            for (int i = 0; i < 19; ++i)
            {
                cout << i + 1 << "\t";
                menuItems[i]->display();
            }
        }

        static void increaseCustom()
        {
            customerCount++;
        }

        virtual ~Cafe()
        {
            for (int i = 0; i < 19; ++i)
            {
                delete menuItems[i];
            }
        }
};

 int Cafe::customerCount = 0;  // Initialize static member variable

// Cashier class (Derived from Cafe)
class Cashier : public Cafe
{
    private:
        string orderID;

    public:
        Cashier(string orderID) : orderID(orderID) {}

        void calculateTotal(MenuItem* orderItems[], int itemCount)
        {
            double total = 0;
            cout << "\nYour cashier today: " << orderID << endl;
            for (int i = 0; i < itemCount; ++i)
            {
                total += orderItems[i]->getPrice();
            }

            double taxAmount = total * taxRate;

            double finalTotal = total + taxAmount;

            cout << "Total before tax: Rs." << total << endl;
            cout << "Tax: Rs." << taxAmount << endl;
            cout << "Final Total: Rs." << finalTotal << endl;
        }
};

// Customer class (Derived from Cafe)
class Customer : public Cafe
{
    private:
        string customerName;

    public:
        Customer(string name) : customerName(name)
        {
            increaseCustom();
        }

        void displayMenu() override
        {
            cout << "\nWelcome " << customerName << "! You are customer number " << customerCount << ". Here's the menu:\n\n";
            for (int i = 0; i < 19; ++i)
            {
                cout << i + 1 << ".  ";
                menuItems[i]->display();
            }
        }
};
// Template class to handle orders
template <typename T>
class Order
{
public:
    T orderID;
    string customerName;
    MenuItem* items[10];
    int itemCount;

    Order(T orderID, string customerName) : orderID(orderID), customerName(customerName), itemCount(0) {}

    void addItem(MenuItem* item)
    {
        if (itemCount < 10)
        {
            items[itemCount++] = item;
        }
        else
        {
            cout << "Error: Order is full. Cannot add more items." << endl;
        }
    }

    void displayOrder()
    {
        cout << "\nOrder ID: " << orderID << ", Customer: " << customerName << endl;
        for (int i = 0; i < itemCount; ++i)
        {
            items[i]->display();
        }
    }
};

int main()
{
    string name;
    int itemChoice;
    MenuItem* customerOrder[10];
    int orderItemCount = 0;

    try
    {
        while (true)
        {
                if (Cafe::customerCount >= 5)
                {
                    throw "Customer limit exceeded. Cafe is now closed.";
                }

                cout << "\nWelcome to the Cafe Management System!" << endl;
                cout << "Enter your name: ";
                getline(cin, name);

                Customer customer(name);
                customer.displayMenu();

                Order<int> order1(Cafe::customerCount, name);

                orderItemCount = 0;

                while (true)
                {
                    cout << "\nEnter the number of the item you want to order (0 to finish): ";
                    cin >> itemChoice;
                    cin.ignore();

                    if (itemChoice == 0)
                    {
                        break;
                    }
                    else if (itemChoice > 0 && itemChoice <= 19)
                    {
                        customerOrder[orderItemCount++] = customer.menuItems[itemChoice - 1];
                        order1.addItem(customer.menuItems[itemChoice - 1]);
                        cout << "Item added to order!" << endl;
                    }
                    else if ((itemChoice >= 'a' && itemChoice <= 'z') || (itemChoice >= 'A' && itemChoice <= 'Z'))
                    {
                        cout << "Please enter a number." << endl;
                    }
                    else
                    {
                        cout << "Invalid menu choice. Please try again." << endl;
                    }
                }

            order1.displayOrder();

            Cashier cashier("Cashier O45");
            cashier.calculateTotal(customerOrder, orderItemCount);

            cout << "\n--- Next Customer ---" << endl;
        }
    }

    catch (const char* message)
    {
        cout << "\nException: " << message << endl;
        cout << "Program terminated." << endl;
    }

    return 0;
}
