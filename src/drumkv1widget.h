// drumkv1widget.h
//
/****************************************************************************
   Copyright (C) 2012-2015, rncbc aka Rui Nuno Capela. All rights reserved.

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2
   of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License along
   with this program; if not, write to the Free Software Foundation, Inc.,
   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*****************************************************************************/

#ifndef __drumkv1widget_h
#define __drumkv1widget_h

#include "ui_drumkv1widget.h"

#include "drumkv1_config.h"

#include "drumkv1.h"


// forward decls.
class drumkv1_sched_notifier;


//-------------------------------------------------------------------------
// drumkv1widget - decl.
//

class drumkv1widget : public QWidget
{
	Q_OBJECT

public:

	// Constructor
	drumkv1widget(QWidget *pParent = 0, Qt::WindowFlags wflags = 0);

	// Destructor.
	~drumkv1widget();

	// Param port accessors.
	void setParamValue(
		drumkv1::ParamIndex index, float fValue, bool bDefault = false);
	float paramValue(drumkv1::ParamIndex index) const;

	// Param kbob (widget) mapper.
	void setParamKnob(drumkv1::ParamIndex index, drumkv1widget_knob *pKnob);
	drumkv1widget_knob *paramKnob(drumkv1::ParamIndex index) const;

	// Preset init.
	void initPreset();
	// Preset clear.
	void clearPreset();

	// Dirty close prompt.
	bool queryClose();

	// Current selected note helpers.
	int currentNote() const;
	QString currentNoteName() const;

	// MIDI note/octave name helpers.
	static QString noteName(int note);
	static QString completeNoteName(int note);

public slots:

	// Preset file I/O.
	void loadPreset(const QString& sFilename);
	void savePreset(const QString& sFilename);

protected slots:

	// Preset renewal.
	void newPreset();

	// Param knob (widget) slots.
	void paramChanged(float fValue);

	// Sample clear slot.
	void clearSample();

	// Sample openner.
	void openSample();

	// Sample loader.
	void loadSample(const QString& sFilename);

	// All element clear.
	void clearElements();

	// Element activation.
	void activateElement(bool bOpenSample = false);

	// Element sample loader.
	void doubleClickElement();

	// Element deactivation.
	void resetElement(void);

	// Common context menu.
	void contextMenuRequest(const QPoint& pos);

	// Reset param knobs to default value.
	void resetParams();

	// Swap params A/B.
	void swapParams(bool bOn);

	// Delay BPM change.
	void bpmSyncChanged();

	// Notification updater.
	void updateNotify();

	// Menu actions.
	void helpConfigure();

	void helpAbout();
	void helpAboutQt();

protected:

	// Synth engine accessor.
	virtual drumkv1 *instance() const = 0;

	// Reload all elements.
	void refreshElements();

	// Reset swap params A/B group.
	void resetSwapParams();

	// Initialize param values.
	void updateParamValues(uint32_t nparams);

	// Reset all param/knob default values.
	void resetParamValues(uint32_t nparams);
	void resetParamKnobs(uint32_t nparams);

	// (En|Dis)able/ all param/knobs.
	void activateParamKnobs(bool bEnabled);
	void activateParamKnobsGroupBox(QGroupBox *pGroupBox, bool bEnable);

	// Sample file clearance.
	void clearSampleFile();

	// Sample loader slot.
	void loadSampleFile(const QString& sFilename);

	// Sample updater.
	void updateSample(drumkv1_sample *pSample, bool bDirty = false);

	// Param port method.
	virtual void updateParam(drumkv1::ParamIndex index, float fValue) const = 0;

	// Update local tied widgets.
	void updateParamEx(drumkv1::ParamIndex index, float fValue);

	// Dirty flag (overridable virtual) methods.
	virtual void updateDirtyPreset(bool bDirtyPreset);

private:

	// Instance variables.
	Ui::drumkv1widget m_ui;

	drumkv1_sched_notifier *m_sched_notifier;

	QHash<drumkv1::ParamIndex, drumkv1widget_knob *> m_paramKnobs;
	QHash<drumkv1widget_knob *, drumkv1::ParamIndex> m_knobParams;

	float m_params_ab[drumkv1::NUM_PARAMS];

	int m_iUpdate;
};


#endif	// __drumkv1widget_h

// end of drumkv1widget.h
