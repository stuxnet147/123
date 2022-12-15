__int64 __fastcall Srv2DecompressData(__int64 a1, __int64 a2, __int64 a3)
{
  __int64 v3; // rax
  __int64 v5; // r10
  __int64 v6; // rax
  __m128i v7; // xmm0
  unsigned int v8; // ebx
  PDEVICE_OBJECT v9; // rcx
  __int64 v10; // rdx
  int v11; // eax
  ULONG v12; // r9d
  __int64 Buffer; // rbx
  __int64 v14; // r11
  int v15; // r10d
  ULONG v16; // r10d
  __int64 v18; // rax
  __int64 v19; // rcx
  int v20; // eax
  int v21; // ecx
  int v22; // r15d
  __m128i ulAugend; // [rsp+30h] [rbp-10h]
  int v24; // [rsp+80h] [rbp+40h] BYREF
  ULONG pulResult; // [rsp+88h] [rbp+48h] BYREF

  v3 = *(_QWORD *)(a1 + 0x50);
  v24 = 0;
  pulResult = 0;
  v5 = *(_QWORD *)(v3 + 0x1F0);
  v6 = *(_QWORD *)(a1 + 0xF8);
  if ( *(_DWORD *)(v6 + 0x24) < 0x10u )
    return 0xC000090B;
  ulAugend = *(__m128i *)*(_QWORD *)(v6 + 0x18);
  v7 = _mm_srli_si128(ulAugend, 8);
  if ( (v7.m128i_i8[2] & 1) == 0 )
  {
    if ( (unsigned int)v7.m128i_u16[0] - 1 > 0x1E )
    {
      v8 = 0xC000090B;
      v9 = WPP_GLOBAL_Control;
      if ( WPP_GLOBAL_Control == (PDEVICE_OBJECT)&WPP_GLOBAL_Control
        || (HIDWORD(WPP_GLOBAL_Control->Timer) & 1) == 0
        || !BYTE1(WPP_GLOBAL_Control->Timer) )
      {
        return v8;
      }
      v10 = 0xAi64;
      goto LABEL_8;
    }
    v11 = *(_DWORD *)(v5 + 0x94);
    if ( !_bittest(&v11, (unsigned __int8)(v7.m128i_i8[0] - 1)) )
    {
      v8 = 0xC000090B;
      v9 = WPP_GLOBAL_Control;
      if ( WPP_GLOBAL_Control == (PDEVICE_OBJECT)&WPP_GLOBAL_Control
        || (HIDWORD(WPP_GLOBAL_Control->Timer) & 1) == 0
        || !BYTE1(WPP_GLOBAL_Control->Timer) )
      {
        return v8;
      }
      v10 = 0xBi64;
LABEL_8:
      WPP_SF_H(v9->AttachedDevice, v10, a3, v7.m128i_u16[0]);
      return v8;
    }
  }
  if ( (ulAugend.m128i_i8[10] & 1) != 0 )
  {
    v12 = ulAugend.m128i_u32[1];
  }
  else
  {
    if ( RtlULongAdd(ulAugend.m128i_u32[1], ulAugend.m128i_u32[3], &pulResult) < 0 )
    {
      v8 = 0xC000090B;
      if ( WPP_GLOBAL_Control != (PDEVICE_OBJECT)&WPP_GLOBAL_Control
        && (HIDWORD(WPP_GLOBAL_Control->Timer) & 1) != 0
        && BYTE1(WPP_GLOBAL_Control->Timer) )
      {
        WPP_SF_DD(
          WPP_GLOBAL_Control->AttachedDevice,
          12i64,
          &WPP_81284eed12f13d9c0c4dd945a4393ede_Traceguids,
          ulAugend.m128i_u32[1],
          ulAugend.m128i_i32[3]);
      }
      return v8;
    }
    v12 = pulResult;
  }
  if ( v12 > (unsigned __int64)(unsigned int)(*(_DWORD *)(v5 + 0x24) + 0x100) + 0x34 )
  {
    v8 = 0xC000090B;
    if ( WPP_GLOBAL_Control != (PDEVICE_OBJECT)&WPP_GLOBAL_Control
      && (HIDWORD(WPP_GLOBAL_Control->Timer) & 1) != 0
      && BYTE1(WPP_GLOBAL_Control->Timer) )
    {
      WPP_SF_d(WPP_GLOBAL_Control->AttachedDevice, 0xDi64, &WPP_81284eed12f13d9c0c4dd945a4393ede_Traceguids);
    }
    return v8;
  }
  Buffer = SrvNetAllocateBuffer(v12, 0i64);
  if ( !Buffer )
    return 0xC000009A;
  v14 = *(_QWORD *)(a1 + 0xF8);
  v15 = *(_DWORD *)(v14 + 0x24);
  if ( (ulAugend.m128i_i8[10] & 1) != 0 )
  {
    v16 = v15 - 8;
  }
  else
  {
    pulResult = v15 - 0x10;
    if ( RtlULongSub(v15 - 0x10, ulAugend.m128i_u32[3], &pulResult) < 0 )
    {
      if ( WPP_GLOBAL_Control != (PDEVICE_OBJECT)&WPP_GLOBAL_Control
        && (HIDWORD(WPP_GLOBAL_Control->Timer) & 1) != 0
        && BYTE1(WPP_GLOBAL_Control->Timer) )
      {
        WPP_SF_LLL((__int64)WPP_GLOBAL_Control->AttachedDevice);
      }
      goto LABEL_36;
    }
    v16 = pulResult;
  }
  v18 = *(_QWORD *)(Buffer + 0x18);
  v19 = *(_QWORD *)(v14 + 0x18);
  if ( (ulAugend.m128i_i8[10] & 1) != 0 )
  {
    v20 = SmbCompressionChainedDecompress(v19 + 8, v16, v18, ulAugend.m128i_u32[1], &v24);
    v21 = v24;
    v22 = v20;
  }
  else
  {
    v22 = SmbCompressionLegacyDecompress(
            v7.m128i_u16[0],
            v19 + ulAugend.m128i_u32[3] + 0x10i64,
            v16,
            v18 + ulAugend.m128i_u32[3],
            ulAugend.m128i_i32[1],
            &v24);
    if ( ulAugend.m128i_i32[3] )
      memmove(
        *(void **)(Buffer + 0x18),
        (const void *)(*(_QWORD *)(*(_QWORD *)(a1 + 0xF8) + 0x18i64) + 0x10i64),
        ulAugend.m128i_u32[3]);
    v21 = ulAugend.m128i_i32[3] + v24;
  }
  *(_DWORD *)(Buffer + 0x24) = v21;
  if ( v22 < 0 || v24 != ulAugend.m128i_i32[1] )
  {
LABEL_36:
    SrvNetFreeBuffer(Buffer);
    return 0xC000090B;
  }
  Srv2ReplaceReceiveBuffer(a1, Buffer);
  return 0i64;
}
