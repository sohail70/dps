#include <iostream>
// Explanation: a square clearly is a type of rectangle in the real world whether we can model this in our code depends on the  
// spec. what the LSP indicates is that subtype behavior should match base type behavior as defined in the base type specification.
// if the rectangle base type spec says that height and width can be set independently, then LSP says that square can not be
// a subtype of rectangle. if the rectangle spec says that a rectangle is immutablr, then a square can be a subtype of rectangle.
// it's all about subtypes maintaining the behavior specified for the base type.

//about immutability : https://benlast.livejournal.com/30085.html
class Rectangle
{
    protected:
        int width, height;
    public:
        Rectangle(const int width, const int height)
            :width(width) , height(height)
        {}

        virtual int getWidth() const
        {
                return width;
        }

        virtual void setWidth(const int width)
        {
            this->width = width;
        }

        virtual int getHeight() const
        {
            return height;
        }
        virtual void setHeight(const int height)
        {
            this->height = height;
        }

        int area() const {return width*height; }
};

class Square : public Rectangle //not good: this means square should be usable anywhere you expect a Rectangle-->
//strange behavior in setWidth and setHeight because setting one would change the other one to match it --> LSP violation
{
    public:
    Square(int size) : Rectangle{size,size}
    {}
    void setWidth(const int width) override{
        this->width = height = width; //because It's square
    }
    void setHeight(const int height) override{
        this->height = width = height; 
    }

};


void process (Rectangle& r)
{
    int w = r.getWidth();
    r.setHeight(10);
    std::cout <<"expect area = " << (w*10)
        << " , got " <<r.area()<< std::endl;
}

int main()
{
    Rectangle r{5,5};
    process(r);


    Square s{5};
    process(s); //you can process square because of polymorphism
    return 0; 
}

//solution :one way is to use rectangle factory --> never have the square class at all