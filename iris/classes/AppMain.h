#ifndef _APP_MAIN_H_
#define _APP_MAIN_H_

#include "Iris.h"

// TODO:
// - Transform component fix
//   - Adding children
//   - Matrices

class AppMain : public iris::Application
{
public:
    AppMain();
    virtual ~AppMain();

    virtual bool onApplicationInit() override;

    virtual void onApplicationStart() override;

    virtual void onApplicationQuit() override;

private:
protected:
};

#endif // _APP_MAIN_H_