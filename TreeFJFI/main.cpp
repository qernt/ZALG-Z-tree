#include <iostream>
#include <string>

struct Product
{
    int cost = 0;
    std::string nameOfProduct = "";
    Product *left = nullptr;
    Product *right = nullptr;
};

Product *tree = nullptr;

void addNewProduct(Product *&p, std::string name, int value)
{
    if (p == nullptr)
    {
        p = new Product;
        p->cost = value;
        p->nameOfProduct = name;
        p->left = nullptr;
        p->right = nullptr;
    }
    else if (p->cost == value && p->nameOfProduct != name)
    {
        addNewProduct(p->left, name, value);
    }
    else if (value < p->cost)
    {
        addNewProduct(p->left, name, value);
    }
    else
    {
        addNewProduct(p->right, name, value);
    }
}

void find (Product *top, int value)
{
    Product *p = top;
    while (p != nullptr && p->cost != value)
    {
        if (value < p->cost)
            p = p->left;
        else
            p = p->right;
    }
    if(p == nullptr)
        std::cout << "We don't have a car for this price ¯|_(ツ)_/¯" << std::endl;
    else if(p->left != nullptr)
    {
        std::cout << "We have: " << p->nameOfProduct << std::endl;
        if(p->left->cost == value) find(p->left, value);
    }else
    {
        std::cout << "We have: " << p->nameOfProduct << std::endl;
    }
}


Product *unlink (Product *&p)
{
    if (p->right != nullptr)
    {
        return unlink (p->right);
    }
    else
    {
        Product *v = p;
        p = p->left;
        return v;
    }
}

void removeProduct(Product *&p, int value)
{
    if (p == nullptr)
    {
        std::cout << "Error of product removing" << std::endl;
    }
    else if (value < p->cost)
    {
        removeProduct(p->left, value);
    }
    else if (value > p->cost)
    {
        removeProduct(p->right, value);
    }
    else
    {
        Product *t = p;
        if (p->left == nullptr)
        {
            p = p->right;
        }
        else if (p->right == nullptr)
        {
            p = p->left;
        }
        else
        {
            Product *p2 = unlink (p->left);
            p2->left = p->left;
            p2->right = p->right;
            p = p2;
        }
        delete t;
    }
}

void print(Product *p, int level = 1) {
    if (p!=nullptr) {
        print(p->left, level+1);

        for (int i = 2; i <=level; i++)
        {
            std::cout << "---- ";
        }
        std::cout << p->nameOfProduct << " for " << p->cost << std::endl;

        print(p->right, level+1);
    }
}


int main()
{
    addNewProduct(tree, "Audi", 50000);
    addNewProduct(tree, "BMW", 60000);
    addNewProduct(tree, "Jac", 5000);
    addNewProduct(tree, "BoratCar", 100000);
    addNewProduct(tree, "Lamborgambr", 200000);
    addNewProduct(tree, "Lada", 1000);
    addNewProduct(tree, "Lada2", 1000);
    addNewProduct(tree, "Lada3", 1000);
    
    removeProduct(tree, 100);
    
    print(tree);
    
    int money = 0;
    
    std::cout << "How much money do you have?" << std::endl;
    std::cin >> money;
    
    find(tree, money);
}
