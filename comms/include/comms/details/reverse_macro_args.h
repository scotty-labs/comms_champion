//
// Copyright 2018 (C). Alex Robenko. All rights reserved.
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

#include "macro_common.h"


//#define COMMS_DO_REVERSE_MACRO_ARGS_0()
#define COMMS_DO_REVERSE_MACRO_ARGS_1(n_) n_
#define COMMS_DO_REVERSE_MACRO_ARGS_2(n_, ...) COMMS_DO_REVERSE_MACRO_ARGS_1(__VA_ARGS__) , n_
#define COMMS_DO_REVERSE_MACRO_ARGS_3(n_, ...) COMMS_DO_REVERSE_MACRO_ARGS_2(__VA_ARGS__) , n_
#define COMMS_DO_REVERSE_MACRO_ARGS_4(n_, ...) COMMS_DO_REVERSE_MACRO_ARGS_3(__VA_ARGS__) , n_
#define COMMS_DO_REVERSE_MACRO_ARGS_5(n_, ...) COMMS_DO_REVERSE_MACRO_ARGS_4(__VA_ARGS__) , n_
#define COMMS_DO_REVERSE_MACRO_ARGS_6(n_, ...) COMMS_DO_REVERSE_MACRO_ARGS_5(__VA_ARGS__) , n_
#define COMMS_DO_REVERSE_MACRO_ARGS_7(n_, ...) COMMS_DO_REVERSE_MACRO_ARGS_6(__VA_ARGS__) , n_
#define COMMS_DO_REVERSE_MACRO_ARGS_8(n_, ...) COMMS_DO_REVERSE_MACRO_ARGS_7(__VA_ARGS__) , n_
#define COMMS_DO_REVERSE_MACRO_ARGS_9(n_, ...) COMMS_DO_REVERSE_MACRO_ARGS_8(__VA_ARGS__) , n_
#define COMMS_DO_REVERSE_MACRO_ARGS_10(n_, ...) COMMS_DO_REVERSE_MACRO_ARGS_9(__VA_ARGS__) , n_
#define COMMS_DO_REVERSE_MACRO_ARGS_11(n_, ...) COMMS_DO_REVERSE_MACRO_ARGS_10(__VA_ARGS__) , n_
#define COMMS_DO_REVERSE_MACRO_ARGS_12(n_, ...) COMMS_DO_REVERSE_MACRO_ARGS_11(__VA_ARGS__) , n_
#define COMMS_DO_REVERSE_MACRO_ARGS_13(n_, ...) COMMS_DO_REVERSE_MACRO_ARGS_12(__VA_ARGS__) , n_
#define COMMS_DO_REVERSE_MACRO_ARGS_14(n_, ...) COMMS_DO_REVERSE_MACRO_ARGS_13(__VA_ARGS__) , n_
#define COMMS_DO_REVERSE_MACRO_ARGS_15(n_, ...) COMMS_DO_REVERSE_MACRO_ARGS_14(__VA_ARGS__) , n_
#define COMMS_DO_REVERSE_MACRO_ARGS_16(n_, ...) COMMS_DO_REVERSE_MACRO_ARGS_15(__VA_ARGS__) , n_
#define COMMS_DO_REVERSE_MACRO_ARGS_17(n_, ...) COMMS_DO_REVERSE_MACRO_ARGS_16(__VA_ARGS__) , n_
#define COMMS_DO_REVERSE_MACRO_ARGS_18(n_, ...) COMMS_DO_REVERSE_MACRO_ARGS_17(__VA_ARGS__) , n_
#define COMMS_DO_REVERSE_MACRO_ARGS_19(n_, ...) COMMS_DO_REVERSE_MACRO_ARGS_18(__VA_ARGS__) , n_
#define COMMS_DO_REVERSE_MACRO_ARGS_20(n_, ...) COMMS_DO_REVERSE_MACRO_ARGS_19(__VA_ARGS__) , n_
#define COMMS_DO_REVERSE_MACRO_ARGS_21(n_, ...) COMMS_DO_REVERSE_MACRO_ARGS_20(__VA_ARGS__) , n_
#define COMMS_DO_REVERSE_MACRO_ARGS_22(n_, ...) COMMS_DO_REVERSE_MACRO_ARGS_21(__VA_ARGS__) , n_
#define COMMS_DO_REVERSE_MACRO_ARGS_23(n_, ...) COMMS_DO_REVERSE_MACRO_ARGS_22(__VA_ARGS__) , n_
#define COMMS_DO_REVERSE_MACRO_ARGS_24(n_, ...) COMMS_DO_REVERSE_MACRO_ARGS_23(__VA_ARGS__) , n_
#define COMMS_DO_REVERSE_MACRO_ARGS_25(n_, ...) COMMS_DO_REVERSE_MACRO_ARGS_24(__VA_ARGS__) , n_
#define COMMS_DO_REVERSE_MACRO_ARGS_26(n_, ...) COMMS_DO_REVERSE_MACRO_ARGS_25(__VA_ARGS__) , n_
#define COMMS_DO_REVERSE_MACRO_ARGS_27(n_, ...) COMMS_DO_REVERSE_MACRO_ARGS_26(__VA_ARGS__) , n_
#define COMMS_DO_REVERSE_MACRO_ARGS_28(n_, ...) COMMS_DO_REVERSE_MACRO_ARGS_27(__VA_ARGS__) , n_
#define COMMS_DO_REVERSE_MACRO_ARGS_29(n_, ...) COMMS_DO_REVERSE_MACRO_ARGS_28(__VA_ARGS__) , n_
#define COMMS_DO_REVERSE_MACRO_ARGS_30(n_, ...) COMMS_DO_REVERSE_MACRO_ARGS_29(__VA_ARGS__) , n_
#define COMMS_DO_REVERSE_MACRO_ARGS_31(n_, ...) COMMS_DO_REVERSE_MACRO_ARGS_30(__VA_ARGS__) , n_
#define COMMS_DO_REVERSE_MACRO_ARGS_32(n_, ...) COMMS_DO_REVERSE_MACRO_ARGS_31(__VA_ARGS__) , n_

#define COMMS_REVERSE_MACRO_ARGS_INTERNAL_(N, ...) COMMS_EXPAND(COMMS_DO_REVERSE_MACRO_ARGS_ ## N(__VA_ARGS__))
#define COMMS_REVERSE_MACRO_ARGS_INTERNAL(N, ...) COMMS_EXPAND(COMMS_REVERSE_MACRO_ARGS_INTERNAL_(N, __VA_ARGS__))
#define COMMS_REVERSE_MACRO_ARGS(...) \
    COMMS_EXPAND(COMMS_REVERSE_MACRO_ARGS_INTERNAL(COMMS_NUM_ARGS(__VA_ARGS__), __VA_ARGS__))













