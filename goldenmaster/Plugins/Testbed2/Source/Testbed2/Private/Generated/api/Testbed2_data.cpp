/**
Copyright 2021 ApiGear UG
Copyright 2021 Epic Games, Inc.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include "Testbed2_data.h"
/**
 * Enumeration ETestbed2Enum1
 */
bool toUE4Type(ETestbed2Enum1& value, uint8 v)
{
	bool bSuccessful = false;
	switch (v)
	{
	case 1:
		value = ETestbed2Enum1::TE_VALUE1;
		bSuccessful = true;
		break;
	case 2:
		value = ETestbed2Enum1::TE_VALUE2;
		bSuccessful = true;
		break;
	case 3:
		value = ETestbed2Enum1::TE_VALUE3;
		bSuccessful = true;
		break;
	case 4:
		value = ETestbed2Enum1::TE_VALUE4;
		bSuccessful = true;
		break;
	default:
		value = ETestbed2Enum1::TE_VALUE1;
	}
	return bSuccessful;
}
/**
 * Enumeration ETestbed2Enum2
 */
bool toUE4Type(ETestbed2Enum2& value, uint8 v)
{
	bool bSuccessful = false;
	switch (v)
	{
	case 1:
		value = ETestbed2Enum2::TE_VALUE1;
		bSuccessful = true;
		break;
	case 2:
		value = ETestbed2Enum2::TE_VALUE2;
		bSuccessful = true;
		break;
	case 3:
		value = ETestbed2Enum2::TE_VALUE3;
		bSuccessful = true;
		break;
	case 4:
		value = ETestbed2Enum2::TE_VALUE4;
		bSuccessful = true;
		break;
	default:
		value = ETestbed2Enum2::TE_VALUE1;
	}
	return bSuccessful;
}
/**
 * Enumeration ETestbed2Enum3
 */
bool toUE4Type(ETestbed2Enum3& value, uint8 v)
{
	bool bSuccessful = false;
	switch (v)
	{
	case 1:
		value = ETestbed2Enum3::TE_VALUE1;
		bSuccessful = true;
		break;
	case 2:
		value = ETestbed2Enum3::TE_VALUE2;
		bSuccessful = true;
		break;
	case 3:
		value = ETestbed2Enum3::TE_VALUE3;
		bSuccessful = true;
		break;
	case 4:
		value = ETestbed2Enum3::TE_VALUE4;
		bSuccessful = true;
		break;
	default:
		value = ETestbed2Enum3::TE_VALUE1;
	}
	return bSuccessful;
}
bool FTestbed2Struct1::operator==(const FTestbed2Struct1& rhs) const
{
	return (field1 == rhs.field1);
}

bool FTestbed2Struct1::operator!=(const FTestbed2Struct1& rhs) const
{
	return !operator==(rhs);
}
bool FTestbed2Struct2::operator==(const FTestbed2Struct2& rhs) const
{
	return (field1 == rhs.field1) && (field2 == rhs.field2);
}

bool FTestbed2Struct2::operator!=(const FTestbed2Struct2& rhs) const
{
	return !operator==(rhs);
}
bool FTestbed2Struct3::operator==(const FTestbed2Struct3& rhs) const
{
	return (field1 == rhs.field1) && (field2 == rhs.field2) && (field3 == rhs.field3);
}

bool FTestbed2Struct3::operator!=(const FTestbed2Struct3& rhs) const
{
	return !operator==(rhs);
}
bool FTestbed2Struct4::operator==(const FTestbed2Struct4& rhs) const
{
	return (field1 == rhs.field1) && (field2 == rhs.field2) && (field3 == rhs.field3) && (field4 == rhs.field4);
}

bool FTestbed2Struct4::operator!=(const FTestbed2Struct4& rhs) const
{
	return !operator==(rhs);
}
bool FTestbed2NestedStruct1::operator==(const FTestbed2NestedStruct1& rhs) const
{
	return (field1 == rhs.field1);
}

bool FTestbed2NestedStruct1::operator!=(const FTestbed2NestedStruct1& rhs) const
{
	return !operator==(rhs);
}
bool FTestbed2NestedStruct2::operator==(const FTestbed2NestedStruct2& rhs) const
{
	return (field1 == rhs.field1) && (field2 == rhs.field2);
}

bool FTestbed2NestedStruct2::operator!=(const FTestbed2NestedStruct2& rhs) const
{
	return !operator==(rhs);
}
bool FTestbed2NestedStruct3::operator==(const FTestbed2NestedStruct3& rhs) const
{
	return (field1 == rhs.field1) && (field2 == rhs.field2) && (field3 == rhs.field3);
}

bool FTestbed2NestedStruct3::operator!=(const FTestbed2NestedStruct3& rhs) const
{
	return !operator==(rhs);
}

/* Returns true if Testbed2Struct1 A is equal to Testbed2Struct1 B (A == B) */
bool UTestbed2Library::EqualEqual_Testbed2Struct1Testbed2Struct1(FTestbed2Struct1 A, FTestbed2Struct1 B)
{
	return A == B;
}

/* Returns true if Testbed2Struct1 A is not equal to Testbed2Struct1 B (A != B) */
bool UTestbed2Library::NotEqual_Testbed2Struct1Testbed2Struct1(FTestbed2Struct1 A, FTestbed2Struct1 B)
{
	return A != B;
}

/* Returns true if Testbed2Struct2 A is equal to Testbed2Struct2 B (A == B) */
bool UTestbed2Library::EqualEqual_Testbed2Struct2Testbed2Struct2(FTestbed2Struct2 A, FTestbed2Struct2 B)
{
	return A == B;
}

/* Returns true if Testbed2Struct2 A is not equal to Testbed2Struct2 B (A != B) */
bool UTestbed2Library::NotEqual_Testbed2Struct2Testbed2Struct2(FTestbed2Struct2 A, FTestbed2Struct2 B)
{
	return A != B;
}

/* Returns true if Testbed2Struct3 A is equal to Testbed2Struct3 B (A == B) */
bool UTestbed2Library::EqualEqual_Testbed2Struct3Testbed2Struct3(FTestbed2Struct3 A, FTestbed2Struct3 B)
{
	return A == B;
}

/* Returns true if Testbed2Struct3 A is not equal to Testbed2Struct3 B (A != B) */
bool UTestbed2Library::NotEqual_Testbed2Struct3Testbed2Struct3(FTestbed2Struct3 A, FTestbed2Struct3 B)
{
	return A != B;
}

/* Returns true if Testbed2Struct4 A is equal to Testbed2Struct4 B (A == B) */
bool UTestbed2Library::EqualEqual_Testbed2Struct4Testbed2Struct4(FTestbed2Struct4 A, FTestbed2Struct4 B)
{
	return A == B;
}

/* Returns true if Testbed2Struct4 A is not equal to Testbed2Struct4 B (A != B) */
bool UTestbed2Library::NotEqual_Testbed2Struct4Testbed2Struct4(FTestbed2Struct4 A, FTestbed2Struct4 B)
{
	return A != B;
}

/* Returns true if Testbed2NestedStruct1 A is equal to Testbed2NestedStruct1 B (A == B) */
bool UTestbed2Library::EqualEqual_Testbed2NestedStruct1Testbed2NestedStruct1(FTestbed2NestedStruct1 A, FTestbed2NestedStruct1 B)
{
	return A == B;
}

/* Returns true if Testbed2NestedStruct1 A is not equal to Testbed2NestedStruct1 B (A != B) */
bool UTestbed2Library::NotEqual_Testbed2NestedStruct1Testbed2NestedStruct1(FTestbed2NestedStruct1 A, FTestbed2NestedStruct1 B)
{
	return A != B;
}

/* Returns true if Testbed2NestedStruct2 A is equal to Testbed2NestedStruct2 B (A == B) */
bool UTestbed2Library::EqualEqual_Testbed2NestedStruct2Testbed2NestedStruct2(FTestbed2NestedStruct2 A, FTestbed2NestedStruct2 B)
{
	return A == B;
}

/* Returns true if Testbed2NestedStruct2 A is not equal to Testbed2NestedStruct2 B (A != B) */
bool UTestbed2Library::NotEqual_Testbed2NestedStruct2Testbed2NestedStruct2(FTestbed2NestedStruct2 A, FTestbed2NestedStruct2 B)
{
	return A != B;
}

/* Returns true if Testbed2NestedStruct3 A is equal to Testbed2NestedStruct3 B (A == B) */
bool UTestbed2Library::EqualEqual_Testbed2NestedStruct3Testbed2NestedStruct3(FTestbed2NestedStruct3 A, FTestbed2NestedStruct3 B)
{
	return A == B;
}

/* Returns true if Testbed2NestedStruct3 A is not equal to Testbed2NestedStruct3 B (A != B) */
bool UTestbed2Library::NotEqual_Testbed2NestedStruct3Testbed2NestedStruct3(FTestbed2NestedStruct3 A, FTestbed2NestedStruct3 B)
{
	return A != B;
}
