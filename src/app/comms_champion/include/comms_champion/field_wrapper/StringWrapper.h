//
// Copyright 2015 (C). Alex Robenko. All rights reserved.
//

// This file is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.


#pragma once


#pragma once

#include <cstdint>
#include <cassert>
#include <memory>

#include <QtCore/QString>

#include "comms/comms.h"

#include "FieldWrapper.h"

namespace comms_champion
{

namespace field_wrapper
{

class StringWrapper : public FieldWrapper
{
public:
    typedef std::vector<std::uint8_t> SerializedType;

    virtual ~StringWrapper() {}

    QString value() const
    {
        return valueImpl();
    }

    void setValue(const QString& val)
    {
        setValueImpl(val);
    }

    SerializedType serialisedValue() const
    {
        return serialisedValueImpl();
    }

    int maxSize() const
    {
        return maxSizeImpl();
    }

protected:
    virtual QString valueImpl() const = 0;
    virtual void setValueImpl(const QString& val) = 0;
    virtual SerializedType serialisedValueImpl() const = 0;
    virtual int maxSizeImpl() const = 0;
};

template <typename TField>
class StaticStringWrapperT : public FieldWrapperT<StringWrapper, TField>
{
    using Base = FieldWrapperT<StringWrapper, TField>;
    using Field = TField;
    using SerializedType = typename Base::SerializedType;
    using UpdateTag = typename Base::UpdateTag;
    using Writable = typename Base::Writable;
    using ReadOnly = typename Base::ReadOnly;

public:
    StaticStringWrapperT(Field& field)
      : Base(field)
    {
    }

    StaticStringWrapperT(const StaticStringWrapperT&) = default;
    StaticStringWrapperT(StaticStringWrapperT&&) = default;
    virtual ~StaticStringWrapperT() = default;

    StaticStringWrapperT& operator=(const StaticStringWrapperT&) = delete;

protected:

    virtual QString valueImpl() const override
    {
        auto& strField = Base::field();
        return QString::fromUtf8(strField.getValue(), strField.size());
    }

    virtual void setValueImpl(const QString& val) override
    {
        setValueImplInternal(val, UpdateTag());
    }

    virtual SerializedType serialisedValueImpl() const override
    {
        auto& field = Base::field();
        SerializedType value;
        value.reserve(field.length());
        auto iter = std::back_inserter(value);
        field.write(iter, value.max_size());
        return value;
    }

    virtual int maxSizeImpl() const override
    {
        if (sizeof(int) <= Field::SizeLength) {
            return std::numeric_limits<int>::max();
        }

        return static_cast<int>((1U << Field::SizeLength) - 1);
    }

private:

    void setValueImplInternal(const QString& val, Writable)
    {
        Base::field().setValue(val.toStdString().c_str());
    }

    void setValueImplInternal(const QString& val, ReadOnly)
    {
        static_cast<void>(val);
        assert(!"Attempt to update readonly field");
    }
};

using StringWrapperPtr = std::unique_ptr<StringWrapper>;

template <typename TField>
StringWrapperPtr
makeStaticStringWrapper(TField& field)
{
    return
        StringWrapperPtr(
            new StaticStringWrapperT<TField>(field));
}

}  // namespace field_wrapper

}  // namespace comms_champion



