// Interface Segregation Principle

// No client should be forced to depend on methods it does not use
#include <iostream>
#include <vector>
  
struct Document;


// ((((((((((((Without breaking the interface))))))))))))

/*
 *   struct IMachine
 *   {
 *       virtual void print(std::vector<Document*> docs) = 0;
 *       virtual void scan(std::vector<Document*> docs) = 0;
 *       virtual void fax(std::vector<Document*> docs) = 0;
 *   };
 *
 *   //bad Idea : why?
 *   // 1: If you want to change 1 functionality (like print) --> you would have to recompile
 *   // 2: client doesnt need all of it --> he just want print and doesnt want to implement other funcs
 *
 *   struct MFP : IMachine
 *   {
 *       void print(std::vector<Document*> docs) override;
 *       void scan(std::vector<Document*> docs) override;
 *       void fax(std::vector<Document*> docs) override;
 *   };
 *
 */
//((((((((((((((((((((((((ISP))))))))))))))))))))))))))

struct IPrinter
{
    virtual void print(std::vector<Document*> docs) = 0;
};

struct IScanner
{
    virtual void scan(std::vector<Document*> docs) = 0;
};


struct Printer : IPrinter
{
    void print(std::vector<Document*> docs) override;
};

struct Scanner : IScanner
{
    void scan(std::vector<Document*> docs) override;
};

//For the whole machine
struct IMachine : IPrinter , IScanner {};

struct Machine : IMachine //Machine is a decorator and aggregates the printer and scanner
{
    IPrinter& printer;
    IScanner& scanner;

    Machine(IPrinter& printer , IScanner& scanner)
        : printer(printer),
          scanner(scanner)
    {}
    void print(std::vector<Document*> docs) override{
        printer.print(docs);
    }
    void scan(std::vector<Document*> docs) override{
        scanner.scan(docs);
    }
};

//Now you can build your own printer and implement IPrinter and use it in Machine which uses any IPrinter (sohail's printer, printer, ...)
// and do not worry about implementing the scanner too!
