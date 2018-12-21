#include <iostream>
#include <vector>
#include <string>
enum class Color {RED , GREEN , BLUE};
enum class Size {SMALL , MEDIUM , LARGE};


struct Product
{
    std::string _name;
    Color _color;
    Size _size;
};



//(((((((((((((((((((((((((((((Bad Design)))))))))))))))))))))))))))))
struct ProductFilter //replicating is not good (modification is bad, but extending is good) ,
// if you need to add more filters you have to change the class which is not good!
{
    typedef std::vector <Product *> Items;
    //color filter
    static Items byColor (Items _items, Color _color)
    {   
        Items result;
        for (auto& i: _items)
            if (i->_color == _color)
                result.push_back(i);
        return result;
    }

    //size filter
    static Items bySize (Items _items, Size _size)
    {   
        Items result;
        for (auto& i: _items)
            if (i->_size == _size)
                result.push_back(i);
        return result;
    }

    //color and size
    static Items byColorAndSize (Items _items, Size _size, Color _color)
    {   
        Items result;
        for (auto& i: _items)
            if (i->_size == _size && i->_color ==_color)
                result.push_back(i);
        return result;
    }

    // what about more filters! --> complexity will go up and up
};





//((((((((((((((((((((((((((((((Good Design))))))))))))))))))))))))))))))))))))
// 1 and 2 is templated  pure virtual class,
// 3-4-5 implements 1 and 2 ,
// 6 is just a templated class (not pure virtual class)


//Specification interface -->is the condition satisfied?
// 1 - interface for any spec T
template <typename T>
struct ISpecification
{
    virtual bool isSatisfied(T* item) = 0 ;
};
 
//General filter (not just for product)
// 2 - interface for filtering any thing
template <typename T>
struct IFilter
{
    virtual std::vector<T*> filter (std::vector<T*> items , ISpecification<T>& spec);
};

// 3 - product filter which is a IFilter
struct betterFilter : IFilter<Product> //betterFilter implements the IFilter--> for product
{
    typedef std::vector <Product*> Items;
    Items filter(Items items , ISpecification<Product>& spec) override{
        Items result;
        for(auto& p : items)
            if (spec.isSatisfied(p))
                result.push_back(p);
        return result;
    }
    
};

// 4 - product spec which is a ISpec
struct colorSpec : ISpecification<Product>  //ISpec is generic-->for product
{
    Color color;
    explicit colorSpec(const Color color)
        :color(color)
    {}
    bool isSatisfied(Product* item) override{
        return item->_color == color;
    }
};


// 5 - we can add more specification without altering any class
struct sizeSpec : ISpecification<Product>
{   
    Size size;
    explicit sizeSpec(const Size size)
        :size(size)
    {}
    bool isSatisfied(Product* item) override{
        return item->_size ==size;
    }
};
// 6 - what about adding "and spec" --> ex: color and size 
template <typename T>
struct ANDSpecification : ISpecification<T> //and spec is also a Ispec which we override the isSatisfied
{   
    ISpecification<T>& first;
    ISpecification<T>& second;
    explicit ANDSpecification(ISpecification<T>& first , ISpecification<T>& second)
        :first(first) , second(second)
    {}
    bool isSatisfied(T* item) override{ //new isSatisfied
        return first.isSatisfied(item) && second.isSatisfied(item); //using the old isSatisfied!
    }
};



int main()
{
    // Bad Design test
    /*
    Product apple {"apple" , Color::RED , Size::SMALL};
    Product desk {"desk" , Color::RED, Size::LARGE};
    std::vector<Product*> all = {&apple , &desk};
    auto filtered = ProductFilter::byColor(all, Color::RED);
    for (auto& i:filtered)
        std::cout<< i->_name <<" is Blue"<<std::endl;
    */

    //Good Design test
    Product shirt {"shirt" , Color::BLUE , Size::MEDIUM};
    Product bag {"bag" , Color::RED , Size::SMALL};
    Product pen {"pen" , Color::GREEN , Size::SMALL};
    std::vector<Product*> all = {&shirt , &bag, &pen};
    betterFilter bf;
    
    colorSpec green{Color::GREEN};
    auto colorFiltered = bf.filter(all, green);
    for (auto& p : colorFiltered)
       std::cout << p ->_name <<" is green" <<std::endl;

    sizeSpec small{Size::SMALL};
    auto sizeFiltered = bf.filter(all , small);
    for (auto& p: sizeFiltered)
        std::cout << p->_name <<" is small" << std::endl;


    //AndSpec
    ANDSpecification<Product> smallAndGreen{small,green};
    auto greenSmall = bf.filter(all,smallAndGreen);
     for (auto& p : colorFiltered)
       std::cout << p ->_name <<" is green and small" <<std::endl;
}