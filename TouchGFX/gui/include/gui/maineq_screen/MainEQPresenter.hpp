#ifndef MAINEQPRESENTER_HPP
#define MAINEQPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class MainEQView;

class MainEQPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    MainEQPresenter(MainEQView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~MainEQPresenter() {}

private:
    MainEQPresenter();

    MainEQView& view;
};

#endif // MAINEQPRESENTER_HPP
