//
// Copyright 2014 (C). Alex Robenko. All rights reserved.
//

// This file is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.


#pragma once

#include <functional>
#include <vector>

#include "comms/CompileControl.h"

CC_DISABLE_WARNINGS()
#include <QtCore/QVariantMap>

#include "ui_ArrayListElementWidget.h"
#include "ui_ArrayListFieldWidget.h"
CC_ENABLE_WARNINGS()

#include "comms_champion/FieldWidget.h"
#include "comms_champion/field_wrapper/ArrayListWrapper.h"

namespace comms_champion
{

class ArrayListElementWidget : public QWidget
{
    Q_OBJECT
    typedef QWidget Base;
public:

    ArrayListElementWidget(
        FieldWidget* fieldWidget,
        QWidget* parentObj = nullptr);

    void refresh();
    void setEditEnabled(bool enabled);
    void setDeletable(bool deletable);
    void updateProperties(const QVariantMap& props);

signals:
    void sigFieldUpdated();
    void sigRemoveRequested();

private:

    void updateUi();
    Ui::ArrayListElementWidget m_ui;
    FieldWidget* m_fieldWidget = nullptr;
    bool m_editEnabled = true;
    bool m_deletable = true;
};

class ArrayListFieldWidget : public FieldWidget
{
    Q_OBJECT
    typedef FieldWidget Base;
public:
    using WrapperPtr = field_wrapper::ArrayListWrapperPtr;
    typedef std::function<std::vector<FieldWidgetPtr> (std::size_t)> CreateMissingDataFieldsFunc;

    explicit ArrayListFieldWidget(
        WrapperPtr wrapper,
        CreateMissingDataFieldsFunc&& updateFunc,
        QWidget* parentObj = nullptr);

    ~ArrayListFieldWidget();

    template <typename TFunc>
    void setCreateMissingDataFieldsCallback(TFunc&& func)
    {
        m_createMissingDataFieldsCallback = std::forward<TFunc>(func);
        addMissingFields();
    }

protected:
    virtual void refreshImpl() override;
    virtual void editEnabledUpdatedImpl() override;
    virtual void updatePropertiesImpl(const QVariantMap& props) override;

private slots:
    void dataFieldUpdated();
    void addNewField();
    void removeField();

private:

    void addDataField(FieldWidget* dataFieldWidget);
    void refreshInternal();
    void updateUi();
    void addMissingFields();
    void updateElementsProperties(const QVariantMap& props);
    void updateElementsProperties(const QVariantList& propsList);

    Ui::ArrayListFieldWidget m_ui;
    WrapperPtr m_wrapper;
    std::vector<ArrayListElementWidget*> m_elements;
    CreateMissingDataFieldsFunc m_createMissingDataFieldsCallback;
    std::vector<QVariantMap> m_elemProperties;
};

}  // namespace comms_champion

