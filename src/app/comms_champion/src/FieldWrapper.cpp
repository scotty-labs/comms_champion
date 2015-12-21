//
// Copyright 2015 (C). Alex Robenko. All rights reserved.
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


#include "comms_champion/field_wrapper/FieldWrapper.h"

#include <cassert>

namespace comms_champion
{

namespace field_wrapper
{


QString FieldWrapper::getSerialisedString() const
{
    auto seq = getSerialisedValue();
    QString str;
    for (auto& byte : seq) {
        str.append(QString("%1").arg((unsigned)byte, 2, 16, QChar('0')));
    }
    return str;
}

bool FieldWrapper::setSerialisedString(const QString& str)
{
    assert((str.size() & 0x1) == 0U);
    SerialisedSeq seq;
    seq.reserve(str.size() / 2);
    QString byteStr;
    for (auto ch : str) {
        byteStr.append(ch);
        if (byteStr.size() < 2) {
            continue;
        }

        bool ok = false;
        auto val = byteStr.toUInt(&ok, 16);
        if (ok) {
            seq.push_back(static_cast<SerialisedSeq::value_type>(val));
        }
        byteStr.clear();
    }

    return setSerialisedValue(seq);
}

}  // namespace field_wrapper

}  // namespace comms_champion

