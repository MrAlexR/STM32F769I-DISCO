#include <gui/maineq_screen/MainEQView.hpp>

MainEQView::MainEQView()
{
	def_eq.vol = 1.0f;

	def_eq.lowG = 0.0f;
	def_eq.midG = 0.0f;
	def_eq.highG = 0.0f;

	def_eq.lowFC = 130.0f;
	def_eq.midFC = 2200.0f;
	def_eq.highFC = 7000.0f;

	def_eq.lowS = 1.0f;
	def_eq.midQ = 0.7f;
	def_eq.highS = 1.0f;

	eq_values = def_eq;

	functionReset();
}

void MainEQView::setupScreen()
{
    MainEQViewBase::setupScreen();
}

void MainEQView::tearDownScreen()
{
    MainEQViewBase::tearDownScreen();
}

void MainEQView::functionReset()
{
	// Volume
	vol.setValue(int(def_eq.vol * 100.0f));
	vol.invalidate();
	functionVolUpdate(int(def_eq.vol * 100.0f));

	//Lows
	lowG.setValue(int(def_eq.lowG));
	lowG.invalidate();
	lowFC.setValue(int(def_eq.lowFC));
	lowFC.invalidate();
	lowS.setValue(int(def_eq.lowS * 10.0f));
	lowS.invalidate();
	lowGupdate(int(def_eq.lowG));
	lowSupdate(int(def_eq.lowS * 10.0f));
	lowFCupdate(int(def_eq.lowFC));

	//mid
	midG.setValue(int(def_eq.midG));
	midG.invalidate();
	midFC.setValue(int(def_eq.midFC));
	midFC.invalidate();
	midQ.setValue(int(def_eq.midQ * 10.0f));
	midQ.invalidate();
	midGupdate(int(def_eq.midG));
	midQupdate(int(def_eq.midQ * 10.0f));
	midFCupdate(int(def_eq.midFC));

	//high
	highG.setValue(int(def_eq.highG));
	highG.invalidate();
	highFC.setValue(int(def_eq.highFC));
	highFC.invalidate();
	highS.setValue(int(def_eq.highS * 10.0f));
	highS.invalidate();
	highGupdate(int(def_eq.highG));
	highSupdate(int(def_eq.highS * 10.0f));
	highFCupdate(int(def_eq.highFC));

	eq_values = def_eq;
}

void MainEQView::functionApply()
{
	updateCoefs(eq_values);
	Avol.setVisible(false);
	Avol.invalidate();

	AlowG.setVisible(false);
	AlowG.invalidate();
	AmidG.setVisible(false);
	AmidG.invalidate();
	AhighG.setVisible(false);
	AhighG.invalidate();

	AlowFC.setVisible(false);
	AlowFC.invalidate();
	AmidFC.setVisible(false);
	AmidFC.invalidate();
	AhighFC.setVisible(false);
	AhighFC.invalidate();

	AlowS.setVisible(false);
	AlowS.invalidate();
	AmidQ.setVisible(false);
	AmidQ.invalidate();
	AhighS.setVisible(false);
	AhighS.invalidate();
}

void MainEQView::activateDSP()
{
	if (toggleButton1.getState())
	{
		resumeDSP();
	}
	else
	{
		pauseDSP();
	}
}

void MainEQView::functionVolUpdate(int value)
{
	eq_values.vol = float(value / 100.f);
	Unicode::snprintf(volValBuffer, VOLVAL_SIZE, "%d", value);
	volVal.invalidate();
	Avol.setVisible(true);
	Avol.invalidate();
}

void MainEQView::lowGupdate(int value)
{
	eq_values.lowG = float(value);
	Unicode::snprintf(lowGvalBuffer, LOWGVAL_SIZE, "%d", value);
	lowGval.invalidate();
	AlowG.setVisible(true);
	AlowG.invalidate();
}

void MainEQView::midGupdate(int value)
{
	eq_values.midG = float(value);
	Unicode::snprintf(midGvalBuffer, MIDGVAL_SIZE, "%d", value);
	midGval.invalidate();
	AmidG.setVisible(true);
	AmidG.invalidate();
}

void MainEQView::highGupdate(int value)
{
	eq_values.highG = float(value);
	Unicode::snprintf(highGvalBuffer, HIGHGVAL_SIZE, "%d", value);
	highGval.invalidate();
	AhighG.setVisible(true);
	AhighG.invalidate();
}

void  MainEQView::lowSupdate(int value)
{
	eq_values.lowS = float(value) / 10.0f;
	Unicode::snprintf(lowSvalBuffer, LOWSVAL_SIZE, "%d", value);
	lowSval.invalidate();
	AlowS.setVisible(true);
	AlowS.invalidate();
}

void  MainEQView::midQupdate(int value)
{
	eq_values.midQ = float(value) / 10.0f;
	Unicode::snprintf(midQvalBuffer, MIDQVAL_SIZE, "%d", value);
	midQval.invalidate();
	AmidQ.setVisible(true);
	AmidQ.invalidate();
}

void  MainEQView::highSupdate(int value)
{
	eq_values.highS = float(value) / 10.0f;
	Unicode::snprintf(highSvalBuffer, HIGHSVAL_SIZE, "%d", value);
	highSval.invalidate();
	AhighS.setVisible(true);
	AhighS.invalidate();
}

void  MainEQView::lowFCupdate(int value)
{
	eq_values.lowFC = float(value);
	Unicode::snprintf(lowFCvalBuffer, LOWFCVAL_SIZE, "%d", value);
	lowFCval.invalidate();
	AlowFC.setVisible(true);
	AlowFC.invalidate();
}

void  MainEQView::midFCupdate(int value)
{
	eq_values.midFC = float(value);
	Unicode::snprintf(midFCvalBuffer, MIDFCVAL_SIZE, "%d", value);
	midFCval.invalidate();
	AmidFC.setVisible(true);
	AmidFC.invalidate();
}

void  MainEQView::highFCupdate(int value)
{
	eq_values.highFC = float(value);
	Unicode::snprintf(highFCvalBuffer, HIGHFCVAL_SIZE, "%d", value);
	highFCval.invalidate();
	AhighFC.setVisible(true);
	AhighFC.invalidate();
}
