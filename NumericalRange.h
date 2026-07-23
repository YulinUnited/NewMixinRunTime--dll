#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#define New_Mixin_Char_BIT          8

#define New_Mixin_Schar_Min        (-128)
#define New_Mixin_Schar_Max          127

#define New_Mixin_Uchar_Max          0xff//255
#define New_Mixin_Uchar_Min          0x0000//0


#define New_Mixin_Shart_Min        (-32768)
#define New_Mixin_Shart_Max          32767

#define New_Mixin_Ushart_Max         0xffff//65535
#define New_Mixin_Ushart_Min         0x0000//0

#define New_Mixin_Int_Min          (-2147483647 - 1)
#define New_Mixin_Int_Max            2147483647

#define New_Mixin_UInt_Max           0xffffffff//4294967295U
#define New_Mixin_UInt_Min           0x0000//0

#define New_Mixin_Long_Max           2147483647L
#define New_Mixin_Long_Min         (-2147483647L - 1)

#define New_Mixin_ULong_Max          0xffffffffUL//4294967295UL
#define New_Mixin_ULong_Min          0x0000//0

#define New_Mixin_LongLong_Max       9223372036854775807i64
#define New_Mixin_LongLong_Min     (-9223372036854775807i64 - 1)

#define New_Mixin_ULongLong_Max      0xffffffffffffffffui64//18446744073709551615Ui64
#define New_Mixin_ULongLong_Min      0x0000//0


#define New_Mixin_Int_8_Min        (-127i8 - 1)
#define New_Mixin_Int_8_Max          127i8

#define New_Mixin_UInt_8_Max         0xffui8//255U
#define New_Mixin_UInt_8_Min         0x0000//0

#define New_Mixin_Int_16_Min       (-32767i16 - 1)
#define New_Mixin_Int_16_Max         32767i16

#define New_Mixin_UInt_16_Max        0xffffui16//65535U
#define New_Mixin_UInt_16_Min        0x0000//0

#define New_Mixin_Int_32_Min       (-2147483647i32 - 1)
#define New_Mixin_Int_32_Max         2147483647i32

#define New_Mixin_UInt_32_Max        0xffffffffui32//4294967295U
#define New_Mixin_UInt_32_Min        0x0000//0

#define New_Mixin_Int_64_Min       (-9223372036854775807i64 - 1)
#define New_Mixin_Int_64_Max         9223372036854775807i64

#define New_Mixin_UInt_64_Max        0xffffffffffffffffui64//18446744073709551615Ui64
#define New_Mixin_UInt_64_Min        0x0000//0

#define New_Mixin_Size_t_64_Max      0xffffffffffffffffui64//18446744073709551615Ui64
#define New_Mixin_Size_t_64_Min      0x0000//0

#define New_Mixin_Size_t_32_Max      0xffffffffui32//4294967295U
#define New_Mixin_Size_t_32_Min      0x0000//0

#ifdef __cplusplus
}
#endif