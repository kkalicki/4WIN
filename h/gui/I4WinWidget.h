#ifndef I4WINWIDGET_H
#define I4WINWIDGET_H

class I4WinWidget{
public:
    virtual void init()=0;
    virtual void preExecute()=0;
    virtual void postExecute()=0;
};

#endif // I4WINWIDGET_H