#ifndef MAINEQVIEW_HPP
#define MAINEQVIEW_HPP

#include <gui_generated/maineq_screen/MainEQViewBase.hpp>
#include <gui/maineq_screen/MainEQPresenter.hpp>
extern "C" {
#include "DSPInterface.h"
}

class MainEQView : public MainEQViewBase
{
public:

	EQ_PARAMS eq_values;
	EQ_PARAMS def_eq;

    MainEQView();
    virtual ~MainEQView() {}

    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void functionReset();
    virtual void functionApply();
    virtual void functionVolUpdate(int value);
    virtual void activateDSP();

    virtual void lowGupdate(int value);
    virtual void midGupdate(int value);
    virtual void highGupdate(int value);

    virtual void lowSupdate(int value);
    virtual void midQupdate(int value);
    virtual void highSupdate(int value);

    virtual void lowFCupdate(int value);
    virtual void midFCupdate(int value);
    virtual void highFCupdate(int value);
protected:
};

#endif // MAINEQVIEW_HPP
