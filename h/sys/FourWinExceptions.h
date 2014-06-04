#ifndef FOURWINEXCEPTIONS_H
#define FOURWINEXCEPTIONS_H

#endif // FOURWINEXCEPTIONS_H

struct EingabeException:public exception{
    std::string s;
    EingabeException(std::string ss) : s(ss) {}
    ~EingabeException() throw () {} // Updated
    const char* what() const throw() { return s.c_str(); }
};


struct SpielFeldException:public exception{
    std::string s;
    SpielFeldException(std::string ss) : s(ss) {}
    ~SpielFeldException() throw () {} // Updated
    const char* what() const throw() { return s.c_str(); }
};

struct ClientException:public exception{
    std::string s;
    ClientException(std::string ss) : s(ss) {}
    ~ClientException() throw () {} // Updated
    const char* what() const throw() { return s.c_str(); }
};

struct TcpServerException:public exception{
    std::string s;
    TcpServerException(std::string ss) : s(ss) {}
    ~TcpServerException() throw () {} // Updated
    const char* what() const throw() { return s.c_str(); }
};


struct MyException : public std::exception
{
   std::string s;
   MyException(std::string ss) : s(ss) {}
   ~MyException() throw () {} // Updated
   const char* what() const throw() { return s.c_str(); }
};
